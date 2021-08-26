/**
 * Testing ass4 movie store functions
 *
 * @author Yusuf Pisan
 * @date 19 Jan 2019
 */

#include "ClassicMovie.h"
#include "ComedyMovie.h"
#include "Customer.h"
#include "DramaMovie.h"
#include "HashTable.h"
#include "Store.h"
#include "Transaction.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

void testMovies() {
  cout << "Running movie tests" << endl;
  // CLASSIC TESTS
  ClassicMovie c(5, "ClassicMovie Title", "Rin Shima", "Rin", "Shima", 5, 2000);
  assert(c.getStockAmt() == 5);
  assert(c.getDirector() == "Rin Shima");
  assert(c.getMajorActorFirst() == "Rin");
  assert(c.getMajorActorLast() == "Shima");
  assert(c.getReleaseMonth() == 5);
  assert(c.getReleaseYear() == 2000);
  ClassicMovie c2(15, "Another Classic", "Rin Shima", "Rin", "Shima", 5, 1995);
  ClassicMovie c3(15, "Another Classic", "Rin Shima", "Rin", "Shima", 5, 1995);
  assert(c.greaterThan(&c2) == true);
  assert(c.lessThan(&c2) == false);
  assert(c.equals(&c2) == false);
  assert(c3.equals(&c2) == true);
  // DRAMA TESTS
  DramaMovie d(10, "Yuru Camp S2", "Rin Shima", 2021);
  DramaMovie d2(30, "BanG Dream!", "Kasumi Toyama", 2019);
  DramaMovie d3(30, "BanG Dream!", "Kasumi Toyama", 2019);
  assert(d.getStockAmt() == 10);
  assert(d.getDirector() == "Rin Shima");
  assert(d.getReleaseYear() == 2021);
  assert(d.greaterThan(&d2) == true);
  assert(d.lessThan(&d2) == false);
  assert(d.equals(&d2) == false);
  assert(d3.equals(&d2) == true);
  // COMEDY TESTS
  ComedyMovie funny(50, "Funny Movie", "Funny Guy", 9999);
  ComedyMovie funny2(50, "Funny Movie", "Funny Guy", 9999);
  assert(funny.getStockAmt() == 50);
  assert(funny.getTitle() == "Funny Movie");
  assert(funny.getDirector() == "Funny Guy");
  assert(funny.getReleaseYear() == 9999);
  assert(funny.equals(&funny2));
  ComedyMovie funny3(50, "A Time To Laugh", "Funny Director", 1995);
  ComedyMovie funny4(50, "A Time To Laugh", "Funny Director", 1997);
  assert(funny.equals(&funny4) == false);
  assert(funny2.greaterThan(&funny3) == true);
  assert(funny3.lessThan(&funny4) == true);

  cout << "Movie tests passed" << endl;
}

void testHashTable() {
  cout << "Running HashTable tests" << endl;
  HashTable<char, string> steam;
  assert(steam.empty() == true);
  char s = 'S';
  char t = 'T';
  char e = 'E';
  char a = 'A';
  char m = 'M';
  string s1 = "Science";
  string s2 = "Technology";
  string s3 = "Engineering";
  string s4 = "Art";
  string s5 = "Mathematics";
  steam.put(s, s1);
  steam.put(t, s2);
  steam.put(e, s3);
  steam.put(a, s4);
  steam.put(m, s5);
  assert(steam.get(s) == "Science");
  assert(steam.get(e) == "Engineering");
  string s6 = "Math";
  assert(steam.contains(a) == true);
  assert(steam.get(m) == "Mathematics");
  steam.put(m, s6);
  assert(steam.get(m) == "Math");
  assert(steam.empty() == false);
  assert(steam.size() == 5);
  steam.remove(s);
  assert(steam.size() == 4);
  assert(steam.contains(s) == false);
  cout << "HashTable tests passed" << endl;
}

void testCustomer() {
  cout << "Running customer tests" << endl;
  Customer *rin = new Customer("Rin", "Shima", 0000);
  // Transaction *t = new Transaction('F',"BanG Dream!", "Kasumi Toyama", "Rin
  // Shima",'B');
  rin->addBorrowed('C', 1);

  assert(rin->getCustomerID() == 0000);
  assert(rin->getLastName() == "Shima");
  assert(rin->getFirstName() == "Rin");
  assert(rin->isCurrentlyBorrowing('C', 1) == true);
  rin->returnADVD('C', 1);
  assert(rin->isCurrentlyBorrowing('C', 1) == false);
  // cout << *t << endl;
  cout << "Customer tests passed" << endl;
}

void testStoreAndInventory() {
  Store s;
  s.fillCustomerDatabase("AlanCustomers.txt");
  s.stockDVDShelves("AlanMovies.txt");
  s.readTransactions("AlanCommands.txt");
  cout << "Store tests ran" << endl;
}

void testFinal() {
  Store s;
  s.fillCustomerDatabase("data4customers.txt");
  s.stockDVDShelves("data4movies.txt");
  s.readTransactions("data4commands.txt");
  cout << "testFinal() tests ran" << endl;
}

void testAll() {
  testMovies();
  testHashTable();
  testCustomer();
  // testStoreAndInventory();
  testFinal();
}
