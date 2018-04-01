/* 
 * File:  7.6 Rain or Shine
 Author: Mariia Gregory
 *
 * Created on February 26, 2018, 6:48 PM
 * Purpose: Create a report on weather conditions during the 3-month summer season
 */
//System libraries
#include <iostream>
#include <fstream> // for reading from and writing to a text file
#include <ctime> // for time(0) as unsigned seed
#include <cstdlib>  // For srand() and rand()
#include <iomanip> //  for setw(), for neat display
using namespace std;

//User libraries

// Global constants: math, science, conversion factors, 2D array columns
const short DAYS=30;

// Function prototypes
short daysOfAMonth(char[][DAYS], short, char); // find number of days with specified weather
void reportMostRainyMonth(short[], short); // returns the month with the most rainy days
string getSumMonth(short);
void showTable(char[][DAYS], short); // for TEST

// Execution begins here
int main(int argc, char** argv) {
    fstream sumFile;
    sumFile.open("RainOrShine.txt", ios::out);
    if(!sumFile) {
        cout<<"Error opening the file!";
        return -1;
    }
    short months=3;
    enum summer { JUNE, JULY, AUGUST }; // june=0, july=1, august=2
    char conds[] = { 'R', 'C', 'S' }; // R for rainy, C for cloudy, S for shiny
    char weather[months][DAYS]; // 2D array of chars representing weather conditions for all days
    // three parallel 1D arrays to store numbers of rainy, cloudy, and sunny days
    short rainyDs[months], cloudDs[months], sunnyDs[months]; 
    // plant a seed for a random number generator in a range 0-2, corresponding to the values in conds[] array
    unsigned seed = time(0);
    srand(time(0));
    
    cout<<"This program generates a weather report for the past year's summer\n";
    cout<<"\t(R - rainy, C - cloudy, S - shiny)\n";
    cout<<"First, let\'s write data to a text file...\n";
    
    for(short mon=JUNE; mon<=AUGUST; mon++) {
        for(short day=1; day<=DAYS; day++) {
            // generate a random number in a range 0-2 and take its corresponding char from conds[] array
            sumFile << conds[ rand()%3 ]; // write the resulting char to the file
        }
    }
    sumFile.close();
    cout<<"Done writing data to a text file!\n\n";
    
    cout<<"Now, reading data from a text file...\n\n";
    sumFile.open("RainOrShine.txt", ios::in); // open the file for output, this time
    if(!sumFile) { cout<<"Cannot open the file..."; return -1; }
    // read data for each element from the file
    for(short mon=JUNE; mon<=AUGUST; mon++) {
        for(short day=0; day<DAYS; day++) {
            sumFile>>weather[mon][day]; //store this char in our 2D array 
        }
    }
    sumFile.close();
    
    // TEST to see how the data are read from the file and to check the following calculations
    showTable(weather, months); 
    
    //Calculate and display number of rainy, cloudy, and shiny days for each month
    cout<<"There were\n";
    for(short mon=JUNE; mon<=AUGUST; mon++) {
        rainyDs[mon]=daysOfAMonth(weather,mon,'R');
        cloudDs[mon]=daysOfAMonth(weather,mon,'C');
        sunnyDs[mon]=daysOfAMonth(weather,mon,'S');
        cout<<"\t"<<rainyDs[mon]<<" rainy, "<<cloudDs[mon]<<" cloudy, and "<<sunnyDs[mon]<<" sunny days";
        cout<<" in "<<getSumMonth(mon)<<endl;
    }
    // find a display a month with the highest number of rainy days
    reportMostRainyMonth(rainyDs,months); 
    
    return 0;
}
/* Calculate how many days were 'R'-rainy, 'C'-cloudy, or 'S'shiny
 */
short daysOfAMonth(char weather[][DAYS], short month, char cond) {
    short days = 0;
    for(short day=0; day<DAYS; day++) {
        if(weather[month][day]==cond) {
            days++;
        }
    }
    return days;
}
/* Find the maximal number of rainy days 
 * and display (a) month(s) name(s) with the highest number of rainy days 
 */
void reportMostRainyMonth(short data[], short months) {
    short max=data[0], count=1;
    // count indicates if there are more than 1 month with max rainfall
    // Determine the largest rainfall
    for(short mon=1; mon<months; mon++) {
        if(data[mon]>=max) {
            max=data[mon];
        }
    }
    // In case there are 2 or all 3 months with equally largest rainfall, display all of them
    for(short mon=0; mon<months; mon++) {
        if(data[mon]==max) {
            if(count>1) cout<<" and "; //if there are more than 1 month, join them with "and" 
            cout<<getSumMonth(mon);
            count++;
        }
    }
    cout<<" had the largest number of rainy days."<<endl;;
}
/* Converts a number in a range 1-2 to a string with a month name */
string getSumMonth(short mon) {
    if(mon<0 || mon>2) return "What??";
    switch(mon) {
        case 0: return "June"; break;
        case 1: return "July"; break;
        case 2: return "August";
    }
}
/* This is just to test how the 2D was generated and how it is written to and read from the text file */
void showTable(char weather[][DAYS], short months) {
    //skip some space for neat table header output 
    cout<<setw(8)<<"";
    // display days from 1 to 30 as a table header
    for(short day=0; day<DAYS; day++) {
        cout<<setw(4)<<day+1; // since day # has 1-2 digits, it'd be nice to show each in 4-character space
    }   
    //start displaying data for each month
    for(short mon=0; mon<months; mon++) {
        cout<<"\n"<<setw(6)<<getSumMonth(mon)<<": ";
        for(short day=0; day<DAYS; day++) {
            cout<<setw(4);
            cout<<weather[mon][day];
        }
    } cout<<endl;
}