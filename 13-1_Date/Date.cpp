/* 
 * Author: Mariia Gregory
 * Created on March 27, 2018, 12:36 AM
 * Purpose: Date class specification
 */
#include "Date.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>
using namespace std;

//constructor, when all arguments are provided
Date::Date(short m, short d, short y) {
    setDate(m,d,y);
}
// Mutator functions:
//validate parameter values and assign them to member variables
void Date::setDate(short m, short d, short y) {
    year = y < 1000 ? 1000 : y>2050 ? 2050 : y;
    month = m<1 ? 1 : m>12 ? 12 : m;
    day = d<1 ? 1 : d>31 ? 31 : d;
    if(day==31) {
        if(m==2) { // February
            if(year%4==0) day=29; // leap year
            else day=28;
        } else if((m<8 && m%2==0) || (m>7 && m%2) ) {
            day=30;
        }
    }
    setMon(month);
}
// convert a month # to a corresponding string
void Date::setMon(const short m) { 
    monStr = new char[10];
    switch(m) {
        case 1: { strcpy(monStr,"January"); break; }
        case 2: { strcpy(monStr,"February"); break; }
        case 3: { strcpy(monStr,"March"); break; }
        case 4: { strcpy(monStr,"April"); break; }
        case 5: { strcpy(monStr,"May"); break; }
        case 6: { strcpy(monStr,"June"); break; }
        case 7: { strcpy(monStr,"July"); break; }
        case 8: { strcpy(monStr,"August"); break; }
        case 9: { strcpy(monStr,"September"); break; }
        case 10: { strcpy(monStr,"October"); break; }
        case 11: { strcpy(monStr,"November"); break; }
        default: strcpy(monStr,"December");
    }
}
//Overloaded print functions, for different display formats
void Date::print() { // default format mm/dd/yyyy
    if(month<10) cout<<"0";
    cout<< month <<"/";
    if(day<10) cout<<"0";
    cout<<day<<"/"<<year<<endl;
}
void Date::print(char *m) { //Month dd, yyyy
    cout<<monStr << " " << day <<", "<<year<<endl;
}
void Date::print(short d, char* m) { // dd Month yyyy
    cout<< day << " "<<monStr << " "<<year<<endl;    
}