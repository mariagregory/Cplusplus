/* 
 * File:   Primes.h
 * Author: Maria Gregory
 *
 * Created on April 20, 2018, 10:19 PM
 */

#ifndef PRIMES_H
#define PRIMES_H

struct Prime {
    unsigned char prime; // values from 0 to 255 inclusive
    unsigned char power;
};
struct Primes {
    Prime *prime;
    unsigned char nPrimes; 
};

#endif /* PRIMES_H */

