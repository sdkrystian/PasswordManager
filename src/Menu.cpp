#include "Menu.h"
#include <algorithm>
#include <iostream>
#include "Button.h"
#include <functional>

std::vector<Button> Menu::buttons_ = { };
int Menu::selectedbutton_ = 0;
bool Menu::enabled_ = true;
unsigned Menu::inputcallbackx_;
unsigned Menu::inputcallbacky_;
std::function<void(std::string)> Menu::inputcallback_;

std::vector<Button>& Menu::Buttons()
{
  return buttons_;
}

void Menu::AddButtons(const std::vector<Button>& buttons)
{
  buttons_.insert(buttons_.end(), buttons.begin(), buttons.end());
}

void Menu::SetInputCallback(std::function<void(std::string)> callback, unsigned x, unsigned y)
{
  inputcallback_ = callback;
  inputcallbackx_ = x;
  inputcallbacky_ = y;
}

void Menu::ExecuteInputCallback(const std::string& input)
{
  inputcallback_(input);
}

void Menu::CloseCallback()
{
  inputcallback_ = [] (std::string) {};
  inputcallbackx_ = 0;
  inputcallbacky_ = 0;
}

void Menu::NextUp()
{
  if (selectedbutton_ - 1 >= 0)
  {
    buttons_[selectedbutton_].Select(false);
    buttons_[--selectedbutton_].Select(true);
  }
}

void Menu::NextDown()
{
  if (selectedbutton_ + 1 < buttons_.size())
  {
    buttons_[selectedbutton_].Select(false);
    buttons_[++selectedbutton_].Select(true);
  }
}

void Menu::Press()
{
  if (!buttons_.empty())
   buttons_[selectedbutton_].Press();
}

void Menu::Clear()
{
  selectedbutton_ = 0;
  for (Button& b : buttons_)
  {
    b.Show(false);
  }
  buttons_.clear();
  Console::Clear();
}

bool& Menu::Enabled()
{
  return enabled_;
}

unsigned Menu::InputX()
{
  return inputcallbackx_;
}

unsigned Menu::InputY()
{
  return inputcallbacky_;
}
