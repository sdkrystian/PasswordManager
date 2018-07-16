// Copyright 2018 Krystian Stasiowski

#pragma once
#include <windows.h>
#include <map>
#include <chrono>
#include <iostream>

class Input
{
public:
  Input() = delete;
  Input(const Input&) = delete;
  Input& operator=(const Input&) = delete;
  Input(Input&&) = delete;
  Input& operator=(Input&&) = delete;
  static bool GetKeyDown(char key, unsigned delay = 150);
private:
  static std::map<char, std::chrono::time_point<std::chrono::steady_clock>> keys_;
};