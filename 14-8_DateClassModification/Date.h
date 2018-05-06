/**
 * File:   Date.h
 * Author: Mariia Gregory
 *
 * Created on March 27, 2018, 12:10 PM
 * Purpose: Date class declaration
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>
using namespace std;

class Date; // Forward Declaration
ostream &operator<< (ostream &, const Date &);
istream &operator>> (istream &, Date &);
const short CALNDR[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; // in a non-leap year

class Date {
    private:
        short month, day, year;
        char *monStr;
        Date *temp; // for returning an non-updated object in postfix ++/-- operator functions 
        void setMonStr(const short); // private function; called from setDate(...)
    public:
        Date(short = 1, short = 1, short = 1901 );
        Date(Date &); // copy constructor
        void setDate(short, short, short);
        short getMon() const { return month; }
        char* getMonStr() const { return monStr; };
        short getDay() const { return day; }
        short getYear() const {return year; }
        Date* operator++(int); // postfix
        Date* operator++(); // prefix
        Date* operator--(int); // postfix
        Date* operator--(); // postfix
        int operator-(Date &); // returns # of days between 2 dates
        void print();//short,short,short);
        void print(char*);
        void print(short, char*);
        ~Date() { delete monStr; }
        //Friend - overloaded input stream operator
        friend istream &operator>> (istream &, Date &);
};

#endif /* DATE_H */

