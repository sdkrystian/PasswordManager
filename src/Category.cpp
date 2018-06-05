#include "Category.h"
#include "Menu.h"
#include <iostream>

Category::Category(unsigned x, unsigned y, Color textcolor, Color backgroundcolor, Color selectedtextcolor, Color selectedbackgroundcolor, Color activatedtextcolor, Color activatedtbackgroundcolor, const std::string& text, const std::string& selectedtext, const std::string& activatedtext, std::vector<int> elements, bool opened, bool show) : Element(-1, x, y, textcolor, backgroundcolor, selectedtextcolor, selectedbackgroundcolor, activatedtextcolor, activatedtbackgroundcolor, text, selectedtext, activatedtext, [&] () { ShowList(); }, [&] () { HideList(); }), opened_(opened), elements_(elements)
{
  if (show)
    Show(true);
  for (int e : elements_)
  {
    Menu::Elements()[e].Move(X() + Menu::Elements()[e].X(), Y() + Menu::Elements()[e].Y());
    Menu::Elements()[e].Show(opened);
  }
}

std::vector<int>& Category::Elements()
{
  return elements_;
}

void Category::ShowList()
{
  if (opened_)
    return;
  opened_ = true;
  for (Category& c : Menu::Categories())
  {
    if (c.Y() > Menu::Categories()[Menu::CategoryIndex()].Y())
      c.Move(c.X(), c.Y() + elements_.size());
  }
  for (int e : elements_)
    Menu::Elements()[e].Show(true);

}

void Category::HideList()
{ 
  if (!opened_)
    return;
  opened_ = false;
  for (int e : elements_)
    Menu::Elements()[e].Show(false);
  for (Category& c : Menu::Categories())
  {
    if (c.Y() > Menu::Categories()[Menu::CategoryIndex()].Y())
      c.Move(c.X(), c.Y() - elements_.size());
  }
}

bool Category::Opened()
{
  return opened_;
}

void Category::Move(int x, int y)
{
  bool show = show_;
  bool opened = opened_;
  if (opened)
    HideList();
  if (show)
    Show(false);
  int xdist = x - x_;
  int ydist = y - y_;
  for (int e : elements_)
    Menu::Elements()[e].Move(Menu::Elements()[e].X() + xdist, Menu::Elements()[e].Y() + ydist);
  x_ = x;
  y_ = y;
  if (show)
    Show(true);
  if (opened)
    ShowList();
}