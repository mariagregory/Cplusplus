/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 * Created on March 8th, 2018, 1:20 PM
 * Purpose: Create a date class object.
 *          Define 3 overloaded member functions to display a date in 3 different formats
 *          Define overloaded pre-/postfix ++/-- operators
 *          Define overloaded - operator to find a difference in days between 2 dates              
 */
//System libraries
#include <iostream>  //I/O Library
#include <iomanip> // setw()
//#include <cstdlib>
#include <cstring> // atoi(...)
#include <string> // for takeNum(...)
#include <ctime> // for random month, day, and year generation
#include "Date.h"
using namespace std;
//User Libraries
//Global Constants - Math, Science, Conversions, 2D Array Sizes
//Function Prototypes
short takeNum(short, short);
void showTbl(Date*, short);

//Executions Begin Here
int main(int argc, char** argv) {
    srand(time(0));
    short mon, day, year; //  Variables for a new date    
    cout<<"\nEnter a date: \n";
    cout<<"\tMonth (1-12): ";
    mon = takeNum(1,12);
    cout<<"\tDay (1-31): ";
    day = takeNum(1,31);
    cout<<"\tYear: ";
    year = takeNum(1600,2100);
    
    Date date(mon, day, year); // declare and initialize a Date object
    cout<<"Here is your date printed using an overloaded << operator:\n";
    cout<<date<<endl;
    
    Date other;
    cout<<"Now, please enter another date in \"mm dd yyyy\" format:\n";
    cin>>other;
//    { cout<<"Please don\'t try anything stupid!\n";
//    cout<<"Enter a date in \"mm dd yyyy\" format:\n";
//  }
    cout<<"The date you entered is ";
    cout<<other<<endl;
    
    cout<<"\nNow, I will create 3 more dates.\n";
    
    Date dates[5] = { date, other, { rand()%12+1, rand()%31+1, year },
        { rand()%12+1, rand()%31+1, rand()%(2100-1600)+1600 },
        { rand()%12+1, rand()%31+1, rand()%(2100-1600)+1600 },
    };
    
    showTbl(dates, 5);
    cout<<"\nIncrementing...\n";
    for(short i=0; i<5; i++) { ++dates[i]; }
    showTbl(dates, 5);
    cout<<"\nIncrementing again...\n";
    for(short i=0; i<5; i++) { dates[i]++; }
    showTbl(dates, 5);
    cout<<"\nDecrementing...\n";
    for(short i=0; i<5; i++) { --dates[i]; }
    showTbl(dates, 5);
    cout<<"\nDecrementing again...\n";
    for(short i=0; i<5; i++) { dates[i]--; }
    showTbl(dates, 5);
    
    cout<<"\nDifference between dates:\n";
    for(short i=0; i<4; i++) {
        cout<<"\t"; dates[i].print();
        cout<<" - "; dates[i+1].print();
        cout<<" = "<<dates[i]-dates[i+1]<<" days.\n";
    }

    return 0;
}

void showTbl(Date *date, short size) {
    cout<<endl;
    for(short i=0; i<size; i++) {
//        if(!i) {
//            cout<<left<<setw(7)<<""<<"| Format 1\tFormat 2\t\tFormat 3"<<endl;
//        }
        cout<<"Date "<<i+1<<" | ";
        date[i].print(); // default format mm/dd/yyyy
        cout<<"\t";
        date[i].print(date[i].getMonStr()); //Month dd, yyyy
        cout<<"\t\t";
        date[i].print(date[i].getDay(), date[i].getMonStr()); // dd Month yyyy
        cout<<endl;
    }
}
// Take and validate user's input for a number in a range min-max
short takeNum(short min, short max) {
    string input;
    short result;
    bool valid;
    
    do {
        valid = false;
        getline(cin, input);
        if(!input.length()) return min; // if the user just pressed Enter, return the min value
        for(short i=0; i<input.length(); i++) {
            if(!isdigit(input[i])) { cout<<"Numbers only please: "; break; }
            // no need to compare with min and max in this case because the largest allowed 4-digit input cannot exceed 9999 anyway
            if(i==input.length()-1) valid = true;
        }
        if(valid) { 
            result = atoi(input.c_str());
            if(!result || result<min || result>max) {
                valid = false;
                cout<<"Oh please... Enter a number between "<<min<<" and "<<max<<": ";
            }
        }
    }while(!valid);
    return result;
}