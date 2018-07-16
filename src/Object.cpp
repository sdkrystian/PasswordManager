// Copyright 2018 Krystian Stasiowski

#include "Object.h"

Object::Object(unsigned x, unsigned y, bool show) : x_(x), y_(y), show_(show) { }

unsigned Object::X() const
{
  return x_;
}

unsigned Object::Y() const
{
  return y_;
}
