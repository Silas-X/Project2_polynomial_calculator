#pragma once
#include "UI.h"
#include <iostream>
#include <string>
namespace UI {
UserInterface::UserInterface() : opt{0}, opt_str{""}, callMenu{0} {}
UserInterface::~UserInterface() {}

bool UserInterface::setCallMenu(int opt) {
  callMenu = opt;
  return true;
}

int UserInterface::getOption() const { return opt; }
int UserInterface::getNext() const { return callMenu; }

void UserInterface::dispatch() {
  bool exitFlag = false;
  while (!exitFlag) {
    switch (callMenu) {
      case -1:
        sayGoodbye();
        exitFlag = true;
        break;
      case 0:
        welcomePage();
        break;
      case 1:
        mainMenu();
        break;
      default:
        std::cout << "CATASTROPHY" << std::endl;
        callMenu = -1;
        break;
    }
  }
  return;
}

bool UserInterface::setOption() {
  bool valid = false;
  std::cout << "Please choose option" << std::endl;
  while (!valid) {
    std::getline(std::cin, opt_str);
    if (opt_str.size() == 1 && isdigit(opt_str[0])) {
      valid = true;
      opt = opt_str[0] - 48;
      return true;
    }
    /*    if (opt_str.size() == 1 && (opt_str[0] == 'x' || opt_str[0] == 'X')) {
          valid = true;
          std::cout << "Warning abandon" << std::endl;
          break;
        }*/
  }
  return false;
}

void UserInterface::welcomePage() {
  using std::cout;
  using std::endl;
  cout << "\tWelcome To the polynomial calculator" << endl;
  cout << "\tThis is intended for Programming Courses Homework II" << endl;
  cout << "\tAuthor: Silas XU" << endl;
  cout << "\tIf there is any problem while using, please fell free to contact "
          "with me."
       << endl;
  cout << "Start Program?" << endl;
  bool exitFlag = false;
  while (!exitFlag) {
    setOption();
    switch (getOption()) {
      case 0:
        sayGoodbye();
        exitFlag = true;
        callMenu = -1;
        break;
      case 1:
        callMenu = 1;
        exitFlag = true;
        break;
      default:
        break;
    }
    system("PAUSE");
  }
  return;
}

void UserInterface::mainMenu() {
  bool exitFlag = false;
  std::cout << "Still in progress, goodbye" << std::endl;
  while (!exitFlag) {
    //   getNum(opt);
  }
}
}  // namespace UI
