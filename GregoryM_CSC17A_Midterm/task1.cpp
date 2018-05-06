/* 
 * File:   task1.cpp
 * Author: Maria gGregory
 *
 * Created on April 18, 2018, 8:39 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip> // setprecision(), for $ and cents
#include <cstring> // strcpy
#include <string> // length(), c_str()
#include "Account.h"
using namespace std;

// function prototypes
float takeNum(float, float);

// Function definitions
void task1() {
    Account *acc = new Account;
    string input; bool valid;
    float amount, endBal=0; // check amount and ending balance, in $ 

    cout<<"Your name: ";
    getline(cin, input);
    acc->name = new char[input.length()+1];
    strcpy(acc->name, input.c_str());
    cout<<"Your address: ";
    getline(cin, input);
    acc->address = new char[input.length()+1];
    strcpy(acc->address, input.c_str());
    acc->number = new char[6];
    do {
        valid = false;
        cout<<"Your account number: ";
        getline(cin, input);
        if(input.length() != 5) { cout<<"\tError! Account number is in 12345 format.\n";
        } else {
            for(short i=0; i<5; i++) {
                if(!isdigit(input[i])) { cout<<"\tError! Account number can contain only digits!\n"; break; }
                if(i==4) valid = true;
            } if(valid) strcpy(acc->number, input.c_str());
        }
    }while(!valid);
    
    cout<<"Beginning balance: $";
    amount = takeNum(-100000, 100000);
    acc->begBal = amount;
    acc->tWrtten=0; acc->tDpsted=0;
    cout<<fixed<<setprecision(2); // to show $ and cents
    
    cout<<"\nNow, you will be asked to write checks. To stop, please type 0.\n";
    do {
        cout<<"\nWrite a check on $";
        amount = takeNum(0, 10000);
        if(amount) {
            acc->tWrtten += amount;
            cout<<"\tYour new balance is $" << acc->begBal - acc->tWrtten;
        }
    }while(amount);
    
    endBal = acc->begBal - acc->tWrtten; //! update ending balance */
    
    cout<<"\nNow, you will be asked to deposit checks. To stop, please type 0.\n";
    do {
        cout<<"\nDeposit a check on $";
        amount = takeNum(0, 10000);
        if(amount) {
            acc->tDpsted += amount;
            cout<<"\tYour new balance is $" << endBal + acc->tDpsted;
             // if I call this program first, it displays garbage; if I call it after another program, works OK...
        }
    }while(amount);
    
    endBal += acc->tDpsted;
    
    if(endBal<0) {
        endBal-=15; // debit the account $15 if overdrawn
        cout<<"\t*** Your account was overdrawn, so the additional $15 fee has been accessed. ***\n";
    }
    
    cout<<"\nYour account at the end of the month:\n\n";
    cout<<"Account number: "<<acc->number<<endl;
    cout<<"Name: "<<acc->name<<endl;
    cout<<"Address: "<<acc->address<<endl;
    cout<<"Beginning balance: " << acc->begBal<<endl;
    cout<<"Total checks written on $"<<acc->tWrtten<<endl;
    cout<<"Total checks deposited on $"<<acc->tDpsted<<endl;
    cout<<"Ending balance"; if(endBal<0) cout<<" (with extra $15 debited)";
    cout<<": $"<< endBal <<endl;
    
    delete acc->name;
    delete acc->address;
    delete acc->number;
    delete acc;
}