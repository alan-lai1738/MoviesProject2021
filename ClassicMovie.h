/*
 * Alan Lai/Steven Chau
 * CSS 343: Movie Project
 * Yusuf Pisan
 * 3/6-14/21
 * ClassicMovie.h
 * A child that inherits Movie. Classic Movie has a major actor and release
 * month, special to Classic.
 */
#ifndef CLASSICMOVIE_H
#define CLASSICMOVIE_H
#include "Movie.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class ClassicMovie : public Movie {
public:
  // Default constructor
  ClassicMovie(const int &stock, const string &title, const string &director,
               const string &majActorFirstName, const string &majActorLastName,
               const int &relMonth, const int &relYear)
      : Movie(stock, title, director, relYear) {
    this->majorActorFirst = majActorFirstName;
    this->majorActorLast = majActorLastName;
    this->releaseMonth = relMonth;
    this->type = 'C';
  }

  // copy constructor
  explicit ClassicMovie(ClassicMovie *other)
      : Movie(other->getStockAmt(), other->getTitle(), other->getDirector(),
              other->getReleaseYear()) {
    this->releaseMonth = other->getReleaseMonth();
    this->majorActorFirst = other->getMajorActorFirst();
    this->majorActorLast = other->getMajorActorLast();
    this->type = 'C';
  }
  // Getters
  int getReleaseMonth() const { return releaseMonth; }
  string getMajorActorFirst() const { return majorActorFirst; }
  string getMajorActorLast() const { return majorActorLast; }

  ostream &display(ostream &os) const override {
    os << "[" << title << "] Classic | " << releaseMonth << "/" << releaseYear
       << " | By " << director << " | "
       << "Featuring " << majorActorFirst << " " << majorActorLast << " | "
       << stock << " copies available / " << borrowed
       << " copies currently being borrowed." << endl;
    return os;
  }

  bool equals(Movie *other) const override {
    assert(other != nullptr);
    auto otherMovie = dynamic_cast<ClassicMovie *>(other);
    return (title == otherMovie->title && director == otherMovie->director &&
            releaseMonth == otherMovie->releaseMonth &&
            releaseYear == otherMovie->releaseYear &&
            majorActorFirst == otherMovie->majorActorFirst &&
            majorActorLast == otherMovie->majorActorLast);
  }

  // greaterThan function
  bool greaterThan(Movie *other) const override {
    if (equals(other)) {
      return false;
    }
    return (!lessThan(other));
  }

  // less Than function for classic: Compares release date then actor name.
  bool lessThan(Movie *other) const override {
    assert(other != nullptr);
    auto rhs = dynamic_cast<ClassicMovie *>(other);
    if (equals(other)) {
      return false;
    }
    if (releaseYear != rhs->getReleaseYear()) {
      return releaseYear < rhs->getReleaseYear();
    }
    if (releaseMonth != rhs->getReleaseMonth()) {
      return releaseMonth < rhs->getReleaseMonth();
    }
    if (releaseMonth != rhs->getReleaseMonth()) {
      return releaseMonth < rhs->getReleaseMonth();
    }
    string actorName = majorActorFirst + " " + majorActorLast;
    string actorNameRHS =
        rhs->getMajorActorFirst() + " " + rhs->getMajorActorLast();
    if (actorName != actorNameRHS) {
      return actorName < actorNameRHS;
    }
    return false;
  }

private:
  string majorActorFirst;
  string majorActorLast;
  int releaseMonth;
};
#endif