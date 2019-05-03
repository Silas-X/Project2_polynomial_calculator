#pragma once
#define DEBUG_
#ifndef POLYCALC_CALCULATOR_H_
#define POLYCALC_CALCULATOR_H_

#include <iostream>
#include <string>

namespace calculator {
const int MAXORDER = 1000;

class Polynomial {
 private:
  int data[MAXORDER + 1];
  int maxOrder;
  // auxilary
  bool copyData(int* data, const int* origin, int size);

 public:
  // constructor
  Polynomial();
  Polynomial(std::string);
  Polynomial(const Polynomial& origin);

  // destructor
  ~Polynomial();

  // accessor
  inline int getMaxOrder() const;
  inline std::string getPolynominal() const;

  // mutator
  bool clear();
  bool setPolynominal(const std::string);
  bool setPolynominal(const int* array, const int maxOrder);
  inline bool setMaxOrder(const int x);
  bool modifyPolynominal(const int order, const int coefficient);

#ifdef DEBUG_
  int* getAddr() { return data; }
  int& at(const int pos);
#endif

  Polynomial& reverse();

  // operators

  Polynomial& operator=(const Polynomial& origin);
  Polynomial operator+(const Polynomial& another);
  Polynomial operator-(const Polynomial& another);
  Polynomial operator*(const Polynomial& another);

  //  Polynomial& operator==(const Polynomial& another);
  //  Polynomial& operator!=(const Polynomial& another);
  //  Polynomial& operator<(const Polynomial& another);
  //  Polynomial& operator>(const Polynomial& another);
  //  Polynomial& operator<=(const Polynomial& another);
  //  Polynomial& operator>=(const Polynomial& another);

  //  int& operator[](const int x);
  //  friend Polynomial operator-(Polynomial& origin);

  friend std::istream operator<<(std::istream out, Polynomial& current);
  friend std::istream operator>>(std::istream in, Polynomial& current);
};
inline int Polynomial::getMaxOrder() const { return maxOrder; }
}  // namespace calculator

#endif
