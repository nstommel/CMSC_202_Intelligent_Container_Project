// 
// sorted_driver.cpp : minimal test program for sorted<T> class and iterators
//

#include <iostream>
#include "sorted.h"

using namespace std;

int main() {

  sorted<int> x;

  sorted<int>::const_iterator itr;
  sorted<int>::rand_iterator rnditr;

  // insert some values into x
  for (int i = 0; i < 10; i++ ) 
    x.insert( (i*i) % 23 );

  // sorted stores items in ascending order
  cout << "Items in x: ";
  for (itr = x.begin(); itr != x.end(); itr++)
    cout << *itr << " ";
  cout << endl << endl;

  cout << "capacity of x is " << x.capacity() << endl;
  cout << "size of x is " << x.size() << endl << endl;

  // erase() a couple items from x and print the result;
  // notice that erasing the item at index 2 changes
  // the value at index 7
  cout << "Now we will erase() some items in x..." << endl;
  int i = 0;
  for (itr = x.begin(); itr != x.end(); ) {
    if (i == 2 || i == 4 || i == 7) {
      itr = x.erase(itr);
    } else {
      itr++;
    }
    i++;
  }
  cout << "Items in x: ";
  for (itr = x.begin(); itr != x.end(); itr++)
    cout << *itr << " ";
  cout << endl << endl;

  cout << "capacity of x is " << x.capacity() << endl;
  cout << "size of x is " << x.size() << endl << endl;

  cout << "Insert a few more items in x (21, -3, 9)..." << endl;

  x.insert(21);
  x.insert(-3);
  x.insert(9);

  cout << "Items in x: ";
  for (itr = x.begin(); itr != x.end(); itr++)
    cout << *itr << " ";
  cout << endl << endl;

  
  cout << "Items in x using rand_iterator: ";
  for (rnditr = x.rndbegin(); rnditr != x.rndend(); rnditr++)
    cout << *rnditr << " ";
  cout << endl << endl;

  cout << "Items in x using rand_iterator with seed 12345: ";
  for (rnditr = x.rndbegin(12345); rnditr != x.rndend(); rnditr++)
    cout << *rnditr << " ";
  cout << endl << endl;
  
  
  
  cout << "Create a 'playlist' of Prince songs..." << endl;

  sorted<string> songs;

  songs.insert("When You Were Mine");
  songs.insert("Pop Life");
  songs.insert("Adore");
  songs.insert("Purple Rain");
  songs.insert("Kiss");
  songs.insert("If I Was Your Girlfriend");
  songs.insert("Joy in Repetition");
  songs.insert("The Ballad of Dorothy Parker");
  songs.insert("Little Red Corvette");
  songs.insert("When Doves Cry");
  
  sorted<string>::const_iterator songitr;
  sorted<string>::rand_iterator rndsongitr;

  cout << endl;
  cout << "My Prince songs:" << endl;
  for ( songitr = songs.begin(); songitr != songs.end(); songitr++ )
    cout << "  " << *songitr << endl;

  cout << endl;
  cout << "My Prince songs shuffled:" << endl;
  for ( rndsongitr = songs.rndbegin(); rndsongitr != songs.rndend(); rndsongitr++ )
    cout << "  " << *rndsongitr << endl;
  cout << endl;
  
  // Test assignment operator
  // Can test copy constructor by changing following two lines to
  //   sorted<string> test(songs);
  sorted<string> test;
  test = songs; 

  cout << "Testing operator= by creating a copy and then deleting "
       << "one item from copy..." << endl;

  // Delete a song from test; test and songs should be different
  songitr = test.begin();
  songitr++;
  songitr++;
  test.erase(songitr);

  cout << endl;
  cout << "My Prince songs:" << endl;
  for ( songitr = songs.begin(); songitr != songs.end(); songitr++ )
    cout << "  " << *songitr << endl;

  cout << endl;
  cout << "My Prince songs (copy with 'Joy in Repetition' deleted):" << endl;
  for ( songitr = test.begin(); songitr != test.end(); songitr++ )
    cout << "  " << *songitr << endl;
  

  return 0;
}
