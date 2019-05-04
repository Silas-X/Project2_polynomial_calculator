#pragma once
#ifndef POLYCALC_CONTROLLER_H_
#define POLYCALC_CONTROLLER_H_
//#include "UI.h"
#include "calculator.h"
// namespace UI {
class UserInterface {
 private:
  int opt;
  int callMenu;
  std::string opt_str;

 public:
  UserInterface(/* args */);
  ~UserInterface();
  // accessors
  int getOption() const;
  int getNext() const;
  // mutator
  bool setCallMenu(int opt);
  void dispatch();
  bool setOption();
  void welcomePage();  // 0
  void sayGoodbye();   //-1
  void mainMenu();     // 1
  void calcMenu();     // 2
                       // friend void ctl::controller::start();
};

//}  // namespace UI

// namespace ctl {

const int MAXSTORAGE = 26;
class controller {  // should be singleton Only one
 private:
  CalcCore::Polynomial*
      storage[MAXSTORAGE];  // store the expression mapped by "A"-"Z"
  int numbers;
  static controller* commander;

  // CalcCore::Polynomial findPolynominal(char sym) const;
  // Singleton contructor
  controller();

 public:
  ~controller();

  // accessor
  // bool getPolynominal(char sym, CalcCore::Polynomial current) const;
  // int getTotalNumbers() const;
  // void showMemory() const;
  // mutator
  // bool storeIt(char sym);
  // bool clear();
  // Problem  with Namespace UI UI::UserInterface Menu;
  UserInterface Menu;
  // singleton creator;
  static controller* init();
  void start();
};

//}  // namespace ctl

#endif  // POLYCALC_CONTROLLER_H_