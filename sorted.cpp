
/*********************************************
 * File:    sorted.cpp
 * Project: CMSC 202 Project 5, Spring 2016
 * Author:  Nick Stommel
 * Date:    05/03/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu 
 * 
 * Description:
 * 
 * This file contains the implementation of the sorted<T> template
 * class, and its critical subclasses const_iterator and rand_iterator
 * Note the use of the logCapacity() function for determining appropriate
 * container size based on m_size during construction and after insert()
 * and delete() operations have been performed
 * 
 **********************************************/

#ifndef SORTED_CPP
#define SORTED_CPP

#include <iostream>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <stdexcept>

using namespace std;

#include "sorted.h"
#include "iterator_ex.h"

template<typename T> 
int sorted<T>::logCapacity(int size) const {
    return pow(2, ceil(log2(size)));
}

template<typename T> 
sorted<T>::sorted() : 
    m_size(0), m_capacity(0), m_randItrsValid(false), m_data(NULL)
{}

template<typename T> 
sorted<T>::sorted(T* data, int len) throw (insufficientMemory) :
//Initialize values to default in case allocation of m_data array fails
    m_size(0), m_capacity(0), m_randItrsValid(false), m_data(NULL)
{
    try {
        m_data = new T[logCapacity(len)];
    } catch (bad_alloc) {
        throw insufficientMemory();
    }
    
    //Fill m_data array
    for(int i = 0; i < len; ++i) {
        m_data[i] = data[i];
    }
    
    //Bubble Sort the imported data 
    for (int li = 0; li < len - 1; ++li) {
        for (int ri = li + 1; ri < len; ++ri) {
            if (m_data[li] > m_data[ri]) {

                T temp = m_data[li];
                m_data[li] = m_data[ri];
                m_data[ri] = temp;
            }
        }
    }
    
    //Re-Initialize necessary member fields after successful allocation:
    m_size = len;
    m_capacity = logCapacity(len);
    
}

template<typename T> 
sorted<T>::~sorted() {
    
    delete [] m_data;
    
}

template<typename T> 
sorted<T>::sorted(const sorted<T>& srtd) throw (insufficientMemory) {
    
    try {
        m_data = new T[srtd.m_capacity];
    } catch (bad_alloc) {
        throw insufficientMemory();
    }
    
    //Fill newly allocated m_data array (if attempt does not throw bad_alloc)
    for (int i = 0; i < srtd.m_size; ++i) {
        m_data[i] = srtd.m_data[i];
    }
    
    //Initialize member fields:
    
    m_size = srtd.m_size;
    m_capacity = srtd.m_capacity;
    //m_data was newly allocated, rand_iterators become invalid
    m_randItrsValid = false;
        
    
}

template<typename T> 
sorted<T>& sorted<T>::operator=(const sorted<T>& srtd) throw (insufficientMemory) {
    
    //Guard against self-assignment
    if ( this != &srtd ) {
        
        try {
            //Test if there is enough memory in the heap
            T* memTest = new T[srtd.m_capacity];
            //If a bad_alloc exception is not thrown, delete the memTest array and proceed
            //past catch statement
            delete [] memTest;
            
        } catch (bad_alloc) {
            throw insufficientMemory();
        }
        
        //We include the request to delete m_data AFTER the try-catch statement so that the
        //original object data is preserved (that is NOT deleted) if an exception is thrown. 
        //Therefore, the object is never modified if there is not enough memory in the heap to
        //perform reassignment.
        delete [] m_data;
        
        //It is now safe to allocate memory for the new m_data array
        m_data = new T[srtd.m_capacity];
        
        //Fill newly allocated m_data array with the m_data of the passed in sorted<T> container
        for (int i = 0; i < srtd.m_size; ++i) {
            m_data[i] = srtd.m_data[i];
        }
        
        //Initialize member fields:
        
        m_size = srtd.m_size;
        m_capacity = srtd.m_capacity;
        
        //If reassignment of a container is performed, all rand_iterators become invalid
        //(size could be changed and the container has been reallocated, making
        //all associated rand_iterators invalid)
        m_randItrsValid = false;
    }
    
    return *this;
}

template <typename U> 
ostream& operator<<(ostream& os, sorted<U>& obj) {
    
    os << "[";
    int i = 0;
    //Use const_iterators to advance down the array and print its contents
    for(typename sorted<U>::const_iterator itr = obj.begin(); itr != obj.end(); ++itr, ++i) {
        os << *itr;
        if(i < obj.m_size - 1) {
            os << ", ";
        }
    }
    os << "]";
    
    return os;
}

template <typename T> 
T& sorted<T>::operator[](const int indx) throw (out_of_range, emptyContainer) {
    //If the [] operator is attempted to access data in an array with no elements,
    //throw an emptyContainer() exception
    if(m_size == 0) {
        throw emptyContainer("ERROR: container is empty! sorted<T>::operator[](...) cannot access nonexistent data");
    }
    //If the user attempts to access nonexistent data at an invalid index,
    //throw a out_of_range exception
    if(indx >= m_size || indx < 0) {
        throw out_of_range("ERROR: sorted<T>::operator[] : index is out of range");
    } else {
        return m_data[indx];
    }
}

template<typename T> 
int sorted<T>::size() const {
    return m_size;
}

template<typename T> 
int sorted<T>::capacity() const {
    return m_capacity;
}

template<typename T> 
T* sorted<T>::getStorageArray() const {
    return m_data;
}

template<typename T> 
const T& sorted<T>::at(const int indx) throw (out_of_range, emptyContainer) {
    //If the user attempts to access data in an array with no elements,
    //throw an emptyContainer() exception
    if(m_size == 0) {
        throw emptyContainer("ERROR: container is empty! sorted<T>::at(...) cannot access nonexistent data");
    }
    //If the user attempts to access nonexistent data at an invalid index,
    //throw a out_of_range exception
    if(indx >= m_size || indx < 0) {
        throw out_of_range("ERROR: sorted<T>::at() : index is out of range");
    } else {
        return m_data[indx];
    }
}

template<typename T> 
typename sorted<T>::const_iterator sorted<T>::begin() {
    return const_iterator(&m_data[0]);
}

template<typename T> 
typename sorted<T>::const_iterator sorted<T>::end() {
    return const_iterator(&m_data[m_size]);
}

template<typename T> 
typename sorted<T>::rand_iterator sorted<T>::rndbegin() {
    
    rand_iterator rb(this);
    rb.m_currIndex = 0;
    rb.m_current = &m_data[rb.m_permutation[0]];
    
    //NOTE: rand_iterators are ONLY declared valid after rndbegin(...) is called                                                               
    //This prevents invalid use of an iterator after a container has been changed                                                              
    //through the reassignment operator=() 
    m_randItrsValid = true;
    
    return rb;
}

template<typename T> 
typename sorted<T>::rand_iterator sorted<T>::rndbegin(unsigned seed) {
    
    rand_iterator rb(this, seed);
    rb.m_currIndex = 0;
    rb.m_current = &m_data[rb.m_permutation[0]];
    
    //NOTE: rand_iterators are ONLY declared valid after rndbegin(...) is called                                                               
    //This prevents invalid use of an iterator after a container has been changed                                                              
    //through the reassignment operator=() 
    m_randItrsValid = true;   

    return rb;
}

template<typename T> 
typename sorted<T>::rand_iterator sorted<T>::rndend() {
    
    //Take note that a new permutation array is NOT created upon call to
    //rndend as this would be an unnecessarily expensive operation
    //considering that rndend() is called every time != comparison
    //is performed in an iterator for loop and that rndend.m_current shouldn't 
    //point to an existent data value. Therefore, the default constructor is
    //used (m_permutation is set to NULL) and the pointer to the sorted container is 
    //linked afterward
    rand_iterator re;
    re.m_srtdPtr = this;
    re.m_currIndex = m_size;

    //Set m_current to one past all data in the array by default
    //(Safer than attempting to set the end to an element that actually
    //exists, which could prove problematic in determingin where to end)
    re.m_current = &m_data[m_size];
    
    return re;
}


template<typename T> 
typename sorted<T>::const_iterator sorted<T>::insert(T data) throw (insufficientMemory) {
    
    //Assumes array is sorted!

    int index = 0;
    //If the array is not empty, update the index of insertion
    if(m_size > 0) {
        //Temporary T value used in comparison loop to find index of insertion,
        //discarded once index is found (it goes out of scope)
        T beforeInsert = m_data[0];
        //Find index to place data 
        for (int i = 0; i < m_size; ++i) {
            //If the value of the data at index i is greater than or equal to the highest value
            //already found that does not exceed that of the data, update the index of insertion
            if(m_data[i] >= beforeInsert && m_data[i] < data) {
                beforeInsert = m_data[i];
                index = i + 1;
            }
        }
    }

    //If new size does not exceed maximum capacity, 
    if((m_size + 1) <= m_capacity) {
        
        //rand_iterators become invalid
        m_randItrsValid = false;
        
        //Insertion is safe to perform, increase size
        ++m_size;

        //Start shifting all data to the right by one at index of end of array, 
        //which is the previous size (m_size before increment) minus one,
        //or m_size - 2. Stop at the index of insertion.
        for(int i = m_size - 2; i >= index; --i) {
            m_data[i + 1] = m_data[i];
        }
        m_data[index] = data;
        
    //Otherwise, if new size exceeds maximum capacity, create new array and copy in data
    } else {
        
        T* newData;
        try {
            //Attempt to create an array with the new capacity
            newData = new T[logCapacity(m_size + 1)];
        } catch (bad_alloc) {
            //Throw exception if memory cannot be allocated
            throw insufficientMemory();
        }
        
        //rand_iterators should be declared invalid once insertion is safe to perform
        //Note that this field is NOT modified if there is insufficient capacity
        m_randItrsValid = false;
        
        //We increment m_size AFTERWARD so that it is NOT changed if there is
        //insufficient capacity
        ++m_size;
        
        //If array of new size can be created, update m_capacity of container
        m_capacity = logCapacity(m_size);
        
        //Fill new data array up to insertion point
        for(int i = 0; i < index; ++i) {
            newData[i] = m_data[i];
        }
        //Insert new data
        newData[index] = data;
        //Fill new array with remaining old data greater than that inserted
        //i is the index in the array to start from. Stop when i reaches the new m_size
        for(int i = index + 1; i < m_size; ++i) {
            newData[i] = m_data[i - 1];
        }
        //Delete old array
        delete [] m_data;
        //Link m_data pointer to newly allocated array
        m_data = newData;
        
    }
    
    //Return const_iterator to the inserted object
    return const_iterator(&m_data[index]);
}

template<typename T> 
typename sorted<T>::const_iterator sorted<T>::erase(const_iterator itr) 
throw (emptyContainer, insufficientMemory) {
    
    //If array is empty and no element can be removed, throw an emptyContainer() 
    //exception
    if(m_size == 0) {
        throw emptyContainer("ERROR: container is empty! sorted<T>::erase(...) cannot be performed");
        
    } else {
        
        //Reallocate array size if the appropriate capacity drops below that
        //of the current capacity
        //Notice how m_size is NOT decremented here, so that if allocation fails,
        //the container attributes are not modified
        bool reallocated = false;
        T* newData;
        if(logCapacity(m_size - 1) < m_capacity) {
            
            try {
                newData = new T[logCapacity(m_size)];
                //cout << "Reallocating after erase!" << endl;
                reallocated = true;
                
            } catch (bad_alloc) {
                throw insufficientMemory(); 
            }
        }
        
        //Erase is safe to perform, rand_iterators become invalid
        m_randItrsValid = false;
    

        T* dataEnd = &m_data[m_size];  // one past the end of data in array
        T* ptr = itr.m_current;        // element to erase
        
        // to erase element at ptr, shift elements from ptr+1 to 
        // the end of the array down one position
        while ( ptr+1 != dataEnd ) {
            *ptr = *(ptr+1);
            ++ptr;
        }
        
        //Find index of element to be erased based on passed in iterator
        int index = 0;
        for(const_iterator tempItr = begin(); tempItr != itr; ++tempItr) {
            ++index;
        }
        
        //It is now safe to decrement m_size, erase has been performed
        --m_size;
        
        //
        if(reallocated) {
            
            //If array of new size can be created, update m_capacity of container
            //with new size
            m_capacity = logCapacity(m_size);
            
            for(int i = 0; i < m_size; ++i) {
                newData[i] = m_data[i];
            }
            //Delete old data
            delete [] m_data;
            //reassign m_data pointer to that of the newly allocated newData array
            m_data = newData;
        }
        
        return const_iterator(&m_data[index]);
    }
}

//const_iterator class implementation

template<typename T> sorted<T>::const_iterator::const_iterator() :
    m_current(NULL)
{}

template<typename T> sorted<T>::const_iterator::const_iterator(T* addr) :
    m_current(addr)
{}

template<typename T> bool sorted<T>::const_iterator::operator!=(const const_iterator& itr) {
    //Compare address of memory location contained in m_current pointers
    return m_current != itr.m_current;
}

template<typename T> 
typename sorted<T>::const_iterator sorted<T>::const_iterator::operator++() {
    //Use pointer arithmetic to advance down array
    ++m_current;
    return *this;
}

template<typename T> 
typename sorted<T>::const_iterator sorted<T>::const_iterator::operator++(int) {
    //Save state of current iterator
    const_iterator result(*this);
    //Advance down array (but don't return updated state)
    ++m_current;
    //return saved state of iterator
    return result;
}

template<typename T> 
const T& sorted<T>::const_iterator::operator*() {
    
    return *m_current;
}

//rand_iterator class implementation

//Default constructor, initialize m_permutation array pointer to null 
//(can be reassigned later)
template<typename T> 
sorted<T>::rand_iterator::rand_iterator() :
    m_current(NULL), m_currIndex(0), m_permutation(NULL), m_srtdPtr(NULL)
{}

//Basic destructor to free dynamically allocated permutation array
template<typename T> 
sorted<T>::rand_iterator::~rand_iterator() {
    delete [] m_permutation;
}

template<typename T> 
sorted<T>::rand_iterator::rand_iterator(sorted<T>* srtdPtr) throw (insufficientMemory) :
    //Initialize fields to default in case allocation of m_permutation array fails
    m_current(NULL), m_currIndex(0), m_permutation(NULL), m_srtdPtr(NULL)
{
    try {
        m_permutation = new int[srtdPtr->m_size];
    } catch (bad_alloc) {
        throw insufficientMemory();
    }
    
    //Fill m_permutation array with indices
    for(int i = 0; i < srtdPtr->m_size; ++i) {
        m_permutation[i] = i;
    }
    
    //Create random permutation
    srand(time(NULL));
    for(int i = 0, j; i < srtdPtr->m_size; ++i) {
        //Generate random index within array
        j = rand() % srtdPtr->m_size;
        //Perform swap of index numbers
        int temp = m_permutation[i];
        m_permutation[i] = m_permutation[j] ;
        m_permutation[j] = temp ;
    }
    
    //Link to associated container
    m_srtdPtr = srtdPtr;
    
}

template<typename T> 
sorted<T>::rand_iterator::rand_iterator(sorted<T>* srtdPtr, unsigned seed) 
throw (insufficientMemory) :
    //Initialize fields to default in case allocation of m_permutation array fails
    m_current(NULL), m_currIndex(0), m_permutation(NULL), m_srtdPtr(NULL) 
 {
    try {
        m_permutation = new int[srtdPtr->m_size];
    } catch (bad_alloc) {
        throw insufficientMemory();
    }
    
    //Fill m_permutation array with indices
    for(int i = 0; i < srtdPtr->m_size; ++i) {
        m_permutation[i] = i;
    }
    
    //Create random permutation    
    srand(seed);
    for(int i = 0, j; i < srtdPtr->m_size; ++i) {
        //Generate random index within array
        j = rand() % srtdPtr->m_size;
        //Perform swap of index numbers
        int temp = m_permutation[i];
        m_permutation[i] = m_permutation[j] ;
        m_permutation[j] = temp ;
    }
    
    //Link to associated container
    m_srtdPtr = srtdPtr;
    
}

template<typename T> 
sorted<T>::rand_iterator::rand_iterator(const rand_iterator& itr) throw (insufficientMemory) {

    try {
        m_permutation = new int[itr.m_srtdPtr->m_size];
    } catch (bad_alloc) {
        throw insufficientMemory();
    }
    
    //If m_permutation array can be allocated, copy the values of the 
    //rand_iterator passed in
    for(int i = 0; i < itr.m_srtdPtr->m_size; ++i) {
        m_permutation[i] = itr.m_permutation[i];
    }
    
    //Copy fields of passed in iterator
    m_current = itr.m_current;
    m_currIndex = itr.m_currIndex;
    m_srtdPtr = itr.m_srtdPtr;

}

template<typename T> 
typename sorted<T>::rand_iterator& sorted<T>::rand_iterator::operator=(const rand_iterator& itr) 
throw (insufficientMemory) {
    
    //Guard against self-assignment
    if ( this != &itr ) {
        
        try {
            int* memTest = new int[itr.m_srtdPtr->m_size];
            //If exception is not thrown and memory can be allocated, subsequently free 
            //that memory for new permutation
            delete [] memTest;
        } catch (bad_alloc) {
            throw insufficientMemory();
        }

        //We include the request to delete m_permutation AFTER the try-catch statement so that the
        //original object data is preserved (that is NOT deleted) if an exception is thrown. 
        //Therefore, the object is never modified if there is not enough memory in the heap to
        //perform reassignment.
        delete [] m_permutation;
        
        //It is now safe to allocate memory for the new m_permutation array
        m_permutation = new int[itr.m_srtdPtr->m_size];
        
        //Fill the new m_permutation with the data of the passed in rand_iterator
        for(int i = 0; i < itr.m_srtdPtr->m_size; ++i) {
            m_permutation[i] = itr.m_permutation[i];
        }
        
        //Copy fields of passed in iterator
        m_current = itr.m_current;
        m_currIndex = itr.m_currIndex;
        m_srtdPtr = itr.m_srtdPtr;
     
    }

    return *this;
}

template<typename T> 
const T& sorted<T>::rand_iterator::operator*() throw (invalidRandItr) {
    
    if(!m_srtdPtr->m_randItrsValid) {
        throw invalidRandItr("ERROR: rand_iterator cannot be dereferenced, container has been modified");
    }
        
    return *m_current;
}

template<typename T> 
bool sorted<T>::rand_iterator::operator!=(const rand_iterator& itr) throw (invalidRandItr) {
    
    if(!m_srtdPtr->m_randItrsValid || !itr.m_srtdPtr->m_randItrsValid) {
        throw invalidRandItr("ERROR: comparison cannot be performed, either container has been modified");
    }
    
    //Compare address of memory location contained in m_current pointers
    return m_current != itr.m_current;
}

template<typename T> 
typename sorted<T>::rand_iterator sorted<T>::rand_iterator::operator++() throw (invalidRandItr) {
    
    if(!m_srtdPtr->m_randItrsValid) {
        throw invalidRandItr("ERROR: pre-increment cannot be performed, container has been modified");
    }
    
    //Increment current index in m_permutations array
    ++m_currIndex;
    
    //If the index reaches the end of the m_permutations array, set m_current to one 
    //past the last element of the sorted<T> array. This way, it effectively makes it 
    //equal to the rndend() iterator and the != operator can be used easily
    if(m_currIndex == m_srtdPtr->m_size) {
        //Basically the same as re.m_current = &m_data[m_size]; in rndend()
        m_current = &(m_srtdPtr->m_data[m_srtdPtr->m_size]);
    
    //Otherwise, 
    } else {
        //Advance down array according to m_permutation order
        m_current = &(m_srtdPtr->m_data[m_permutation[m_currIndex]]);
    }
    
    return *this;
}

template<typename T> 
typename sorted<T>::rand_iterator sorted<T>::rand_iterator::operator++(int) throw (invalidRandItr) {
    
    if(!m_srtdPtr->m_randItrsValid) {
        throw invalidRandItr("ERROR: post-increment cannot be performed, container has been modified");
    }
    
    //Save state of current rand_iterator
    rand_iterator result(*this);
    
    //Increment current index in m_permutations array
    ++m_currIndex;
    
    //If the index reaches the end of the m_permutations array, set m_current to one 
    //past the last element of the sorted<T> array. This way, it effectively makes it 
    //equal to the rndend() iterator and the != operator can be used easily
    if(m_currIndex > m_srtdPtr->m_size - 1) {
        //Basically the same as re.m_current = &m_data[m_size]; in rndend()
        m_current = &(m_srtdPtr->m_data[m_srtdPtr->m_size]);
    
    //Otherwise, 
    } else {
        //Advance down array according to m_permutation order
        m_current = &(m_srtdPtr->m_data[m_permutation[m_currIndex]]);
    }
    
    //Return saved iterator state (although current state was changed above)
    return result;
}

template<typename T> 
void sorted<T>::rand_iterator::printPermutation() {
    
    //If the permutation array has been dynamically allocated, and the m_data array
    //it requires exists, print its indices and their corresponding elements of the m_data
    if(m_permutation != NULL && m_srtdPtr->m_data != NULL) {
        //Output template for user clarification
        cout << endl << "Permutation [index:data, ...]" << endl;
        
        cout << "[";
        for(int i = 0; i < m_srtdPtr->m_size; ++i) {
            cout << m_permutation[i] << ":" << m_srtdPtr->m_data[m_permutation[i]];
            if(i < m_srtdPtr->m_size - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl << endl;
        
    } else {
        cerr << "ERROR: Permutation array not initialized" << endl << endl;
    }
    
}

#endif
    