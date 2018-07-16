// Copyright 2018 Krystian Stasiowski

#include "Console.h"
#include "Button.h"
#include "Input.h"
#include "Menu.h"
#include <iostream>
#include "UserInfo.h"
#include <algorithm>
#include "Popup.h"
#include <limits>

#ifdef max
#undef max
#endif

void ShowConfiguration();
void ShowMain();
void ViewCategories();
void DeleteEntry();

std::string GetRegValue(HKEY root, const std::string& key, const std::string& name)
{
  HKEY hkey;
  if (RegOpenKeyEx(root, key.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &hkey) != ERROR_SUCCESS)
  {
    return "";
  }
  DWORD type;
  DWORD data;
  if (RegQueryValueEx(hkey, name.c_str(), NULL, &type, NULL, &data) != ERROR_SUCCESS)
  {
    RegCloseKey(hkey);
    return "";
  }
  if (type != REG_SZ)
  {
    RegCloseKey(hkey);
    return "";
  }
  std::string value(data / sizeof(char), '\0');
  if (RegQueryValueEx(hkey, name.c_str(), NULL, NULL, reinterpret_cast<LPBYTE>(&value[0]), &data) != ERROR_SUCCESS)
  {
    RegCloseKey(hkey);
    return "";
  }
  RegCloseKey(hkey);
  size_t first = value.find_first_of('\0');
  if (first != std::string::npos)
  {
    value.resize(first);
  }
  return value;
}

void SetRegValue(HKEY root, const std::string& key, const std::string& name, const std::string& data)
{
  HKEY hkey;
  LONG result = RegOpenKeyEx(root, key.c_str(), 0, KEY_ALL_ACCESS, &hkey);
  if (result != ERROR_SUCCESS && result != ERROR_FILE_NOT_FOUND)
  {
    return;
  }
  if (result == ERROR_FILE_NOT_FOUND)
  {
    RegCreateKeyEx(root, key.c_str(), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, NULL);
  }
  RegSetValueEx(hkey, name.c_str(), NULL, REG_SZ, (LPCBYTE)data.c_str(), data.length() * sizeof(wchar_t));
  RegCloseKey(hkey);
}

int main()
{
  Console::Resize(450, 300);
  const std::string regvalue = GetRegValue(HKEY_CURRENT_USER, "Software\\PasswordManager", "Config");
  if (regvalue.empty())
  {
    const std::string& currentpath = std::experimental::filesystem::v1::current_path().string();
    SetRegValue(HKEY_CURRENT_USER, "Software\\PasswordManager", "Config", currentpath);
    UserInfo::Configuration = currentpath;
  }
  else
  {
    UserInfo::Configuration = regvalue;
  }
  HWND window = GetConsoleWindow();
  SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
  Console::ShowConsoleCursor(false);
  if (std::experimental::filesystem::v1::exists(UserInfo::Configuration + "\\information.xml"))
    UserInfo::ReadFromFile();
  Console::SetTitle("password manager");
  ShowMain();
  while (true)
  {
    if (Menu::Enabled())
    {
      FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
      if (Input::GetKeyDown(VK_DOWN))
        Menu::NextDown();
      if (Input::GetKeyDown(VK_UP))
        Menu::NextUp();
      if (Input::GetKeyDown(VK_RETURN))
        Menu::Press();
    }
    else
    {
      Console::SetCursorPosition(Menu::InputX(), Menu::InputY());
      std::string input = Console::ReadLine();
      if (!input.empty())
      {
        Menu::ExecuteInputCallback(input);
        std::cin.clear();
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
      }
    }
  }
  return 0;
}

void NewCategory()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ new category ]", Color::LIGHT_AQUA);
  Console::WriteLine("");
  Console::WriteLineCentered("Category Name", Color::LIGHT_GREEN);
  Console::ColorLineCentered(Color::LIGHT_GREEN, 32);
  Console::SetColor(Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
  Menu::Enabled() = false;
  Console::ShowConsoleCursor(true);
  Menu::SetInputCallback([] (const std::string& name) 
  {
    Menu::Enabled() = true;
    Console::ShowConsoleCursor(false);
    if (std::any_of(UserInfo::Categories().begin(), UserInfo::Categories().end(), [&] (Category& x) { return x.name == name; }))
    {
      Popup(1000, 6, 20, 3, "Already Exists", Color::WHITE, Color::LIGHT_RED);
      ShowConfiguration();
    }
    else
    {
      UserInfo::Categories().push_back({ name, std::vector<Entry>() });
      UserInfo::Save();
      Popup(1000, 6, 20, 3, "Category Added", Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
      ShowConfiguration();
    }
  }, (Console::GetSize().X - 32) / 2, 4);
}

void EntrySelection(const Category& category)
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ " + category.name + " ]", Color::LIGHT_AQUA);
  Console::WriteLine("");
  Console::WriteLineCentered("Select Entry", Color::LIGHT_GREEN);
  int j = 0;
  for (const Entry& e : category.entries)
  {
    Menu::Buttons().emplace_back(0, (j++) + 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, e.name, e.name, e.name, [&] () 
    {
      int spacing = 10;
      Menu::Clear();
      Console::WriteLine("");
      Console::WriteLine("");
      Console::WriteLineCentered("[ " + e.name + " ]", Color::LIGHT_AQUA);
      Console::WriteLine("");
      if (!e.username.empty())
      {
        Console::WriteLineCentered("Username: " + e.username);
      }
      else
      {
        --spacing;
      }
      if (!e.email.empty())
      {
        Console::WriteLineCentered("Email: " + e.email);
      }
      else
      {
        --spacing;
      }
      Console::WriteLineCentered("Password: " + e.password);
      Console::WriteLineCentered("URL: " + e.url);
      Console::WriteLineCentered("Note: " + e.note);
      Menu::Buttons().emplace_back(0, spacing, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Back", "Back", "Back", [&] () {EntrySelection(category); }, [] () {}, true);
      Menu::Buttons()[0].Select();
    }, [] () {}, true);
  }
  Menu::Buttons().emplace_back(0, j + 5, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Back", "Back", "Back", ViewCategories, [] () {}, true);
  Menu::Buttons()[0].Select();
}

void ViewCategories()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ categories ]", Color::LIGHT_AQUA);
  Console::WriteLine("");
  Console::WriteLineCentered("Select Category", Color::LIGHT_GREEN);
  int i = 0;
  for (Category& c : UserInfo::Categories())
  {
    Menu::Buttons().emplace_back(0, (i++) + 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, c.name, c.name, c.name, [&] () { EntrySelection(c); }, [] () {}, true);
  }
  Menu::Buttons().emplace_back(0, i + 5, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Back", "Back", "Back", ShowMain, [] () {}, true);
  Menu::Buttons()[0].Select();
}

void DeleteCategory()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ delete category ]", Color::LIGHT_RED);
  Console::WriteLine("");
  Console::WriteLineCentered("Select Category", Color::LIGHT_GREEN);
  int i = 0;
  for (Category& c : UserInfo::Categories())
  {
    Menu::Buttons().emplace_back(0, (i++) + 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, c.name, c.name, c.name, [&] ()
    { 
      UserInfo::Categories().erase(std::find_if(UserInfo::Categories().begin(), UserInfo::Categories().end(), [&] (Category& x) { return x.name == c.name; }));
      Popup(1000, 6, 20, 3, "Category Deleted", Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
      UserInfo::Save();
      DeleteCategory();
    }, [] () {}, true);
  }
  Menu::Buttons().emplace_back(0, i + 5, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Back", "Back", "Back", ShowConfiguration, [] () {}, true);
  Menu::Buttons()[0].Select();
}

void CreateEntry(Category& category)
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ new entry ]", Color::LIGHT_AQUA);
  Console::WriteLine("");
  Console::WriteLineCentered("Entry Name", Color::LIGHT_GREEN);
  Console::ColorLineCentered(Color::LIGHT_GREEN, 32);
  Console::SetColor(Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
  Menu::Enabled() = false;
  Console::ShowConsoleCursor(true);
  Menu::SetInputCallback([&] (const std::string& name) 
  {
    Menu::Enabled() = true;
    Console::ShowConsoleCursor(false);
    if (std::any_of(category.entries.begin(), category.entries.end(), [&] (Entry& x) { return x.name == name; }))
    {
      Popup(1000, 6, 20, 3, "Already Exists", Color::WHITE, Color::LIGHT_RED);
      ShowConfiguration();
    }
    else
    {
      category.entries.emplace_back();
      Entry& entry = category.entries.back();
      entry.name = name;
      Menu::Clear();
      Console::WriteLine("");
      Console::WriteLineCentered("[ new entry ]", Color::LIGHT_AQUA);
      Console::WriteLine("");
      Console::WriteLineCentered("Username (N for none)", Color::LIGHT_GREEN);
      Console::ColorLineCentered(Color::LIGHT_GREEN, 32);
      Console::SetColor(Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
      Menu::Enabled() = false;
      Console::ShowConsoleCursor(true);
      Menu::SetInputCallback([&] (const std::string& username) 
      {
        Menu::Enabled() = true;
        Console::ShowConsoleCursor(false);
        entry.username = (username == "N") || (username == "n") ? "" : username;
        Menu::Clear();
        Console::WriteLine("");
        Console::WriteLineCentered("[ new entry ]", Color::LIGHT_AQUA);
        Console::WriteLine("");
        Console::WriteLineCentered("Email (N for none)", Color::LIGHT_GREEN);
        Console::ColorLineCentered(Color::LIGHT_GREEN, 32);
        Console::SetColor(Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
        Menu::Enabled() = false;
        Console::ShowConsoleCursor(true);
        Menu::SetInputCallback([&] (const std::string& email) 
        {
          Menu::Enabled() = true;
          Console::ShowConsoleCursor(false);
          entry.email = (email == "N") || (email == "n") ? "" : email;
          Menu::Clear();
          Console::WriteLine("");
          Console::WriteLineCentered("[ new entry ]", Color::LIGHT_AQUA);
          Console::WriteLine("");
          Console::WriteLineCentered("Password", Color::LIGHT_GREEN);
          Console::ColorLineCentered(Color::LIGHT_GREEN, 32);
          Console::SetColor(Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
          Menu::Enabled() = false;
          Console::ShowConsoleCursor(true);
          Menu::SetInputCallback([&] (const std::string& password)
          {
            Menu::Enabled() = true;
            Console::ShowConsoleCursor(false);
            entry.password = password;
            Menu::Clear();
            Console::WriteLine("");
            Console::WriteLineCentered("[ new entry ]", Color::LIGHT_AQUA);
            Console::WriteLine("");
            Console::WriteLineCentered("URL", Color::LIGHT_GREEN);
            Console::ColorLineCentered(Color::LIGHT_GREEN, 32);
            Console::SetColor(Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
            Menu::Enabled() = false;
            Console::ShowConsoleCursor(true);
            Menu::SetInputCallback([&] (const std::string& url)
            {
              Menu::Enabled() = true;
              Console::ShowConsoleCursor(false);
              entry.url = url;
              Menu::Clear();
              Console::WriteLine("");
              Console::WriteLineCentered("[ new entry ]", Color::LIGHT_AQUA);
              Console::WriteLine("");
              Console::WriteLineCentered("Note (N for none)", Color::LIGHT_GREEN);
              Console::ColorLineCentered(Color::LIGHT_GREEN, 32);
              Console::SetColor(Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
              Menu::Enabled() = false;
              Console::ShowConsoleCursor(true);
              Menu::SetInputCallback([&] (const std::string& note) 
              {
                Menu::Enabled() = true;
                Console::ShowConsoleCursor(false);
                entry.note = (note == "N") || (note == "n") ? "" : note;
                Popup(1000, 6, 20, 3, "Entry Added", Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
                UserInfo::Save();
                ShowConfiguration();
              }, (Console::GetSize().X - 32) / 2, 4);
            }, (Console::GetSize().X - 32) / 2, 4);
          }, (Console::GetSize().X - 32) / 2, 4);
        }, (Console::GetSize().X - 32) / 2, 4);
      }, (Console::GetSize().X - 32) / 2, 4);
    }
  }, (Console::GetSize().X - 32) / 2, 4);
}

void RemoveEntry(Category& category)
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ " + category.name + " ]", Color::LIGHT_AQUA);
  Console::WriteLine("");
  Console::WriteLineCentered("Select Entry", Color::LIGHT_GREEN);
  int j = 0;
  for (Entry& e : category.entries)
  {
    Menu::Buttons().emplace_back(0, (j++) + 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, e.name, e.name, e.name, [&] () 
    {
      category.entries.erase(std::find_if(category.entries.begin(), category.entries.end(), [&] (Entry& x) { return x.name == e.name; }));
      Popup(1000, 6, 20, 3, "Entry Deleted", Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
      UserInfo::Save();
      RemoveEntry(category);
    }, [] () {}, true);
  }
  Menu::Buttons().emplace_back(0, j + 5, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Back", "Back", "Back", DeleteEntry, [] () {}, true);
  Menu::Buttons()[0].Select();
}

void DeleteEntry()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ delete entry ]", Color::LIGHT_RED);
  Console::WriteLine("");
  Console::WriteLineCentered("Select Category", Color::LIGHT_GREEN);
  int i = 0;
  for (Category& c : UserInfo::Categories())
  {
    Menu::Buttons().emplace_back(0, (i++) + 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, c.name, c.name, c.name, [&] () { RemoveEntry(c); }, [] () {}, true);
  }
  Menu::Buttons().emplace_back(0, i + 5, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Back", "Back", "Back", ShowConfiguration, [] () {}, true);
  Menu::Buttons()[0].Select();
}

void NewEntry()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ new entry ]", Color::LIGHT_AQUA);
  Console::WriteLine("");
  Console::WriteLineCentered("Select Category", Color::LIGHT_GREEN);
  int i = 0;
  for (Category& c : UserInfo::Categories())
  {
    Menu::Buttons().emplace_back(0, (i++) + 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, c.name, c.name, c.name, [&] () { CreateEntry(c); }, [] () {}, true);
  }
  Menu::Buttons().emplace_back(0, i + 5, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Back", "Back", "Back", ShowConfiguration, [] () {}, true);
  Menu::Buttons()[0].Select();
}

void ChangeConfig()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ change config file ]", Color::LIGHT_AQUA);
  Console::WriteLine("");
  Console::WriteLineCentered("New Config Path", Color::LIGHT_GREEN);
  Console::ColorLineCentered(Color::LIGHT_GREEN, 52);
  Console::SetColor(Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
  Menu::Enabled() = false;
  Console::ShowConsoleCursor(true);
  Menu::SetInputCallback([] (const std::string& path) 
  {
    Menu::Enabled() = true;
    Console::ShowConsoleCursor(false);
    if (!std::experimental::filesystem::v1::exists(path))
    {
      Popup(1000, 6, 20, 3, "Not Found", Color::WHITE, Color::LIGHT_RED);
      ShowConfiguration();
    }
    else
    {
      Popup(1000, 6, 20, 3, "Config Changed", Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
      SetRegValue(HKEY_CURRENT_USER, "Software\\PasswordManager", "Config", path);
      UserInfo::MoveConfig(path);
      ShowConfiguration();
    }
  }, (Console::GetSize().X - 52) / 2, 4);
}

void ShowConfiguration()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ config ]", Color::LIGHT_AQUA);
  Menu::AddButtons(std::vector<Button>
  {
      Button(0, 3, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_GREEN, Color::LIGHT_PURPLE, "New Category", "New Category", "New Category", NewCategory, [] () {}, true),
      Button(0, 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_RED, Color::LIGHT_PURPLE, "Delete Category", "Delete Category", "Delete Category", DeleteCategory, [] () {}, true),
      Button(0, 5, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_GREEN, Color::LIGHT_PURPLE, "New Entry", "New Entry", "New Entry", NewEntry, [] () {}, true),
      Button(0, 6, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_RED, Color::LIGHT_PURPLE, "Delete Entry", "Delete Entry", "Delete Entry", DeleteEntry, [] () {}, true),
      Button(0, 7, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_YELLOW, Color::LIGHT_PURPLE, "Config File", "Config File", "Config File", ChangeConfig, [] () {}, true),
      Button(0, 8, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Back", "Back", "Back", ShowMain, [] () {}, true)
  });
  Menu::Buttons()[0].Select(true);
}

void ShowMain()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ password manager ]", Color::LIGHT_AQUA);
  Console::WriteLineCentered("program and api by: cry", Color::LIGHT_AQUA);
  Menu::AddButtons(std::vector<Button>
  {
      Button(0, 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Categories", "Categories", "Categories", ViewCategories, [] () {}, true),
      Button(0, 5, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Configuration", "Configuration", "Configuration", ShowConfiguration, [] () {}, true),
      Button(0, 6, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Exit", "Exit", "Exit", [] () { exit(0); }, [] () {}, true)
  });
  Menu::Buttons()[0].Select(true);
}