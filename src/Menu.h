#pragma once
#include "Object.h"
#include "Button.h"
#include <vector>

class Menu
{
public:
  static std::vector<Button>& Buttons();
  static void NextUp();
  static void NextDown(); 
  static void Press();
  static void Redraw();
private:
  static std::vector<Button> Buttons_;
  static int selectedelem_;
};
