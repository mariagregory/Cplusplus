/* 
 * File:   TimeOff.h
 * Author: Mariia Gregory
 *
 * Created on May 4, 2018, 10:01 AM
 * Purpose: TimeOff class declaration
 */
#ifndef TIMEOFF_H
#define TIMEOFF_H
#include "NumDays.h"
#include <iostream>
using namespace std;

class TimeOff {
    private: 
        char *name;
        char *empID;
        NumDays maxVac; // 6-week paid vacation? That's great!
        NumDays maxSick; // 1 week of paid sick leave
        NumDays maxUnpd; // 2 weeks of unpaid sick leave
        NumDays vacTkn; // # of vacation days taken
        NumDays sickTkn; // # of paid sick days taken
        NumDays unpdTkn; // # of unpaid sick days taken
        void setUnpd(short); // sets # of unpaid sick leave days taken. Called from setSick() and constructor
    public:
        TimeOff(const char*, const char*, short = 0, short = 0); // # of vacation and sick days taken are 0 by default
        void setName(const char*);
        void setId(const char*);
        // sets max allowed # of vacations and sick leave days (paid and unpaid) in the company
        void setMax(short vac = 30, short sick = 7, short unpaid = 14) { // vac = 240 hours / 8 hours = 30 days, etc.
            maxVac.stDays(vac);
            maxSick.stDays(sick);
            maxUnpd.stDays(unpaid);
        }
        void setSick(short); // accepts # of days
        void setVac(short); // accepts # of days
        char* getName() const { return name; }
        char* getId() const { return empID; }
        NumDays getSick() const { return sickTkn; } // returns # of days
        NumDays getVac() const { return vacTkn; } // returns # of days
        NumDays getUnpd() const { return unpdTkn; } // returns # of days
        ~TimeOff();
};
#endif /* TIMEOFF_H */