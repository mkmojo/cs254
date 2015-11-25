##How to use:

###Compile the project 
    mkdir build && cd build && cmake .. && make
###Run Main Application
    build/src/main
###Run Test
    build/test/oset_test

List of requirements satisfied:  
    - [X] Comparator provided as template parameter, not constructor argument  
    - [X] Extend code to support reverse iterators  
    - [X] Extend code to support various other methods of std::set  

### Comparator in constructor VS. template argument
I prefer passing comparator as template argument.
The reason being compiler will type check and make sure comparator are of same type.
It will refuse to compile if comparator does not match.

### Support for reverse iterator
The major challege to this is to extend linked list to be doubly linked.
Each node needs to have a field pointing to its predecessor, in my implementation, 
I used a pointer to node class.

The rest is simply just labor work, `operator+=` and `operator-=` needs to be carefully updated
together with some constructors. 

### Extend supported methods
size(), empty(), find(), and erase() are added to oset.

