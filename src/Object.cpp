#include "Object.h"

Object::Object(int x, int y, bool show) : x_(x), y_(y), show_(show) { }

int Object::X() const
{
  return x_;
}

int Object::Y() const
{
  return y_;
}

ObjectType Object::GetType()
{
  return type_;
}
