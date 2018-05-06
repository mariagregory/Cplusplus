/**
 * File:   TimeOff.cpp
 * Author: Mariia Gregory
 *
 * Created on May 4, 2018, 8:02 AM
 * Purpose: Function definitions for TimeOff class
 */
#include "TimeOff.h"
#include <cstring>
#include <iostream>
using namespace std;

/// Constructor accepting 3 arguments, the last one has a default 0 value, if not provided
TimeOff::TimeOff(const char *name, const char *id, short months) {
    setName(name);
    setId(id);
    setMnths(months);
}
void TimeOff::setName(const char *name){ /// sets a worker's name
    this->name = new char[20]; /// allocate memory for a c-string
    strcpy(this->name, name); 
}
void TimeOff::setId(const char *id)  {  /// sets a worker's id
    this->empID = new char[7]; /// allocate memory for a c-string
    strcpy(empID, id); 
}
void TimeOff::setMnths(short months) { /// sets # of months worked
    this->months = months>0 ? months : 0;
    setMax(); /// every time # of months is supplied/updated, recalculate # of vacation and sick leave days earned
}
/// Set # of sick days taken
void TimeOff::setSick(short sick) { 
    if(sick>0) sickTkn.stDays(sick);
    else sickTkn.stDays(0);
}
/// Set # of vacation days taken.
void TimeOff::setVac(short vacatn) { 
//    if(vacatn>maxVac.gtDays()) vacTkn.stDays(maxVac.gtDays()); 
    if(vacatn>0) vacTkn.stDays(vacatn);
}
TimeOff::~TimeOff() { /// Destructor
    delete [] name; /// deallocate memory for dynamic c-strings
    delete [] empID;
}
