#pragma once
#include "Object.h"
#include "Button.h"
#include "Console.h"
#include <vector>

class Category : public Button
{
public:
  Category(unsigned x, unsigned y, Color textcolor, Color backgroundcolor, Color selectedtextcolor, Color selectedbackgroundcolor, Color activatedtextcolor, Color activatedtbackgroundcolor, const std::string& text, const std::string& selectedtext, const std::string& activatedtext, std::vector<int> elements, bool opened = false, bool show_ = true);
  std::vector<int>& Elements();
  void ShowList();
  void HideList();
  bool Opened();
private:
  void Move(int x, int y) override;
  mutable bool opened_;
  std::vector<int> elements_;
};