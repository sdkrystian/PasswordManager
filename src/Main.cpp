#include "Console.h"
#include "Element.h"
#include "Input.h"
#include "Category.h"
#include "Menu.h"
#include <iostream>

int main()
{
  Console::ShowConsoleCursor(false);
  Menu::Elements().emplace_back(0, 2, 1, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Button", "Button", "Button", [] () {}, [] () {}, false);
  Menu::Elements().emplace_back(0, 2, 2, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Button", "Button", "Button", [] () {}, [] () {}, false);
  Menu::Elements().emplace_back(0, 2, 3, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Button", "Button", "Button", [] () {}, [] () {}, false);
  Menu::Elements().emplace_back(0, 2, 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Button", "Button", "Button", [] () {}, [] () {}, false);
  Menu::Elements().emplace_back(1, 2, 1, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Button", "Button", "Button", [] () {}, [] () {}, false);
  Menu::Elements().emplace_back(1, 2, 2, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Button", "Button", "Button", [] () {}, [] () {}, false);
  Menu::Elements().emplace_back(1, 2, 3, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Button", "Button", "Button", [] () {}, [] () {}, false);
  Menu::Elements().emplace_back(1, 2, 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Button", "Button", "Button", [] () {}, [] () {}, false);
  Menu::Elements().emplace_back(2, 2, 1, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Button", "Button", "Button", [] () {}, [] () {}, false);
  Menu::Elements().emplace_back(2, 2, 2, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Button", "Button", "Button", [] () {}, [] () {}, false);
  Menu::Elements().emplace_back(2, 2, 3, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Button", "Button", "Button", [] () {}, [] () {}, false);
  Menu::Elements().emplace_back(2, 2, 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Button", "Button", "Button", [] () {}, [] () {}, false);
  Category c1(2, 2, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Category", "Category", "Category", std::vector<int> { 0, 1, 2, 3 });
  Category c2(2, 3, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Category", "Category", "Category", std::vector<int> { 4, 5, 6, 7 });
  Category c3(2, 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::BLACK, "Category", "Category", "Category", std::vector<int> { 8, 9, 10, 11 });
  Menu::Categories().push_back(c1);
  Menu::Categories().push_back(c2);
  Menu::Categories().push_back(c3);
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