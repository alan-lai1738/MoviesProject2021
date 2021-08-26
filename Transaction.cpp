/*
 * Alan Lai/Steven Chau
 * CSS 343: Movie Project
 * Yusuf Pisan
 * 3/6-14/21
 * Transaction.cpp
 * A transaction class that keeps track of movie information and customer
 * information. All stored as string like a receipt
 */
#include "Transaction.h"
#include "Movie.h"

// Default Constructor
Transaction::Transaction(const char &movType, const string &movTitle,
                         const string &dirName, const string &customerName,
                         const char &type) {
  switch (movType) {
  case 'F':
    movieType = "Comedy";
    break;
  case 'C':
    movieType = "Classic";
    break;
  case 'D':
    movieType = "Drama";
    break;
  default:
    cerr << "ERROR: Invalid Movie Type: " << movieType << endl;
    break;
  }
  movieTitle = movTitle;
  director = dirName;
  customerInvolved = customerName;
  if (type == 'B') {
    transactionType = "borrow";
  } else if (type == 'R') {
    transactionType = "return";
  }
}
