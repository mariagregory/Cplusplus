/* 
 * File:   5.11 Population  
 * Author: Mariia Gregory
 *
 * Created on February 26, 2018, 11:51 AM
 * Purpose: predict the size of a population of organisms based on an average daily increase rate
 */
//System libraries
#include <iostream>
using namespace std;

//User libraries

// Global constants: math, science, conversion factors, 2D array columns

// Function prototypes

// Execution begins here
int main(int argc, char** argv) {
    int popSize, days; 
    float rate;
    
    cout<<"Hi,\nEnter the starting number of organisms?: ";
    cin>>popSize;
    while(popSize<2) {
        cout<<"Oh no! Please enter the size of 2 and greater: ";
        cin>>popSize;
    }
    cout<<"And now, enter the average daily population increase (in %): ";
    cin>>rate;
    while(rate<0) { // Do not accept a negative number for population increase
        cout<<"Enter a non-negative value please! ";
        cin>>rate;
    }
    cout<<"How many days will they multiply?: ";
    cin>>days;
    while(days<1){ //Do not accept a number less than 1 for the number of days they will multiply
        cout<<"Enter a positive value please: ";
        cin>>days;
    }     
    cout<<"The population size by the end of each day:\n";
    for(short day=1; day<=days; day++) {
        popSize*=(1+rate/100);
        cout<<"Day "<<day<<": "<<popSize<<endl;
    }

    cout<<"Thank you for using this program.\nBye!";
    return 0;
}