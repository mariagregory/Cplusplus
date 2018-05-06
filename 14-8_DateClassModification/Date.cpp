/**
 * Author: Mariia Gregory
 * Created on March 27, 2018, 12:36 AM
 * Purpose: Date class specification
 */
#include "Date.h"
#include <cstring>
#include <string>
#include <cmath> // for abs()
using namespace std;

//constructor, when all arguments are provided
Date::Date(short m, short d, short y) {
    setDate(m,d,y);
}
Date::Date(Date &obj) { // copy constructor
    setDate(obj.month, obj.day, obj.year);
}
// Mutator functions:
//validate parameter values and assign them to member variables
void Date::setDate(short m, short d, short y) {
    year = y < 1600 ? 1600 : y>2100 ? 2100 : y;
    month = m<1 ? 1 : m>12 ? 12 : m;
    day = d<1 ? 1 : d>31 ? 31 : d;
    if(day>28) {
        if(m==2) { // February
            if( year%400==0 || (year%4==0 && year%100) ) {
                day=29; // leap year
            } else day=28;
        } else if( day>30 && ( (m<7 && m%2==0) || (m>8 && m%2) ) ) {
            day=30;
        }
    }
    setMonStr(month); // set value of monStr
}
// convert a month # to a corresponding string
void Date::setMonStr(const short m) { // PRIVATE function; called from setDate(...)
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
        case 12: strcpy(monStr,"December"); // 12 is a default case, actually, but just to be safe...
    }
}
// Overloading operator functions
Date* Date::operator++() { // prefix
    day++;
    if(day>28) { // the whole following block is skipped if the day is in a range 1-28
        if(month==2) { // February
            if(year%400==0 || (year%4==0 && year%100))  {// Leap year
                if(day==30) { setDate(3, 1, year); }
            }else if(day==29) { setDate(3, 1, year); }  // Non-leap year       
        } else if( (month<8 && month%2==0) || (month>7 && month%2)) { // 30-day-long months
            if(day==31) { setDate(month+1, 1, year); }
        } else if(month==12 && day==32) { // December
            setDate(1, 1, year+1);
        } else if(day==32) { setDate(month+1, 1, year); } // 31-day-long months, except December
    }
    return this;
}
Date* Date::operator--() { // prefix
    day--;
    if(day==0) { // the whole following block is skipped if the day > 0
        if(month==3) { // March
            if(year%400==0 || (year%4==0 && year%100))  {// Leap year
                setDate(2, 29, year);
            } else setDate(2, 28, year);  // Non-leap year       
        } else if(month==1) { //January
            setDate(12, 31, year-1);
        } else if( (month<9 && month%2==0) || month==9 || month==11) { 
         // months following 31-day-long months, except January
            setDate(month-1, 31, year);
        } else if( month==5 || month==7 || month==10 || month==12) {
          // months following 30-day-long months
            setDate(month-1, 30, year); 
        } 
    }
    return this;
}
Date* Date::operator++(int) { // postfix
    temp = this;
    this->operator++(); // call prefix ++ operator
    return temp; // return a previous version (before incrementing)
}
Date* Date::operator--(int) { // postfix
    temp = this;
    this->operator--(); // call prefix -- operator
    return temp; // return a previous version (before incrementing)
}
int Date::operator-(Date &other) {
    if(month==other.month && year==other.year) {
        return abs(other.day-day);
    } // when different months / years
    int days = 0, mon1, mon2, year1=0, year2=0, years=0;
    if(year != other.year) { // when years differ
        year1 = year < other.year ? year : other.year;
        year2 = year > other.year ? year : other.year;
        mon1 = year==year1 ? month : other.month;
        mon2 = year==year2 ? month : other.month;
        years = abs(other.year-year);
//        days += years*365 + years/4; // 365 days per year, adjust for a leap year
    } else { // if the years are the same
        mon1 = month <= other.month ? month : other.month;
        mon2 = month > other.month ? month : other.month;
    }
    if(mon2==month) { days+=day; days+=CALNDR[mon1-1]-other.day; } // **************************  for a non-leap year
    else{ days+=other.day; days+=CALNDR[mon1-1]-day; } // ************************** for a NON-leap year
    
    if(!years) { // when years are the same
        for(short i=mon1; i<mon2-1; i++) {
            days+=CALNDR[i]; // for a non-leap year
            if(i==1) {//February
                if(year%400==0 || (year%4==0 && year%100))  // Leap year
                    days++; // adjust for February 29
            }
        }
    } else { // if years differ
        for(short i=mon1; i<12; i++) {
            days+=CALNDR[i]; // for a non-leap year
            if(i==1) {//February
                if(year%400==0 || (year%4==0 && year%100))  // Leap year
                    days++; // adjust for February 29
            }
        } 
        for(short i=0; i<mon2-1; i++) {
            days+=CALNDR[i]; // for a non-leap year
            if(i==1) {//February
                if(year%400==0 || (year%4==0 && year%100))  // Leap year
                    days++; // adjust for February 29
            }
        }
        if(years>1) {
            days += (years-1)*365; // 365 days per year
            for(short i=year1+1; i<year2; i++) {
                if(i%400==0 || (i%4==0 && i%100)) // Leap year
                    days++; // adjust for February 29
            }
        }
    }
    return days;
}
//Overloaded print functions, for different display formats
void Date::print() { // Print in a default format mm/dd/yyyy
    if(month<10) cout<<"0";
    cout<< month <<"/";
    if(day<10) cout<<"0";
    cout<<day<<"/"<<year;
}
void Date::print(char *m) { //Print in American format <Month dd, yyyy>
    cout<<monStr << " " << day <<", "<<year;
}
void Date::print(short d, char* m) { // Print in a European format: <dd Month yyyy>
    cout<< day << " "<<monStr << " "<<year;    
}