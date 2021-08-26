/*
 * Alan Lai/Steven Chau
 * CSS 343: Movie Project
 * Yusuf Pisan
 * 3/6-14/21
 * Inventory.h
 * An inventory object which holds our shelves of different Movie DVDs.
 * Mainly consists of ways to add, borrow, and return DVD to shelves. Also
 * allows peeking movies in shelves. Our shelves are done with vectors.
 */
#ifndef INVENTORY_H
#define INVENTORY_H
#include "ClassicMovie.h"
#include "ComedyMovie.h"
#include "DramaMovie.h"
#include "Movie.h"
#include <algorithm>
#include <string>
#include <vector>

// Outstreams all movies from every shelf. This is called when using 'I' in
// commands.
class Inventory {
  friend ostream &operator<<(ostream &os, const Inventory &inv) {
    os << "____________________[Viewing Inventory]____________________" << endl;
    for (auto i : inv.comedyMovieShelf) {
      os << *(i);
    }
    for (auto j : inv.dramaMovieShelf) {
      os << *(j);
    }
    for (auto k : inv.classicMovieShelf) {
      os << *(k);
    }
    return os;
  }

public:
  // Adders: Allows us to construct and add with parameters taking from file.
  // These methods are useful for store when reading files and parsing tokens.
  // The tokens imitate movie constructors.
  void addClassicMovie(const int &stock, const string &title,
                       const string &director, const string &majActorFirstName,
                       const string &majActorLastName, const int &relMonth,
                       const int &relYear);

  void addComedyMovie(const int &stock, const string &title,
                      const string &director, const int &releaseYear);

  void addDramaMovie(const int &stock, const string &title,
                     const string &director, const int &releaseYear);

  // Borrow/Return Movie methods that take in the type of movie as a string(for
  // convenience). Finds index in a certain shelf. Returns false for borrow.
  // Errors are thrown if not found.
  bool borrowMovie(const string &movieType, const int &index);
  void returnMovie(const string &movieType, const int &index);

  // Allows peeking shelves at certain indexes. Useful for getting movie
  // information.
  ClassicMovie *peekClassicMovie(const int &index) const;
  ComedyMovie *peekComedyMovie(const int &index) const;
  DramaMovie *peekDramaMovie(const int &index) const;

  // Find movies by their parameters. If a match is found, returns index.
  // Otherwise, -1
  int getClassicIndex(const int &month, const int &year, const string &first,
                      const string &last);
  int getComedyIndex(const int &year, const string &title);
  int getDramaIndex(const string &director, const string &title);

  // A method that sorts all movie shelves.
  void sortMovies();

private:
  // vectors to hold movies based on their genre
  vector<ClassicMovie *> classicMovieShelf;
  vector<ComedyMovie *> comedyMovieShelf;
  vector<DramaMovie *> dramaMovieShelf;

  // Sort helper methods to short movie shelves.
  static bool sortByDrama(DramaMovie *a, DramaMovie *b);
  static bool sortByComedy(ComedyMovie *a, ComedyMovie *b);
  static bool sortByClassic(ClassicMovie *a, ClassicMovie *b);
};
#endif