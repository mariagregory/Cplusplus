/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on April 30, 2018, 9:42 AM
 * Purpose: Translate a number from 1 to 365 to a date
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <sstream>
#include "DayOfYear.h"
using namespace std;

/*
 * 
 */

int takeNum(int, int);

void DayOfYear::print() {
    string date;
    string month;
    int dayCount = 0;
    for(short i=0; i<=DEC; i++) {
        dayCount += daysIn[i];
        if(day <= dayCount) {
            month = months[i];
            date = months[i];
            cout<<date<<" "<<day-dayCount+daysIn[i]<<".\n";
            break;
        }
    }
}
int main(int argc, char** argv) {
    cout<<"Hi,\nPlease enter a day of the year as a number from 1 to 365: ";
    int figure = takeNum(1, 365);
    DayOfYear date(figure);
    cout<<"The date is ";
    date.print();
    return 0;
}

int takeNum(int min, int max) {
    string input;
    int result;
    bool valid;

    do {
        valid = false;
        getline(cin, input);
        for(short i=0; i<input.length(); i++) {
            if(!isdigit(input[i])) { cout<<"Digits only please: "; break; }
            // no need to compare with min and max in this case because the largest allowed 4-digit input cannot exceed 9999 anyway
            if(i==input.length()-1) valid = true;
        }
        if(valid) { 
            result = atoi(input.c_str());
            if(result<min || result>max) {
                valid = false;
                cout<<"Oh please... Enter a number in a range "<<min<<" to "<<max<<endl;
            }
        }
    }while(!valid);
    return result;
}
