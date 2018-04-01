/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on March 29, 2018, 12:08 PM
 * Purpose: Calculate monthly mortgage payment based on provided data
 *          Create a mortgage class object; use its member variables and member functions
 */
//System libraries
#include <cstdlib>
#include <iostream>
#include <iomanip>
# include "Mortgg.h"
using namespace std;
//User libraries
// Global constants: math, science, conversion factors, 2D array columns
// Function prototypes
void show(Mortgg &); // Display the data and the calculated payment
Mortgg *newLoan(float, float, short); // Dynamically creates another mortgage object
void compare(Mortgg &, Mortgg &); // displays a table comparing 2 mortgages
template <class T> void getVal(T &); // take and validate user's input

// Execution
int main(int argc, char** argv) {
    float loan, rate; // to store user-specified values
    short years; // ... before setting them as a mortgage object's data
    
    cout<<"This program calculates monthly mortgage payments.\n\n";
    cout<<"Please enter the loan amount, in $ ";
    getVal(loan); // take and validate user's input
    cout<<"The annual interest rate, in % ";
    getVal(rate); // take and validate user's input
    cout<<"How many years will you pay? ";
    getVal(years); // take and validate user's input
    cout<<"Thank you.\n\n";
    
    Mortgg mort(loan, rate, years); // loan, annual rate, years
    show(mort); // display data and results in the screen
    
    cout<<"\nNow, try another mortgage, with different values.\n";
    Mortgg *other = newLoan(loan, rate, years); // Dynamically create another mortgage object
    compare(mort, *other); // display table comparing 2 mortgages
    
    cout<<"\nThank you for using this program.\nBye!\n";
    delete other;
    
    return 0;
}
// take and validate user's input; possible T's are float and short
template <class T> void getVal(T &value) {
    cin>>value;
    while(!cin || value<=0) {
       cin.clear(); cin.ignore(100, '\n'); 
       cout<<"Please enter a positive number: ";
       cin>>value;
    }
}
// Display the data and the calculated payment
void show(Mortgg &m) {
    cout<<"Loan: $"<<fixed<<setprecision(2)<<m.getPV()<<endl;
    cout<<"Annual rate: "<<fixed<<setprecision(1)<<m.getRate()<<"%"<<endl;
    cout<<"Years: "<<m.getYrs()<<endl;
    cout<<"Monthly payment: $"<<fixed<<setprecision(2)<<m.getPmt()<<endl;
    cout<<"In total, $"<<m.getTot()<<" will be paid to repay $"<<m.getPV()<<" loan,\n";
    cout<<"Which is $"<<m.getTot()-m.getPV()<<" ("<< fixed<<setprecision(0);
    cout<<100*(m.getTot()-m.getPV())/m.getPV()<<"%) more than the loan itself.\n";
}
// Ask user for new numbers and set new values to another mortgage object
Mortgg *newLoan(float loan, float rate, short years) {
    Mortgg *m = new Mortgg(); // simply copy the values from the argument to the newly created object
    cout<<"Loan amount, $ ";
    getVal(loan);
    m->setPV(loan);
    cout<<"Annual interest rate, % ";
    getVal(rate);
    m->setYRte(rate);
    cout<<"For how many years? ";
    getVal(years);
    m->setYrs(years);
    cout<<endl;
    return m;
}
// display a table comparing 2 mortgages
void compare(Mortgg &m1, Mortgg &m2) {
    short w=12;
    float compInt; // to hold a compound interest, as % of initial loan
    
    for(short i=0; i<4*w; i++) cout<<"_"; cout<<endl;
    cout<<left;
    cout<<setw(2*w)<<"Loan"<<"$"<<setw(w)<<fixed<<setprecision(2);
    cout<<right<<m1.getPV()<<setw(w)<<m2.getPV()<<endl;
    cout<<left<<setw(2*w)<<"Annual rate"<<setw(w)<<fixed<<setprecision(1);
    cout<<right<<m1.getRate()<<"%"<<setw(w-1)<<m2.getRate()<<"%"<<endl;
    cout<<left<<setw(2*w)<<"Years"<<setw(w-2)<<fixed<<setprecision(0);
    cout<<right<<m1.getYrs()<<setw(w)<<m2.getYrs()<<endl;
    cout<<left<<setw(2*w)<<"Monthly payment"<<"$"<<setw(w)<<fixed<<setprecision(2);
    cout<<right<<m1.getPmt()<<setw(w)<<m2.getPmt()<<endl;
    for(short i=0; i<(4*w); i++) cout<<"-"; cout<<endl;
    cout<<left<<setw(2*w)<<"Total payment"<<"$"<<right<<setw(w)<<m1.getTot()<<setw(w)<<m2.getTot()<<endl;
    cout<<left<<setw(2*w)<<"Total interest"<<"$";
    cout<<right<<setw(w)<<m1.getTot()-m1.getPV()<<setw(w)<<m2.getTot()-m2.getPV()<<endl;
    compInt = 100*(m1.getTot()-m1.getPV())/m1.getPV();
    cout<<left<<setw(2*w)<<"Compound interest, %"<<setw(w)<<fixed<<setprecision(1);
    cout<<right<<compInt<<"%";
    compInt = 100*(m2.getTot()-m2.getPV())/m2.getPV();
    cout<<setw(w-1)<<compInt<<"%"<<endl;
    for(short i=0; i<4*w; i++) cout<<"_"; cout<<endl;
}