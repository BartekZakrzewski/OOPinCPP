#include "Array.h"
#include <iostream>
#include <ostream>

int main() {
  std::cout << "60%" << std::endl;
  Array a1(2);
  a1.fill(1.6);
  std::cout << a1 << std::endl;
  std::cout << a1.getSize() << std::endl;
  a1.add(7.9);
  std::cout << a1 << std::endl;
  std::cout << a1.getSize() << std::endl;
  a1.setElement(0, 0.3);
  a1.setElement(2, 3.4);
  std::cout << a1 << std::endl;

  Array a2(4);
  a2.fill(0.8);
  a2.setElement(2, -0.3);
  std::cout << a2 << std::endl;
  std::cout << a2.getSize() << std::endl;

  std::cout << "80%" << std::endl;
  a1.swap(a2);
  std::cout << a1 << std::endl;
  std::cout << a1.getSize() << std::endl;
  std::cout << a2 << std::endl;
  std::cout << a2.getSize() << std::endl;

  std::cout << "100%" << std::endl;
  Array a3 = a1;
  a3.append(a2);
  std::cout << a3 << std::endl;

  return 0;
}
