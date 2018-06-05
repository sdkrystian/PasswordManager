#include "Menu.h"
#include <algorithm>
#include <iostream>
#include "Button.h"
#include <functional>

std::vector<Button> Menu::Buttons_ = { };
int Menu::selectedelem_ = 0;

std::vector<Button>& Menu::Buttons()
{
  return Buttons_;
}

void Menu::NextUp()
{
  if (selectedelem_ - 1 >= 0)
  {
    Buttons_[selectedelem_].Select(false);
    Buttons_[--selectedelem_].Select(true);
  }
}

void Menu::NextDown()
{
  if (selectedelem_ + 1 < Buttons_.size())
  {
    Buttons_[selectedelem_].Select(false);
    Buttons_[++selectedelem_].Select(true);
  }
}

void Menu::Press()
{
  Buttons_[selectedelem_].Press();
  //Redraw();
}

void Menu::Redraw()
{
  for (Button& e : Buttons_)
  {
    if (!e.Hidden())
    {
      e.Show(false);
      e.Show(true);
    }
  }
}