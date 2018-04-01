/* File:  4.18 Fat Gram Calculator
 Author: Mariia Gregory
 *
 * Created on February 27, 2018, 10:44 AM
 * Purpose: Search an array of strings (sorted) using a binary search algorithm
 */
//System libraries
#include <iostream>
using namespace std;

//User libraries

// Global constants: math, science, conversion factors, 2D array columns
const short FAT_CAL = 9;
// Function prototypes

// Execution begins here
int main(int argc, char** argv) {
    short fatGram, totCals, fatCals;
    float fromFat; // percentage of calories coming from fat
    
    cout<<"Hi,\nThis program calculates how much Calories came from fat in your diet.\n";
    cout<<"How many dietary Calories (kkal) have you consumed? ";
    cin>>totCals;
    while(totCals<0) {
        cout<<"Come on, tell me the truth!\nType a positive number (or 0 if you haven\'t eaten at all): ";
        cin>>totCals;
    }
    cout<<"And how much fat (in grams) was in that food? ";
    cin>>fatGram;
    while(totCals<0) {
        cout<<"This can\' be!\nType a positive number (or 0 if you have eaten fat-free food): ";
        cin>>totCals;
    }
    fatCals=FAT_CAL*fatGram;
    fromFat=100*fatCals/totCals;
    
    cout<<"Your food contains "<<fromFat<<"% Calories coming from fat.\n";
    if(fromFat < 30) { 
        cout<<"It has been a low-fat diet, so far.\n";
    } else if(fromFat>45) { cout<<"Hey, be careful with what you eat!\n"; }
    
    cout<<"\nThank you for using this program.\nBye!";
    
    return 0;
}

