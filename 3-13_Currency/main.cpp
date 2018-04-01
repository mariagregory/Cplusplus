/* 
 * File:   3.12 Currency
 * Author: Mariia Gregory
 * Purpose: convert a given dollar amount to euros and Japanese yens
 * 
 * Created on February 26, 2018, 10:58 AM
 */

#include <iostream>
#include <iomanip>
using namespace std;

//currency exchange rates are taken from www.xe.com/currencyconverter
float EUROS_PER_DOLLAR = 0.81;
float YEN_PER_DOLLAR = 106.97;

int main(int argc, char** argv) {
    float dollars, euros, yens;
    cout<<"Hi!\nTell me a dollar amount, and I will tell you how much it is in euros and Japanese yens: ";
    // Input validation loop
    do{
        cin>>dollars;
        if(dollars<0) { cout<<"Oh please! Type a non-negative dollar amount: "; }
    }while(dollars<0);
    
    euros=EUROS_PER_DOLLAR*dollars;
    yens=YEN_PER_DOLLAR*dollars;
    
    cout<<fixed<<setprecision(2); // format the currency output with 2 decimal places
    cout<<"$"<<dollars<<" is €" << euros<<" (euros) and ¥"<<yens<<" (yens)."<<endl;
    cout<<"Thank you for using this program.\nBye!";
    return 0;
}