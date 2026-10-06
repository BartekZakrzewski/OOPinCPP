#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>

class Point {
public:
  Point(double x = 0.0, double y = 0.0) : x_(x), y_(y) {}
  double x() const { return x_; }
  double y() const { return y_; }
  double distance(Point &p) {
    return std::sqrt(std::abs(p.x() - x()) + std::abs(p.y() - y()));
  }

private:
  double x_, y_;
};

class Shape {
public:
  Shape(std::string name) : name_(std::move(name)) { ++count_; }
  Shape(const Shape &other) : name_(other.name_) { ++count_; }
  Shape &operator=(const Shape &) = default;
  virtual ~Shape() { --count_; }
  virtual double area() const = 0;
  virtual void describe() const {
    std::cout << name_ << " with area " << area() << "\n";
  }
  const std::string &name() const { return name_; }
  static int count() { return count_; }

protected:
  std::string name_;

private:
  static int count_;
};

int Shape::count_ = 0;
