/* 
 * File:   8.5 Rainfall Statistics
 * Author: Mariia Gregory
 * Purpose: Store rainfall data in all 12 months of the year, 
 *      determine the total annual and average monthly rainfall
 *      and months with the highest and lowest amounts.
 *      Then display a list of months, sorted in order of rainfall. from highest to lowest
 * 
 * Created on February 27, 2018, 1:09 PM
 */
//System libraries
#include <iostream>
#include <iomanip> // for fixed keyword
#include <string> // to compare strings alphabetically
using namespace std;

//User libraries

// Global constants: math, science, conversion factors, 2D array columns
const short MONTHS=12;

// Function prototypes
// No array size in parameters because MONTHS global constant serves as the size
float totalRF(float[]);
float averRF(float[]);
bool sorted(float[]); // checks if the array has already been sorted before calling selectionSort function
void selectionSort(float[], string[]);
void showArr(float[], string[]); // TO TEST how the array is sorted
void showMax(float[], string[]);
void showMin(float[], string[]);

// Execution begins here
int main(int argc, char** argv) {
    float rainfl[MONTHS],
        total, average;
    // declare an array to store names of months; will be rearranged later with most raining months first
    string maxMon[MONTHS]={ "January", "February", "March", "April", "May", "June",
                            "July", "August", "September","October","November","December" };
    bool validRF = false; // set the flag for invalid rainfall figure input as a floating point number
    
    cout<<"This program generates a rainfall statistics for the year.\n\n";
    cout<<"Please enter the rainfall data for each month: \n";    
    for(short month=0; month<MONTHS; month++) {
        cout<<maxMon[month]<<": ";
        do {
            validRF=false;
            if(!(cin>>rainfl[month])) { // take the user's input and see if it's stored OK as a float
                cout<<"Numbers only please: ";
                cin.clear(); // clear "bad" flag
                cin.ignore(1000,'\n'); // skip the next 1000 chars or a newline, whichever encountered first
            } else if(rainfl[month]<0) {
                cout<<"How can than be?\nType a non-negative number: ";
            } else { validRF=true; } //cout<<rainfl[month]<<" is a valid float value.\n"; }
            
        } while( !validRF);
    }
    cout<<"\nThe total rainfall for this year was "<<totalRF(rainfl)<<endl;
    cout<<"The average rainfall for this year was "<<fixed<<setprecision(2)<<averRF(rainfl)<<endl<<endl;
    selectionSort(rainfl,maxMon);
        cout<< "Here is the sorted array:\n";
        showArr(rainfl,maxMon);
    // Show months with max and min rainfalls
    showMax(rainfl,maxMon);
    showMin(rainfl,maxMon);
    return 0;
}

float totalRF(float rains[]) {
    float total=0;
    for(short i=0; i<MONTHS; i++) {
        total+=rains[i];
    }
}

float averRF(float rains[]) {
    return totalRF(rains)/MONTHS;
}

/* Before calling the selection sort function, why not to check if the array is already sorted?! */
bool sorted(float arr[]) {
    for(short i=0; i<(MONTHS-1); i++) {
        //cout<<"Checking if "<<arr[i]<<" is larger than "<<arr[i+1]<<"...\n";
        if(arr[i]<arr[i+1]) {
            return false;
        }
    }
    return true;
}

/* Perform an descending order selection sort on the array */
void selectionSort(float list[], string maxMths[]) {
    
//   cout<< "Initial (unsorted) array:\n";   showArr(list,maxMths);
    
    if(!sorted(list)) {
        short startAt, maxI; //maxI will refer to the element index, to access corresponding months
        float maxValue;
        string tempMon; // to store max month temporarily before storing it as the array element
        for(startAt=0; startAt<(MONTHS-1); startAt++) {
            //cout<<"Start scanning at "<<startAt<<endl;
            maxValue=list[startAt]; // here, maxValue resets correctly, but later, it takes its value from previous iteration
            maxI=startAt; 
            //cout<<"list["<<startAt<<"] is now "<<list[startAt]<<endl;
            //cout<<"MaxValue is set to "<<maxValue<<", maxI is now "<<maxI<<", which refers to "<<maxMths[maxI]<<endl;
            
            // inside the scanned range, find the minimal value and its index
            for(short i=startAt+1; i<MONTHS; i++) {
                //cout<<"\tInner loop: i= "<<i<<"\n";
                //cout<<"\tChecking if "<<list[i]<<" > "<<maxValue<<"...\n";
                if(list[i]>maxValue) {
                    maxValue=list[i];
                    maxI=i; // take the corresponding index in the parallel array of month names
                }
            }
//            cout<<"Max rainfall "<<maxValue<<" was in "<<maxMths[maxI]<<endl;
            list[maxI]=list[startAt]; // exchange the first scanned element with the minimal value
 //           cout<<"list["<<maxI<<"] becomes "<<list[startAt]<<endl; //DEBUG
            list[startAt]=maxValue; // Place the max value at the beginning element in scanned range
   //         cout<<"list["<<startAt<<"] becomes "<<maxValue<<endl; //DEBUG
            tempMon=maxMths[maxI];
            //cout<<"The max month is now "<<maxMths[maxI]<<", so store it temporarily somewhere...";
            maxMths[maxI]=maxMths[startAt];
  //          cout<<"maxMths["<<maxI<<"] becomes "<<maxMths[startAt]<<endl; //DEBUG
            maxMths[startAt]=tempMon; // so 0 for January becomes 1, and so on
 //           cout<<"maxMths["<<startAt<<"] becomes "<<tempMon<<endl; //DEBUG/
        }
    } 
}
// Determine the month(s) with the highest rainfalls
void showMax(float rains[], string mMonths[]) {
    selectionSort(rains, mMonths); // make sure the array is sorted in descending order
    // the fist element in descending sorted array is about the largest rains
    short max=rains[0];
    string minMon=mMonths[0];
    
    //Display the first month in array, which had the most rains
    cout<<minMon;
    
    for(short i=1; i<MONTHS; i++) {
        if(rains[i]==max) {
            cout<<", "<<mMonths[i];
        } else break;
    }
    cout<<" had the largest number of rainy days.\n";
}

// Determine the month(s) with the lowest rainfalls
void showMin(float rains[], string mMonths[]) {
    if(!sorted(rains)) { cout<<"Sort your array first!\n"; } // make sure the array is sorted in descending order
    short min=rains[MONTHS-1];
    string minMon=mMonths[MONTHS-1];
    cout<<minMon;
    
    for(short i=MONTHS-2; i>=0; i--) {
        if(rains[i]==min) {
            cout<<", "<<mMonths[i];
        } else break;
    }
    cout<<" had the lowest number of rainy days."<<endl;;
}

// Display the list of rainfall values by month. Month indices are passed to keys[] parameter
void showArr(float values[], string keys[]) {
    for(short i=0; i<MONTHS; i++) { 
        cout<<keys[i]<<": "<<values[i]<<"\n";
    }
    cout<<endl;
}