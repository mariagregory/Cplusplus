/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 * Created on March 8th, 2018, 1:20 PM
 * Purpose: Create a date class object.
 *          Define 3 overloaded member functions to display a date in 3 different formats
 */
//System libraries
#include <iostream>  //I/O Library
#include <cstdlib>
#include <cstring>
#include <sstream>
#include "Date.h"
using namespace std;
//User Libraries
//Global Constants - Math, Science, Conversions, 2D Array Sizes
//Function Prototypes

//Executions Begin Here
int main(int argc, char** argv) {
    Date date;   
    // Initial output (with default values 01/01/1901
    cout<<"Default date:\n";
    date.print(); // default format mm/dd/yyyy
    date.print(date.monName()); //Month dd, yyyy
    date.print(date.getDay(), date.monName()); // dd Month yyyy
    
//  Declare variables for a new date
    short mon, day, year;
    // Taking user-defined values
    cout<<"\nEnter a new date, as prompted: \n";
    cout<<"Month (a number 1-12): ";
    cin>>mon;
//    clear buffer in case user entered something inadequate
    if(!cin) { cin.clear(); cin.ignore(100, '\n'); }
    cout<<"Day (a number 1-31): ";
    cin>>day;
   if(!cin) { cin.clear(); cin.ignore(100, '\n'); }
    cout<<"Year (a 4-digit number <= 2050): ";
    cin>>year;
   if(!cin) { cin.clear(); cin.ignore(100, '\n'); }
    date.setDate(mon,day,year);

    date.print(); // default format mm/dd/yyyy
    date.print(date.monName()); //Month dd, yyyy
    date.print(date.getDay(), date.monName()); // dd Month yyyy

    return 0;
}
