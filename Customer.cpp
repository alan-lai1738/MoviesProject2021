/*
 * Alan Lai/Steven Chau
 * CSS 343: Movie Project
 * Yusuf Pisan
 * 3/6-14/21
 * Customer.cpp
 * Implements methods required for Customer
 */
#include "Customer.h"

Customer::Customer(string first, string last, int id) {
  customerFirstName = std::move(first);
  customerSecondName = std::move(last);
  customerID = id;
}

void Customer::addToHistory(Transaction *t) { history.push_back(t); }

string Customer::getFirstName() const { return customerFirstName; }

string Customer::getLastName() const { return customerSecondName; }

int Customer::getCustomerID() const { return customerID; }

void Customer::printHistory() {

  cout << "____________________[Displaying " << customerFirstName << " "
       << customerSecondName << "'s History]____________________" << endl;
  if (history.empty()) {
    cout << "History is Empty!" << endl;
  } else {
    for (int i = history.size() - 1; i >= 0; i--) {
      cout << *history[i];
    }
  }
}

void Customer::addBorrowed(char movieType, int movieIndex) {
  borrowedMovies.emplace_back(make_pair(movieType, movieIndex));
}

void Customer::returnADVD(char movieType, int movieIndex) {
  for (int i = 0; i < borrowedMovies.size(); i++) {
    if (borrowedMovies[i].first == movieType &&
        borrowedMovies[i].second == movieIndex) {
      borrowedMovies.erase(borrowedMovies.begin() + i);
      return;
    }
  }
}

bool Customer::isCurrentlyBorrowing(char movieType, int movieIndex) {
  return count(borrowedMovies.begin(), borrowedMovies.end(),
               make_pair(movieType, movieIndex)) != 0;
}