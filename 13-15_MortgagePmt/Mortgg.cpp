/* 
 * File:   Mortgg.cpp
 * Author: Mariia Gregory
 *
 * Created on March 29, 2018, 12:08 PM
 * Purpose: Specification file for the mortgage (Mortgg) class
 */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "Mortgg.h"
using namespace std;

//constructor, when all arguments are provided
Mortgg::Mortgg(float pv, float yR, short ys) {
    setPV(pv);
    setYRte(yR);
    setYrs(ys);
}
// Mutator functions:
//validate parameter values and assign them to member variables
void Mortgg::setPV(float pv) {
    loanAmt = pv>0 ? pv : pv<0 ? -pv : 0;
//    setPmt();
}
void Mortgg::setYRte(float yR) {
    anRate = yR>1 ? yR : yR<0 ? -yR : 1;
//    setPmt();
}
void Mortgg::setYrs(short ys) {
    years = ys>1 ? ys : ys<0 ? -ys : 1;
    setPmt();
}
// calculate monthly payment
void Mortgg::setPmt() {
//  to get a value of % monthly rate, we divide the annual rate by 12 and also by 100%
//  to get total # of month, we * year by 12
    float term = pow( (1+anRate/12/100),years*12); // term is (1+r)^n
//    cout<<"Term is "<<term<<endl;
    monPmt = loanAmt*(anRate/12/100);
    monPmt *= term / (term-1);
}
//calculate total payments: loan amount + all the accumulated interest
float Mortgg::getTot() {
    total = monPmt*years*12;
}