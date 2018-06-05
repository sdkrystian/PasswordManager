#pragma once
#include "Object.h"
#include "Category.h"
#include <vector>

class Menu
{
public:
  static std::vector<Category>& Categories();
  static std::vector<Element>& Elements();
  static int CategoryIndex();
  static void NextUp();
  static void NextDown(); 
  static void Press();
  static void Redraw();
private:
  static std::vector<Category> categories_;
  static std::vector<Element> elements_;
  static unsigned xindex_;
  static unsigned yindex_;
  static int selectedcat_;
  static int selectedelem_;
};
