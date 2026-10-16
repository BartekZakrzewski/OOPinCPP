#pragma once

#include <map>
#include <ostream>

class Poly {
public:
  Poly(double constant = 0);

  class CoeffRef {
  public:
    CoeffRef(std::map<unsigned, double> &coeffs, unsigned exp)
        : _coeffs(coeffs), _exp(exp) {}
    CoeffRef &operator=(double value) {
      if (value == 0) {
        _coeffs.erase(_exp);
      } else {
        _coeffs[_exp] = value;
      }
      return *this;
    }
    CoeffRef &operator=(const CoeffRef &other) {
      return *this = static_cast<double>(other);
    }

    operator double() const {
      auto it = _coeffs.find(_exp);
      return it == _coeffs.end() ? 0.0 : it->second;
    }

  private:
    std::map<unsigned, double> &_coeffs;
    unsigned _exp;
  };

  CoeffRef operator[](unsigned exp);
  double operator[](unsigned exp) const;

  double operator()(double x) const;

  Poly &operator+=(const Poly &other);
  Poly &operator-=(const Poly &other);
  Poly &operator*=(const Poly &other);

  friend std::ostream &operator<<(std::ostream &os, const Poly &p);
  friend bool operator==(const Poly &lhs, const Poly &rhs);

private:
  std::map<unsigned, double> _coeffs;
};

Poly operator+(Poly lhs, const Poly &rhs);
Poly operator-(Poly lhs, const Poly &rhs);
Poly operator*(Poly lhs, const Poly &rhs);
Poly operator-(const Poly &p);
bool operator!=(const Poly &lhs, const Poly &rhs);
