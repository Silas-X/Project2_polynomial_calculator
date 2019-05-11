#include "controller.h"
#include <iomanip>
//#include "utilities.h"

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

bool controller::getPolynominal(std::string token,
                                CalcCore::Polynomial& current) const {
  if (token == LASTANSWER) {
    current = last_res;
    return true;
  }
  if (token.size() > 1) return false;
  int sym = toupper(token[0]) - 'A';
  if (sym < 0 || sym >= MAXSTORAGE || storage[sym] == NULL) return false;
  current = *storage[sym];
  return true;
}

bool controller::isEmpty() const { return numbers; }

bool controller::isExist(std::string token) const {
  if (!isToken(token)) return false;
  return (!storage[toupper(token[0]) - 'A'] == NULL);
}
bool controller::isToken(std::string token) const {
  if (token == LASTANSWER) return true;
  if (token.size() == 1) {
    int sym = toupper(token[0]) - 'A';
    if (sym >= 0 && sym < MAXSTORAGE) return true;
  }
  return false;
}
void controller::showMemory() const {
  for (int i = 0; i < MAXSTORAGE; i++) {
    char sym = i + 'A';

    std::cout << "\t" << sym << "= ";
    if (storage[i] == NULL)
      std::cout << "NaN" << std::endl;
    else
      std::cout << *storage[i] << std::endl;
  }
  std::cout << "\t LAST RESULT = " << last_res << std::endl;
}

// mutator
bool controller::StoreUnit() {
  std::string token1, token2;
  std::cout << "Please enter expression" << std::endl
            << "Format: [Target_symbol:[A-Z]] "
               "[expression:[(base1,order1)(base2,order2)...]] or "
               "[Target_symbol:[A-Z]] "
               "[Source_symbol:[A-Z]]"
            << std::endl;
  std::cin >> token1 >> token2;
  if (!(TransferIt(token1, token2) || storeIt(token1, token2))) {
    std::cout << "Invalid input!" << std::endl;
    return false;
  }
  CalcCore::Polynomial temp;
  getPolynominal(token1, temp);
  std::cout << "SUCCESS" << std::endl << token1 << " = " << temp << std::endl;
  return true;
}

bool controller::TransferIt(std::string token1, std::string token2) {
  if (!(isToken(token1) && isToken(token2))) return false;
  CalcCore::Polynomial temp;
  if (!getPolynominal(token2, temp)) return false;
  return storeIt(token1, temp);
}

bool controller::storeIt(std::string token1, std::string token2) {
  CalcCore::Polynomial temp;
  if (!temp.setPolynomial(token2)) return false;
  return storeIt(token1, temp);
}
bool controller::storeIt(std::string token, CalcCore::Polynomial temp) {
  if (token == LASTANSWER) {
    last_res = temp;
    return true;
  }
  if (token.size() != 1) return false;
  char sym = token[0];
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

CalcCore::Polynomial controller::addition() {
  return expression1 + expression2;
}

CalcCore::Polynomial controller::substraction() {
  return expression1 - expression2;
}

CalcCore::Polynomial controller::multiplication() {
  return expression1 * expression2;
}

CalcCore::Polynomial controller::derivation() {
  CalcCore::Polynomial temp{expression1};
  return temp.D();
}

CalcCore::Polynomial controller::evaluation() {
  std::cout << "Please enter a integer X= ";
  int x;
  std::cin >> x;
  return expression1.Evaluate(x);
}

bool controller::setExpression(CalcCore::Polynomial& expression) {
  bool ok = false;
  std::string temp;
  while (!ok) {
    std::cout
        << "Please enter a [expression:[(base1,order1)(base2,order2)...]] or a "
           "[symbol:[A-Z]], [exit] to cancel"
        << std::endl;
    std::cin >> temp;
    if (temp == "Exit" || temp == "exit") return false;
    if (getPolynominal(temp, expression)) {
      ok = true;
      continue;
    }
    if (expression.setPolynomial(temp)) {
      ok = true;
      continue;
    }
    std::cout << "Failed, please checkout if it exists or the format is right."
              << std::endl;
  }
  std::cout << "SUCCESS" << std::endl
            << "Expression: " << expression << std::endl;

  return true;
}

bool controller::CalcUnit(CalcCore::Polynomial (controller::*process)()) {
  if (process == &this->derivation || process == &this->evaluation) {
    if (!setExpression(expression1)) return false;
  } else if (!(setExpression(expression1) && setExpression(expression2)))
    return false;
  CalcCore::Polynomial temp =
      (this->*process)();  // TODO:pointer to a class function?
  std::cout << temp << std::endl;
  storeIt(LASTANSWER, temp);
  std::cout << "Do you want to store your answer?(y/n)" << std::endl;

  std::string flag;
  std::cin >> flag;
  while (flag != "y" && flag != "Y" && (flag != "N") && (flag != "n")) {
    std::cin >> flag;
  }

  if (flag == "y" || flag == "Y") {
    std::cout << "Please enter [symbol:[A-Z]]" << std::endl;
    std::string sym;
    std::cin >> sym;
    while (!TransferIt(sym, LASTANSWER)) {
      std::cout << "Failed, Please enter [symbol:[A-Z]]" << std::endl;
      std::cin >> sym;
      if (sym == "Exit") {
        std::cout << "Cancel" << std::endl;
        break;
      }
    }
    if (sym != "Exit") std::cout << "SUCCESS" << std::endl;
  }
  return true;
}

// static members
controller* controller::commander = NULL;
}  // namespace ctl