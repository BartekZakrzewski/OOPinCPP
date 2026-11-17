#include "Vect.h"
#include <iostream>

int main() {
  std::cout << "60%" << std::endl;
  Vect v1(3);
  v1.setElement(0, 0.5);
  v1.setElement(1, 1.5);
  v1.setElement(2, 2.5);

  v1.print();
  std::cout << std::endl;
  std::cout << v1.getSize() << std::endl;
  std::cout << v1.getAverage() << std::endl;

  Vect v2(2);
  v2.setElement(0, 0.1);
  v2.setElement(1, -0.2);

  v2.print();
  std::cout << std::endl;
  std::cout << v2.getSize() << std::endl;
  std::cout << v2.getAverage() << std::endl;

  std::cout << "80%" << std::endl;
  Vect v3;
  std::cout << v1.getMin() << std::endl;
  std::cout << v2.getMin() << std::endl;
  std::cout << v3.getMin() << std::endl;

  std::cout << "100%" << std::endl;
  Vect v4 = v1.concatenate(v2);
  v4.print();
  std::cout << std::endl;

  return 0;
}
