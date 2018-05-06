/* 
 * File:   Numbers.h
 * Author: Mariia Gregory
 *
 * Created on April 30, 2018, 9:42 AM
 * Purpose: DayOfYear class declaration
 */

#ifndef DAYOFYEAR_H
#define DAYOFYEAR_H

#include <string>
using namespace std;

enum MON { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEPT, OCT, NOV, DEC };
const string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const int daysIn[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        
class DayOfYear {
    private:
        int day;
        string month;  
    public:
        DayOfYear(int num = 1) { day = num >=1 ? num<=365 ? num : 365 : 1; } // constructor with a default parameter
        void print();
};
#endif /* DAYOFYEAR_H */