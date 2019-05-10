#include "controller.h"
#include <iomanip>
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

// accessor

bool controller::isEmpty() const { return numbers; }

void controller::showMemory() const {
  for (int i = 0; i < MAXSTORAGE; i++) {
    char sym = i + 'A';

    std::cout << "\t" << sym << "= ";
    if (storage[i] == NULL)
      std::cout << std::endl;
    else
      std::cout << storage[i] << std::endl;
    ;
  }
  std::cout << std::endl;
}

// mutator

bool controller::storeIt(char sym, CalcCore::Polynomial& temp) {
  sym = toupper(sym);
  if (sym > 'Z' || sym < 'A') {
    std::cout << "Invalid Linker.(Variable notation must belongs to [A,Z])"
              << std::endl;
    return false;
  }
  int code = sym - 'A';
  if (storage[code] != NULL) {
    std::cout << "\t======WARNING======\t" << std::endl;
    std::cout << "Data will be overwritten!" << std::endl;
    delete storage[code];
    storage[code] = NULL;
  }
  storage[code] = new CalcCore::Polynomial{temp};
  std::cout << sym << "=" << *storage[code] << std::endl;
  numbers++;
  return true;
}

bool controller::clear() {
  for (int i = 0; i < MAXSTORAGE; i++) {
    if (storage[i] != NULL) {
      delete storage[i];
      storage[i] = NULL;
    }
  }
  numbers = 0;
  return true;
}

CalcCore::Polynomial& controller::addition() {
  CalcCore::Polynomial num1;
  CalcCore::Polynomial num2;
  setExpression(num1);
  setExpression(num2);
  return num1 + num2;
}

CalcCore::Polynomial& controller::substraction() {
  CalcCore::Polynomial num1;
  CalcCore::Polynomial num2;
  setExpression(num1);
  setExpression(num2);
  return num1 - num2;
}

CalcCore::Polynomial& controller::multiplication() {
  CalcCore::Polynomial num1;
  CalcCore::Polynomial num2;
  setExpression(num1);
  setExpression(num2);
  return num1 * num2;
}

bool CalcUnit(CalcCore::Polynomial& (*process)()) {
  CalcCore::Polynomial temp{process()};
  std::cout << "Do you want to store your answer?" << std::endl;
  // setOption();
  // getOption();
}
// static members
controller* controller::commander = NULL;
}  // namespace ctl