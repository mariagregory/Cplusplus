/* 
 * File: Numeric Base Convertion
 * Author: Mariia Gregory
 *
 * Created on February 21, 2018, 1:42 PM
 */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <bitset>//to display binary number
using namespace std;

//void showBinary(int);

void displayResults(int hexadec, int decimal, int binary, int octal) {	
    cout<<"Binary  = "<< bitset<12>(binary)<<endl;
    cout<<"Octal   = "<<oct<<octal<<endl;
    cout<<"Hex     = "<<hex<<hexadec<<endl;
    cout<<"Decimal = "<<dec<<decimal<<endl<<endl;
    
    //  cout<<"TEST using printf():\n";
    //	printf("The hexadecimal %lx is %ld in base-10 and %lo in base-8.\n\n",hexadec,hexadec,hexadec);
}
     
int main(int argc, char** argv) {
    int hexadec, binary, octal, decimal;
    
    // PROBLEM #1: ABC base 16
    hexadec = 0xABC;
    decimal = 2748;
    binary = 0b101010111100;
    octal= 05274;
    cout<<"PROBLEM #1: ABC base 16 to other 3:"<<endl;
    displayResults(hexadec, decimal, binary, octal);
  
    // PROBLEM #2: 678  base 8 to other 3
    cout<<"PROBLEM #2: 678  base 8 to other 3:"<<endl;
    cout<<"Base-8 numbers can contain only digits in a range from 0 to 7,\n";
    cout<<"Therefore, there is no solution for this one.\n\n";
	
    // PROBLEM #3: 678  base 10 to other 3
    decimal = 678;
    hexadec = 0x2A6;
    binary = 0b1010110110;
    octal= 01246;
    cout<<"PROBLEM #3: ABC base 16 to other 3:"<<endl;
    displayResults(hexadec, decimal, binary, octal);
	
    // PROBLEM #4: 10010 base 2 to other 3
    binary = 0b10010;
    hexadec = 0x12;
    decimal = 18;
    octal= 022;
    cout<<"PROBLEM #4: 10010 base 2 to other 3:"<<endl;
    displayResults(hexadec, decimal, binary, octal);
  
    return 0;
}

/*void showBinary(int num) {
    int rmndr, half = num, digits = 0;
    while(half) // while half >= 0
    { 
        half/=2;
        digits++;
    }
    int buffer[digits]={0};
    half=num;
    
    for(int i=digits-1; i>0; i--) {
        rmndr=half%2;
        half/=2;
        buffer[i]=rmndr;
    }
    for(int i=0; i<digits-1; i++) {
        cout<<buffer[i];
    }
}*/