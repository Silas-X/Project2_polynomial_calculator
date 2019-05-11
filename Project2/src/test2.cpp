#include <iostream>
#include "UI.h"
#include "calculator.h"
#include "controller.h"
//#define _DEBUG
#ifdef _DEBUG
#include "UI.cpp"
#include "calculator.cpp"
#include "controller.cpp"
#endif
using namespace CalcCore;

int main() {
  ctl::controller* _controller = ctl::controller::init();
  UI::UserInterface calculator{_controller};
  calculator.dispatch();
  return 0;
}