
/*********************************************
 * File:    iterator_ex.h
 * Project: CMSC 202 Project 5, Spring 2016
 * Author:  Nick Stommel
 * Date:    05/03/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu 
 * 
 * Description:
 * 
 * This file contains the declaration of the exception
 * classes invalidRandItr(), emptyContainer(), and insufficientMemory()
 * 
 **********************************************/

#ifndef ITERATOR_EX_H
#define ITERATOR_EX_H

#include <stdexcept>
using namespace std;

//Exception class for use when a rand_iterator is invalid, but 
//the user attempts to perform an operation
class invalidRandItr : public exception {
public:
    invalidRandItr();
    invalidRandItr(const char* message);
    const char* what() const throw();
    
private:
    const char* m_message;
};

//Exception class for use when a container is empty and element access is attempted
//using at() or operator[], or when erase() is attempted on an empty array
class emptyContainer : public exception {

public:
  emptyContainer();
  emptyContainer(const char* message);
  const char* what() const throw();

private:
  const char* m_message;

}; 

//Exception class for use when memory cannot be allocated, basically a minimally extended
//version of the bad_alloc exception class with an error message for better user feedback
class insufficientMemory : public exception {
public:
    insufficientMemory();
    insufficientMemory(const char* message);
    const char* what() const throw();
private:
    const char* m_message;
}; 

#endif /* ITERATOR_EX_H */

