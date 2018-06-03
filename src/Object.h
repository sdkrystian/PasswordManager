#pragma once

enum class ObjectType
{
  BUTTON,
  CATEGORY,
  TEXT,
  INPUT,
  PASSWORD
};

class Object
{
protected:
  mutable int x_;
  mutable int y_;

  Object(int x, int y);
  
  virtual void Show(bool) const = 0;
  virtual bool Selectable() const = 0;
};