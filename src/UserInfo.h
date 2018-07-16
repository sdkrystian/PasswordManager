// Copyright 2018 Krystian Stasiowski

#pragma once
#include <windows.h>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

struct Entry
{
  std::string name;
  std::string username;
  std::string email;
  std::string password;
  std::string url;
  std::string note;
};

struct Category
{
  std::string name;
  std::vector<Entry> entries;
};

class UserInfo
{
public:
  static std::string Configuration;
  static void MoveConfig(const std::string& path);
  static std::vector<Category>& Categories();
  static void Save();
  static void ReadFromFile();
private:
  static std::vector<Category> categories_;
};