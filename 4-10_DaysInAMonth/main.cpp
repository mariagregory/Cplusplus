/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 * Purpose: Determine number of days in a given month and year  
 * 
 * Created on February 26, 2018, 11:51 AM
 */

#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    short days, month, year;
    bool leapY=false;

    cout<<"Hi,\nPlease tell me a month (1-12): ";
    do{
        cin>>month;
        if(month<1 || month>12) cout<<"Oh please, type a number between 1 and 12 (inclusive): "; 
    }while(month<1 || month>12);
    
    cout<<"Okay, now tell me a year: ";
    cin>>year;
    //check if this is a leap year
    if(year%100==0){ if(year%400==0) leapY=true; }
    else if(year%4==0) leapY=true;

    if(month==2) { 
        if(leapY) days=29;
        else days=28;
    } else if( (month<8 && month%2) || (month>=8 && month%2==0) ) { 
        //for odd months before august or even months starting august
        days=31;
    } else days=30;
    
    cout<<"There are "<<days<<" days in "<<month<<"/"<<year<<".\n\n";
    cout<<"Thank you for using this program.\nBye!";
    return 0;
}