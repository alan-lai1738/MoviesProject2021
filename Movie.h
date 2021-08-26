/*
 * Alan Lai/Steven Chau
 * CSS 343: Movie Project
 * Yusuf Pisan
 * 3/6-14/21
 * Movie.h
 * Movie parent class consists off stock, director, title, release yr, type, and
 * borrowed amount.
 */
#ifndef MOVIE_H
#define MOVIE_H

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Movie {
  // To be overloaded in subclass: Classic/Drama/Comedy may have different
  // outputs depending on data values
  friend ostream &operator<<(ostream &os, const Movie &rhs) {
    // Calls display to update oustream
    return rhs.display(os);
  }

protected:
  int stock;
  string director;
  string title;
  int releaseYear;
  char type = 'z'; // To avoid clang-tidy. Always initialized as something else.
  int borrowed;

  // To be implemented in children: display
  virtual ostream &display(ostream &os) const = 0;
  // To be implemented in children: comparator functions
  virtual bool equals(Movie *m) const = 0;
  virtual bool lessThan(Movie *m) const = 0;
  virtual bool greaterThan(Movie *m) const = 0;

public:
  // Default constructor
  Movie(const int &stock, const string &title, const string &director,
        const int &releaseYear) {
    this->stock = stock;
    this->title = title;
    this->director = director;
    this->releaseYear = releaseYear;
    this->borrowed = 0;
  }

  // Setters and getters for values
  string getDirector() const { return director; }

  string getTitle() const { return title; }

  int getReleaseYear() const { return releaseYear; }

  int getStockAmt() const { return stock; }

  char getType() const { return type; }

  void setStock(int amt) { this->stock = amt; }

  void setBorrowed(int amt) { borrowed = amt; }

  int getBorrowedAmt() const { return borrowed; }
};

#endif