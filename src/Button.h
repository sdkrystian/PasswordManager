#pragma once
#include "Console.h"
#include "Object.h"
#include <functional>

class Button : public Object
{
public:
  Button(int x, int y, Color textcolor, Color backgroundcolor, Color selectedtextcolor, Color selectedbackgroundcolor, Color activatedtextcolor, Color activatedtbackgroundcolor, std::string text, std::string selectedtext, std::string activatedtext, std::function<void()> activateaction, std::function<void()> deactivateaction, bool show = true, bool selected = false, bool activated = false);
  void Select() const;
  void Press() const;
  void Select(bool select) const;
  void Press(bool press) const;
  bool Activated() const;
  bool Selected() const;
  void Show(bool show) const override;
  bool Selectable() const override;
  int X() const;
  int Y() const;
  void Move(int x, int y) const;
private:
  mutable bool activated_;
  mutable bool selected_;
  mutable bool show_;
  Color textcolor_;
  Color backgroundcolor_;
  Color selectedtextcolor_;
  Color selectedbackgroundcolor_;
  Color activatedtextcolor_;
  Color activatedbackgroundcolor_;
  std::string text_;
  std::string selectedtext_;
  std::string activatedtext_;
  std::function<void()> activateaction_;
  std::function<void()> deactivateaction_;
};