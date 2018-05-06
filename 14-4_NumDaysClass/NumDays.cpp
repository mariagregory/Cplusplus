/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on May 4, 2018, 8:02 AM
 * Purpose: Function definitions for NumDays class
 */
#include "NumDays.h"
using namespace std;

NumDays::NumDays(short hours) {
    stHours(hours);
}
void NumDays::stHours(short hours) {
    this->hours = hours>=0 ? hours : (-1)*hours;
    days = static_cast<float>(this->hours)/8.0;
}
void NumDays::stDays(short days) {
    this->days = days>=0 ? days : (-1)*days;
    this->hours = this->days * 8;
}

NumDays NumDays::operator+(NumDays &other) {
    if(other.hours>0) { NumDays third(hours+other.hours); return third; }
    else return *this;
}
NumDays NumDays::operator-(NumDays &other) {
    if(other.hours>=hours) { NumDays third(hours-other.hours); return third; }
    else return *this;
}
NumDays NumDays::operator++() { stHours(hours+1); return *this; } // prefix increment
NumDays NumDays::operator--() { stHours(hours-1); return *this; } // prefix decrement
NumDays NumDays::operator++(int) {  // postfix increment
    NumDays temp(hours); 
    stHours(hours+1); 
    return temp;
}
NumDays NumDays::operator--(int) { // postfix decrement
    NumDays temp(hours); 
    stHours(hours-1); 
    return temp;
}