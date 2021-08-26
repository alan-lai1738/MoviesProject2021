/*
 * Alan Lai/Steven Chau
 * CSS 343: Movie Project
 * Yusuf Pisan
 * 3/6-14/21
 * HashTable.h
 * Custom implemented hashtable
 * Holds keys and values; does not accept duplicate keys
 * Utilizes two vectors to hold keys and values
 */
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;
template <typename K, typename V> class HashTable {
  friend ostream &operator<<(ostream &os, const HashTable &h) {
    for (int i = 0; i < h.keys.size(); i++) {
      os << "[" << h.keys[i] << "]: " << h.values[i] << endl;
    }
    return os;
  }

public:
  // add item to hashtable
  void put(K &key, V &value) {
    if (find(keys.begin(), keys.end(), key) !=
        keys.end()) // If our hashtable contains the key
    {
      int index = getIndex(
          key); // We get the key's index, and update the value for that key.
      values[index] = value;
    } else {
      keys.push_back(key);
      values.push_back(value);
    }
  }
  // remove item from hashtable
  void remove(K key) {
    if (!contains(key)) {
      return;
    }
    int index = getIndex(key);
    keys.erase(keys.begin() + index);
    values.erase(values.begin() + index);
  }
  // check if item is in hashtable
  bool contains(K key) {
    return find(keys.begin(), keys.end(), key) != keys.end();
  }
  // retrieve item
  V &get(K key) {
    int index = getIndex(key);
    return values[index];
  }
  // check if hashtable is empty
  bool empty() { return (keys.empty()); }

  int size() { return keys.size(); }

private:
  // vectors to hold keys and values, indexes for keys and values are updated
  // concurrently as items are added
  vector<K> keys;
  vector<V> values;
  // retrive index of item based on key
  int getIndex(K key) {
    auto it = find(keys.begin(), keys.end(), key);
    if (it != keys.end()) {
      int index = it - keys.begin();
      return index;
    }
    return -1;
  }
};
#endif
