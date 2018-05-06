/* 
 * File:   task3.cpp
 * Author: Maria Gregory
 *
 * Created on April 19, 2018, 5:48 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip> // to make sure numbers are not in scientific notation or otherwise messed up
#include <vector> // for getMode()
#include "Stats.h"
using namespace std;

/*! Function prototypes */
Stats *avgMedMode(int *, int);
void printStat(Stats*);
void sortArr(int *, int);
int* getMode(int *, int);
float takeNum(float, float); 

// Function definitions
// For user-defined array of integer numbers, do statistical analysis
void task3() {
    Stats *stats = nullptr;
    short size;

    cout<<"How many numbers are you going to enter? ";
    size = static_cast<short>(takeNum(2,20));
    int *array = new int[size];
    
    cout<<"Please enter "<<size<<" integer values.\n";
    for(short i=0; i<size; i++) {
        cout<<"\tValue "<<i+1<<": ";
        array[i] = static_cast<int>(takeNum(-2147483648, 2147483647));
    } cout<<"\nThank you.\n";
    
    stats = avgMedMode(array, size); // determine mean, median, and mode(s) (if any)
    printStat(stats); // print the statistics for this array

    delete [] array; array = nullptr;
    delete stats;
}
// determine mean, median, and mode(s) of the array of integers
Stats *avgMedMode(int *arr, int size) {
    Stats *stats = new Stats;
    float mean, median; // even in an integer array, after dividing an integer by integer, the result can be float
    int *mode = nullptr; // mode is going to be an array 
    bool even = size%2 ? false : true; 
    
    // 1) find a mean
    for(short i=0; i<size; i++) mean += arr[i];
    mean /= (float)size;
    stats->avd = mean;

    // (2) find median and mode, but first sort values
    sortArr(arr, size);
    //******TEST
    cout<<"\nSorted array:\n"; 
    for(short i=0; i<size; i++) cout<<arr[i]<<" "; cout<<endl;
    // ****** End of TEST
    if(!even) median = arr[size/2]; // If the size is 5, we need 3rd element, i.e. [2], which is (int)(5/2)
    else { median = .5 * ( arr[size/2-1] + arr[size/2] ); }
    // If the cols is 6, we need the half-sum of 3rd and 4th elements, i.e. [2] and [3]    
    stats->median = median;
    
    // (3) Find (a) mode(s)
    mode = getMode(arr, size); // returns a pointer to a dynamically allocated array of modes
    stats->nModes = *mode;
    stats->maxFreq = mode[1];
    if(*mode) { // mode[0] will be 0 if the array has no modes (all frequencies are the same)
        stats->mode = new int[stats->nModes];
        for(short i=0; i<stats->nModes; i++) { stats->mode[i] = mode[i+2]; }
    } else stats->mode = nullptr;
    
 // deallocate memory for mode array... 
    delete[] mode; mode = nullptr;
    return stats;
}
// Sort the array values in ascending order using a selection sort algorithm
void sortArr(int *values, int size) {
    short startAt, minIndx; // startAt is the 1st value index in the array to be scanned
    int minVal; 
    for(startAt=0; startAt<(size-1); startAt++) {
        minIndx=startAt; // assume that the 1st scanned value is the minimal one; then compare to others
        minVal = *(values + startAt); // same as values[startAt]
        // inside the scanned range, find the minimal value ant its index
        for(short i=startAt+1; i<size; i++) { 
            if( *(values+i) < minVal ) {
                // Check if the scanned value is less than the previous, set this value as a new minimal value
                minVal=*(values+i);
                minIndx=i; // ... and mark its index as an index of the minimal value
            }
        }
        *(values+minIndx) = *(values+startAt); // exchange the first scanned element with the minimal value
        *(values+startAt) = minVal; // Place the minimal value at the beginning element in scanned range
    }
}
//Looking for the mode
int* getMode(int *arr, int size) { // arr should be already sorted!
    // 3 vectors: values - distinct values
                // freqs - their frequencies
                // modes - distinct values sharing the same max frequency
    vector<int> values, freqs, modes;
    int *modesAr = nullptr; // will be an array of modes to return from the function
    int count=0, maxFreq; // count - number of distinct values; maxFreq - max value in "freqs" vector
    bool noModes = false; // if all frequencies are the same, no modes

    for(short i=0; i<size-1; i++) {
        count=1; // count how many times arr[i] value repeats in the array
        while(arr[i]==arr[i+1] && i<size-1) {
            count++; i++;
        }
        values.push_back(arr[i]);
        freqs.push_back(count);
    }
    // first check if all frequencies are the same
    for(short i=1; i<freqs.size(); i++) {
        if(freqs[0]!=freqs[i]) break;
        if(i==freqs.size()-1) { noModes = true; }
    }
    //find the highest frequency   
    maxFreq=freqs[0]; // first, assume it's the 1st frequency. Then compare to others.
    if(!noModes) { // if all frequencies are the same, don't bother with this block         
        for(short i=1; i<freqs.size(); i++) {
            if(freqs[i]>maxFreq) maxFreq=freqs[i];
        }
        //now, again, step through the whole freqs vector and compare its elements with "maxFreq",
    //    then add the corresponding elements from "values" vector to "modes" vector
        for(short i=0; i<freqs.size(); i++) {
            if(freqs[i]==maxFreq) modes.push_back(values[i]);
        }
    }
    modesAr=new int[modes.size()+2]; // enough size for all modes; if no modes, modes.size()=0
//    the 1st element will store # of modes for the array
//    the 2nd element will store max frequency
    //... so to pass # of modes and max frequency to the calling function
    *modesAr=modes.size();
    *(modesAr+1) = maxFreq;
    // and now, copy all modes to the modesAr and return it
    // if no modes, this loop will not even start
    for(int i=2; i<modes.size()+2; i++) { *(modesAr+i)=modes[i-2]; }
    return modesAr;
}
// Display the array statistics
void printStat(Stats *stats) {
    cout<<"\n\n**** Array statistics ******\n\n";
    cout<<fixed<<setprecision(1);
    cout<<"Mean is "<<stats->avd<<endl;
    cout<<"Median is "<<stats->median<<endl;
    cout<<"The highest frequency is "<<stats->maxFreq<<endl;
    cout<<"There "; if(stats->nModes==1) cout<<"is "; else cout<<"are "; 
    cout<<stats->nModes<<" mode"; if(stats->nModes!=1) cout<<"s";
    if(stats->nModes) {  cout<<":"; // if there are modes display them
        for(int i=0; i<stats->nModes; i++) {
            if(i) cout<<","; cout<<" "<<stats->mode[i];
        }
    } else cout<<"."; cout<<endl;
}