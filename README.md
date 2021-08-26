# MoviesProject

# Description
Our Movie Project takes in a list of Movies to be stored into Inventory. Then, we add our customers to a customer database in store which is stored in  a HashMap by Customer ID and 
Customer object. After, we process commands where customers can borrow different Movies and/or return DVDs they already checked out. In cases where there isn't stock left or they are returning
a DVD they didn't return, the program will show a message for the error.

# Overview
A local movie rental store wishes to automate their inventory tracking system. Currently there are three types of movies/videos (in DVD media) to be tracked:

Comedy (denoted as ‘F’ for funny)
Drama (denoted as ‘D’)
Classics (denoted as ‘C’)
Borrows and returns of items by customers are also to be tracked. Four types of actions are desired in the system:

Borrow (denoted as ‘B’): (stock – 1) for each item borrowed  
Return (denoted as ‘R’): (stock + 1) for each item returned
Inventory (denoted as ‘I’): outputs the inventory of all the items in the store
History (denoted as ‘H’): outputs all the transactions of a customer 

# UML Design
![image](https://cdn.discordapp.com/attachments/557811688347533333/880541231552278528/UML_Movie_1.jpg)

The information about each movie is listed as follows: 

Comedy: F, Stock, Director, Title, Year it released 
Drama: D, Stock, Director, Title, Year it released
Classics: C, Stock, Director, Title, Major actor Release date
For example,

F, 10, Nora Ephron, You've Got Mail, 1998
D, 10, Steven Spielberg, Schindler's List, 1993
C, 10, George Cukor, Holiday, Katherine Hepburn 9 1938
C, 10, George Cukor, Holiday, Cary Grant 9 1938
Z, 10, Hal Ashby, Harold and Maude, Ruth Gordon 2 1971
D, 10, Phillippe De Broca, King of Hearts, 1967


# Constraints
You may assume correct formatting, but codes may be invalid; e.g., in this data, the 'Z' code is an invalid entry so this line has to be discarded and users should be notified about this issue. 
While the stock for each line is 10, do not assume that is the case in your design and implementation.
The movies should be sorted as follows when stored in the system:
Comedy (‘F’) sorted by Title, then Year it released 
Dramas (‘D’) are sorted by Director, then Title 
Classics (‘C’) are sorted by Release date, then Major actor
Each item is uniquely identified by its complete set of sorting attributes.  
The classical movie type has a different format than the other two. 
Major actor is always formatted as two strings, FirstName and LastName, separated by a space.
The Release date contains month and year information, and no comma (but a space) between Major actor and Release date. 
In addition, for classical movies, one movie (e.g., Holiday) may have multiple lines, but since each classical movie is uniquely identified by its sorting attributes (Release date, then Major actor in this case), the two entries are treated as separate movies.
data4customers.txt:

The information about each customer is listed as follows: 

Customer: CustomerID LastName FirstName 
For example,

1111 Mouse Mickey
1000 Mouse Minnie

#Commands
You may assume that the data is formatted correctly. 
CustomerID is 4-digits and uniquely identifies each customer
data4commands.txt/AlanCommands.txt:

The information about each command is listed as follows:

Inventory I
History H CustomerID
Borrow B CustomerID MediaType MovieType (movie sorting attributes)
Return R CustomerID MediaType MovieType (movie sorting attributes)
For example,

B 1234 D C 9 1938 Katherine Hepburn
B 1234 D F Pirates of the Caribbean, 2003
R 1234 D C 9 1938 Katherine Hepburn
B 1234 D D Steven Spielberg, Schindler's List
I
H 1234
X 1234 Z C 9 1938 Katherine Hepburn
B 1234 D Y 2 1971 Ruth Gordon
B 9999 D F Pirates of the Caribbean, 2003
B 1234 D C 2 1975 Blah Blah     

