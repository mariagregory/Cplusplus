/* 
 * File:   11.5 Weather Statistics Modification
 * Author: Mariia Gregory
 * Purpose: Store information on weather for each month in an array of structures. 
 *          ...
 */
//System libraries
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Weather.h"

using namespace std;

//User libraries
enum Month { JAN, FEB, MAR, APR, MAY, JUN, JUL, AVG, SEP, OCT, NOV, DEC };
// Global constants: math, science, conversion factors, 2D array columns

// Function prototypes
Weather *fillAry(); // allocate memory for weather array and fill it with values
//  find extreme temp-s and months
void getRecT(Weather *, float&, float&, float&, vector<string>&, vector<string>&);
void report(Weather * ); // calculate and display the info
float getFloat(const float min, const float max); // input validation for rainfall and temperature figures
//void toFahr(float &); // Some users, like me, prefer to use Celsius, so I conveniently convert it for them
string getMon(Month); // how a month name instead if a digit

//execution starts here
int main(int argc, char** argv) {
//    const short months = 12;
    Weather *weather = fillAry();
    
    report(weather);
            
    delete [] weather;
    weather = nullptr;
    return 0;
}

//
Weather* fillAry() {
    Weather *stat = new Weather[ static_cast<Month>(DEC+1) ];
    cout<<"Please enter monthly rainfall figures and temperatures, highest and lowest, as prompted.\n";
    for(Month i=JAN; i<=DEC; i = static_cast<Month>(i+1)) {
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
//
void report(Weather stat[]) {
    // calculate total yearly and average monthly rainfall
    float totRain = 0, aveRain = 0;
    float minTemp, maxTemp, avgTemp;
    vector<string> hotMons, colMons; // arrays of strings with unknown size yet
    
    getRecT(stat, minTemp, maxTemp, avgTemp, hotMons, colMons);
    
    // display a header
    cout<<endl;
    cout<<right<<setw(22)<<"|"<<setw(24)<<"T e m p e r a t u r e"<<endl;
    cout<<left<<setw(9)<<"Month"<<" | "<<"Rainfall"<<" | ";
    cout<<"Highest"<<" | "<<"Lowest"<<" | "<<"Average\n";
    for(short i=0; i<50; i++) cout<<"-"; cout<<endl;
    
    for(Month i=JAN; i<static_cast<Month>(DEC+1); i = static_cast<Month>(i+1)) {
        // calculate total and average rainfall
        totRain += (stat+i)->rainfll;        
        // Diplay rainfall with 2 decimal places and temperatures with 1 decimal place
        cout<<left<<setw(9)<<getMon(i)<<" | ";
        cout<<right<<fixed<<setprecision(2)<<setw(8)<<(stat+i)->rainfll<<" | ";
        cout<<fixed<<setprecision(1)<<setw(7)<<(stat+i)->tempMax<<" | ";
        cout<<setw(6)<<(stat+i)->tempMin<<" | "<<setw(7)<<(stat+i)->tempAvr<<endl;
    }
    aveRain = totRain/static_cast<Month>(DEC+1);
    
    cout<<fixed<<setprecision(2);
    cout<<"The total rainfall for the year was "<<totRain<<" inches.\n";
    cout<<"The average monthly rainfall was "<<aveRain<<" inches.\n";
    cout<<fixed<<setprecision(1);
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

void getRecT(Weather *data, float &minT, float &maxT, float &avgT, 
    vector<string> &hotMons, vector<string> &colMons) {
    avgT = 0;
    minT = data->tempMin; // set both max and min temperatures ...
    maxT = data->tempMax; // .. to that of the 1st month
//    short count = 0; // counter for months, hottest and coldest
    
    for(Month i=FEB; i<=DEC; i = static_cast<Month>(i+1)) {
        avgT += (data+i)->tempAvr;
        
        if((data+i)->tempMin < minT) {
            minT=(data+i)->tempMin;
        } 
        if((data+i)->tempMax > maxT) {
            maxT=(data+i)->tempMax;
        }
    }
    avgT /= static_cast<Month>(DEC+1);
    // find the hottest months 
    for(Month i=JAN; i<=DEC; i = static_cast<Month>(i+1)) {
        if(minT == (data+i)->tempMin) {
            colMons.push_back(getMon(i));
        } // I don't use else if because.. what if the temperature was the same throughout the year?!
        if(maxT == (data+i)->tempMax) {
            hotMons.push_back(getMon(i));
        }
    }
    
}
// Take and validate user's input for temperatures and rainfall
float getFloat(const float min, const float max) {
    float result;
//    bool valid;
    
//    do {
//        valid=false;
        if(!(cin>>result)) { 
            cout<< "Numbers only please: ";
            cin.clear(); cin.ignore(100, '\n');
            getFloat(min,max);
        } else if(result<min || result>max) {
            cout<<"ERROR:\nPlease enter a number in a range from "<<min<<" to "<<max<<": ";
            getFloat(min,max);
        }
//        } else valid=true;
//    } while(!valid);
        return result;
    
}

string getMon(Month i) {
    if(i<JAN || i>DEC) return "What???";
    switch(i) {
        case JAN: return "January";
        case FEB: return "February";
        case MAR: return "March";
        case APR: return "April";
        case MAY: return "May";
        case JUN: return "June";
        case JUL: return "July";
        case AVG: return "August";
        case SEP: return "September";
        case OCT: return "October";
        case NOV: return "November";
        default: return "December";
    }
} 