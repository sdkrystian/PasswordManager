#include "Console.h"
#include "Button.h"
#include "Input.h"
#include "Menu.h"
#include <iostream>

int main()
{
  Console::ShowConsoleCursor(false);
  Menu::Buttons().emplace_back(2, 1, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, "Button", "Button", "Button", [] () {}, [] () {}, true);
  Menu::Buttons().emplace_back(2, 2, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, "Button", "Button", "Button", [] () {}, [] () {}, true);
  Menu::Buttons().emplace_back(2, 3, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, "Button", "Button", "Button", [] () {}, [] () {}, true);
  Menu::Buttons().emplace_back(2, 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, "Button", "Button", "Button", [] () {}, [] () {}, true);
  Menu::Buttons().emplace_back(2, 5, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, "Button", "Button", "Button", [] () {}, [] () {}, true);
  Menu::Buttons().emplace_back(2, 6, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, "Button", "Button", "Button", [] () {}, [] () {}, true);
  Menu::Buttons().emplace_back(2, 7, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, "Button", "Button", "Button", [] () {}, [] () {}, true);
  Menu::Buttons().emplace_back(2, 8, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, "Button", "Button", "Button", [] () {}, [] () {}, true);
  Menu::Buttons().emplace_back(2, 9, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, "Button", "Button", "Button", [] () {}, [] () {}, true);
  Menu::Buttons().emplace_back(2, 10, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, "Button", "Button", "Button", [] () {}, [] () {}, true);
  Menu::Buttons().emplace_back(2, 11, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, "Button", "Button", "Button", [] () {}, [] () {}, true);
  Menu::Buttons().emplace_back(2, 12, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, "Button", "Button", "Button", [] () {}, [] () {}, true);
  Menu::Buttons()[0].Select(true);
  while (true)
  {
    if (Input::GetKeyDown(VK_DOWN))
    {
      Menu::NextDown();
    }
    if (Input::GetKeyDown(VK_UP))
    {
      Menu::NextUp();
    }
    if (Input::GetKeyDown(VK_RETURN))
    {
      Menu::Press();
    }
  }
  return 0;
}