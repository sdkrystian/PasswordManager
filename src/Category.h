#pragma once
#include "Object.h"
#include "Button.h"
#include "Console.h"
#include <vector>

class Category : public Button
{
public:
  Category(unsigned x, unsigned y, Color textcolor, Color backgroundcolor, Color selectedtextcolor, Color selectedbackgroundcolor, Color activatedtextcolor, Color activatedtbackgroundcolor, std::string text, std::string selectedtext, std::string activatedtext, std::vector<Button> objects, bool opened = false);
  std::vector<Button> Buttons();
private:
  void ShowList();
  void HideList();
  bool opened_;
  std::vector<Button> buttons_;
};