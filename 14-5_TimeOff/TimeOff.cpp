/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on May 4, 2018, 8:02 AM
 * Purpose: Function definitions for TimeOff class
 */
#include "TimeOff.h"
#include <cstring>
#include <iostream>
using namespace std;

// Constructor accepting 4 arguments, the last 2 have default values if not provided
TimeOff::TimeOff(const char *name, const char *id, short vacatn, short sick) {
    setName(name);
    setId(id);
    setMax(); // sets max allowed # of vacations and sick leave days (paid and unpaid) in the company
    setVac(vacatn); // sets # of vacation days taken
//    if # of sick days taken are higher than the max # of paid sick days, set the difference as unpaid sick leave 
    if(sick > maxSick.gtDays()) {
        setSick(maxSick.gtDays());
        setUnpd(sick - maxSick.gtDays());
    } else { setSick(sick); setUnpd(0); }
}
void TimeOff::setName(const char *name){ 
    this->name = new char[20]; // allocate memory
    strcpy(this->name, name); 
}
void TimeOff::setId(const char *id)  { 
    this->empID = new char[7]; // allocate memory
    strcpy(empID, id); 
}
// Set # of sick days taken. If > paid sick days allowed, the rest is unpaid
void TimeOff::setSick(short sick) { 
    if(sick > maxSick.gtDays()) { 
        sickTkn.stDays(maxSick.gtDays()); 
        setUnpd(sick - maxSick.gtDays());
    } else if(sick>0) { sickTkn.stDays(sick); }
}
// Set # of vacation days taken.
void TimeOff::setVac(short vacatn) { 
    if(vacatn>0) { vacTkn.stDays(vacatn); } 
    if(vacatn>maxVac.gtDays()) { vacTkn.stDays(maxVac.gtDays()); }
}
// Set # of unpaid sick days taken. PRIVATE function. Called from setSick(...) and TimeOff(...)
void TimeOff::setUnpd(short unpaid) { 
    if(unpaid>=0) { unpdTkn.stDays(unpaid); }
    if(unpaid>maxUnpd.gtDays()) { unpdTkn.stDays(maxUnpd.gtDays()); }
}
TimeOff::~TimeOff() { // Destructor
    delete [] name; // deallocate memory
    delete [] empID;
}