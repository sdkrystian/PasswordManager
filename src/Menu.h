#pragma once
#include "Object.h"
#include "Button.h"
#include <vector>

class Menu
{
public:
  static std::vector<Button>& Buttons();
  static void AddButtons(const std::vector<Button>& buttons);
  static void NextUp();
  static void NextDown(); 
  static void Press();
  static void Clear();
  static bool& Enabled();
private:
  static std::vector<Button> buttons_;
  static int selectedbutton_;
};
