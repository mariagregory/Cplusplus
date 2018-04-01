/* 
 * File:   11.4 Weather Statistics
 * Author: Mariia Gregory
 * Purpose: Store information on weather for each month in an array of structures. 
 *          Calculate some statistics and display info.
 */
//System libraries
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Weather.h"
using namespace std;

//User libraries

// Global constants: math, science, conversion factors, 2D array columns

// Function prototypes
Weather *fillAry(const short ); // allocate memory for weather array and fill it with values
//  find extreme temp-s and months
void getRecT(Weather *, short, float&, float&, float&, vector<string>&, vector<string>&);
void report(Weather *, short ); // calculate and display the info
float getFloat(const float min, const float max); // input validation for rainfall and temperature figures
string getMon(const short); // how a month name instead if a digit

//execution starts here
int main(int argc, char** argv) {
    const short months = 12;
    Weather *weather = fillAry(months);
    
    report(weather, months);
            
    delete [] weather;
    return 0;
}

//
Weather* fillAry(const short months) {
    Weather *stat = new Weather[months];
    cout<<"Please enter monthly rainfall figures and temperatures, highest and lowest, as prompted.\n";
    for(short i=0; i<months; i++) {
        cout<<getMon(i)<<endl;
        cout<<"\tTotal rainfall: ";
        (stat+i)->rainfll=getFloat(0, 150); // in inches
        // the wettest place in the world https://en.wikipedia.org/wiki/Cherrapunji#Climate
        
        do{
            cout<<"\tHighest temperature (in Fahrenheit): ";
            (stat+i)->tempMax=getFloat(-100, 140); // in fahrenheit, so far
            cout<<"\tLowest temperature (in Fahrenheit): ";
            (stat+i)->tempMin=getFloat(-100, 140); 
            if((stat+i)->tempMin > (stat+i)->tempMax) { 
                cout<<"ERROR:\nHighest temperature is colder than the lowest?\nTry again.\n";
            }
        } while((stat+i)->tempMin > (stat+i)->tempMax);
        (stat+i)->tempAvr =((stat+i)->tempMax+(stat+i)->tempMin)/2; 
    }
    return stat;
}
// Calculate total and average rainfall for the year
// Display the info as a beautiful table
void report(Weather stat[], const short months) {
    // calculate total yearly and average monthly rainfall
    float totRain = 0, aveRain = 0;
    float minTemp, maxTemp, avgTemp;
    vector<string> hotMons, colMons; // arrays of strings with unknown size yet
    
    getRecT(stat, months, minTemp, maxTemp, avgTemp, hotMons, colMons);
    
    // display a header
    cout<<endl;
    cout<<right<<setw(22)<<"|"<<setw(24)<<"T e m p e r a t u r e"<<endl;
    cout<<left<<setw(9)<<"Month"<<" | "<<"Rainfall"<<" | ";
    cout<<"Highest"<<" | "<<"Lowest"<<" | "<<"Average\n";
    // display the line of dashes under the table heading
    for(short i=0; i<50; i++) cout<<"-"; cout<<endl;
    
    for(short i=0; i<months; i++) {
        // calculate total and average rainfall
        totRain += (stat+i)->rainfll;        
        // Display rainfall with 2 decimal places and temperatures with 1 decimal place
        cout<<left<<setw(9)<<getMon(i)<<" | ";
        cout<<right<<fixed<<setprecision(2)<<setw(8)<<(stat+i)->rainfll<<" | ";
        cout<<fixed<<setprecision(1)<<setw(7)<<(stat+i)->tempMax<<" | ";
        cout<<setw(6)<<(stat+i)->tempMin<<" | "<<setw(7)<<(stat+i)->tempAvr<<endl;
    }
    aveRain = (float)totRain/months;
    // Rainfalls will be displayed with 2 decimal places
    cout<<fixed<<setprecision(2);
    cout<<"The total rainfall for the year was "<<totRain<<" inches.\n";
    cout<<"The average monthly rainfall was "<<aveRain<<" inches.\n";
    cout<<fixed<<setprecision(1); // temp-res will be displayed with 1 decimal place
    cout<<"The average monthly temperature was "<<avgTemp<<" degrees Fahrenheit\n";
    cout<<"The hottest temperature, "<<maxTemp<<" degrees, was in ";
    for(short i=0; i<hotMons.size(); i++) {
        if(i) cout<<", ";
        cout<<hotMons[i];
    } cout<<endl;
    cout<<"The coldest temperature, "<<minTemp<<" degrees, was in ";
    for(short i=0; i<colMons.size(); i++) {
        if(i) cout<<", ";
        cout<<colMons[i];
    } cout<<endl;
}
// Determine extremes of temperatures, max and min. Also calculate average t-re
void getRecT(Weather *data, short size, float &minT, float &maxT, float &avgT, 
    vector<string> &hotMons, vector<string> &colMons) {
    avgT = data->tempAvr;
    minT = data->tempMin; // set both max and min temperatures ...
    maxT = data->tempMax; // .. to that of the 1st month
//    short count = 0; // counter for months, hottest and coldest
    
    for(short i=1; i<size; i++) {
        avgT += (data+i)->tempAvr;
        
        if((data+i)->tempMin < minT) {
            minT=(data+i)->tempMin;
        } 
        if((data+i)->tempMax > maxT) {
            maxT=(data+i)->tempMax;
        }
    }
    avgT /= size;
    // find the hottest months 
    for(short i=0; i<size; i++) {
        if(minT == (data+i)->tempMin) {
            colMons.push_back(getMon(i));
        } // I don't use else if because... if the temp-re was the same throughout the year, min = max.
        if(maxT == (data+i)->tempMax) {
            hotMons.push_back(getMon(i));
        }
    }
}
// Take and validate user's input for temperatures and rainfall
float getFloat(const float min, const float max) {
    float result;
    bool valid;
    
    do {
        valid=false;
        if(!(cin>>result)) { 
            cout<< "Numbers only please: ";
            cin.clear(); cin.ignore(100, '\n');
        } else if(result<min || result>max) {
            cout<<"ERROR:\nPlease enter a number in a range from "<<min<<" to "<<max<<": ";
        } else valid=true;
    } while(!valid);

    return result;
}
// replace indices with names of months
string getMon(const short i) {
    if(i<0 || i>11) return "What???";
    switch(i) {
        case 0: return "January";
        case 1: return "February";
        case 2: return "March";
        case 3: return "April";
        case 4: return "May";
        case 5: return "June";
        case 6: return "July";
        case 7: return "August";
        case 8: return "September";
        case 9: return "October";
        case 10: return "November";
        default: return "December";
    }
} 