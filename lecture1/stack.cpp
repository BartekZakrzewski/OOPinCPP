#include <iostream>
#include <memory>
#include <vector>
template <typename T> class Stack {
public:
  T push(std::shared_ptr<T> x) { stack_.push_back(x); }
  T top() { return stack_.front(); }
  std::shared_ptr<T> pop() { return stack_.pop_back(); }

private:
  std::vector<T> stack_;
};

int main() {
  Stack<int> s;
  s.push(1);
  s.push(2);
  std::cout << s.top() << "\n" << s.pop();
  return 0;
}
