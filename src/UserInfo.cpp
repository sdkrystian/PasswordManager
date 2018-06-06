#include "UserInfo.h"

std::vector<Category> UserInfo::categories_;

std::vector<Category>& UserInfo::Categories()
{
  return categories_;
}

void UserInfo::Save()
{
  return;
}

void UserInfo::ReadFromFile()
{
  return;
}