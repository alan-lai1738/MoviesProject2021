/*
 * Alan Lai/Steven Chau
 * CSS 343: Movie Project
 * Yusuf Pisan
 * 3/6-14/21
 * Transaction.h
 * A transaction class that keeps track of movie information and customer
 * information. All stored as string like a receipt
 */
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <string>
using namespace std;
class Transaction {
  // Outstream operator prints transaction info. Useful for customer.
  friend ostream &operator<<(ostream &os, const Transaction &rhs) {
    os << rhs.customerInvolved << " " << rhs.transactionType << "ed "
       << "'" << rhs.movieTitle << "' which is a " << rhs.movieType
       << " movie by " << rhs.director << endl;
    return os;
  }

public:
  // Default constructor
  Transaction(const char &movType, const string &movTitle,
              const string &dirName, const string &customerName,
              const char &type);

private:
  string movieType;
  string movieTitle;
  string director;

  string customerInvolved;
  string transactionType;
};

#endif
