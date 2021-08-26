/*
 * Alan Lai/Steven Chau
 * CSS 343: Movie Project
 * Yusuf Pisan
 * 3/6-14/21
 * Drama.h
 * A child that inherits Movie. Drama Movie uses all stock private data members.
 */
#ifndef DRAMAMOVIE_H
#define DRAMAMOVIE_H
#include "Movie.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class DramaMovie : public Movie {
public:
  DramaMovie(const int &stock, const string &title, const string &director,
             const int &releaseYear)
      : Movie(stock, title, director, releaseYear) {
    this->type = 'D';
  }

  ostream &display(ostream &os) const override {
    os << "[" << title << "] Drama | " << releaseYear << " | By " << director
       << " | " << stock << " copies available / " << borrowed
       << " copies currently being borrowed." << endl;
    return os;
  }

  bool equals(Movie *m) const override {
    return ((type == m->getType()) && (title == m->getTitle()) &&
            (director == m->getDirector()) &&
            (releaseYear == m->getReleaseYear()));
  }

  bool greaterThan(Movie *m) const override { return (!lessThan(m)); }

  // Sorted by director then title
  bool lessThan(Movie *m) const override {
    if (equals(m)) {
      return false;
    }
    if (director != m->getDirector()) {
      return director < m->getDirector();
    }
    if (title != m->getTitle()) {
      return title < m->getTitle();
    }
    return false;
  }
};
#endif
