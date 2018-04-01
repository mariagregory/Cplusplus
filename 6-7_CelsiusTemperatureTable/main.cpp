/* 
 * File:  6.7 Celsius Temperature Table
 Author: Mariia Gregory
 *
 * Created on February 26, 2018, 06:20 PM
 * Purpose: display a table of temperatures in Fahrenheit and Celsius
 */
//System libraries
#include <iostream>
#include <iomanip> // for neat output in table
using namespace std;

//User libraries

// Global constants: math, science, conversion factors, 2D array columns

// Function prototypes
float Celsius(short);

// Execution begins here
int main(int argc, char** argv) {
    short fahr; // declare a variable to store the temperature in Fahrenheit
    
    cout<<"This program displays a range of temperatures in Fahrenheit and their Celsius equivalents.\n\n";
    // Display a table header
    cout<<"Fahrenheit"<<setw(10)<<right<<"Celsius\n";
    cout<<"*********************\n";
    // calculate and display temperature range from 0 to 20 Fahrenheit and its Celsius equivalent
    for(fahr=0; fahr<=20; fahr++) {
        cout<<setw(6)<<fahr;
        // for better accuracy, allow 1 decimal place in calculated Celsius temperature
        cout<<setw(12)<<fixed<<setprecision(1)<<showpoint<<Celsius(fahr)<<endl;
    }
    return 0;
}

float Celsius(short fahr) {
    // the formula for converting Fahrenheit to Celsius
    float cels = 5*(fahr-32)/9.0;
    // Made "9" a floating point value to allow decimals in calculated Celsius value
    return cels; 
}
