/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on March 27, 2018, 9:36 PM
 * Purpose: Create employee objects with ID, name, Department, and Position as member variables
 *          Define 3 overloaded constructors. Also define mutator and accessor functions to set/retrieve data.
 *          Display info on employees as a table.
 */
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "Emplyee.h"
using namespace std;
//User libraries

// Global constants: math, science, conversion factors, 2D array columns

// Function prototypes
void print(Emplyee &, short = 30);

// Execution
int main(int argc, char** argv) {    
    Emplyee guy_1;
    Emplyee guy_2("Patrick Crackhead",5); // name, age
    // when all arguments are provided: name, age, department, position
    Emplyee guy_3("Jason Papandopulus",25,"Information Technologies","Programmer"); 
    Emplyee guy_4("Janet Jackson",-1); // name, age (illegal value)
    Emplyee guy_5("Mary Poppins",333333333,"Fairy Tales","Magician Babysitter");

    print(guy_1);
    print(guy_2);
    print(guy_3);
    print(guy_4);
    print(guy_5);

    return 0;
}
// Display people's data in a table
void print(Emplyee &guy, short w){
    static bool first = true;
    if(first) { // display the table header if the function is called for the 1st time
        cout<<left<<setw(w/4)<<"ID"<<setw(w)<<"Name"<<setw(w)<<"Department"<<setw(w)<<"Position"<<endl;
        for(short i=0; i<(4*w); i++) cout<<"-";
        cout<<endl;
        first=false;
    }
    cout<<setw(w/4)<<guy.getId()<<setw(w)<<guy.getName()<<setw(w)<<guy.getDept()<<setw(w)<<guy.getPosn()<<endl;
    
}
//Sources:
// When using char* with assigned string literal values, then I pass it to functions as const char* data type 
// https://stackoverflow.com/questions/59670/how-to-get-rid-of-deprecated-conversion-from-string-constant-to-char-warnin
// Otherwise, compiler gives me"warning: deprecated conversion from string constant to char*