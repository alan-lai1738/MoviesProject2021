
/**
 * Driver for starting movie store tests
 */
#include "ClassicMovie.h"
#include "ComedyMovie.h"
#include "Customer.h"
#include "DramaMovie.h"
#include "HashTable.h"
#include "Movie.h"
#include "Store.h"
#include "Transaction.h"
#include <iostream>
#include <string>
using namespace std;

// forward declaration, implementation in store_test.cpp
void testAll();

int main() {
  testAll();
  cout << "Done." << endl;
  // cout << "test" << endl;
  /*Store s;
  s.fillCustomerDatabase("data4customers.txt");
  s.stockDVDShelves("data4movies.txt");
  s.readTransactions("data4commands.txt");
  // s.fillCustomerDatabase("AlanCustomers.txt");
  s.stockDVDShelves("AlanMovies.txt");
  s.readTransactions("AlanCommands.txt");*/

  /* Store s;
   s.fillCustomerDatabase("AlanCustomers.txt");
   s.stockDVDShelves("AlanMovies.txt");
   s.readTransactions("AlanCommands.txt");
   s.displayInventory();
   */
  return 0;
}

/* ClassicMovie classic(2000, "YuruCamp", "Rin Shima", "Rin", "Shima", 3, 2021);
  ComedyMovie ourMovie2(20, "C", "Steven Hoc Chau", 1999);
  ComedyMovie ourMovie4(203, "B", "St123even Hoc Chau", 19939);
  //DramaMovie ourMovie(35, "The Day I was Born", "Steven Hoc Chau", 1999);

  DramaMovie titanic(15, "Titanic", "Bob Mcadoo", 1996);
  //DramaMovie: (int stock, string title, string director, int releaseYear)
  //ClassicMovie: (int stock, string title, string director, string
 majActorFirstName, string majActorLastName, int relMonth, int relYear;)
 //cout << classic.getDirector()
  ClassicMovie classic2(13255, "YuruCamp2", "Aoi Inuyama", "Aoi", "Inuyama", 3,
 2017);


  //cout << classic.equals(&classic2);
  cout << classic.lessThan(&classic2) << endl;
  cout << classic << endl;
  cout << classic2 << endl;
  cout << titanic << endl;
  cout << ourMovie2 << endl;

  cout << (ourMovie2 > ourMovie4) << endl;*/

/*ComedyMovie ourMovie2(20, "MovieTitle", "Steven Hoc Chau", 1999);
//BSTree<Movie> comedyTree;
//comedyTree.insert(&ourMovie2);
// comedyTree.printTree();

Transaction t('C', "Yuru Camp", "Rin Shima", "Hubby", 'B');
cout << t << endl;

Customer c("Hubby", "Bubby", 1234);
c.addToHistory(t);
c.printHistory();
int one = 1;
string rin = "rin";
HashTable<int, string> h;
h.put(one, rin);
int two = 2;
int three = 3;
string b = "nadeshiko";
string d  ="aoi";
h.put(two, b);
h.put(three, d);
h.put(two, d);

cout << h;

Store s;
s.fillCustomerDatabase("data4customers.txt");
s.stockDVDShelves("data4movies.txt");*/