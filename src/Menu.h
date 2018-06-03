#pragma once
#include <vector>
#include "Category.h"

class Menu
{
public:
  std::vector<Object*>& Objects();
  Object* NextUp();
  Object* NextDown();
  Object* NextLeft();
  Object* NextRight();
private:
  unsigned xindex_;
  unsigned yindex_;
  std::vector<Object*> objects_;
};
