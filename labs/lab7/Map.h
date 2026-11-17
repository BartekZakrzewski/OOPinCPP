#pragma once
#include <cstring>
#define ll long long

template <typename K, typename V> class Map {
public:
  Map<K, V>() {
    keys = new K();
    values = new V();
    n = 0;
  }

  Map<K, V>(const Map<K, V> &other) {
    delete[] keys;
    delete[] values;
    keys = new K[other.n]();
    std::memcpy(keys, other.keys, n);
    values = new V[other.n]();
    std::memcpy(values, other.values, n);
    n = other.n;
  }

  Map<K, V> &operator=(const Map<K, V> &other) {
    delete[] keys;
    delete[] values;
    keys = new K[other.n]();
    std::memcpy(keys, other.keys, n);
    values = new V[other.n]();
    std::memcpy(values, other.values, n);
    n = other.n;
  }

  V *find(K key) {
    // TODO error handling
    for (ll index = 0; index < n; index++) {
      if (keys[index] == key) {
        return &values[index];
      }
    }
  }

  void add(K key, V value) {
    ll index = findKeyIndex(key);
    if (index >= 0) {
      values[index] = value;
    } else {
      keys[n] = key;
      values[n++] = value;
    }
  }

private:
  K *keys;
  V *values;
  ll n;

  ll findKeyIndex(K key) {
    for (ll index = 0; index < n; index++) {
      if (keys[index] == key) {
        return index;
      }
    }
    return -1;
  }
};
