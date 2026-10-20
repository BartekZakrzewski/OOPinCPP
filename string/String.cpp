#include "String.h"
#include <cstddef>
#include <cstdlib>

String::String() {
  _string = new char[INITIAL_CAPACITY]();
  _size = INITIAL_CAPACITY;
  _length = 0;
}
String::String(char *s) {
  _size = 0;
  while (s[_size] != '\0')
    _size++;
  _string = new char[_size]();
  _string = s;
  _length = _size;
}
String::String(char c) {
  _size = 1;
  _string = new char[_size]();
  _string[0] = c;
  _length = _size;
}
String::String(const String &other)
    : _size(other._size), _length(other._length), _string(other._string) {}
String &String::operator=(const String &other) {
  delete[] _string;
  _string = new char[other._size]();
  _string = other._string;
  _size = other._size;
  _length = other._length;
  return *this;
}
String::~String() { delete[] _string; }

char &String::operator[](int x) {
  if (x >= _length)
    throw;
  return *(_string + x);
}

String &String::operator+=(const String &other) {
  std::size_t new_size = other._length + _length;
  char *tmp =
      static_cast<char *>(std::realloc(_string, new_size * sizeof(char)));
  if (tmp == nullptr)
    throw;
  _string = tmp;
  for (std::size_t i = 0; i < other._length; i++) {
    _string[_length - 1 + i] = other._string[i];
  }
  _size = new_size;
  _length = new_size;
  return *this;
}

String &String::operator+=(const char *c) {
  std::size_t new_size = 0;
  while (*(c + new_size) != '\0')
    new_size++;
  char *tmp = static_cast<char *>(
      std::realloc(_string, (new_size + _length) * sizeof(char)));
  if (tmp == nullptr)
    throw;
  _string = tmp;
  for (std::size_t i = 0; i < new_size; i++) {
    _string[_length - 1 + i] = *(c + i);
  }
  _size = new_size + _length;
  _length = _size;
  return *this;
}

String &String::operator+=(const char c) {
  std::size_t new_size = _length + 1;
  char *tmp =
      static_cast<char *>(std::realloc(_string, new_size * sizeof(char)));
  if (tmp == nullptr)
    throw;
  _string = tmp;
  _string[new_size - 1] = c;
  _size = new_size;
  _length = _size;
  return *this;
}

bool operator==(const String &lhs, const String &rhs) {
  if (lhs._length != rhs._length)
    return false;
  for (std::size_t i = 0; i < lhs._length; i++) {
    if (lhs._string[i] != rhs._string[i])
      return false;
  }
  return true;
}

String operator+(String lhs, const String &rhs) { return lhs += rhs; }

String operator+(String lhs, const char *rhs) { return lhs += rhs; }
String operator+(String lhs, const char rhs) { return lhs += rhs; }
String operator+(const char *lhs, String rhs) { return rhs += lhs; }
String operator+(const char lhs, String rhs) { return rhs += lhs; }

bool operator!=(const String &lhs, const String &rhs) { return !(lhs == rhs); }
