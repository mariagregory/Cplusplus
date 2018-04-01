/* 
 * File:   Person.cpp
 * Author: Mariia Gregory
 *
 * Created on March 28, 2018, 10:37 AM
 * Purpose: Specification for Person class
 */

#include <cstdlib>
#include <cstring>
#include "Person.h"

//constructor, when no arguments are provided
Person::Person() {
    name = new char[31];
    address = new char[51];
    phone = new char[21];
    setName("");
    age = 0;
    setAddr("");
    setPhon("");
}
//constructor, when all arguments are provided
Person::Person(const char *n, short yOld, const char *add, const char *ph) {
    name = new char[51]; // it allocates only 8 bytes, though, so sizeof(name) is now 8, unless I assign smth
    address = new char[61]; // ... if I declared this as a static c-string with this size, it would have exactly this size
    phone = new char[21];
    setName(n);
    setAge(yOld);
    setAddr(add);
    setPhon(ph);
}
// Mutator functions:
//validate parameter values and assign them to member variables
void Person::setName(const char *n) {
    short maxLen = 60;
    if(strlen(n)>maxLen) {
        strncpy(name,n,maxLen);
        name[maxLen]='\0';
    } else if(!strlen(n)) strcpy(name,"---John Doe---"); 
    else strcpy(name,n);
}
void Person::setAge(short yOld) {
    age = yOld>0 ? yOld<123 ? yOld : 100 : 0;
}
void Person::setAddr(const char* add) {
    short maxLen = 59;
    if(strlen(add)>maxLen) {
        strncpy(address,add,maxLen);
        address[maxLen]='\0';
    } else if(!strlen(add)) strcpy(address,"--"); 
    else strcpy(address,add);
}
void Person::setPhon(const char* ph) {
    short maxLen = 19;
    if(strlen(ph)>maxLen) {
        strncpy(phone,ph,maxLen);
        phone[maxLen]='\0';
    } else if(!strlen(ph)) strcpy(phone,"#"); 
    else strcpy(phone,ph);
}