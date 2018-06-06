#include "Button.h"

Button::Button(int x, int y, Color textcolor, Color backgroundcolor, Color selectedtextcolor, Color selectedbackgroundcolor, Color activatedtextcolor, const std::string& text, const std::string& selectedtext, const std::string& activatedtext, const std::function<void()>& activateaction, const std::function<void()>& deactivateaction, bool centered, bool show, bool activated) :
  Object(x, y, show), textcolor_(textcolor), backgroundcolor_(backgroundcolor), selectedtextcolor_(selectedtextcolor), selectedbackgroundcolor_(selectedbackgroundcolor), activatedtextcolor_(activatedtextcolor), text_(text), selectedtext_(selectedtext), activatedtext_(activatedtext), activateaction_(activateaction), deactivateaction_(deactivateaction), activated_(activated), selected_(false)
{
  if (centered)
    x_ = (Console::GetSize().X - text.length()) / 2;
  if (show)
    Show(true);
}

void Button::Select()
{
  Select(!selected_);
}

void Button::Select(bool select)
{
  selected_ = select;
  if (!select)
  {
    if (activated_)
    {
      Console::ClearAt(x_, y_, activatedtext_.length());
      Console::WriteLineAt(x_, y_, activatedtext_, activatedtextcolor_, backgroundcolor_);
    }
    else
    {
      Console::ClearAt(x_, y_, selectedtext_.length());
      Console::WriteLineAt(x_, y_, text_, textcolor_, backgroundcolor_);
    }
  }
  else
  {
    if (activated_)
    {
      Console::ClearAt(x_, y_, selectedtext_.length());
      Console::WriteLineAt(x_, y_, activatedtext_, activatedtextcolor_, selectedbackgroundcolor_);
    }
    else
    {
      Console::ClearAt(x_, y_, text_.length());
      Console::WriteLineAt(x_, y_, selectedtext_, selectedtextcolor_, selectedbackgroundcolor_);
    }
  }
}

void Button::Press()
{
  Press(!activated_);
}

bool Button::Hidden() const
{
  return !show_;
}

void Button::Press(bool press)
{
  activated_ = press;
  if (!press)
  {
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
    if (selected_)
    {
      Console::ClearAt(x_, y_, selectedtext_.length());
      Console::WriteLineAt(x_, y_, activatedtext_, activatedtextcolor_, selectedbackgroundcolor_);
    }
    else
    {
      Console::ClearAt(x_, y_, text_.length());
      Console::WriteLineAt(x_, y_, activatedtext_, activatedtextcolor_, selectedbackgroundcolor_);
    }
    activateaction_();
  }
}

void Button::Show(bool show)
{
  show_ = show;
  if (show)
  {
    if (activated_)
    {
      Console::WriteLineAt(x_, y_, activatedtext_, activatedtextcolor_, backgroundcolor_);
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

bool Button::Activated() const
{
  return activated_;
}

bool Button::Selected() const
{
  return selected_;
}

void Button::Move(int x, int y)
{
  bool show = show_;
  if (show)
    Show(false);
  x_ = x;
  y_ = y;
  if (show)
    Show(true);
}