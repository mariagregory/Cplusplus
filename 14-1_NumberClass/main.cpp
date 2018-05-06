/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on April 30, 2018, 9:42 AM
 * Purpose: Ask user for a positive 4-digit number and display it in English words.
 */
#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <sstream>
#include "Numbers.h"
using namespace std;

// Function prototypes
int takeNum(int);

// Execution
int main(int argc, char** argv) {
    cout<<"Hi,\nPlease enter an integer between 1 and 9999: ";
    int figure = takeNum(9999);
    Numbers amount(figure);
    amount.print();
    return 0;
}

int takeNum(int max) {
    string input;
    int result;
    stringstream ss;
    bool valid;
    
    ss << max;
    int maxLen = ss.str().length();
    do {
        valid = false;
        getline(cin, input);
        if(input.length() > maxLen) { 
            cout<<"Error! The number cannot exceed "<<maxLen<<" digits."<<endl;
        }
        else {
            for(short i=0; i<input.length(); i++) {
                if(!isdigit(input[i])) { cout<<"Digits only please: "; break; }
                // no need to compare with min and max in this case because the largest allowed 4-digit input cannot exceed 9999 anyway
                if(i==input.length()-1) valid = true;
            }
            if(valid) { 
                result = atoi(input.c_str());
                if(!result) {
                    valid = false;
                    cout<<"Oh please... Enter a non-zero, positive number: ";
                }
            }
        }
    }while(!valid);
    return result;
}