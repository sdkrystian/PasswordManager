#include "Menu.h"
#include <algorithm>
#include <iostream>
#include "Element.h"
#include <functional>

std::vector<Element> Menu::elements_ = { };
std::vector<Category> Menu::categories_ = {};
unsigned Menu::xindex_ = 0;
unsigned Menu::yindex_ = 0;
int Menu::selectedcat_ = 0;
int Menu::selectedelem_ = -1;

std::vector<Category>& Menu::Categories()
{
  return categories_;
}

std::vector<Element>& Menu::Elements()
{
  return elements_;
}

int Menu::CategoryIndex()
{
  return selectedcat_;
}

void Menu::NextUp()
{
  if (selectedcat_ - 1 >= 0)
  {
    categories_[selectedcat_].Select(false);
    categories_[--selectedcat_].Select(true);
  }
}

void Menu::NextDown()
{
  if (selectedcat_ + 1 < categories_.size())
  {
    categories_[selectedcat_].Select(false);
    categories_[++selectedcat_].Select(true);
  }
}

void Menu::Press()
{
  if (selectedelem_ == -1)
  {
    categories_[selectedcat_].Press();
  }
  else
  {
    elements_[selectedelem_].Press();
  }
  Redraw();
}

void Menu::Redraw()
{
  for (Category& c : categories_)
  {
    if (!c.Hidden())
    {
      c.Show(false);
      c.Show(true);
    }
  }
  for (Element& e : elements_)
  {
    if (!e.Hidden())
    {
      e.Show(false);
      e.Show(true);
    }
  }
}