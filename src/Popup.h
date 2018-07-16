// Copyright 2018 Krystian Stasiowski

#pragma once
#include "Object.h"
#include "Console.h"

class Popup
{
public:
  Popup() = delete;
  Popup(const Popup&) = delete;
  Popup& operator=(const Popup&) = delete;
  Popup(Popup&&) = delete;
  Popup& operator=(Popup&&) = delete;
  Popup(unsigned lifetime, unsigned y, unsigned sizex, unsigned sizey, const std::string& text, Color textcolor, Color backgroundcolor);
};