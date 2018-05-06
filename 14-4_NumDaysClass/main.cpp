/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on May 4, 2018, 8:02 AM
 * Purpose: Set # of hours worked by employees and translate them to days
 *          Add # of hours for 2 workers, subtract one worker's hours from another's
 *          Increment and decrement worker's hours.  
 */
#include <iostream>
#include <iomanip>
#include <cmath>
#include "NumDays.h"
using namespace std;

// Execution
int main(int argc, char** argv) {
    NumDays workers[3] = { 8,15,25 }; // number in initialization list act like constructor parameters. Woo-Hoo!
    
    for(short i=0; i<3; i++) {
        cout<<"Worker "<<i+1<<" worked "<<fixed<<setprecision(0)<<workers[i].gtHours()<<" hours,";
        cout<<" or "<<fixed<<setprecision(2)<<workers[i].gtDays()<<" days.\n";
    } cout<<endl;
    for(short i=0; i<2; i++) {
        NumDays couple = workers[i]+workers[i+1];
        cout<<"Together workers "<<i+1<<" and "<<i+2<<" worked ";
        cout<<fixed<<setprecision(0)<<couple.gtHours()<<" hours,";
        cout<<" or "<<fixed<<setprecision(2)<<couple.gtDays()<<" days.\n";
        cout<<"One of them worked " << fixed<<setprecision(0);
        cout<<abs( (workers[i]-workers[i+1] ).gtHours() )<<" hours more than the other.\n\n";
    } cout<<endl;
    for(short i=0; i<3; i++) {
        cout<<"After incrementing worker "<<i+1<<" hours: ";
        cout<<fixed<<setprecision(0)<<workers[i].gtHours()<<" + 1 = ";
        cout<<(++workers[i]).gtHours()<<" hours, or ";
        cout<<fixed<<setprecision(2)<<workers[i].gtDays()<<" days.\n"; 
        workers[i]++;
        cout<<"After incrementing again, it\'s ";
        cout<<fixed<<setprecision(0)<<workers[i].gtHours()<<" hours,";
        cout<<" or "<<fixed<<setprecision(2)<<workers[i].gtDays()<<" days.\n\n";
    }
    return 0;
}