/* 
 * File:   11.3 Corporate Sales Data
 * Author: Mariia Gregory
 *
 * Created on March 17, 2018, 9:54 PM
 * Purpose: Use a structure to store the quarterly sales figures on 4 company divisions.
 *          Let user input sales data for each division for each quarter.
 *          Calculate the division's total and average sales 
 *          and store them in appropriate member variables of each structure variable.
 *          Display info on the screen.
 */
//System libraries
#include <cstdlib>
#include <iostream>
#include <iomanip> // for setw
#include <cctype> // for isdigit()
#include <cstring> // for strlen()
//#include <sstream> // I found it the only way to store values in this f***king c-strings
#include "Divisn.h"
using namespace std;

//User libraries

// Global constants: math, science, conversion factors, 2D array columns

// Function prototypes
void setQSls(Divishn *);
float getSale();
void shwSals(Divishn *);

//execution starts here
int main(int argc, char** argv) {
    // declare 4 company divisions
    Divishn east, west, north, south;
    east.name = new char[6];
    west.name = new char[6];
    north.name = new char[6];
    south.name = new char[6];
    
    //Assign their names as corresponding properties
    strcpy(east.name,"East");
    strcpy(west.name,"West"); // or 
    strcpy(north.name,"North");
    strcpy(south.name,"South");
    
    // Set quarterly sales for each division
    setQSls(&east);
    setQSls(&west);
    setQSls(&north);
    setQSls(&south);
    
//  Calculate and display info for each division
    shwSals(&east);
    shwSals(&west);
    shwSals(&north);
    shwSals(&south);
    
    delete [] east.name;    east.name=NULL;
    delete [] west.name;    west.name=NULL;
    delete [] north.name;   north.name=NULL;
    delete [] south.name;   south.name=NULL;
    
}

void setQSls(Divishn *div) {
    div->annual=0;
    short quarter = 1; // simply a counter of quarters...
    cout<<"Please enter quarterly sales figures for "<<div->name<<" division.\n";
    cout<<"Quarter "<<quarter<<": ";
    div->salesQ1=getSale();
    div->annual += (div->salesQ1);
    quarter++;
    cout<<"Quarter "<<quarter<<": ";
    div->salesQ2=getSale();
    div->annual += (div->salesQ2);
    quarter++;
    cout<<"Quarter "<<quarter<<": ";
    div->salesQ3=getSale();
    div->annual += (div->salesQ3);
    quarter++;
    cout<<"Quarter "<<quarter<<": ";
    div->salesQ4=getSale();
    div->annual += (div->salesQ4);
    div->averQ = (div->annual) / quarter;
    cout<<"Thank you.\n\n";
}

float getSale() {
    float amount;
    bool valid;
    do{
        valid=false;
        if(!(cin>>amount)) {
            cout<<"Numbers only please! "; // if it were't, it means something other than a number was entered
            cin.clear(); // clear cin.bad() flag...
            cin.ignore(10000, '\n'); // ignore the next 1000 characters or everything until the newline character
        }else if(amount<0) {
            cout<<"Invalid! Sales figure cannot be negative.\n";
        } else valid=true;
    } while(!valid);

    return amount;
}

void shwSals(Divishn *div) {
    static short rows=0;
    
    if(!rows) {
        cout<<setw(50)<<right<<"S a l e s,  $\n";
        cout<<left<<setw(6)<<"Name"<<right<<fixed<<setprecision(2);
        cout<<setw(11)<<"Quarter 1"<<setw(11)<<"Quarter 2"<<setw(11)<<"Quarter 3"<<setw(11)<<"Quarter 4";
        cout<<setw(11)<<"Annual"<<setw(11)<<"Average\n";
    }
    rows++;
    cout<<left<<setw(6)<<div->name<<right<<fixed<<setprecision(2);
    cout<<setw(11)<<div->salesQ1<<setw(11)<<div->salesQ2<<setw(11)<<div->salesQ3<<setw(11)<<div->salesQ4;
    cout<<setw(11)<<div->annual<<setw(10)<<div->averQ<<endl;
    
}