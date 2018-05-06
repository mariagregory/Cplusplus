/**
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

class TimeOff { /// tracks # of hours and days off due to sick leave or vacations
    private: 
        char *name; /// employee's name
        char *empID; /// employee's ID
        short months; /// # of months worked
        NumDays maxVac; /// # of vacation days earned
        NumDays maxSick; /// # of paid sick leave days earned
        NumDays vacTkn; /// # of vacation days taken
        NumDays sickTkn; /// # of paid sick days taken
    public:
        TimeOff(const char*, const char*, short = 0); /// constructor accepts a name, ID, and # of months worked
        void setName(const char*); /// sets a worker's name
        void setId(const char*); /// sets a worker's ID
        /// sets earned # of paid vacation and sick leave days
        void setMax(short vac = 12, short sick = 8) { /// 12 hours of vacations and 8 hours of sick leave earned per month
            maxVac.stHours(vac*months);
            maxSick.stHours(sick*months);
        }
        void setMnths(short); /// sets # of months worked
        void setSick(short); /// accepts # of sick days taken
        void setVac(short); /// accepts # of vacation days taken
        char* getName() const { return name; } /// returns a worker's name
        char* getId() const { return empID; } /// returns a worker's ID
        NumDays getSick() const { return sickTkn; } /// returns # of sick leave days taken
        NumDays getVac() const { return vacTkn; } /// returns # of vacation days taken
        NumDays getMaxSick() const { return maxSick; } /// returns # of sick leave days earned
        NumDays getMaxVac() const { return maxVac; } /// returns # of vacation days earned
        short getMnths() const { return months; } /// returns # of months worked
        ~TimeOff(); /// destructor (deletes dynamic c-strings)
};
#endif /* TIMEOFF_H */
