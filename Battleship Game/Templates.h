/* 
 * File:   Templates.h
 * Author: Mariia Gregory
 *
 * Created on May 15, 2018, 1:30 PM
 * Purpose: Specification file for Board class
 */

#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <cstdlib>
#include <new> // for bad_alloc
using namespace std;

template<class T> /// template in a separate .H file because it doesn't link properly when in main.
T* alloc(const short &size) { // dynamically allocates memory
    try { 
        T *arr = new T[size];
        return arr;
    }
    catch(bad_alloc) { 
        cout<<"Error: Insufficient memory.\n";
        exit(EXIT_FAILURE);
    } 
}
#endif /* TEMPLATES_H */