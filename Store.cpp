#include "Store.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Store::Store() { inv = new Inventory(); }

// adds customers to customerDatabase hashtable
void Store::fillCustomerDatabase(const string &fileName) {
  // open file
  ifstream in(fileName);
  string line; // Line were reading
  if (!in) {
    cout << "Can't open file " << fileName << endl;
  }
  // iterate through lines
  while (!in.eof()) {
    getline(in, line);
    if (line.empty()) { // end loop when reached end of file or break in lines
      break;
    }
    istringstream parseLine(line); // get contents (string) of line
    int custID;                    // customer id
    parseLine >> custID;           // assign custID value
    if (custID > 999 && custID < 10000 && !customerDatabase.contains(custID)) {
      string first, last;         // customer first and last names
      parseLine >> first >> last; // assign first and last values
      Customer *c = new Customer(first, last, custID); // creaate new customer
      customerDatabase.put(custID, c); // add customer to database
    } else {
      cerr << "ERROR: Invalid Customer Id: " << custID << endl;
    }
  }
  in.close();
  // close file reader
}

// adds movies to vector shelves
void Store::stockDVDShelves(const string &fileName) {
  ifstream in(fileName);
  string line; // Line were reading
  if (!in) {
    cout << "Can't open file " << fileName << endl;
  }

  while (!in.eof()) {
    getline(in, line);
    if (line.empty()) {
      break;
    }
    istringstream parseLine(line);
    // tokenize lines to easily separate commas from strings
    string token; // individual strings (words/phrases/numbers) from line
                  // separated with space
    vector<string> tokens;                   // holds all strings
    while (getline(parseLine, token, ',')) { // remove comma
      if (token[0] == ' ')                   // Remove beginning space.
      {
        token.erase(0, 1);
      }
      tokens.push_back(
          token); // push in tokens(strings) without beginning space and comma
    }
    string movieType = tokens[0]; // get movie type from tokens vector
    if (movieType == "C") {       // if movie is classic
      int stock = stoi(tokens[1]);
      string dir = tokens[2];
      string title = tokens[3];
      istringstream ss2(tokens[4]);
      string firstName, lastName, month, year;
      ss2 >> firstName >> lastName >> month >>
          year; // assign these variables appropriate values
      inv->addClassicMovie(
          stock, title, dir, firstName, lastName, stoi(month),
          stoi(
              year)); // create movie using variables and add to classMovieShelf
    } else if (movieType == "F" ||
               movieType ==
                   "D") { // comedy and drama movies contain the same variables
      int stock = stoi(tokens[1]); // convert string to int
      string dir = tokens[2];
      string title = tokens[3];
      int year = stoi(tokens[4]);
      if (movieType == "F") {
        inv->addComedyMovie(stock, title, dir, year);
      } else {
        inv->addDramaMovie(stock, title, dir, year);
      }
    } else {
      cerr << "ERROR: Invalid Movie Type: " << movieType << endl;
    }
  }
}

// creates and executes transactions
void Store::readTransactions(const string &fileName) {
  ifstream in(fileName);
  string line; // Line were reading
  if (!in) {
    cout << "Can't open file " << fileName << endl;
  }
  while (!in.eof()) {
    getline(in, line);
    if (line.empty()) {
      break;
    }
    istringstream parseLine(line);
    string transType;
    parseLine >> transType; // First letter is the Store Transaction Type

    switch (transType[0]) { // switch case for transaction types
    case 'I': {             // Inventory
      displayInventory();
      break;
    }
    case 'H': { // History
      int custID;
      parseLine >> custID; // read customer id
      customerDatabase.get(custID)->printHistory();
      break;
    }
    case 'R': { // Return transaction type
      int custID;
      string mediaType, movieType;
      parseLine >> custID;
      parseLine >> mediaType;
      if (mediaType == "D") {
        parseLine >> movieType;
        if (movieType == "C") {
          int month, year;
          string first, last;
          // C 5 1940 Katherine Hepburn
          parseLine >> month;
          parseLine >> year;
          parseLine >> first;
          parseLine >> last;
          int idx = inv->getClassicIndex(
              month, year, first,
              last);     // get index of movie from the vector shelf
          if (idx == -1) // If Classic movie doesn't exist, error
          {
            cerr << "ERROR: Classic Movie Not Found!" << endl;
          } else // Otherwise, movie exists
          {
            ClassicMovie *c = inv->peekClassicMovie(idx);
            if (customerDatabase.contains(
                    custID)) // If Customer exists, continue
            {
              // check if customer is borrowing the movie
              if (customerDatabase.get(custID)->isCurrentlyBorrowing('C',
                                                                     idx)) {
                inv->returnMovie(movieType, idx);
                customerDatabase.get(custID)->returnADVD(movieType[0], idx);
                Transaction *t = new Transaction(
                    'C', c->getTitle(), c->getDirector(),
                    customerDatabase.get(custID)->getFirstName() + " " +
                        customerDatabase.get(custID)->getLastName(),
                    transType[0]);
                customerDatabase.get(custID)->addToHistory(t);
              } else {
                cerr << "ERROR: "
                     << customerDatabase.get(custID)->getFirstName() << " "
                     << customerDatabase.get(custID)->getLastName()
                     << " is not currently borrowing the classic movie "
                     << c->getTitle() << ", " << c->getDirector()
                     << ", so we can't return it." << endl;
              }
            } else // Otherwise, the customer doesn't exist. Throw an error.
            {
              cerr << "ERROR: Invalid Customer ID: " << custID << endl;
            }
          }
        } else if (movieType == "F") {
          // F You've Got Mail, 1998
          int year;
          string title;
          string token;
          vector<string> tokens;
          while (getline(parseLine, token, ',')) {
            if (token[0] == ' ') // Remove beginning space.
            {
              token.erase(0, 1);
            }
            tokens.push_back(token);
          }
          title = tokens[0];
          year = stoi(tokens[1]);
          int idx = inv->getComedyIndex(year, title);
          if (idx == -1) {
            cerr << "ERROR: Comedy Movie: " << title << ", " << year
                 << " Not Found!" << endl;
          } else {
            ComedyMovie *c = inv->peekComedyMovie(idx);
            if (customerDatabase.contains(
                    custID)) // if customer exists, continue
            {
              if (customerDatabase.get(custID)->isCurrentlyBorrowing(
                      'F', idx)) // if customer is borrowing this movie, we can
                                 // successfully return it
              {
                inv->returnMovie(movieType, idx);
                customerDatabase.get(custID)->returnADVD(movieType[0], idx);
                Transaction *t = new Transaction(
                    'F', c->getTitle(), c->getDirector(),
                    customerDatabase.get(custID)->getFirstName() + " " +
                        customerDatabase.get(custID)->getLastName(),
                    transType[0]);

                customerDatabase.get(custID)->addToHistory(t);
              } else {
                cerr << "ERROR: "
                     << customerDatabase.get(custID)->getFirstName() << " "
                     << customerDatabase.get(custID)->getLastName()
                     << " is not currently borrowing the comedy movie "
                     << c->getTitle() << ", " << c->getDirector()
                     << ", so we can't return it." << endl;
              }
            } else // otherwise error for non-existent ID.
            {
              cerr << "ERROR: Invalid Customer ID: " << custID << endl;
            }
          }
        } else if (movieType == "D") {
          // D Barry Levinson, Good Morning Vietnam,
          string director, title;
          string token;
          vector<string> tokens;
          while (getline(parseLine, token, ',')) {
            if (token[0] == ' ') // Remove beginning space.
            {
              token.erase(0, 1);
            }
            tokens.push_back(token);
          }
          director = tokens[0];
          title = tokens[1];
          int idx = inv->getDramaIndex(director, title);
          if (idx == -1) // If movie not found throw error
          {
            cerr << "ERROR: Drama Movie: " << title << " by " << director
                 << " Not Found!" << endl;
          } else // Otherwise movie exists, continue
          {
            DramaMovie *d = inv->peekDramaMovie(idx);
            if (customerDatabase.contains(
                    custID)) // if customer exists, continue
            {
              if (customerDatabase.get(custID)->isCurrentlyBorrowing('D',
                                                                     idx)) {
                inv->returnMovie(movieType, idx);
                customerDatabase.get(custID)->returnADVD(movieType[0], idx);
                Transaction *t = new Transaction(
                    'D', d->getTitle(), d->getDirector(),
                    customerDatabase.get(custID)->getFirstName() + " " +
                        customerDatabase.get(custID)->getLastName(),
                    transType[0]);

                customerDatabase.get(custID)->addToHistory(t);
              } else {
                cerr << "ERROR: "
                     << customerDatabase.get(custID)->getFirstName() << " "
                     << customerDatabase.get(custID)->getLastName()
                     << " is not currently borrowing the drama movie "
                     << d->getTitle() << ", " << d->getDirector()
                     << ", so we can't return it." << endl;
              }
            } else // throw error for non existing customer
            {
              cerr << "ERROR: Invalid Customer ID: " << custID << endl;
            }
          }
        } else {
          cerr << "ERROR: Invalid Movie Type: " << movieType << endl;
        }
      } // if media type is d
      else {
        cerr << "ERROR: Invalid Media Type:" << mediaType << endl;
      }
      break;
    }
    case 'B': { // Borrow
      int custID;
      string movieType, mediaType;
      parseLine >> custID;
      parseLine >> mediaType;
      if (mediaType == "D") {
        parseLine >> movieType;
        if (movieType == "C") {
          int month, year;
          string first, last;
          // C 5 1940 Katherine Hepburn
          parseLine >> month;
          parseLine >> year;
          parseLine >> first;
          parseLine >> last;
          int idx = inv->getClassicIndex(month, year, first, last);
          if (idx == -1) {
            cerr << "ERROR: Classic Movie Not Found!" << endl;
          } else {
            if (customerDatabase.contains(custID)) {
              if (inv->borrowMovie(movieType, idx)) {
                ClassicMovie *c = inv->peekClassicMovie(idx);
                Transaction *t = new Transaction(
                    'C', c->getTitle(), c->getDirector(),
                    customerDatabase.get(custID)->getFirstName() + " " +
                        customerDatabase.get(custID)->getLastName(),
                    transType[0]);
                customerDatabase.get(custID)->addBorrowed('C', idx);
                customerDatabase.get(custID)->addToHistory(t);
              }
            } else {
              cerr << "ERROR: Invalid Customer ID: " << custID << endl;
            }
          }
        } else if (movieType == "F") {
          // F You've Got Mail, 1998
          int year;
          string title;
          string token;
          vector<string> tokens;
          while (getline(parseLine, token, ',')) {
            if (token[0] == ' ') // Remove beginning space.
            {
              token.erase(0, 1);
            }
            tokens.push_back(token);
          }
          title = tokens[0];
          year = stoi(tokens[1]);
          int idx = inv->getComedyIndex(year, title);
          if (idx == -1) {
            cerr << "ERROR: Comedy Movie: " << title << ", " << year
                 << " Not Found!" << endl;
          } else {
            if (customerDatabase.contains(custID)) {
              if (inv->borrowMovie(movieType, idx)) {
                ComedyMovie *c = inv->peekComedyMovie(idx);
                Transaction *t = new Transaction(
                    'F', c->getTitle(), c->getDirector(),
                    customerDatabase.get(custID)->getFirstName() + " " +
                        customerDatabase.get(custID)->getLastName(),
                    transType[0]);
                customerDatabase.get(custID)->addBorrowed('F', idx);
                customerDatabase.get(custID)->addToHistory(t);
              }
            } else {
              cerr << "ERROR: Invalid Customer ID: " << custID << endl;
            }
          }
        } else if (movieType == "D") {
          // D Barry Levinson, Good Morning Vietnam,
          string director, title;
          string token;
          vector<string> tokens;
          while (getline(parseLine, token, ',')) {
            if (token[0] == ' ') // Remove beginning space.
            {
              token.erase(0, 1);
            }
            tokens.push_back(token);
          }
          director = tokens[0];
          title = tokens[1];
          int idx = inv->getDramaIndex(director, title);
          if (idx == -1) {
            cerr << "ERROR: Drama Movie: " << title << " by " << director
                 << " Not Found!" << endl;
          } else {
            if (customerDatabase.contains(custID)) {
              if (inv->borrowMovie(movieType, idx)) {
                DramaMovie *c = inv->peekDramaMovie(idx);
                Transaction *t = new Transaction(
                    'D', c->getTitle(), c->getDirector(),
                    customerDatabase.get(custID)->getFirstName() + " " +
                        customerDatabase.get(custID)->getLastName(),
                    transType[0]);
                customerDatabase.get(custID)->addBorrowed('D', idx);
                customerDatabase.get(custID)->addToHistory(t);
              }
            } else {
              cerr << "ERROR: Invalid Customer ID: " << custID << endl;
            }
          }
        } else {
          cerr << "ERROR: Invalid Movie Type: " << movieType << endl;
        }
      } else {
        cerr << "ERROR: Invalid Media Type:" << mediaType << endl;
      }
      break;
    }
    default:
      cerr << transType << " is an invalid transaction type." << endl;
      break;
    }
    inv->sortMovies();
  }
}

// Display inventory by outstreaming shelf contents.
void Store::displayInventory() {
  inv->sortMovies();
  cout << *inv;
}
