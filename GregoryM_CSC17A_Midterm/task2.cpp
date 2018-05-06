/* 
 * File:   task2.cpp
 * Author: Maria gGregory
 *
 * Created on April 18, 2018, 8:39 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip> // fixed, setprecision()
#include <cstring> // strcpy
#include <string> // getline
#include "Emplyee.h"
using namespace std;

// function prototypes
string sAmount(float);
float takeNum(float, float);

// Execution starts here
void task2() {
    string input;
    short size;
    Emplyee *workers = nullptr;
    float gross;
    
    cout<<"How many employee are you dealing with? "; 
    cout<<fixed<<setprecision(0); // to ensure # of employees is an integer if re-prompting
    size = static_cast<short>(takeNum(0,20));
    workers = new Emplyee[size];
            
    for(short i=0; i<size; i++) {
        cout<<"\nEmployee #"<<i+1<<"\n\tName: ";
        getline(cin, input);
        workers[i].name = new char[input.length()+1];
        strcpy(workers[i].name, input.c_str());
        cout<<"\tHours worked (0-80): ";
        workers[i].hours = takeNum(0,80);
        cout<<"\tHourly pay rate ($7.25 - $ 120): "; // https://www.dol.gov/general/topic/wages/minimumwage
        workers[i].payRate = takeNum(7.25, 120); 
        //https://www.forbes.com/sites/jacquelynsmith/2013/05/13/the-best-and-worst-paying-jobs-in-america-2/#48c376c56b2d
        // straight-time hourly pay rate for the first 30 hours
        if(workers[i].hours <=30) gross = workers[i].hours * workers[i].payRate;
        else { gross = 30*workers[i].payRate; // double for over 30 but <= 50 hours
            if(workers[i].hours <=50) gross += 2*(workers[i].hours-30)*workers[i].payRate;
            else {  // 50-30 = 20, paid double and everything over it - triple
                gross += 2*20*workers[i].payRate + 3*(workers[i].hours-50)*workers[i].payRate;
            }
        }
        cout<<"\n\nEmployee\'s #"<<i+1<<" paycheck:\n\n";
        cout<<"Company: RCC\nAddress: Magnolia, Riverside CA 92500\n";
        cout<<"Name: "<<workers[i].name<<"\tAmount: $"<<fixed<<setprecision(2)<<gross<<endl;
        cout<<"Amount: "<<sAmount(gross)<<"\n\tSignature: ____\n";
    }
    
    if(size) { for(short i=0; i<size; i++) delete workers[i].name; delete [] workers; }
    else cout<<"Okay, have a nice day...\n";
}

string sAmount(float amt) {
    short number = static_cast<short>(amt);
    short cents = 100*(amt-number);
    string amount;
    if(number>=1000) { 
        if(number/1000==19) amount="Nineteen ";
        else if(number/1000==18) amount="Eighteen ";
        else if(number/1000==17) amount="Seventeen ";
        else if(number/1000==16) amount="Sixteen ";
        else if(number/1000==15) amount="Fifteen ";
        else if(number/1000==14) amount="Fourteen ";
        else if(number/1000==13) amount="Thirteen ";
        else if(number/1000==12) amount="Twelve ";
        else if(number/1000==11) amount="Eleven ";
        else if(number/1000==10) amount="Ten ";
        else if(number/1000==9) amount="Nine ";
        else if(number/1000==8) amount="Eight ";
        else if(number/1000==7) amount="Seven ";
        else if(number/1000==6) amount="Six ";
        else if(number/1000==5) amount="Five ";
        else if(number/1000==4) amount="Four ";
        else if(number/1000==3) amount="Three ";
        else if(number/1000==2) amount="Two ";
        else amount="One ";
        amount+="Thousand ";
        number%=1000;
    }
    if(number>=100) {
        if(number/100==9) amount+="Nine ";
        else if(number/100==8) amount+="Eight ";
        else if(number/100==7) amount+="Seven ";
        else if(number/100==6) amount+="Six ";
        else if(number/100==5) amount+="Five ";
        else if(number/100==4) amount+="Four ";
        else if(number/100==3) amount+="Three ";
        else if(number/100==2) amount+="Two ";
        else amount+="One ";
        amount+="Hundred ";
        number%=100;
    }
   if(number>=10) {
        if(number>=20) {
            if((number/10)==9) amount+="Ninety ";
            else if((number/10)==8) amount+="Eighty ";
            else if((number/10)==7) amount+="Seventy ";
            else if((number/10)==6) amount+="Sixty ";
            else if((number/10)==5) amount+="Fifty ";
            else if((number/10)==4) amount+="Forty ";
            else if((number/10)==3) amount+="Thirty ";
            else amount+="Twenty ";
                
        } else {
            if(number==10) amount+="Ten";
            else if(number%10==9) amount+="Nineteen";
            else if(number%10==8) amount+="Eighteen";
            else if(number%10==7) amount+="Seventeen";
            else if(number%10==6) amount+="Sixteen";
            else if(number%10==5) amount+="Fifteen";
            else if(number%10==4) amount+="Fourteen";
            else if(number%10==3) amount+="Thirteen";
            else if(number%10==2) amount+="Twelve";
            else amount+="Eleven";
            number%=number;
        }
       number%=10;
   }
   if(number) {
        if(number==9) amount+="Nine ";
        else if(number==8) amount+="Eight ";
        else if(number==7) amount+="Seven ";
        else if(number==6) amount+="Six ";
        else if(number==5) amount+="Five ";
        else if(number==4) amount+="Four ";
        else if(number==3) amount+="Three ";
        else if(number==2) amount+="Two ";
        else amount+="One ";
    }
    // Add cents to the check value
    amount+="and ";
    if(cents) amount+=to_string(cents);
    else amount+="no";
    amount+="/100's Dollars";
    return amount;
}