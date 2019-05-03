#include "calculator.h"
#include <string>

#define DEBUG_
namespace calculator {
Polynomial::Polynomial() : data{0},maxOrder{0} {}
Polynomial::Polynomial(std::string) {}  // TODO:Convert String to Polynomial;
Polynomial::Polynomial(const Polynomial& origin) {
  this->maxOrder = origin.maxOrder;
  copyData(this->data, origin.data, this->maxOrder + 1);
}

Polynomial::~Polynomial() {
  maxOrder = 0;
  data[0] = 0;
}

bool Polynomial::copyData(int* data, const int* origin, int size) {
  if (size > MAXORDER) return false;
  for (int i = 0; i < size; i++) data[i] = origin[i];
  return true;
}

inline std::string Polynomial::getPolynomial() const {
  // TODO::return a string form;
  return "";
}
bool Polynomial::clear() {
  maxOrder = 0;
  for (int i = 0; i < MAXORDER; i++) data[i] = 0;
  return true;
}
inline bool Polynomial::setMaxOrder(const int x) {
  maxOrder = x;
  return true;
}
bool Polynomial::setPolynomial(const std::string origin) {
  // TODO::readIn a String
  return true;
}

bool Polynomial::setPolynomial(const int* data, const int maxOrder) {
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
#ifdef DEBUG_
int& Polynomial::at(const int pos) { return this->data[pos]; }
#endif
Polynomial& Polynomial::operator=(const Polynomial& origin) {
  this->maxOrder = origin.maxOrder;
  copyData(this->data, origin.data, maxOrder);
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

/*Polynomial operator-(Polynomial& origin) {
  Polynomial res;
  for (int i = 0; i < origin.maxOrder; i++) {
    res.data[i] = -origin.data[i];
  }
  res.maxOrder = origin.maxOrder;
  return res;
}
*/
}  // namespace calculator