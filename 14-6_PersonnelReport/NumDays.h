/**
 * File:   NumDays.h
 * Author: Mariia Gregory
 *
 * Created on May 4, 2018, 8:05 AM
 * Purpose: NumDays class declaration
 */

#ifndef NUMDAYS_H
#define NUMDAYS_H

class NumDays { /// tracks # of hours and days, worked or taken off by an employee (or a group of employees)
    private: 
        short hours; ///# of hours
        float days; ///# of days
    public:
        NumDays(short = 0); /// a constructor, which initializes # of hours and days
        void stHours(short); /// sets # of hours (days are also updated)
        void stDays(short); /// sets # of days
        short gtHours() const { return hours; } /// returns # of hours
        float gtDays() const { return days; } /// returns # of days
        NumDays operator+(NumDays &); /// add hours of 2 workers
        NumDays operator-(NumDays &); /// subtract the 2nd worker's hours from the 1st one
        NumDays operator++(); /// prefix increment
        NumDays operator--(); /// prefix decrement
        NumDays operator++(int); /// postfix increment
        NumDays operator--(int); /// postfix increment
};
#endif /* NUMDAYS_H */