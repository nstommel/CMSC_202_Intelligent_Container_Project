
/*********************************************
 * File:    sorted.h
 * Project: CMSC 202 Project 5, Spring 2016
 * Author:  Nick Stommel
 * Date:    05/03/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu 
 * 
 * Description:
 * 
 * This file contains the declaration of the sorted<T> template
 * class, and its critical subclasses const_iterator and rand_iterator
 * The sorted<T> template class is a container class which includes data 
 * in a contiguous, resizable dynamically allocated array.
 * 
 **********************************************/

#ifndef SORTED_H
#define SORTED_H

#include <iostream>
#include <stdexcept>
using namespace std;

#include "iterator_ex.h"

template<typename T> class sorted {
    
public:
    
    class const_iterator;
    class rand_iterator;
    
    // Overloaded assignment operator made a friend of template class
    // Used for debugging and simplicity in printing container contents
    // Uses const_iterators in implementation. The container cannot
    // be passed by const reference simply because the begin() and end()
    // functions make no promise to not modify container members (do not include
    // const keyword after parameters in definition)
    // Rest assured, however, that no members are modified upon printing the
    // object
    template<typename U>
    friend ostream& operator<<(ostream& os, sorted<U>& obj);
    
    //Default constructor
    sorted();

    // Non-default constructor copies data from array to sorted
    // Can throw insufficientMemory() exception
    sorted(T* data, int len) throw (insufficientMemory);

    // Copy constructor
    // Can throw insufficientMemory() exception
    sorted(const sorted<T>& srtd) throw (insufficientMemory);

    // Destructor
    ~sorted();

    // Overloaded assignment operator
    // Should return by reference to avoid overhead (returning a new
    // container object from *this is unnecessary when *this already exists) 
    // returning by reference also allows chaining, e.g. a = b = c 
    // Can throw insufficientMemory() exception
    sorted<T>& operator=(const sorted<T>& srtd) throw (insufficientMemory);
    
    // Added square bracket operator, can be used to write or read values at an index
    // The hallmark of containers with contiguous data storage, it allows the container
    // to be used just like an ordinary array but also includes bounds checking by throwing
    // an out_of_range exception if the index provided is invalid
    // Can throw out_of_range() exception
    T& operator[](const int indx) throw (out_of_range, emptyContainer); 
    
    // Return the capacity of the storage array
    int capacity() const;

    // Return number of items stored
    int size() const;

    // Return the address of the storage array;
    // for use in grading programs
    T* getStorageArray() const;

    // Insert an item in sorted; return iterator to inserted item
    // Can throw an insufficientMemory() exception
    const_iterator insert(T data) throw (insufficientMemory);

    // Remove an item from sorted<T>; return iterator to next item
    // after the erased item
    // Can throw an insufficientMemory() or emptyContainer() exception
    const_iterator erase(const_iterator itr) throw (emptyContainer, insufficientMemory);

    // Get element at indx position
    // Does not allow modification of indices due to const return value
    // This is made possible in overloaded square bracket operator[] above
    // and is MUCH more convenient for assigning values at indices, just like
    // a normal vector container
    // Performs critical bounds checking, can throw out_of_range() exception
    const T& at(const int indx) throw (out_of_range, emptyContainer);

    // Starting iterator value for const_iterator
    const_iterator begin();

    // Ending iterator value for const_iterator;
    // One element beyond the last valid element in the array.
    const_iterator end();

    // Starting iterator value for rand_iterator.
    // Uses time(NULL) as seed value for srand().
    rand_iterator rndbegin();

    // Starting iterator value for rand_iterator with seed for
    // srand() specified.  Given a sorted<T> object x, repeated 
    // use of rndbegin( unsigned seed ) with the same seed value
    // must produce the same permutation of the elements of x.
    rand_iterator rndbegin( unsigned seed );

    // Ending iterator value for rand_iterator
    rand_iterator rndend();
    
    
    class const_iterator {

    public:
        
        // Allows sorted<> to access const_iterator's private variables.
        // Used by sorted<>::erase().
        friend class sorted;
        
        // Default constructor
        const_iterator();

        // Non-default constructor sets value to given address
        const_iterator(T* addr);

        // Pre-increment, e.g. ++itr
        const_iterator operator++();

        // Post-increment, e.g. itr++
        const_iterator operator++(int);
        
        // operator!= needed for loop control, e.g. itr != x.end()
        bool operator!=(const const_iterator& itr);

        // Unary dereference operator; returns element currently pointed
        // to by the const_iterator
        const T& operator*();
        
    private:
        
        T* m_current;  // pointer to current entry in array
    };
    
    
    class rand_iterator {
    
    public:
        
        // Allows sorted<T> to access rand_iterator's private variables.
        friend class sorted;
        
        // Default constructor
        rand_iterator();

        // Non-default constructor; pointer to sorted<T> object passed 
        // as a parameter, which allows the rand_iterator to access 
        // variables of the associated sorted<T>> container
        // Can throw an insufficientMemory() exception
        rand_iterator(sorted<T>* srtdPtr) throw (insufficientMemory);

        // Non-default constructor; pointer to sorted<T> passed as in
        // previous constructor, but also passes seed for random number
        // generator
        // Can throw an insufficientMemory() exception
        rand_iterator(sorted<T>* srtdPtr, unsigned seed) throw (insufficientMemory);

        // Copy constructor
        // Can throw an insufficientMemory() exception
        rand_iterator(const rand_iterator& itr) throw (insufficientMemory);

        // Destructor
        ~rand_iterator();

        // pre-increment
        // Can throw an invalidRandItr() exception
        rand_iterator operator++() throw (invalidRandItr);

        // post-increment
        // Can throw an invalidRandItr() exception
        rand_iterator operator++(int) throw (invalidRandItr);

        // operator!= needed for loop control, e.g. itr != x.end()
        // Can throw an invalidRandItr() exception
        bool operator!=(const rand_iterator& itr) throw (invalidRandItr);

        // Unary dereference operator
        // Can throw an invalidRandItr() exception
        const T& operator*() throw (invalidRandItr);

        // Overloaded assignment operator
        // Should return by reference to avoid overhead (returning a new
        // container object from *this is unnecessary when *this already exists) 
        // returning by reference also allows chaining, e.g. a = b = c
        // Can throw an insufficientMemory() exception
        rand_iterator& operator=(const rand_iterator& itr) throw (insufficientMemory);
        
        // Nice helper function to print the current permutation and corresponding
        // elements of the container, simply prints an error message if the
        // permutation has not yet been determined (as is the case with the default
        // rand_iterator constructor where no container is linked, which is required
        // to generate the permutation) 
        void printPermutation();
        
    private:
        
        T* m_current;               // pointer to current entry in array
        int m_currIndex;            // current index in permutation array
        int* m_permutation;         // permutation array of random indices
        sorted<T>* m_srtdPtr;       // link to the sorted<T> container
    };
    
    
private:
    
    int logCapacity(int size) const;
    
    int m_size;             // number of items in my_array
    int m_capacity;         // capacity of array
    bool m_randItrsValid;   // boolean to indicate whether rand_iterators are valid
    T* m_data;              // storage array
};

#include "sorted.cpp"

#endif