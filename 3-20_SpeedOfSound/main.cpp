/* File:   3.20 Speed of Sound
 * Author: Mariia Gregory
 * Purpose: Determine the time it will take for a sound to travel through air, water, or steel
 *
 * Created on February 27, 2018, 11:14 AM
 */

//System libraries
#include <iostream>
#include <iomanip> // for setprecision() in displaying time as # of seconds
#include <cctype>
using namespace std;

//User libraries

// Global constants: math, science, conversion factors, 2D array columns
const short SND_AIR = 1100;
const short SND_H2O = 4900;
const short SND_STE = 16400;

// Function prototypes
string getMedm(char );

// Execution begins here
int main(int argc, char** argv) {
    char choice; // in case user types something other than a digit...
    float dist, time;
    bool valid=false;
    
    cout<<"Please select ";
    do{ // taking and verifying user's input for a menu choice
        cout<<"1 for Air, 2 for Water, and 3 for Steel.\n(or type 0 to exit.): ";
        cin>>choice;
        if( choice=='0') { 
            cout<<"Okay....Bye!"; return 0; 
        } else if(!isdigit(choice)) {
            cout<<"Type a digit!\n"; // '0' is 48 in ASCII code, so if user typed '1' in becomes 49 in char....
            cin.ignore(1000,'\n');
        } else if( (choice-'0')<1 || (choice-'0')>3) {
            cout<<"Invalid choice! Read carefully!\n";
        }
    }while(!isdigit(choice) || (choice-'0')<1 || (choice-'0')>3);
    
    cout<<"You chose "<<getMedm(choice)<<endl;
    
    cout<<"What distance, in feet, will a sound wave travel in the "<<getMedm(choice)<<"? ";
 
    do {
        if(!(cin >> dist)) { 
            cout<<"Numbers only please! So what\'s the distance? ";
            cin.clear(); // clear "bad" flag
            cin.ignore(1000,'\n'); // skip the next 1000 chars or a newline, whichever encountered first
        } else if(dist<0) {
            cout<<"How can the distance be negative?\nType a positive number (or 0 if it stood still): ";
        } else valid=true;
    }while( !valid || dist<0);
    
        
    switch(choice) {
        case '1': time=dist/SND_AIR;
                break;
        case '2': time=dist/SND_H2O;
                break;
        case '3': time=dist/SND_STE;
                break;
        default: cout<<"Okay....Bye!";
                return 0;
    }
    
    cout<<"It will take "<<scientific<<setprecision(1)<<time;
    cout<<" seconds for sound to travel "<<fixed<<setprecision(0)<<dist;
    cout<<" feet in the "<<getMedm(choice)<<endl;
    
    return 0;
}

string getMedm(char choice) {
    switch(choice) {
        case '1': return "air";
        case '2': return "water";
        case '3': return "steel";
    }
}