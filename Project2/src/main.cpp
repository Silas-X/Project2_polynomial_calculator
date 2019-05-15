#include <iostream>
#include "UI.h"
#include "calculator.h"
#include "controller.h"

using namespace CalcCore;

int main() {
  ctl::controller* _controller = ctl::controller::init();
  UI::UserInterface calculator{_controller};
  calculator.dispatch();
  return 0;
}