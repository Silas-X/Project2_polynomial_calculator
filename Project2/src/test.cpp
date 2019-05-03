#define DEBUG_
#include <iostream>
#include "calculator.h"
using namespace calculator;

struct data {
  int num[1000];
  int maxOrder;
  data() : num{0}, maxOrder{0} {}
  data(int* number, int size) {
    for (int i = 0; size; i++) num[i] = number[i];
    maxOrder = size - 1;
  }
};

void print(Polynomial current) {
  for (int i = current.getMaxOrder(); i >= 0; i--) {
    if (i > 0) std::cout << current.at(i) << "x^" << i << "+";
    else std::cout << current.at(i);
  }
  std::cout << std::endl;
}

int main() {
  Polynomial num_1, num_2;
  int num1[3] = {3, 2, 1};
  int num2[4] = {2, 1};
  num_1.setPolynomial(num1, 2);
  num_2.setPolynomial(num2, 1);
  print(num_1);
  print(num_2);
  print(num_1 + num_2);
  print(num_1 - num_2);
  print(num_1 * num_2);

  return 0;
}