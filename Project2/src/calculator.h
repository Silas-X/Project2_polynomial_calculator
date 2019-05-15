#pragma once
#ifndef POLYCALC_CALCULATOR_H_
#define POLYCALC_CALCULATOR_H_

#include <iostream>
#include <string>

namespace CalcCore {
const int MAXORDER = 1000;

class Polynomial {
 private:
  int data[MAXORDER + 1];
  int maxOrder;
  // auxilary
  bool insert(std::string tuple);
  bool str2num(std::string tuple, int& x);
  bool copyData(int* data, const int* origin, int size);
  bool convert(const std::string str);

 public:
  // constructor
  Polynomial();
  Polynomial(int x);
  Polynomial(std::string);
  Polynomial(const Polynomial& origin);

  // destructor
  ~Polynomial();
  // accessor
  inline int getMaxOrder() const;

  // mutator
  bool initPoly();
  bool clear();
  bool setPolynomial(const std::string);
  bool setPolynomial(const int* array, const int maxOrder);
  inline bool setMaxOrder(const int x);
  bool modifyPolynomial(const int order, const int coefficient);
  Polynomial& reverse();

  // operators

  Polynomial& operator=(const Polynomial& origin);
  Polynomial operator+(const Polynomial& another);
  Polynomial operator-(const Polynomial& another);
  Polynomial operator*(const Polynomial& another);
  Polynomial D();
  Polynomial Evaluate(int& x);

  friend std::ostream& operator<<(std::ostream& out, const Polynomial& current);
  friend std::istream& operator>>(std::istream& in, Polynomial& current);
};
inline int Polynomial::getMaxOrder() const { return maxOrder; }
}  // namespace CalcCore

#endif
