/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 * Created on March 05, 2018
 * Purpose:  Input something, output it reversed with some modifications
 * Note:Range should be 5 digits, 321 = 00321 reverse = 12300 before subtraction
 *      12300 - 999 = 11301 after subtraction
 *      12300 = 00321 = 321 after reversal and no subtraction
 */

//System Libraries Here
#include <iostream>//cin,cout,endl
#include <cstring> //strlen()
#include <cctype> // isdigit(char)
#include <cstdlib> //atoi(char*)
#include <sstream>
#include <stdio.h> // for sprintf()
using namespace std;
//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, conversions, or the columns for 2-D arrays

//Function Prototypes Here
bool  inRange(const char [],unsigned short &);//Output true,unsigned or false
bool  reverse(unsigned short,signed short &);//Output true,short or false
short subtrct(signed short,int);
char *strcat_1(char *, const char *); // for some reason, the standard <cstring> function doesn't work on HackerRank!

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int SIZE=80;     //More than enough
    char  digits[SIZE];    //Character digits or not
    unsigned short unShort;//Unsigned short
    short snShort;         //Signed short
    
    //Input or initialize values Here
    cout<<"Reverse a number and subtract if possible."<<endl;
    cout<<"Input a number in the range of an unsigned short"<<endl;
    cin>>digits;
    
    //Test if it is in the Range of an unsigned short
    if(!inRange(digits,unShort)){
        cout<<"No Conversion Possible"<<endl;
        return 0;
    }
    
    //Reverse and see if it falls in the range of an signed short
    if(!reverse(unShort,snShort)){
        cout<<"No Conversion Possible"<<endl;
        return 0;
    }
    
    //Now subtract if the result is not negative else don't subtract
    snShort=subtrct(snShort,999);
    
    //Output the result
    cout<<snShort<<endl;
    
    //Exit
    return 0;
}

bool inRange(const char digits[], unsigned short &unShort) {
    if(strlen(digits)>5) return false;
    else if (strlen(digits)==5 && digits[0]>'6') { //cout<<strlen(digits)<< "=5 and "<<digits[0]<<">6, so...\n";
        return false;	
    }
    else {
        for(short i=0; i<strlen(digits); i++) {
            if(!isdigit(digits[i])) {             	//cout<<"Non-digit character found, so...\n";
            	return false;
            }
        }
    }
    if(atoi(digits)<=65535) { 
        unShort=atoi(digits);
        return true;    
    }  else {//cout<<"The number "<<digits<<"is between 65535 and 69999, which is out of range, so...\n";
    return false;  //if all 5 characters are digits, but the number is between 65535 and 69999, it's out of range
    }
}

bool reverse(unsigned short unShort, signed short &snShort) {
    stringstream ss;
    string numStr; // temporary string to store unShort as string
    char digits[5], *newDgts=new char[5];
    short zeroes=0; // number or 0's at the beginning of a number, 
	// ... so that I can "cut" the digits c-string with '\0' before concatenating 0s and a number containing less than 5 digits
    
    ss << unShort; // read unShort into stringstream object
    numStr=ss.str(); //cout<<"numStr is "<<ss.str()<<", same as "<<numStr<<endl; 
//    if(unShort>=10000) {  	//cout<<unShort<<" is greater than or equal to 10000\n";
//        //sprintf(digits, "%d", unShort); // Store unShort in base-10 as "digits" c-string
    // sprintf(...) worked not everywhere. It work in CCC lab but doesn't on my home PC, so .....
    
    if(numStr.length()==5) {
        strcpy(digits,numStr.c_str());
    } else { 		//cout<<unShort<<" is less than 10000\n";
        digits[0]='0';
        zeroes++; // now, there's 1 zero at the beginning
        if(numStr.length()==4) {
            digits[zeroes]='\0'; // place null terminator and concatenate with "digits"
            strcat_1(digits, numStr.c_str()); //cout<<"Concatenating "<<digits<<" and "<<numStr.c_str()<<"...\n";
        } else {
            digits[zeroes]='0';
            zeroes++; // now, there are 2 zeros at the beginning
            if(numStr.length()==3) {
                digits[zeroes]='\0'; 
                strcat_1(digits, numStr.c_str()); //cout<<"Concatenating "<<digits<<" and "<<numStr.c_str()<<"...\n";
            } else {
                digits[zeroes]='0';
                zeroes++;	// now, there are 3 zeros at the beginning
                if(numStr.length()==2) {
                    digits[zeroes]='\0';
                    strcat_1(digits, numStr.c_str()); //cout<<"Concatenating "<<digits<<" and "<<numStr.c_str()<<"...\n";
                } else {
                    digits[3]='0';
                    zeroes++;
                    digits[zeroes]='\0';
                    strcat_1(digits, numStr.c_str()); //cout<<"Concatenating "<<digits<<" and "<<numStr.c_str()<<"...\n";
                }
            }
        }
    } 
    //cout<<"Represented as 5-character c-string - "<<digits<<endl;
    for(short i=0; i<strlen(digits); i++) { //for(short i=0; i<=4; i++) 
        newDgts[i]=digits[strlen(digits)-1-i]; //newDgts[i]=digits[4-i];
    }
    if(atoi(newDgts)>32767) { //cout<<"The reversed number, "<<newDgts<<" is > 32768, which is out of range, so...\n";
        return false;
    }
    snShort = atoi(newDgts); 	//cout<<"The reverse number is "<<snShort<<endl;

    delete [] newDgts; // release the dynamically allocated memory
    newDgts=nullptr;

    return true;
}

short subtrct(short snShort, int num) {
    //cout<<"Calling subtrcs with "<<snShort<<", "<<num<<endl;
    if(num<=snShort) {
        //cout<<num<<" <= " <<snShort<<endl;
        return snShort-num;
    }
    return 0;
}

char *strcat_1(char *to, const char *from) {
	///cout<<"Calling strcat_1() function with to = "<<to<<" and from = "<<from<<endl;
	int lenFrom = strlen(from), lenTo = strlen(to);
	for(int i=0; i<lenFrom; i++) {
            *(to+lenTo+i)=*(from+i);
	}
	*(to+lenTo+lenFrom)='\0';
	return to;
}