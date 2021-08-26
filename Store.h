/*
 * Alan Lai/Steven Chau
 * CSS 343: Movie Project
 * Yusuf Pisan
 * 3/6-14/21
 * Store.h
 * Core class of the program
 * Contains all file readers and constructs all relevant objects (movies,
 * customers, transactions, inventory, HashTable)
 */
#ifndef STORE_H
#define STORE_H
#include "Customer.h"
#include "HashTable.h"
#include "Inventory.h"
#include "Movie.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Store {
public:
  Store();
  string getHistory(const int &id) const;
  // file reader for movies.txt
  void stockDVDShelves(const string &fileName);
  // file reader for customer.txt
  void fillCustomerDatabase(const string &fileName);
  // file reader for commands.txt
  void readTransactions(const string &fileName);
  void displayInventory();

private:
  // holds all customer objects, customer IDs are used as the key
  HashTable<int, Customer *> customerDatabase;
  // Inventory object to store and maintain all movie objects
  Inventory *inv;
};
#endif