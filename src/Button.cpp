#include "Button.h"

Button::Button(int x, int y, Color textcolor, Color backgroundcolor, Color selectedtextcolor, Color selectedbackgroundcolor, Color activatedtextcolor, Color activatedtbackgroundcolor, std::string text, std::string selectedtext, std::string activatedtext, std::function<void()> activateaction, std::function<void()> deactivateaction, bool show, bool selected, bool activated) : Object(x, y), textcolor_(textcolor), backgroundcolor_(backgroundcolor), selectedtextcolor_(selectedtextcolor), selectedbackgroundcolor_(selectedbackgroundcolor), activatedbackgroundcolor_(activatedtbackgroundcolor), activatedtextcolor_(activatedtextcolor), text_(text), selectedtext_(selectedtext), activatedtext_(activatedtext), activateaction_(activateaction), deactivateaction_(deactivateaction), show_(show), selected_(selected), activated_(activated)
{
  if (show)
    Show(true);
}

void Button::Select() const
{
  Select(!selected_);
}

void Button::Select(bool select) const
{
  if (!select)
  {
    selected_ = false;
    if (activated_)
    {
      Console::ClearAt(x_, y_, activatedtext_.length());
      Console::WriteLineAt(x_, y_, activatedtext_, activatedtextcolor_, activatedbackgroundcolor_);
    }
    else
    {
      Console::ClearAt(x_, y_, selectedtext_.length());
      Console::WriteLineAt(x_, y_, text_, textcolor_, backgroundcolor_);
    }
  }
  else
  {
    selected_ = true;
    if (activated_)
    {
      return;
    }
    else
    {
      Console::ClearAt(x_, y_, text_.length());
      Console::WriteLineAt(x_, y_, selectedtext_, selectedtextcolor_, selectedbackgroundcolor_);
    }
  }
}

void Button::Press() const
{
  Press(!activated_);
}

void Button::Press(bool press) const
{
  if (!press)
  {
    activated_ = false;
    if (selected_)
    {
      Console::ClearAt(x_, y_, activatedtext_.length());
      Console::WriteLineAt(x_, y_, selectedtext_, selectedtextcolor_, selectedbackgroundcolor_);
    }
    else
    {
      Console::ClearAt(x_, y_, activatedtext_.length());
      Console::WriteLineAt(x_, y_, text_, textcolor_, backgroundcolor_);
    }
    deactivateaction_();
  }
  else
  {
    activated_ = true;
    if (selected_)
    {
      Console::ClearAt(x_, y_, selectedtext_.length());
      Console::WriteLineAt(x_, y_, activatedtext_, activatedtextcolor_, activatedbackgroundcolor_);
    }
    else
    {
      Console::ClearAt(x_, y_, text_.length());
      Console::WriteLineAt(x_, y_, activatedtext_, activatedtextcolor_, activatedbackgroundcolor_);
    }
    activateaction_();
  }
}

void Button::Show(bool show) const
{
  if (show)
  {
    if (activated_)
    {
      Console::WriteLineAt(x_, y_, activatedtext_, activatedtextcolor_, activatedbackgroundcolor_);
    }
    else if (selected_)
    {
      Console::WriteLineAt(x_, y_, selectedtext_, selectedtextcolor_, selectedbackgroundcolor_);
    }
    else
    {
      Console::WriteLineAt(x_, y_, text_, textcolor_, backgroundcolor_);
    }
  }
  else
  {
    if (activated_)
    {
      Console::ClearAt(x_, y_, activatedtext_.length());
    }
    else if (selected_)
    {
      Console::ClearAt(x_, y_, selectedtext_.length());
    }
    else
    {
      Console::ClearAt(x_, y_, text_.length());
    }
  }
}


bool Button::Selectable() const
{
  return true;
}

bool Button::Activated() const
{
  return activated_;
}

bool Button::Selected() const
{
  return selected_;
}

void Button::Move(int x, int y) const
{
  Show(false);
  x_ = x;
  y_ = y;
  if (show_)
    Show(true);
}

int Button::X() const
{
  return x_;
}

int Button::Y() const
{
  return y_;
}