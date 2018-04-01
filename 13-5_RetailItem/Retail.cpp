/* 
 * File:   Retail.cpp
 * Author: Mariia Gregory
 *
 * Created on March 28, 2018, 07:37 PM
 * Purpose: Specification (member function definitions) for Retail class
 */

#include <cstdlib>
#include <cstring>
#include "Retail.h"

//constructor, when no arguments are provided
Retail::Retail() {
    descr = new char[31];
    setDesc("");
    onHand=0;
    price=0;
}
//constructor, when all arguments are provided
Retail::Retail(const char *d, short q, float p) {
    descr = new char[31]; // it allocates only 8 bytes, though, so sizeof(name) is now 8, unless I assign smth
    setQnty(q);
    setPrce(p);
}
// Mutator functions:
//validate parameter values and assign them to member variables
void Retail::setDesc(const char *d) {
    short maxLen = 30;
    if(strlen(d)>maxLen) {
        strncpy(descr, d, maxLen);
        descr[maxLen]='\0';
    } else if(!strlen(d)) strcpy(descr,"--Some thingy--");
    else strcpy(descr, d);
}
void Retail::setQnty(short q) {
    onHand = q>=0 ? q<=32000 ? q : 32000 : 0;
}
void Retail::setPrce(float p) {
    price = p>=0 ? p : 0;
}