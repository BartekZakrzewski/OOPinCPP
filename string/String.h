#pragma once

#include <cstddef>

class String {

public:
  String();
  String(char *s);
  String(char c);
  String(const String &other);
  String &operator=(const String &other);
  ~String();

  char &operator[](int x);

  String &operator+=(const String &other);
  String &operator+=(const char *c);
  String &operator+=(const char c);

  friend bool operator==(const String &lhs, const String &rhs);

private:
  char *_string;
  std::size_t _size;
  std::size_t _length;

  static constexpr std::size_t INITIAL_CAPACITY = 16;
  static constexpr std::size_t GROWTH_FACTOR = 2;
};

String operator+(String lhs, const String &rhs);

String operator+(String lhs, const char *rhs);
String operator+(String lhs, const char rhs);
String operator+(const char *lhs, String rhs);
String operator+(const char lhs, String rhs);

bool operator!=(const String &lhs, const String &rhs);
