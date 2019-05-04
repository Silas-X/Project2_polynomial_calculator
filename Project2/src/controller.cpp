#include "controller.h"
#include "UI.h"
namespace ctl {
controller::controller() : numbers{0} {
  for (int i = 0; i < MAXSTORAGE; i++) {
    storage[i] = NULL;
  }
}
controller::~controller() {
  delete commander;
  commander = NULL;
}

controller* controller::init() {
  if (commander == NULL) {
    commander = new controller;
  }
  return commander;
}

void controller::start() {
  Menu.setCallMenu(
      0);  // why can't access when set it as private and declare as friend
  Menu.dispatch();
  return;
}

controller* controller::commander = NULL;
}  // namespace ctl