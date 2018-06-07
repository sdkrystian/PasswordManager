#include "Popup.h"

Popup::Popup(unsigned lifetime, unsigned y, unsigned sizex, unsigned sizey, const std::string& text, Color textcolor, Color backgroundcolor)
{
  for (unsigned i = y; i < y + sizey; ++i)
  {
    Console::SetCursorPosition((Console::GetSize().X - sizex) / 2, i);
    Console::ColorLine(backgroundcolor, sizex);
  }
  Console::SetCursorPosition((Console::GetSize().X - text.length()) / 2, y + (sizey / 2));
  Console::Write(text, textcolor, backgroundcolor);
  Sleep(lifetime);
  for (unsigned i = y; i < y + sizey; ++i)
  {
    Console::SetCursorPosition((Console::GetSize().X - sizex) / 2, i);
    Console::ColorLine(Color::BLACK, sizex);
  }
}
