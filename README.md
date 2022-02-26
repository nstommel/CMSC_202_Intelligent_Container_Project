# CMSC_202_Intelligent_Dynamic_Storage_WIth_Iterators_Class
This project implements a dynamically allocated and intelligent templated storage container class that contains an array of sorted data that resizes itself based on a logarithmic function in relation to the number of elements added or deleted. Constant and random iterators as well as numerous overloaded operators are implemented for this "sorted" class. Exceptions are also fully implemented to prevent illegal access, deletion, or write operations in memory.

sorted_driver.cpp is a test program for checking functionality of the class and includes a list of songs illustrating a templated string type container.

mytest.cpp is a more extensive test program for the sorted<T> container class and its associated const_iterator and rand_iterator
  
# Assignment Prompt:

Your assignment is to implement a templated class called sorted<T> that stores items in increasing order within a dynamically-allocated array. The elements of sorted<T> can be of any type that implements operator< and operator>. In addition, you must create two iterators: a constant iterator const_iterator that iterates over the elements in sorted order, and a pseudo-random iterator rand_iterator that iterates over the elements according to a pseudo-randomly generated permutation.

The container class sorted<T> and the iterator classes should be defined in the file sorted.h and implemented in sorted.cpp. You must also thoroughly test the classes and submit your tests in the main program mytest.cpp.

Although the my_array class and iterator are very basic, you should study them well as their structure is similar to the container and iterators that you will write.
sorted<T> Container Requirements

The container must be able to store elements of any type that implements operator> and operator<, and must store the items in ascending order.

The container should not have any fixed limits on the number of items that it can hold; to achieve this, it must use a dynamically-allocated storage array. (Clearly, the number of items that can be stored is limited by the amount of memory in the computer, but we're not worried about that.) The storage array must be re-sized as elements are inserted or erased from the container, but it is inefficient to re-size the array every time an element is inserted or erased. One approach is to initialize the array to a small length n; once the number of elements in the array equals n, double the size of the array to 2n; if the number of elements increases to 2n, double the size again to 4n, etc. Similarly, if after erasing elements, at most one-quarter of the capacity of the array is used, it should be re-sized to half the current capacity, but never to less than n elements. The choice of n is up to you, but something like 10 (or 8 if you prefer powers of two) would be reasonable.

Note that you will have to keep track of both the capacity of the array, that is, it's allocated length, and it's size, the number of items stored in the array. In the remainder of the project description, the term 'capacity' will always refer to the allocated storage in the container and 'size' will refer to the number of items stored in the container.

Since the class must use dynamically allocated memory, you must implement a copy constructor and overload operator=.

See the Required Functions section below for a list of functions that must be implemented in the sorted<T> class; additional functions may implemented as needed.
const_iterator and rand_iterator Iterator Requirements

You must implement two iterators for the sorted<T> class:

A constant iterator const_iterator that iterates over the elements of a sorted<T> object in sorted order. We use a const_iterator rather than a plain iterator because we do not want to be able to change a value by dereferencing the iterator since this would potentially store elements out of the proper order.

A random iterator rand_iterator that iterates over the elements of a sorted<T> object in order of a pseudo-random permutation; that is, the iterator access each item of the object exactly once, but in a pseudo-random order.

For rand_iterator constructors that do not accept a seed for the random number generator as a parameter, you may use either a fixed seed or time(NULL).

The rand_iterator will need to construct a permutation, and since the size of the permutation depends on the container it is being used with, the permutation array will need to be allocated dynamically. Therefore, rand_iterator needs a copy constructor and overloaded operator=. 
