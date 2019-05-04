#pragma once
#ifndef POLYCALC_CONTROLLER_H_
#define POLYCALC_CONTROLLER_H_
#include "UI.h"
#include "calculator.h"
namespace ctl {

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
  UI::UserInterface Menu;
  // singleton creator;
  static controller* init();
  void start();
};

}  // namespace ctl

#endif  // POLYCALC_CONTROLLER_H_