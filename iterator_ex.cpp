
/*********************************************
 * File:    iterator_ex.cpp
 * Project: CMSC 202 Project 5, Spring 2016
 * Author:  Nick Stommel
 * Date:    05/03/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu 
 * 
 * Description:
 * 
 * This file contains the implementation of the exception
 * classes invalidRandItr(), emptyContainer(), and insufficientMemory()
 * 
 **********************************************/

#include "iterator_ex.h"

invalidRandItr::invalidRandItr() : m_message("ERROR: rand_iterators invalid!")
{}

invalidRandItr::invalidRandItr(const char* message) : m_message(message)
{}

const char* invalidRandItr::what() const throw() {
    return m_message;
}


emptyContainer::emptyContainer() : m_message("ERROR: container is empty!") 
{}

emptyContainer::emptyContainer(const char* message) : m_message(message)
{}

const char* emptyContainer::what() const throw() { 
    return m_message; 
}

insufficientMemory::insufficientMemory() : m_message("ERROR: insufficient memory!")
{}

insufficientMemory::insufficientMemory(const char* message) : m_message(message)
{}

const char* insufficientMemory::what() const throw() {
    return m_message;
}



