#include "Console.h"
#include "Button.h"
#include "Input.h"
#include "Menu.h"
#include <iostream>
#include <thread>

void ShowConfiguration();
void ShowMain();

int main()
{ 
  //Console::Resize(300, 300);
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
  }
  return 0;
}

void NewCategory()
{
  Menu::Enabled() = false;
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ new category ]", Color::LIGHT_AQUA);
  Console::WriteLine("");
  Console::WriteLine("");
  Console::WriteLine("");
  Console::WriteLineCentered("Category Name", Color::LIGHT_GREEN);
  Console::ColorLineCentered(Color::LIGHT_GREEN, 16);
  Console::SetCursorPosition((Console::GetSize().X - 16) / 2, Console::GetCursorPosition().Y);
  Console::ShowConsoleCursor(true);
  //Console::ReadLine(Color::WHITE, Color::LIGHT_GREEN);
  Menu::Enabled() = true;
  //Menu::Buttons()[0].Select(true);
}

void EditCategory()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ edit category ]", Color::LIGHT_AQUA);
  Menu::Buttons()[0].Select(true);
}

void DeleteCategory()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ delete category ]", Color::LIGHT_AQUA);
  Menu::Buttons()[0].Select(true);
}

void ShowConfiguration()
{
  Menu::Clear();
  Console::WriteLine("");
  Console::WriteLineCentered("[ config ]", Color::LIGHT_AQUA);
  Menu::AddButtons(std::vector<Button>
  {
      Button(0, 3, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_GREEN, Color::LIGHT_PURPLE, "New Category", "New Category", "New Category", NewCategory, [] () {}, true),
      Button(0, 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_YELLOW, Color::LIGHT_PURPLE, "Edit Category", "Edit Category", "Edit Category", [] () {}, [] () {}, true),
      Button(0, 5, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_RED, Color::LIGHT_PURPLE, "Delete Category", "Delete Category", "Delete Category", [] () {}, [] () {}, true),
      Button(0, 6, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_GREEN, Color::LIGHT_PURPLE, "New Entry", "New Entry", "New Entry", [] () {}, [] () {}, true),
      Button(0, 7, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_YELLOW, Color::LIGHT_PURPLE, "Edit Entry", "Edit Entry", "Edit Entry", [] () {}, [] () {}, true),
      Button(0, 8, Color::WHITE, Color::BLACK, Color::BLACK, Color::LIGHT_RED, Color::LIGHT_PURPLE, "Delete Entry", "Delete Entry", "Delete Entry", [] () {}, [] () {}, true),
      Button(0, 9, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_PURPLE, "Back", "Back", "Back", ShowMain, [] () {}, true)
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
