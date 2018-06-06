#pragma once
#include "Object.h"
#include "Button.h"

class Menu
{
public:
  static std::vector<Button>& Buttons();
  static void AddButtons(const std::vector<Button>& buttons);
  static void SetInputCallback(std::function<void(std::string)> callback, unsigned x, unsigned y);
  static void ExecuteInputCallback(std::string input);
  static void NextUp();
  static void NextDown(); 
  static void Press();
  static void Clear();
  static bool& Enabled();
  static unsigned InputX();
  static unsigned InputY();
private:
  static std::vector<Button> buttons_;
  static bool enabled_;
  static int selectedbutton_;
  static unsigned inputcallbackx_;
  static unsigned inputcallbacky_;
  static std::function<void(std::string)> inputcallback_;
};
