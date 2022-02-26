
/*********************************************
 * File:    mytest.cpp
 * Project: CMSC 202 Project 5, Spring 2016
 * Author:  Nick Stommel
 * Date:    05/03/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu 
 * 
 * Description:
 * 
 * This file is a test program for the sorted<T> container class
 * and its associated const_iterator and rand_iterator
 * 
 **********************************************/

#include <iostream>
using namespace std;

#include "sorted.h"
#include "iterator_ex.h"

int main() {
    
    cout << endl << "***** Test Program for sorted<T> container *****" << endl << endl;
    
    //Test Default constructor
    
    cout << "Testing default constructor..." << endl;
    sorted<int> dsint;
    cout << "size: " << dsint.size() << endl;
    cout << "capacity: " << dsint.capacity() << endl;
    cout << dsint << endl << endl;
    
    
    
    //Test Non-default constructor
    
    int intarr[] = {3};
    cout << "Testing non-default constructor..." << endl;
    sorted<int> sint(intarr, 1);
    cout << "size: " << sint.size() << endl;
    cout << "capacity: " << sint.capacity() << endl;
    cout << sint << endl << endl;
    
    int intarr1[] = {2, 5, 4};
    
    sorted<int> sint1(intarr1, 3);
    cout << "size: " << sint1.size() << endl;
    cout << "capacity: " << sint1.capacity() << endl;
    cout << sint1 << endl << endl;
    
    
    
    //Test copy constructor
    
    cout << "Testing copy constructor..." << endl;
    sorted<int> sint2(sint1);
    cout << "size: " << sint2.size() << endl;
    cout << "capacity: " << sint2.capacity() << endl;
    cout << sint2 << endl << endl;
    
    
    
    //Create array for use in assignment below
    int intarr2[] = {2, 6, 8, 2};
    
    cout << "Creating container for assignment..." << endl;
    sorted<int> sint3(intarr2, 4);
    cout << "size: " << sint3.size() << endl;
    cout << "capacity: " << sint3.capacity() << endl;
    cout << sint3 << endl << endl;
    
    //Test assignment operator
    cout << "Testing assignment operator..." << endl;
    cout << "Before: ";
    cout << sint2 << endl;
    sint2 = sint3;
    cout << "After: ";
    cout << sint2 << endl << endl;
    
    
    
    //Test sorted<T>::at() exception handling
    
    try {
        string adeleArr[] = {"hello", "from", "the", "other", "side"};
        sorted<string> hello(adeleArr, 5);
        cout << "Attempting to access element at invalid index..." << endl;
        cout << hello.at(8) << endl;
        
    } catch (exception& e) {
        cerr << e.what() << endl << endl;
    }
    
    //Test Square Bracket operator
    
    cout << "Testing square bracket operator (read)" << endl;
    double dblarr[] = {4.2, 1.8, 8.3, 2.7, 9.6, 3.4};
    sorted<double> sdbl1(dblarr, 6);
    
    cout << " ";
    for(int i = 0; i < sdbl1.size(); ++i) {
        cout << sdbl1[i] << "  ";
    }
    cout << endl << sdbl1 << endl << endl;
    
    cout << "Testing square bracket operator (write)" << endl;
    cout << "Before: " << sdbl1 << endl;
    for(int i = 0; i < sdbl1.size(); ++i) {
        sdbl1[i] = 3.14;
    }
    cout << "After: " << sdbl1 << endl << endl;
    
    try {
        cout << "Attempting to read invalid index with operator[]..." << endl;
        cout << sdbl1[6] << endl;
        cout << "EXCEPTION NOT THROWN!" << endl;
    } catch (exception& e) {
        cerr << e.what() << endl << endl;
    }
    try {
        cout << "Attempting to write at invalid index with operator[]..." << endl;
        sdbl1[6] = 2.7183;
    } catch (exception& e) {
        cerr << e.what() << endl << endl;
    }
    
    
    
    //Test insertion
    
    //Insert on empty array
    cout << "Inserting on empty array, initial capacity = " << dsint.capacity() << endl;
    dsint.insert(9);
    cout << dsint << endl;
    cout << "Capacity after insert = " << dsint.capacity() << endl << endl;
    
    //Insert on full capacity array
    cout << "Inserting on full capacity array, initial capacity = " << sint2.capacity() << endl;
    sint2.insert(4);
    cout << sint2 << endl;
    cout << "Capacity after insert = " << sint2.capacity() << endl << endl;
    
    //Insert on non-full capacity array
    cout << "Inserting on non-full capacity array, initial capacity = " << sint1.capacity() << endl;
    sint1.insert(3);
    cout << sint1 << endl;
    cout << "Capacity after insert = " << sint1.capacity() << endl << endl;
    
    
    
    //Test deletion
    
    cout << "Testing erase..." << endl;
    
    //Erase at index 4 of sint2
    sorted<int>::const_iterator itr(&sint2[4]);
    cout << "Before erase, initial capacity = " << sint2.capacity() << endl;
    cout << sint2 << endl;
    
    sint2.erase(itr);
    
    cout << "After erase, capacity = " << sint2.capacity() << endl;
    cout << sint2 << endl << endl;
      
    //Test erasing multiple indices
    int intarr4[] = {3, 1, 0, 7, 4, 8, 6, 2, 5, 9};
    sorted<int> sint4(intarr4, 10);
    cout << "Before erasing entries, initial capacity = " << sint4.capacity() << endl;
    cout << sint4 << endl;
    
    int i = 0;
    for (itr = sint4.begin(); itr != sint4.end(); ) {
        if (i == 2 || i == 4 || i == 6 || i == 9) {
            itr = sint4.erase(itr);
        } else {
            itr++;
        }
        i++;
    }
    
    cout << "After erasing entries, capacity =  " << sint4.capacity() << endl;
    cout << sint4 << endl << endl;
    
    //Test erase and throwing exception if container is empty
    try {
        int intarr[] = {8};
        sorted<int> sint(intarr, 1);
        cout << sint << endl;
        sint.erase(sint.begin());
        cout << sint << endl;
        cout << "Attempting erase on empty container..." << endl;
        sint.erase(sint.begin());
        
    } catch (exception &e) {
        cerr << e.what() << endl;
    }
    
    //Test erase reallocation
    int intarr5[] = {3, 2, 5, 6, 1};
    sorted<int> sint5(intarr5, 5);
    cout << endl << "Testing erase reallocation..." << endl;
    cout << sint5 << endl;
    cout << "Initial capacity: " << sint5.capacity() << endl;
    cout << "Erasing element..." << endl;
    sint5.erase(sorted<int>::const_iterator(&sint5[2]));
    cout << sint5 << endl;
    cout << "New capacity: " << sint5.capacity() << endl << endl;
    
    //Test erasing entire container using iterators and throwing emptyContainer() exception
    sorted<int> eraseTest(intarr4, 10);
    try {
        sorted<int>::const_iterator itr;
        cout << "Testing erase with iterators from beginning..." << endl;
        cout << eraseTest << endl;
        for( itr = eraseTest.begin(); itr != eraseTest.end(); ) {
            eraseTest.erase(itr);
            cout << eraseTest << endl;
            itr = eraseTest.begin();
        }
        
        itr = eraseTest.begin();
        //Should cause exception to be thrown, container is empty
        eraseTest.erase(itr);
        
        cout << "EXCEPTION NOT CAUGHT" << endl;
        
    } catch (exception &e) {
        cerr << e.what() << endl << endl;
    }
    
    try {
        sorted<int> eraseTest2(intarr4, 10);
        cout << "Testing erase with operator[] and iterators from end..." << endl;
        int i = eraseTest2.size() - 1;
        cout << eraseTest2 << endl;
        
        while(true) {
            eraseTest2.erase(sorted<int>::const_iterator(&eraseTest2[i]));
            cout << eraseTest2 << endl;
            --i;
        }
        cout << "EXCEPTION NOT CAUGHT" << endl;
        
    } catch (exception &e) {
        cerr << e.what() << endl << endl;
    }
    
    //Test using at() on empty array and throwing an emptyContainer() exception
    try {
        cout << "Testing access using at() on empty array..." << endl;
        cout << eraseTest.at(0) << endl;
    } catch (exception &e) {
        cerr << e.what() << endl << endl;
    }
    //Test using operator[] on empty array and throwing an emptyContainer() exception
    try {
        cout << "Testing access using operator[] on empty array..." << endl;
        cout << eraseTest[0] << endl;
    } catch (exception &e) {
        cerr << e.what() << endl << endl;
    }
    
    
    //Test rand_iterators
    
    char charr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    sorted<char> schar(charr, 10);
    cout << "Testing rand_iterator constructors for array... " << endl;
    cout << schar << endl;
    cout << " 0, 1, 2, 3, 4, 5, 6, 7, 8, 9" << endl;
    sorted<char>::rand_iterator rnditr(&schar);
    rnditr.printPermutation();
    
    cout << "Testing rand_iterators for printing..." << endl;
    i = 0;
    for(rnditr = schar.rndbegin(); rnditr != schar.rndend(); ++rnditr, ++i) {
        cout << *rnditr << " ";
    } 
    cout << endl << endl;
    
    //Testing invalidRandItr exception throw with try-catch
    //Exceptions are thrown when a rand_iterator's associated container is modified
    
    //Use assignment operator to assign rnditr to the returned iterator from rndbegin()
    rnditr = schar.rndbegin();
    //Insert an element in the schar array which rnditr belongs to, rendering the iterator invalid
    schar.insert('k');
    
    try {
        cout << "Attempting to preincrement rand_iterator after array is modified..." << endl; 
        ++rnditr;
        cout << "EXCEPTION NOT THROWN!" << endl;
    } catch (exception& e) {
        cerr << endl << e.what() << endl << endl;
    }
    
    try {
        cout << "Attempting to postincrement rand_iterator after array is modified..." << endl;
        rnditr++;
    } catch (exception& e) {
        cerr << endl << e.what() << endl << endl;
    }
    
    try {
        cout << "Attempting to dereference rand_iterator after array is modified..." << endl;
        cout << *rnditr << endl;
        cout << "EXCEPTION NOT THROWN!" << endl;
    } catch (exception& e) {
        cerr << endl << e.what() << endl << endl;
    } 
    
    try {
        cout << "Attempting to compare rand_iterators after array is modified..."<< endl;
        sorted<char>::rand_iterator rnditr2 = schar.rndend();
        cout << (rnditr != rnditr2) << endl;
        cout << "EXCEPTION NOT THROWN!" << endl;
    } catch (exception& e) {
        cerr << endl << e.what() << endl << endl;
    }

    try {
        int intarr6[] = {1, 3, 2};
        int intarr7[] = {7, 2, 5, 8};

        sorted<int> sint6(intarr6, 3);
        sorted<int> sint7(intarr7, 4);
        
        
        sorted<int>::rand_iterator rnditr2 = sint7.rndbegin();
        sint7 = sint6;
        cout << "Attempting to increment rand_iterator of container after container has been reassigned..." << endl;
        ++rnditr2;
        cout << "EXCEPTION NOT THROWN!" << endl;
    } catch (exception& e) {
        cerr << endl << e.what() << endl << endl;
    }
    
    //!!!NOTE uncomment if you want to play around with throwing an
    //std::bad_alloc exception (which is caught during dynamic allocation 
    //in the sorted<T> functions and re-thrown as a more informative 
    //insufficientMemory exception with a string parameter for the what() method
    //or modify if you want to flood the heap for kicks
    /*
    try {
        cout << "Attempting to construct container of a size that cannot be allocated in heap..." << endl;
        //We will 'trick' the program into trying to create a container
        //that should throw an insufficientMemory exception,
        //without actually passing in an array of such ridiculous capacity
        //NOTE: changing the len to a size which can actually be allocated will cause a
        //segfault because there are no elements in the passed in pointer/array
        sorted<long> memError(NULL, 9999999999999999);
        cout << "EXCEPTION NOT THROWN!" << endl;
    } catch (exception& e) {
        cerr << endl << e.what() << endl << endl;
    }
    */
    
    //!!!NOTE uncomment if you want to test sorted<T> container insertion
    //at its finest. Basically just goes forever (well...it should stop
    //once the capacity reaches a certain point and the heap cannot
    //contain such a large container)
    /*
    try {
        srand(time(NULL));
        sorted<long> memError;
        while(true) {
            long num = rand() % RAND_MAX;
            memError.insert(num);
            cout << "capacity = " << memError.capacity()
                 << ", size = " << memError.size()
                 << ", inserting number " << num << endl;
        }
    } catch (exception &e) {
        cout << e.what() << endl;
    }
    */
    
    
    return 0;

}
