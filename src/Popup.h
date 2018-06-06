#pragma once
#include "Object.h"
#include "Console.h"

class Popup
{
public:
  Popup(unsigned lifetime, unsigned y, unsigned sizex, unsigned sizey, const std::string& text, Color textcolor, Color backgroundcolor);
};