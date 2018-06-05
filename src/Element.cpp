#include "Element.h"

Element::Element(int parentindex, int x, int y, Color textcolor, Color backgroundcolor, Color selectedtextcolor, Color selectedbackgroundcolor, Color activatedtextcolor, Color activatedtbackgroundcolor, const std::string& text, const std::string& selectedtext, const std::string& activatedtext, const std::function<void()>& activateaction, const std::function<void()>& deactivateaction, bool show, bool activated) :
  Object(x, y, show), textcolor_(textcolor), backgroundcolor_(backgroundcolor), selectedtextcolor_(selectedtextcolor), selectedbackgroundcolor_(selectedbackgroundcolor), activatedbackgroundcolor_(activatedtbackgroundcolor), activatedtextcolor_(activatedtextcolor), text_(text), selectedtext_(selectedtext), activatedtext_(activatedtext), activateaction_(activateaction), deactivateaction_(deactivateaction), activated_(activated), parentindex_(parentindex), selected_(false)
{
  type_ = ObjectType::BUTTON;
  if (show)
    Show(true);
}

Element::Element(int parentindex, int x, int y, Color textcolor, Color backgroundcolor, Color selectedtextcolor, Color selectedbackgroundcolor, const std::string& text, const std::string& selectedtext, bool show) :
  Object(x, y, show), textcolor_(textcolor), backgroundcolor_(backgroundcolor), selectedtextcolor_(selectedtextcolor), selectedbackgroundcolor_(selectedbackgroundcolor), text_(text), selectedtext_(selectedtext), parentindex_(parentindex), selected_(false)
{
  type_ = ObjectType::TEXT;
}

void Element::Select()
{
  Select(!selected_);
}

void Element::Select(bool select)
{
  selected_ = select;
  if (!select)
  {
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

void Element::Press()
{
  if (type_ == ObjectType::BUTTON)
    Press(!activated_);
}

bool Element::Hidden() const
{
  return !show_;
}

void Element::Press(bool press)
{
  if (type_ != ObjectType::BUTTON)
    return;
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

void Element::Show(bool show)
{
  show_ = show;
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

bool Element::Activated() const
{
  return activated_;
}

bool Element::Selected() const
{
  return selected_;
}

void Element::Move(int x, int y)
{
  bool show = show_;
  if (show)
    Show(false);
  x_ = x;
  y_ = y;
  if (show)
    Show(true);
}