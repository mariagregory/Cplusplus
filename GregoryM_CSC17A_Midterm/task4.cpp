/*
 * File:   task4.cpp
 * Author: Maria Gregory
 *
 * Created on April 19, 2018, 9:55 PM
 */

#include <cstdlib>
#include <iostream>
#include <cstring> // strcpy
#include <string> // for length()
#include <cctype> // isdigit
#include <vector> // for getMode()
using namespace std;

// function prototypes
char* takeNumStr(short);
char *encrypt(const char*, char*, short); //original message, key, size
char *decrypt(const char*, const char*, short); //encoded message, key, size

// Function definitions
// Ask user for a 4-octal-digit message, encrypt it, and then decrypt it
void task4() {
    const short dataLen = 4;
    char *origin = new char[dataLen],
         *encoded = new char[dataLen],
         *decoded = new char[dataLen], 
         *key = new char[dataLen]; // parallel array with values needed to decode "encoded" back into "origin"
    
    cout<<"Please enter the 4-digit number: \n";
    origin = takeNumStr(dataLen);
    encoded = encrypt(origin, key, dataLen);
    decoded = decrypt(encoded, key, dataLen);
    cout<<"The encoded message is "<<encoded<<endl;
    cout<<"The decoded message is "<<decoded<<endl;
    
    delete [] origin; origin = nullptr;
    delete [] encoded; encoded = nullptr;
    delete [] decoded; decoded = nullptr;
    delete [] key; key = nullptr;
}
// Take and validate the user input for a message: 4 digits in a range 0-7 each
char* takeNumStr(short length) {
    char *result = new char[length];
    string input;
    bool valid;
    do {
        valid = false;
        getline(cin, input);
        if(input.length()!=length) { cout<<"\tError! Type "<<length<<" digits: "; }
        else {
            for(short i=0; i<length; i++) {
                if(!isdigit(input[i]) || input[i]<'0' || input[i]>'7')
                    { cout<<"\tError! Digits from 0 to 7 please: "; break; }
                if(i==length-1) valid = true; // if it's the last char in input, then all are digits
            }
        }
        if(valid) strcpy(result,input.c_str());
    }while(!valid);
    return result;
}
// encrypt data by +5 to each digit, then take %8 of each. Then swap 1st with 3rd, and 2nd with 4th chars.
// store the integer results of /8 as "key"
char *encrypt(const char *data, char *key, short size) {
    char *result = new char[size];
    char toSwap; // temporary holds a char when swapping
    short digit; // for calculation purposes
    for(short i=0; i<size; i++) { 
        digit = static_cast<short>(data[i]-'0'); // convert from char to short by subtracting ASCII value of '0'
        digit += 5;
        key[i] = '0'+(digit/8); // store the integral part of division as a key (will be needed later, to decrypt)
        result[i] = '0'+(digit%8); // convert the resulting digit back to char before storing in encoded c-string
    } result[size]='\0'; // store a null terminator at the end
//    swap 1st and 3rd digits
    toSwap = result[0]; result[0] = result[2]; result[2] = toSwap;
    toSwap = key[0]; key[0] = key[2]; key[2] = toSwap;
//    swap 2nd and 4th digits    
    toSwap = result[1]; result[1] = result[3]; result[3] = toSwap;
    toSwap = key[1]; key[1] = key[3]; key[3] = toSwap;
    
    return result;
}
// decrypt data by using "key": Multiply "key" element back by 8 and + remainder (encoded char)
// Then -5 from each resulting digit. Then swap 1st with 3rd, and 2nd with 4th chars.
char *decrypt(const char *code, const char *key, short size) {
    char *result = new char[size];
    char toSwap; // temporary holds a char when swapping
    short digit;// for calculation purposes
//    convert the remainders back into original values using the integral result from division as a "key"
    for(short i=0; i<size; i++) { 
// when converting char to short, subtract the ascii code for '0'
        digit = 8 * static_cast<short>(key[i]-'0'); // multiply the integer part ("key") back by 8
        digit += static_cast<short>(code[i]-'0'); // add a remainder
        digit -= 5; // subtract 5
        result[i]='0'+digit; // convert the digit back to char by adding ascii code of '0' and 
    } result[size]='\0'; // store a null terminator at the ends
//    swap 1st and 3rd digits
    toSwap = result[0];
    result[0] = result[2];
    result[2] = toSwap;
//    swap 2nd and 4th digits    
    toSwap = result[1];
    result[1] = result[3];
    result[3] = toSwap;
//    short index=0;
//    while(index*2 < strlen(code)) { result[index] = code[index + strlen(code)/2]; index++; }
//    while(index < strlen(code)) { result[index] = code[index - strlen(code)/2]; index--; }
    return result;
}