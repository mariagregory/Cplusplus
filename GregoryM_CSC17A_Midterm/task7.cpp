/* 
 * File:   task7.cpp
 * Author: Maria Gregory
 *
 * Created on April 20, 2018, 8:59 PM
 */
// Libraries used
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector> // for getMode()
#include<limits.h> // UCHAR_MAX = 255
#include "Primes.h"
using namespace std;

// Function prototypes
Primes *factor(int);
void prntPrm(Primes *); 
bool isPrime(int);
float takeNum(float, float); // defined in main()

// Function definitions
// Ask user for a number, then factor it to prime numbers
void task7() {
    Primes *primes = nullptr;
    cout<<"Enter a positive integer value: "; cout<<fixed<<setprecision(0); // to display values as integers
    unsigned int value = takeNum(2, 10000); //*****TEST -- for(value=502; value<=2000; value++) { cout<<value<<endl; ...}
    primes = factor(value);
    if(primes->nPrimes=='0') cout<<value<<" is a prime number itself!\n";
    else { cout<<value<<" = "; prntPrm(primes); }
    if(primes) {
//        for(short i=0; i<primes->nPrimes-'0'; i++) 
        delete [] primes->prime;
        delete primes; primes = nullptr;
    }
}
// returns true is the argument is a prime number
bool isPrime(int n) {
    for(short i=2; i<=n/2; i++) {
       if(n%i == 0) return false;
    }
    return true;
}
// Determine dividers for an argument number. Fill the Primes structure instance with primes and their powers
Primes *factor(int value) {
    Primes *primes = new Primes;
    if(isPrime(value)) { primes->nPrimes='0'; primes->prime = nullptr; return primes; }    
// if the value itself is not a prime number, it is divided by at least 1 smaller value >= 2
    vector<unsigned char> dvders; // we don't know how many dividing primes there are...
    vector<unsigned char> powers; // ... so push them to vectors before allocating a dynamic array
    short cPowers; // counter for multiplicity of divider
    
    for(int i=2; i<=value/2; i++) {
       cPowers = 0;
       while(isPrime(i) && value%i == 0) { // if i is a prime number and divides the value...
           cPowers++; // increment i's multiplicity
           value /= i; // divide value by i
       } 
       if(cPowers) { // Value is divided by i cPowers times 
           dvders.push_back(i+'0');
           powers.push_back(cPowers+'0');
        }
    }
    if(value > 1) { // if the remainder is greater than 1
        dvders.push_back(value+'0');
        powers.push_back('1');
//      If the value > 207, when add 48 (ascii code for '0', to store the value as unsigned char) 
//        ... it will overflow the max 255. And there is no way I can catch it in prntPrm() function...
        if(value > UCHAR_MAX-'0') {
                cout<<"\t****  "<<value<<" overflows "<<UCHAR_MAX<<" ! "; 
                //... so just tell user to add 256 (n times, n is how many times it exceeds 255 (after +'0') )
                cout<<"Add "<<(UCHAR_MAX+1)*((value+'0')/UCHAR_MAX)<<" to the last term. ****\n";
            }
        } 
    
    primes->nPrimes = '0'+ dvders.size(); // all detected + remainder
    primes->prime = new Prime[dvders.size()]; // all detected + remainder
    
    for(short i=0; i<dvders.size(); i++) {
        primes->prime[i].prime = dvders[i];
        primes->prime[i].power = powers[i];
    }
    return primes;
}
// print the contents of Primes object
void prntPrm(Primes *primes) {
    for(short i=0; i<primes->nPrimes-'0'; i++) {
        if(i) cout<<" * "; // before the 2nd and following terms, display *
        cout<<primes->prime[i].prime-'0' << "^"<<primes->prime[i].power;
    } cout<<endl;
}