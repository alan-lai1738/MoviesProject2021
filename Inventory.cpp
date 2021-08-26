/*
 * Alan Lai/Steven Chau
 * CSS 343: Movie Project
 * Yusuf Pisan
 * 3/6-14/21
 * Inventory.cpp
 * An inventory object which holds our shelves of different Movie DVDs.
 * Mainly consists of ways to add, borrow, and return DVD to shelves. Also
 * allows peeking movies in shelves. Our shelves are done with vectors.
 */
#include "Inventory.h"

// Add movie methods
void Inventory::addDramaMovie(const int &stock, const string &title,
                              const string &director, const int &releaseYear) {
  auto d = new DramaMovie(stock, title, director, releaseYear);
  for (auto &i : dramaMovieShelf) { // Checks to see if a movie exists already.
    if (d->equals(i)) {             // If it does exist
      i->setStock(d->getStockAmt() +
                  i->getStockAmt()); // Just update that movie's stock amount.
      return;
    }
  }
  dramaMovieShelf.push_back(d); // Otherwise, add this movie to the drama shelf.
}

// The same for the other two shelves.
void Inventory::addComedyMovie(const int &stock, const string &title,
                               const string &director, const int &releaseYear) {
  auto f = new ComedyMovie(stock, title, director, releaseYear);
  for (auto &i : comedyMovieShelf) {
    if (f->equals(i)) {
      i->setStock(f->getStockAmt() + i->getStockAmt());
      return;
    }
  }
  comedyMovieShelf.push_back(f);
}

void Inventory::addClassicMovie(const int &stock, const string &title,
                                const string &director,
                                const string &majActorFirstName,
                                const string &majActorLastName,
                                const int &relMonth, const int &relYear) {
  auto c = new ClassicMovie(stock, title, director, majActorFirstName,
                            majActorLastName, relMonth, relYear);
  for (auto &i : classicMovieShelf) {
    if (c->equals(i)) {
      i->setStock(c->getStockAmt() + i->getStockAmt());
      return;
    }
  }
  classicMovieShelf.push_back(c);
}

// Peek movies by index
ClassicMovie *Inventory::peekClassicMovie(const int &index) const {
  if (index >= classicMovieShelf.size() ||
      index < 0) { // If index doesn't exist, error and return nullptr.
    cerr << "ERROR: Index exceeds ClassicMovieShelf size" << endl;
    return nullptr;
  }
  return classicMovieShelf[index];
}

ComedyMovie *Inventory::peekComedyMovie(const int &index) const {
  if (index >= comedyMovieShelf.size() || index < 0) {
    cerr << "ERROR: Index exceeds ComedyMovieShelf size" << endl;
    return nullptr;
  }
  return comedyMovieShelf[index];
}

DramaMovie *Inventory::peekDramaMovie(const int &index) const {
  if (index >= dramaMovieShelf.size() || index < 0) {
    cerr << "ERROR: Index exceeds DramaMovieShelf size" << endl;
    return nullptr;
  }
  return dramaMovieShelf[index];
}

// Getters: Search a movie shelf by their parameters/data. If a match is found,
// index will be returned.
int Inventory::getClassicIndex(const int &month, const int &year,
                               const string &first, const string &last) {
  for (int i = 0; i < classicMovieShelf.size(); i++) {
    if (classicMovieShelf[i]->getReleaseMonth() == month &&
        classicMovieShelf[i]->getReleaseYear() == year &&
        classicMovieShelf[i]->getMajorActorFirst() == first &&
        classicMovieShelf[i]->getMajorActorLast() == last) {
      return i;
    }
  }
  return -1;
}

int Inventory::getComedyIndex(const int &year, const string &title) {
  for (int i = 0; i < comedyMovieShelf.size(); i++) {
    if (comedyMovieShelf[i]->getReleaseYear() == year &&
        comedyMovieShelf[i]->getTitle() == title) {
      return i;
    }
  }
  return -1;
}

int Inventory::getDramaIndex(const string &director, const string &title) {
  for (int i = 0; i < dramaMovieShelf.size(); i++) {
    if (dramaMovieShelf[i]->getDirector() == director &&
        dramaMovieShelf[i]->getTitle() == title) {
      return i;
    }
  }
  return -1;
}

// Borrow a movie by type and index.
bool Inventory::borrowMovie(const string &movieType, const int &index) {
  if (movieType == "C") {
    int stockAmt = classicMovieShelf[index]->getStockAmt();
    if (stockAmt >= 1) { // If there stock remaining, allow execution of borrow.
                         // This also means updating borrowed amount.
      classicMovieShelf[index]->setStock(
          classicMovieShelf[index]->getStockAmt() - 1);
      classicMovieShelf[index]->setBorrowed(
          classicMovieShelf[index]->getBorrowedAmt() + 1);
      return true;
    } // Otherwise throw an error for insufficient stock remaining.
    cerr << "ERROR: Insufficient stock of "
         << classicMovieShelf[index]->getTitle() << ", "
         << classicMovieShelf[index]->getReleaseMonth() << " "
         << classicMovieShelf[index]->getReleaseYear() << endl;
    return false;
  }
  if (movieType == "F") {
    int stockAmt = comedyMovieShelf[index]->getStockAmt();
    if (stockAmt >= 1) {
      comedyMovieShelf[index]->setStock(comedyMovieShelf[index]->getStockAmt() -
                                        1);
      comedyMovieShelf[index]->setBorrowed(
          comedyMovieShelf[index]->getBorrowedAmt() + 1);
      return true;
    }
    cerr << "ERROR: Insufficient stock of "
         << comedyMovieShelf[index]->getTitle() << ", "
         << comedyMovieShelf[index]->getReleaseYear() << endl;
    return false;
  }
  if (movieType == "D") {
    int stockAmt = dramaMovieShelf[index]->getStockAmt();
    if (stockAmt >= 1) {
      dramaMovieShelf[index]->setStock(dramaMovieShelf[index]->getStockAmt() -
                                       1);
      dramaMovieShelf[index]->setBorrowed(
          dramaMovieShelf[index]->getBorrowedAmt() + 1);
      return true;
    }
    cerr << "ERROR: Insufficient stock of "
         << dramaMovieShelf[index]->getTitle() << ", "
         << dramaMovieShelf[index]->getReleaseYear() << endl;
  }
  return false;
}

// Same except it returns a movie.
void Inventory::returnMovie(const string &movieType, const int &index) {
  if (movieType == "C") {
    classicMovieShelf[index]->setStock(classicMovieShelf[index]->getStockAmt() +
                                       1);
    classicMovieShelf[index]->setBorrowed(
        classicMovieShelf[index]->getBorrowedAmt() - 1);
  }
  if (movieType == "F") {
    comedyMovieShelf[index]->setStock(comedyMovieShelf[index]->getStockAmt() +
                                      1);
    comedyMovieShelf[index]->setBorrowed(
        comedyMovieShelf[index]->getBorrowedAmt() - 1);
  }
  if (movieType == "D") {
    dramaMovieShelf[index]->setStock(dramaMovieShelf[index]->getStockAmt() + 1);
    dramaMovieShelf[index]->setBorrowed(
        dramaMovieShelf[index]->getBorrowedAmt() - 1);
  }
}

// Sort helpers: Useful with the C++ sort method. These use the lessThan from
// each Movie class.
bool Inventory::sortByDrama(DramaMovie *a, DramaMovie *b) {
  return a->lessThan(b);
}

bool Inventory::sortByComedy(ComedyMovie *a, ComedyMovie *b) {
  return a->lessThan(b);
}

bool Inventory::sortByClassic(ClassicMovie *a, ClassicMovie *b) {
  return a->lessThan(b);
}

// Sorts all shelves.
void Inventory::sortMovies() {
  std::sort(classicMovieShelf.begin(), classicMovieShelf.end(), sortByClassic);
  std::sort(comedyMovieShelf.begin(), comedyMovieShelf.end(), sortByComedy);
  std::sort(dramaMovieShelf.begin(), dramaMovieShelf.end(), sortByDrama);
}
