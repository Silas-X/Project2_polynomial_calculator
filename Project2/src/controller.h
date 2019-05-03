#pragma once
#ifndef POLYCALC_CONTROLLER_H_
#define POLYCALC_CONTROLLER_H_
#include "calculator.h"

namespace ctl {
const int MAXSTORAGE = 26;
class controller {  // should be singleton Only one
 private:
  CalcCore::Polynomial*
      storage[MAXSTORAGE];  // store the expression mapped by "A"-"Z"
  int numbers;
  // Singleton contructor
  controller();

 public:
  ~controller();

  // accessor
  CalcCore::Polynomial getPolynominal(char sym) const;
  int getTotalNumbers() const;

  // mutator
  bool storeIt(char sym);
  bool clear();
  // singleton creator;
  bool butler();
};

}  // namespace ctl

#endif  // POLYCALC_CONTROLLER_H_