#pragma once
#include "Console.h"
#include "Object.h"
#include <functional>

class Button : public Object
{
public:
  Button(unsigned x, unsigned y, Color textcolor, Color backgroundcolor, Color selectedtextcolor, Color selectedbackgroundcolor, Color activatedtextcolor, const std::string& text, const std::string& selectedtext, const std::string& activatedtext, const std::function<void()>& activateaction, const std::function<void()>& deactivateaction, bool centered = false, bool show = true, bool activated = false);
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
  bool activated_;
  bool selected_;
  Color textcolor_;
  Color backgroundcolor_;
  Color selectedtextcolor_;
  Color selectedbackgroundcolor_;
  Color activatedtextcolor_;
  std::string text_;
  std::string selectedtext_;
  std::string activatedtext_;
  std::function<void()> activateaction_;
  std::function<void()> deactivateaction_;
};