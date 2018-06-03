#include "Console.h"
#include "Button.h"
#include "Input.h"
#include "Category.h"
#include <iostream>

int main()
{
  Console::SetColor(Color::PURPLE, Color::AQUA);
  Console::ShowConsoleCursor(false);
  Category c = Category(1, 1, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::WHITE, "Category", "Category", "Category", 
    {
      Button(2, 1, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::WHITE, "Button", "Button", "Button", [] () {}, [] () {}, false),
      Button(2, 2, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::WHITE, "Button", "Button", "Button", [] () {}, [] () {}, false),
      Button(2, 3, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::WHITE, "Button", "Button", "Button", [] () {}, [] () {}, false),
      Button(2, 4, Color::WHITE, Color::BLACK, Color::BLACK, Color::WHITE, Color::LIGHT_GREEN, Color::WHITE, "Button", "Button", "Button", [] () {}, [] () {}, false),
    });
  while (true)
  {
    if (Input::GetKeyDown(VK_SPACE))
    {
      c.Select();
    }
    if (Input::GetKeyDown(VK_RETURN))
    {
      c.Press();
    }
  }
  return 0;
}