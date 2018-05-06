/* 
 * File:   task5.cpp
 * Author: Maria Gregory
 *
 * Created on April 20, 2018, 4:24 PM
 */

#include <cstdlib>
#include <iostream>
#include<limits.h> // for int
#include<float.h> // for float,double
using namespace std;

// Not sure how to use templates yet, but learned something from chapter 16.
// I wanted to handle various data types in one function
template<class T> T factorl(short bytes, T arg) {
    cout<<"\t"<<bytes<<" bytes, max value = "<<scientific<<arg<<endl;
    T result = 1, n; 
    for(n=2; n<=arg; n++) { 
        result *= n; 
//      the thing is that <limits.h> library has SHRT_MAX = 32767 as 4-byte variable, instead of 2
//      also, it doesn't distinguish between same-byte variables like signed T and unsigned T, 
//        so I needed to secure limits in the following way:
        if(result*(n+1) > arg) { break; } 
        else if( result*(n+1)/result < (n+1) ) { break; } 
    } 
    cout<<"\t"<<n<<"! = "<<result<<endl<<endl;;
    return result;
}
// Function definitions
void task5() {
    cout<<"***** MAX FACTORIALS for various data types ******\n\n";
    cout<<"Char\n";
    char fChar = factorl(sizeof(char), CHAR_MAX);
    cout<<"Unsigned char\n";
    unsigned char fCharU = factorl(sizeof(unsigned char), UCHAR_MAX);
    cout<<"Short\n";
    short fShort = factorl(sizeof(short), SHRT_MAX);
    cout<<"Unsigned short\n";
    unsigned short fShortU = factorl(sizeof(unsigned short), USHRT_MAX);
    cout<<"Int\n";
    int fInt = factorl(sizeof(int), INT_MAX);
    cout<<"Unsigned int\n";
    unsigned int fIntU = factorl(sizeof(unsigned int), UINT_MAX);
    cout<<"Long int\n";
    long fIntL = factorl(sizeof(long), LONG_MAX);
    cout<<"Unsigned long int\n";
    unsigned long fIntLU = factorl(sizeof(unsigned long), ULONG_MAX);
    cout<<"Long long int\n";
    long long fIntLL = factorl(sizeof(long long), LLONG_MAX);
    cout<<"Unsigned long long int\n";
    unsigned long long fIntLLU = factorl(sizeof(unsigned long long), ULLONG_MAX);
    cout<<"Float\n";
    float fFloat = factorl(sizeof(float), FLT_MAX);
    cout<<"Double\n";
    double fDouble = factorl(sizeof(double), DBL_MAX);
}