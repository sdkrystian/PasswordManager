#pragma once
#include "Console.h"
#include "Object.h"
#include <functional>
#include <iostream>

class Element : public Object
{
public:
  Element(int parentindex, int x, int y, Color textcolor, Color backgroundcolor, Color selectedtextcolor, Color selectedbackgroundcolor, Color activatedtextcolor, Color activatedtbackgroundcolor, const std::string& text, const std::string& selectedtext, const std::string& activatedtext, const std::function<void()>& activateaction, const std::function<void()>& deactivateaction, bool show = true, bool activated = false);
  Element(int parentindex, int x, int y, Color textcolor, Color backgroundcolor, Color selectedtextcolor, Color selectedbackgroundcolor, const std::string& text, const std::string& selectedtext, bool show = true);
  void Select() override;
  void Select(bool select) override;
  void Show(bool show) override;
  bool Hidden() const override ;
  void Move(int x, int y) override;
  void Press();
  void Press(bool press);
  bool Activated() const;
  bool Selected() const;
private:
  int parentindex_;
  bool activated_;
  bool selected_;
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