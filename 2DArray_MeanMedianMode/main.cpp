/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 * Created on March 5, 2018
 * Purpose:  Static 2-D Array
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>   //srand, rand
#include <ctime>     //Time
#include <vector>	// for frequencies, for calculating mode
using namespace std;

//User Libraries

//Global Constants - Math, Science, Conversions, 2D Array Sizes

//Function Prototypes
void fillAry(int*[],int,int);
void prntAry(int*[],int,int);
void destroy(int*);
void getStat(int*[],int,int);
void sortArr(int *, int);
int *getMode(int *, int);

//Executions Begin Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare and allocate memory for the array
    int row=10,col=20;
    int *array[row]; //array of pointers
    
    //fillAry(array,row, col);
    fillAry(array,row,col);

    //Print the random 2-Digit array
    cout<<"Here is the 2D-array:\n";
    prntAry(array,row,col);
    
    getStat(array,row,col);

    for(int i = 0; i < row; i++) {
        destroy(array[i]);  
    } array[row] = nullptr; // free the array of pointers
}

// Generate (pseudo-)random values from 10 to 99 and store them in 2D-array of rows x cols
void fillAry(int *array[], int rows, int cols){
    //Is the size parameter valid
    if(rows<=0)return;
    if(cols<=0)return;
    
// Here, I got so pissed off that I allocated memory for each row dynamically! 
// I haven't figured out how to do the program with 100% static 2D array...
    for(int row=0;row<rows;row++) {
        *(array+row)=new int[cols];
    }
    
    for(int row=0;row<rows;row++) {
        for(int col=0;col<cols;col++){
            *(*(array+row)+col)=rand()%30+10;
        }
    }
}   

// Displays an array as a table
void prntAry(int *a[],int rows, int cols){
    for(int row=0;row<rows;row++){
        for(int col=0;col<cols;col++){
            cout<<*(*(a+row)+col)<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

// Determine and display mean, median, and mode for each row
void getStat(int* values[], int rows, int cols) {
    float meanRaw, medRaw;
    int mean[rows]{0}, median[rows]{0}, *mode[rows]{nullptr}; 
    // mode is going to be kind of 2D array, 
    // ... i.e. array of pointers (with "rows" elements) to variable-sized arrays with modes for each row
    // to determine the median, we need to know if the # of cols is even or odd:
    bool evenCol= cols%2 ? false : true; 

    for(int row=0;row<rows;row++){
        meanRaw=0; medRaw=0;
        for(int col=0;col<cols;col++){
            meanRaw+=*(*(values+row)+col);
        }
        meanRaw/=cols;
        mean[row]=meanRaw;
        if(meanRaw-mean[row]>=0.5) { (mean[row])++; } // round up the integer, if needed

        cout<<"The row "<<row<<" mean value is "<<mean[row]<<" (before rounding it was "<<meanRaw<<")"<<endl;

        // To find median and mode, sort values first
        sortArr(*(values+row), cols); // Now, the row #row is sorted.
        
        if(!evenCol) { // in odd # of cols, we take the value of the middle element. If cols=5, we need [2] (3rd one)
            median[row]=*(*(values+row)+cols/2); 
        } else {  // in even # of cols, median is the half-sum of two middle values.... 
            median[row]=.5 * ( *(*(values+row)+cols/2-1) + *(*(values+row)+cols/2) ); 
        }
        cout<<"The row "<<row<<"\'s median is "<<median[row]<<endl; 

        //Now, find (a) mode(s)
        mode[row]=getMode(*(values+row), cols); // returns a pointer to a dynamically allocated array of modes
        
        // the first element in mode[row] (deferenced) is # of modes in this row
        cout<<"The row "<<row<<" has "<<**(mode+row)<<" mode(s): ";
        cout<<*(*(mode+row)+1);//display the first mode
        for(int i=2; i < **(mode+row)+1; i++) { // only show 2nd+ mode(s) if there is any
            cout<<", "<<*(*(mode+row)+i); 
        }
        cout<<endl<<endl;
    } 
     // deallocate memory for mode 2D-array 1 row at a time... 
    for(int row=0;row<rows;row++) {
        delete[] mode[row];
    } mode[rows]=nullptr;
}

void sortArr(int *values, int size) {
    short startAt, minIndx;
	int minVal;
	for(startAt=0; startAt<(size-1); startAt++) {
        minIndx=startAt;
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

//Looking for the median
int* getMode(int *row, int cols) {
    // values - distinct values (repeatitions are ignored)
    // freqs - their frequencies
    // modes - vector of distinct values sharing the same max frequency
    vector<int> values, freqs, modes;
    int *modesAr=nullptr; // will be an array of modes to return from the function
    int count=0, max; // count will be counter for frequency for each value; max - max frequency

    for(int col=0; col<cols-1; col++){
        count=1;
        while(row[col]==row[col+1] ) {
            count++; // increment frequency
            col++; // check if the next value is the same
        }
        values.push_back(row[col]);
        freqs.push_back(count);
        //cout<<"The value "<<values[i]<<" has "<<freqs[i]<<" frequency.\n";
    }
//find the highest frequency
    max=freqs[0];
    for(int i=1; i<freqs.size(); i++) {
        if(freqs[i]>max) {
            max=freqs[i];
        }
    }
    //now, again, step through the whole freqs vector and compare its elements with "max", 
    // then add the corresponding elements from "values" vector to "modes" vector
    for(int i=0; i<freqs.size(); i++) {
        if(freqs[i]==max) {
            modes.push_back(values[i]);
        }
    }
    // allocate memory for "modesAr" with enough size for all modes + the 1st element stores # of modes for this row
    modesAr=new int[modes.size()+1];
    //... to pass # of modes for this row to the calling function
    // so that we don't print all the garbage values after all modes are printed 
    *modesAr=modes.size();
    // and now, copy all modes to 1D-array and return it
    for(int i=1; i<modes.size()+1; i++) {
        *(modesAr+i)=modes[i-1];
    }
    return modesAr;
}

//deallocate dynamically allocated memory
void destroy(int *a) {
    delete []a;
}
