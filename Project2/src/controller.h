#pragma once
#ifndef POLYCALC_CONTROLLER_H_
#define POLYCALC_CONTROLLER_H_
#include "calculator.h"

namespace ctl {
const std::string LASTANSWER = "RES";
const int MAXSTORAGE = 26;
class controller {  // should be singleton Only one
 private:
  CalcCore::Polynomial*
      storage[MAXSTORAGE];  // store the expression mapped by "A"-"Z"
  CalcCore::Polynomial expression1, expression2, last_res;
  int numbers;
  static controller* commander;

  // CalcCore::Polynomial findPolynominal(char sym) const;
  // Singleton contructor
  controller();

 public:
  ~controller();

  // accessor
  bool getPolynominal(std::string token, CalcCore::Polynomial& current) const;
  // int getTotalNumbers() const;
  bool isExist(std::string token) const;
  bool isEmpty() const;
  bool isToken(std::string token) const;
  void showMemory() const;

  // mutator
  bool StoreUnit();
  bool TransferIt(std::string token1, std::string token2);
  bool storeIt(std::string token1, std::string token2);
  bool storeIt(std::string token1, CalcCore::Polynomial temp);

  bool deleteUnit();
  bool erase(std::string token);
  bool clear();

  bool CalcUnit(CalcCore::Polynomial (controller::*process)());
  CalcCore::Polynomial addition();
  CalcCore::Polynomial substraction();
  CalcCore::Polynomial multiplication();
  CalcCore::Polynomial derivation();
  CalcCore::Polynomial evaluation();

  bool setExpression(CalcCore::Polynomial& expression);

  // singleton creator;
  static controller* init();
};

}  // namespace ctl

#endif  // POLYCALC_CONTROLLER_H_