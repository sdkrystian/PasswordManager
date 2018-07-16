// Copyright 2018 Krystian Stasiowski

#include "Input.h"

std::map<char, std::chrono::time_point<std::chrono::steady_clock>> Input::keys_;

bool Input::GetKeyDown(char key, unsigned delay)
{
  if (GetKeyState(key) & 0x8000)
  {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - keys_[key]).count() > delay)
    {
      keys_[key] = std::chrono::high_resolution_clock::now();
      return true;
    }
  }
  return false;
}