#include "Poly.h"
#include <cmath>
#include <ostream>

Poly::Poly(double constant) {
  if (constant != 0) {
    _coeffs[0] = constant;
  }
}

Poly::CoeffRef Poly::operator[](unsigned exp) { return CoeffRef(_coeffs, exp); }
double Poly::operator[](unsigned exp) const {
  auto it = _coeffs.find(exp);
  return it == _coeffs.end() ? 0.0 : it->second;
}

double Poly::operator()(double x) const {
  double res = 0;
  for (const auto &[exp, coeff] : _coeffs) {
    res += coeff * std::pow(x, exp);
  }
  return res;
}

Poly &Poly::operator+=(const Poly &other) {
  for (const auto &[exp, coeff] : other._coeffs) {
    _coeffs[exp] += coeff;
    if (_coeffs[exp] == 0) {
      _coeffs.erase(exp);
    }
  }
  return *this;
}
Poly &Poly::operator-=(const Poly &other) {
  if (this == &other) {
    _coeffs.clear();
    return *this;
  }
  for (const auto &[exp, coeff] : other._coeffs) {
    _coeffs[exp] -= coeff;
    if (_coeffs[exp] == 0) {
      _coeffs.erase(exp);
    }
  }
  return *this;
}
Poly &Poly::operator*=(const Poly &other) {
  std::map<unsigned, double> res;
  for (const auto &[exp1, coeff1] : _coeffs) {
    for (const auto &[exp2, coeff2] : other._coeffs) {
      res[exp1 + exp2] += coeff1 * coeff2;
    }
  }
  for (auto it = res.begin(); it != res.end();) {
    if (it->second == 0) {
      it = res.erase(it);
    } else {
      ++it;
    }
  }
  _coeffs = res;
  return *this;
}

Poly operator+(Poly lhs, const Poly &rhs) { return lhs += rhs; }
Poly operator-(Poly lhs, const Poly &rhs) { return lhs -= rhs; }
Poly operator*(Poly lhs, const Poly &rhs) { return lhs *= rhs; }
Poly operator-(const Poly &p) {
  Poly res;
  res -= p;
  return res;
}
bool operator==(const Poly &lhs, const Poly &rhs) {
  if (lhs._coeffs.size() != rhs._coeffs.size()) {
    return false;
  }
  for (const auto &[exp, coeff] : lhs._coeffs) {
    if (coeff != rhs[exp])
      return false;
  }
  return true;
}
bool operator!=(const Poly &lhs, const Poly &rhs) { return !(lhs == rhs); }

std::ostream &operator<<(std::ostream &os, const Poly &p) {
  if (p._coeffs.empty()) {
    return os << 0;
  }
  for (auto it = p._coeffs.rbegin(); it != p._coeffs.rend(); ++it) {
    unsigned exp = it->first;
    double coeff = it->second;

    if (it == p._coeffs.rbegin()) {
      if (coeff < 0) {
        os << "-";
      }
    } else {
      os << (coeff < 0 ? " - " : " + ");
    }

    os << std::abs(coeff);
    if (exp == 1) {
      os << "x";
    } else if (exp > 1) {
      os << "x^" << exp;
    }
  }
  return os;
}
