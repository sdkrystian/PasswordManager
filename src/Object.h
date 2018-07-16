// Copyright 2018 Krystian Stasiowski

#pragma once

class Object
{
public:
  unsigned X() const;
  unsigned Y() const;
  virtual void Select(bool select) = 0;
  virtual void Select() = 0;
  virtual void Show(bool show) = 0;
  virtual void Move(int x, int y) = 0;
  virtual bool Hidden() const = 0;
protected:
  unsigned x_;
  unsigned y_;
  bool show_;

  Object(unsigned x, unsigned y, bool show);
};