/* 
 * File:   NumDays.h
 * Author: Mariia Gregory
 *
 * Created on May 4, 2018, 8:05 AM
 * Purpose: NumDays class declaration
 */

#ifndef NUMDAYS_H
#define NUMDAYS_H

class NumDays {
    private: 
        short hours;
        float days;
    public:
        NumDays(short);
        void stHours(short);
        void stDays(short);
        short gtHours() const { return hours; }
        float gtDays() const { return days; }
        NumDays operator+(NumDays &);
        NumDays operator-(NumDays &);
        NumDays operator++();
        NumDays operator--();
        NumDays operator++(int);
        NumDays operator--(int);
};
#endif /* NUMDAYS_H */