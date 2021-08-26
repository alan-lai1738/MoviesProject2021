/*
 * Alan Lai/Steven Chau
 * CSS 343: Movie Project
 * Yusuf Pisan
 * 3/6-14/21
 * Customer.h
 * A customer object with holds an ID, name, history, and borrowed movies stored
 * as a pair.
 */
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Transaction.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Customer {
  friend ostream &operator<<(ostream &os, const Customer &c) {
    os << c.customerFirstName << " " << c.customerSecondName << endl;
    return os;
  }

public:
  // Default constructor takes in F name L name and ID
  Customer(string first, string last, int id);

  // Adds a transaction object to a customer's history.
  void addToHistory(Transaction *t);

  // Getters
  string getFirstName() const;
  string getLastName() const;
  int getCustomerID() const;

  // A method that prints a customer's history to console.
  void printHistory();

  // A method that helps store keep track of borrwed DVDs.
  void addBorrowed(char movieType, int movieIndex);

  // A method that removes a borrowed DVD since it gets returned.
  void returnADVD(char movieType, int movieIndex);

  // Returns true if a customer is borrowing a certain type of movie on a
  // certain index.
  bool isCurrentlyBorrowing(char movieType, int movieIndex);

private:
  int customerID;
  string customerFirstName;
  string customerSecondName;
  vector<Transaction *> history;

  // Chars are either C for Classic, F for Comedy, and D for Drama
  // Ints are for the index of the movie in the Inventory object.
  // This is helpful for inventory to directly access and check movies without
  // having to move them around.
  vector<pair<char, int>> borrowedMovies;
};
#endif