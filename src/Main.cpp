#include "Console.h"
#include "Button.h"
#include "Input.h"
#include "Menu.h"
#include <iostream>
#include <thread>
#include "UserInfo.h"
#include <algorithm>
#include "Popup.h"

void ShowConfiguration();
void ShowMain();

int main()
{ 
  Console::Resize(300, 300);
  Console::ShowConsoleCursor(false);
  Console::SetTitle("password manager");
  ShowMain();
  while (true)
  {
    if (Menu::Enabled())
    {
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
        Menu::CloseCallback();
      }
    }
  }
  return 0;
}

void NewCategoryCallback(std::string name)
{
  Menu::Enabled() = true;
  Console::ShowConsoleCursor(false);
  if (std::any_of(UserInfo::Categories().begin(), UserInfo::Categories().end(), [&] (Category& x) { return x.name == name; }))
  {
    Popup(1000, 8, 20, 3, "Already Exists", Color::WHITE, Color::LIGHT_RED);
    ShowConfiguration();
  }
  else
  {
    UserInfo::Categories().push_back({ name, std::vector<Entry>() });
    Popup(1000, 8, 20, 3, "Category Added", Color::WHITE, Color::LIGHT_GREEN);
    ShowConfiguration();
  }
}

void NewCategory()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ new category ]", Color::LIGHT_AQUA);
  Console::WriteLine("");
  Console::WriteLine("");
  Console::WriteLine("");
  Console::WriteLineCentered("Category Name", Color::LIGHT_GREEN);
  Console::ColorLineCentered(Color::LIGHT_GREEN, 16);
  Console::SetColor(Color::LIGHT_PURPLE, Color::LIGHT_GREEN);
  Menu::Enabled() = false;
  Console::ShowConsoleCursor(true);
  Menu::SetInputCallback(NewCategoryCallback, (Console::GetSize().X - 16) / 2, Console::GetCursorPosition().Y);
}

void EditCategory()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ edit category ]", Color::LIGHT_AQUA);
  Menu::Buttons()[0].Select(true);
}

void DeleteCategoryCallback(std::string name)
{
  Menu::Enabled() = true;
  Console::ShowConsoleCursor(false);
  auto res = std::find_if(UserInfo::Categories().begin(), UserInfo::Categories().end(), [&] (Category& x) { return x.name == name; });
  if (res == UserInfo::Categories().end())
  {
    Popup(1000, 8, 20, 3, "Category Not Found", Color::WHITE, Color::LIGHT_RED);
    ShowConfiguration();
  }
  else
  {
    UserInfo::Categories().erase(res);
    Popup(1000, 8, 20, 3, "Category Deleted", Color::WHITE, Color::LIGHT_GREEN);
    ShowConfiguration();
  }
}

void DeleteCategory()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ delete category ]", Color::LIGHT_RED);
  Console::WriteLine("");
  Console::WriteLine("");
  Console::WriteLine("");
  Console::WriteLineCentered("Category Name", Color::LIGHT_RED);
  Console::ColorLineCentered(Color::LIGHT_RED, 16);
  Console::SetColor(Color::BRIGHT_WHITE, Color::LIGHT_RED);
  Menu::Enabled() = false;
  Console::ShowConsoleCursor(true);
  Menu::SetInputCallback(DeleteCategoryCallback, (Console::GetSize().X - 16) / 2, Console::GetCursorPosition().Y);
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
      Button(0, 5, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_GREEN, Color::LIGHT_PURPLE, "New Entry", "New Entry", "New Entry", [] () {}, [] () {}, true),
      Button(0, 6, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_YELLOW, Color::LIGHT_PURPLE, "Edit Entry", "Edit Entry", "Edit Entry", [] () {}, [] () {}, true),
      Button(0, 7, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_RED, Color::LIGHT_PURPLE, "Delete Entry", "Delete Entry", "Delete Entry", [] () {}, [] () {}, true),
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
      Button(0, 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Categories", "Categories", "Categories", [] () {}, [] () {}, true),
      Button(0, 5, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Configuration", "Configuration", "Configuration", ShowConfiguration, [] () {}, true),
      Button(0, 6, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "License", "License", "License", [] () {}, [] () {}, true),
      Button(0, 7, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Exit", "Exit", "Exit", [] () { exit(0); }, [] () {}, true)
  });
  Menu::Buttons()[0].Select(true);
}
