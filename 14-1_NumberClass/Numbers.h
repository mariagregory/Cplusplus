/* 
 * File:   Numbers.h
 * Author: Mariia Gregory
 *
 * Created on April 30, 2018, 9:42 AM
 * Purpose: Numbers class declaration
 */

#ifndef NUMBERS_H
#define NUMBERS_H

#include <string>
using namespace std;

class Numbers {
    private:
        int number;
        string digits[10] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        string to19[9] = { "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
        string tens[10] = { "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
        string thousand = "thousand";
        string hundred = "hundred";
    public:
        Numbers(int num = 0) { number = num >=0 ? num : num*(-1); } // constructor with a default parameter
        void print();
//        int getNum() const { return number; }
};


#endif /* NUMBERS_H */

