#include "Category.h"

Category::Category(unsigned x, unsigned y, Color textcolor, Color backgroundcolor, Color selectedtextcolor, Color selectedbackgroundcolor, Color activatedtextcolor, Color activatedtbackgroundcolor, std::string text, std::string selectedtext, std::string activatedtext, std::vector<Button> buttons, bool opened) : Button(x, y, textcolor, backgroundcolor, selectedtextcolor, selectedbackgroundcolor, activatedtextcolor, activatedtbackgroundcolor, text, selectedtext, activatedtext, [&] () { ShowList(); }, [&] () { HideList(); }), opened_(opened), buttons_(buttons)
{
  for (const Button& b : buttons_)
  {
    b.Move(X() + b.X(), Y() + b.Y());
    b.Show(opened);
  }
  Show(true);
}

std::vector<Button> Category::Buttons()
{
  return buttons_;
}

void Category::ShowList()
{
  opened_ = true;
  for (const Button& b : buttons_)
  {
    b.Show(true);
  }
}

void Category::HideList()
{
  opened_ = false;
  for (const Button& b : buttons_)
  {
    b.Show(false);
  }
}