/* 
 * File:   Retail.cpp
 * Author: Mariia Gregory
 *
 * Created on March 28, 2018, 07:37 PM
 * Purpose: Function definitions for inventory item's class
 */
#include <cstdlib>
#include <cstring>
#include "Invntry.h"

//when all arguments are provided
Invntry::Invntry(short n, short q, float c) {
    setItNo(n);
    setQnty(q);
    setCost(c);
    setTot();
}
// Mutator functions:
//validate parameter values and assign them to member variables
void Invntry::setItNo(short n) {
    itemNo = n>=0 ? n<=32000 ? n : 32000 : 0;
}
void Invntry::setQnty(short q) {
    qnty = q>=0 ? q<=32000 ? q : 32000 : 0;
    setTot();
}
void Invntry::setCost(float c) {
    cost = c>=0 ? c : 0;
    setTot();
}
void Invntry::setTot() {
    total = qnty*cost;
}