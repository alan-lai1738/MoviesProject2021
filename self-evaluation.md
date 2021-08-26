# Self-Evaluation

## Name(s): 

Out of 25 points. Use output.txt created using 
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes

- If the program does not compile or gives a segmentation error when run, 
the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: 0

- -2 for each functionality not implemented

For each command, state Full, Partial or None to indicate 
if it has been fully, partially or not implemented at all.
Explain any partial implementations.

Inventory: Full
History: Full
Borrow: Full
Return: Full


Q: -1 for each compilation warning, min -3: 0

- Check under *1. Compiles without warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: 0

- Check under *3. clang-tidy warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: 0

- Check under *4. clang-format does not find any formatting issues*


Q: -2 for any detected memory leak: -2

- Check under *5. No memory leaks using g++*
- Check under *6. No memory leaks using valgrind*

Q: Do the tests sufficiently test the code: 0

- -1 for each large block of code not executed
- -2 for each function that is never called when testing
- Check under *7. Tests have full code coverage* paying attention to *The lines below were never executed*

Q: Are all functions in .h and .cpp file documents (min -3): 0

- -1 for each function not documented

## Location of error message or functionality

State the file and function where the information can be found

invalid command code: Store.cpp under readTransactions 

invalid movie type: Store.cpp under stockDVDShelves (line 94) and readTransactions (line 274)

invalid customer ID: Store.cpp under fillCustomerDatabase
 
invalid movie: Store.cpp under readTransactions (line 146, 193, 242)

factory classes: N/A

hashtable: HashTable.h, used to store customers. (explain what the hashtable is used for)

container used for comedy movies: Inventory.h, vector<ComedyMovie *> comedyMovieShelf (line 78)

function for sorting comedy movies: Inventory.h, sortByComedy(ComedyMovie *a, ComedyMovie *b) (line 83)

function where comedy movies are sorted: Inventory.h, sortMovies() (line 73)

functions called when retrieving a comedy movie based on title and year: getComedyIndex() (line 97) in Inventory.cpp, which can be used for peekComedyMovie() (line 66)

functions called for retrieving and printing customer history: printHistory() in line 25 of Customer.cpp

container used for customer history: vector<pair<char, int>> borrowedMovies; in line 60 of Customer.h

functions called when borrowing a movie: borrowMovie() in Inventory.cpp, line 118.
Calls movie's getters and setters for stock/borrowed amounts.

explain borrowing a movie that does not exist: Store.cpp, readTransaction() line 299, 332, 366

explain borrowing a movie that has 0 stock: borrowMovie() in Inventory.cpp line 129, 144, 158

explain returning a movie that customer has not checked out: Store.cpp, readTransactions line 164, 213, 242

any static_cast or dynamic_cast used: ClassicMovie.h equals() line 61, lessThan line 80


Q: Total points: 23/25 (max 25)