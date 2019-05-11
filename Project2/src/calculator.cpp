#include "calculator.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#define DEBUG_

namespace CalcCore {
Polynomial::Polynomial() : data{0}, maxOrder{0} {}
Polynomial::Polynomial(int x) : data{0}, maxOrder{0} {
  data[0] = x;
  maxOrder = 1;
}
Polynomial::Polynomial(std::string str) : data{0}, maxOrder{0} {
  this->setPolynomial(str);
}

Polynomial::Polynomial(const Polynomial& origin) : data{0}, maxOrder{0} {
  this->maxOrder = origin.maxOrder;
  copyData(this->data, origin.data, this->maxOrder + 1);
}

Polynomial::~Polynomial() {
  maxOrder = 0;
  initPoly();
}

// auxiliary
// TODO: The dread string operation makes me crazy, any other better methods?

bool Polynomial::copyData(int* data, const int* origin, int size) {
  if (size > MAXORDER) return false;
  for (int i = 0; i < size; i++) data[i] = origin[i];
  return true;
}

bool Polynomial::str2num(std::string str, int& x) {
  std::stringstream ss;
  ss.clear();
  ss.str("");
  ss << str;
  ss >> x;
  return (!ss.fail());
}

bool Polynomial::insert(const std::string tuple) {
  int pos = tuple.find(',');
  if (pos == std::string::npos) return false;

  int coeff;
  if (!str2num(tuple.substr(0, pos), coeff)) return false;

  int order;
  if (!str2num(tuple.substr(pos + 1, tuple.size() - pos), order)) return false;

  if (order > MAXORDER) {
    std::cout << "Sorry, MAX ORDER<=" << MAXORDER << std::endl;
    return false;
  }
  if (order < 0) {
    std::cout << "Sorry, current only non-negative order is supported"
              << std::endl;
    return false;
  }
  data[order] += coeff;
  if (order > this->maxOrder) maxOrder = order;
  while (data[this->maxOrder] == 0 && this->maxOrder > 0) this->maxOrder--;
  return true;
}

bool Polynomial::convert(const std::string str) {
  std::string temp = str;
  while (!temp.empty()) {
    int pos1 = temp.find('(');
    int pos2 = temp.find(')');
    if (pos1 == std::string::npos || pos2 == std::string::npos || pos1 != 0 ||
        pos1 >= pos2)
      return false;
    if (!insert(temp.substr(pos1 + 1, pos2 - pos1 + 1 - 2))) return false;
    temp = temp.substr(pos2 + 1, temp.size() - pos2);
  }
  return true;
}

inline std::string Polynomial::getPolynomial() const {
  // TODO::return a string form;
  return "";
}

bool Polynomial::initPoly() {
  for (int i = 0; i <= MAXORDER; i++) {
    data[i] = 0;
  }
  return true;
}

bool Polynomial::clear() {
  maxOrder = 0;
  return initPoly();
}
inline bool Polynomial::setMaxOrder(const int x) {
  maxOrder = x;
  return true;
}
bool Polynomial::setPolynomial(std::string origin) {
  this->clear();
  return (this->convert(origin));
}

bool Polynomial::setPolynomial(const int* data, const int maxOrder) {
  this->clear();
  if (maxOrder > MAXORDER) return false;
  this->maxOrder = maxOrder;
  copyData(this->data, data, maxOrder + 1);
  return true;
}
bool Polynomial::modifyPolynomial(const int order, const int coefficient) {
  if (order > MAXORDER) return false;
  this->data[order] = coefficient;
  if (order > maxOrder) maxOrder = order;
  return true;
}
Polynomial& Polynomial::reverse() {
  for (int i = 0; i <= this->maxOrder; i++) this->data[i] = -this->data[i];
  return *this;
}

Polynomial& Polynomial::operator=(const Polynomial& origin) {
  this->clear();
  this->maxOrder = origin.maxOrder;
  copyData(this->data, origin.data, maxOrder + 1);
  return *this;
}

Polynomial Polynomial::operator+(const Polynomial& another) {
  Polynomial res;
  res.maxOrder = this->maxOrder;
  if (this->maxOrder < another.maxOrder) res.maxOrder = another.maxOrder;
  for (int i = 0; i <= res.maxOrder; i++) {
    res.data[i] = this->data[i] + another.data[i];
  }
  while (res.data[res.maxOrder] == 0) res.maxOrder--;
  if (res.maxOrder < 0) {
    res.clear();
  }
  return res;
}

Polynomial Polynomial::operator-(const Polynomial& another) {
  Polynomial temp{another};
  return (*this + temp.reverse());
}

Polynomial Polynomial::operator*(const Polynomial& another) {
  Polynomial res;
  for (int i = 0; i <= this->maxOrder; i++) {
    for (int j = 0; j <= another.maxOrder; j++) {
      res.data[i + j] = res.data[i + j] + this->data[i] * another.data[j];
    }
  }
  res.maxOrder = this->maxOrder + another.maxOrder;
  while (res.data[res.maxOrder] == 0) res.maxOrder--;
  if (res.maxOrder < 0) {
    res.clear();
  }
  return res;
}

Polynomial Polynomial::D() {
  Polynomial res;
  if (this->maxOrder == 0) {
    res.clear();
    return res;
  }
  res.setMaxOrder(this->maxOrder - 1);
  for (int i = 0; i <= res.maxOrder; i++) {
    res.data[i] = this->data[i + 1] * (i + 1);
  }
  return res;
}
int power(int base, int power) {
  int res = 1;
  while (power > 0) {
    if (power & 1) res = res * base;
    power >>= 1;
    base *= base;
  }
  return res;
}

Polynomial Polynomial::Evaluate(int& x) {
  int res = 0;
  for (int i = 0; i <= this->maxOrder; i++) {
    res += this->data[i] * power(x, i);
  }
  Polynomial temp{res};
  return temp;
}

/*Polynomial operator-(Polynomial& origin) {
  Polynomial res;
  for (int i = 0; i < origin.maxOrder; i++) {
    res.data[i] = -origin.data[i];
  }
  res.maxOrder = origin.maxOrder;
  return res;
}
*/
std::istream& operator>>(std::istream& in, Polynomial& current) {
  std::string temp;
  in >> temp;
  current.clear();
  while (current.convert(temp) == false) {
    std::cout << "Invalid input" << std::endl
              << "Please re-enter the expression" << std::endl;
    in >> temp;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& current) {
  if (current.maxOrder == 0 && current.data[0] == 0) {
    std::cout << "0"  ;
    return out;
  }
  for (int i = current.getMaxOrder(); i >= 0; i--) {
    if (current.getMaxOrder() > 0 && current.data[i] == 0) continue;
    if (i == current.getMaxOrder())
      std::cout << current.data[i] << "x^" << i;
    else {
      if (current.data[i] < 0)
        std::cout << " - " << -current.data[i] << "x^" << i;
      else
        std::cout << " + " << current.data[i] << "x^" << i;
    }
  }
  return out;
}
}  // namespace CalcCore