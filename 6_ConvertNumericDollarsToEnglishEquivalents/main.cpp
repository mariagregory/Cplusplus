/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 * Created on March 5, 2018
 * Purpose:  Convert a number to English check amount
 */

//System Libraries Here
#include <iostream>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    unsigned short number;
    string amount="";
    
    //Input or initialize values Here
    cout<<"Input an integer [1-3000] convert to an English Check value."<<endl;
    cin>>number;
    
    //Calculate the 1000's, 100's, 10's and 1's
    if(number>=1000) {
        if(number/1000==3) amount="Three ";
        else if(number/1000==2) amount="Two ";
        else if(number/1000==1) amount="One ";
        amount+="Thousand";
        number%=1000;
    }
    if(number>=100) {
        if(amount!="") amount+=" ";
        if(number/100==9) amount+="Nine ";
        else if(number/100==8) amount+="Eight ";
        else if(number/100==7) amount+="Seven ";
        else if(number/100==6) amount+="Six ";
        else if(number/100==5) amount+="Five ";
        else if(number/100==4) amount+="Four ";
        else if(number/100==3) amount+="Three ";
        else if(number/100==2) amount+="Two ";
        else amount+="One ";
        amount+="Hundred";
        number%=100;
    }
   if(number>=10) {
       if(amount!="") amount+=" ";
        if(number>=20) {

            if((number/10)==9) amount+="Ninety";
            else if((number/10)==8) amount+="Eighty";
            else if((number/10)==7) amount+="Seventy";
            else if((number/10)==6) amount+="Sixty";
            else if((number/10)==5) amount+="Fifty";
            else if((number/10)==4) amount+="Forty";
            else if((number/10)==3) amount+="Thirty";
            else amount+="Twenty";

        } else if(number==10) amount+="Ten";
                else {
                        //cout<<number<<" is between 11 and 19\n";
            if(number%10==9) amount+="Nineteen";
            else if(number%10==8) amount+="Eighteen";
            else if(number%10==7) amount+="Seventeen";
            else if(number%10==6) amount+="Sixteen";
            else if(number%10==5) amount+="Fifteen";
            else if(number%10==4) amount+="Fourteen";
            else if(number%10==3) amount+="Thirteen";
            else if(number%10==2) amount+="Twelve";
            else amount+="Eleven";
            number%=number;
            //cout<<"The number is now "<<number<<endl;
        }
       number%=10;
       //cout<<"The number is now "<<number<<endl;
   }
   if(number) {
       if(amount!="") amount+=" ";
        if(number==9) amount+="Nine";
        else if(number==8) amount+="Eight";
        else if(number==7) amount+="Seven";
        else if(number==6) amount+="Six";
        else if(number==5) amount+="Five";
        else if(number==4) amount+="Four";
        else if(number==3) amount+="Three";
        else if(number==2) amount+="Two";
        else if(number==1) amount+="One";

    } 

        //Output the check value
            cout<<amount<<" and no/100's Dollars"<<endl;
    
    //Exit
    return 0;
}