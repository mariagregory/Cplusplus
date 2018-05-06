/* 
 * File:   Numbers.cpp
 * Author: Mariia Gregory
 *
 * Created on April 30, 2018, 9:42 AM
 * Purpose: Function definitions for Numbers class
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include "Numbers.h"
using namespace std;

void Numbers::print() {
    string value;
    if(number>=1000) {
        for(short i=9; i>0; i--) {
            if(number/1000==i) { value+=digits[i-1]; break; }
        } value+=" " + thousand;
        number%=1000;
    }
    if(number>=100) {
        for(short i=9; i>0; i--) {
            if(number/100==i) { if(value.length()) value+=" ";
            value+=digits[i-1]; break; 
            }
        } value+=" " + hundred;
        number%=100;
    }
    if(number>=20) {
        for(short i=1; i<10; i++) {
            if(number/10==i+1) { if(value.length()) value+=" ";
                value+=tens[i]; break; 
            }
        } number%=10;
    } else if(number>10) {
        for(short i=1; i<10; i++) {
            if(number==10+i) { if(value.length()) value+=" ";
                value+=to19[i-1]; break; 
            }
        } number%=number;
    } else if(number==10) { if(value.length()) value+=" ";
        value+=tens[0]; 
        number%=10; 
    }
    if(number) { if(value.length()) value+=" "; value+=digits[number-1]; }
    
    value[0]= toupper(value[0]);
    cout<<value<<".";
}
