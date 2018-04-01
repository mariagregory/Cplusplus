/* 
 * File:  9.7 United Cause, modification 2
 Author: Mariia Gregory
 *
 * Created on March 7, 2018, 9:57 PM
 * Purpose: Store user-specifined amounts of donations in an array in the order they were received
 			Dynamically allocate an array, parallel to the first one, and copy the values from the first array
 			Sort the values in the 2nd array in descending order.
 			Display the sorted donation amounts, and then amounts in the order received.
 */
 
//System libraries
#include <iostream>
#include <cctype> // for isdigit()
#include <iomanip> // for fixed and setprecision()
using namespace std;

//User libraries

// Global constants: math, science, conversion factors, 2D array columns

// Function prototypes
 short getNum(const short); // take and validate the user's input for # of donations
 void fillArr(int *, short); // takes and validays the user's input for the array values
 bool sorted(int *, short); // check if the array is already sorted in descending order
 void selSort(int *, short); // sorts values in descending order
 void showArr(const int *, short); // displays the values of the array

//execution starts here
int main() {
    const short DNS_MAX = 30; 
    short numDns;// Number of donations, to be specified by a user
    numDns=getNum(DNS_MAX);

     // An array containing the donation amounts.
    int donatns[numDns] {0}; //}= { 5, 100, 5, 25, 10, 5, 25, 5, 5, 100, 10, 15, 10, 5, 10 };
    cout<<"Please enter the donation amount for each #:\n";
    fillArr(donatns, numDns);

    // A pointer array with the same # of elements as donatns array.
    int *arrPtr = new int[numDns]; // = { [0 ... NUM_DNS-1] = { nullptr };
     // Make each element point to an element in the donations array.
    for (short count = 0; count < numDns; count++)
        *(arrPtr+count) = *(donatns+count);

     // Sort the elements of the array of pointers.
    selSort(arrPtr, numDns);

     // Display the donations using the array of pointers. This
     // will display them in sorted order.
    cout << "The donations, sorted in descending order are: \n";
    //showPtr(arrPtr, NUM_DNS);
    showArr(arrPtr, numDns);

     // Display the donations in their original order.
    cout << "The donations, in their original order are: \n";
    showArr(donatns, numDns);

    delete [] arrPtr; //free dynamically allocated memory
    arrPtr=nullptr;

    return 0;
}

/* This function takes and validates the user's input for # of donations */
short getNum(const short max) {
    int input;
    bool valid;
    cout<<"Please enter # of donations:\n";

    do {
        valid = false; // the input is assumed to be invalid initially
        if(!(cin>>input) ) { // take the user's input and check if it's stored correctly in int type variable
            cout<<"Numbers only please! "; // if it were't, it means something other than a number was entered
            cin.clear(); // clear cin.bad() flag...
            cin.ignore(10000, '\n'); // ignore the next 1000 characters or everything until the newline character is encountered
        } else if(input<1 || input>max) { // if the number was entered but negative or 0 or larger than max # of donations....
            cout<<"Enter a number in a range from 1 to "<<max<<" please: ";
        } else valid = true; // indicate that the input is correct
    } while(!valid);
    //Just in case, remove any remaining characters from the buffer...
    cin.ignore(10000, '\n'); // ... (if user typed some # and then some symbols, symbols may remain in buffer.)
    return input;
}

/* Fill the array with donation amounts entered by user */
void fillArr(int *values, short size) {
    int amount;
    bool valid; // flag to indicate if the $ amount entered is valid

    for(short i=0; i<size; i++) {
        cout<<"Donation #" << i+1 << ": ";
        // Input validation loop
        do {
            valid = false; // the input is assumed to be invalid initially
            if( ! (cin >> amount ) ) { // take the user's input and check if it went OK
                cout<<"Numbers only please!"; // if it were't, it means something other than a number was entered
                cin.clear(); // clear cin.bad() flag...
                cin.ignore(10000, '\n'); // ignore the next 1000 characters or everything until the newline character is encountered
            } else if(amount<=0) { // if the number was entered but negative or 0
                cout<<"Enter a positive value for the donation "<<i+1<<", in $: ";
            } else valid = true; // indicate that the input is correct
        } while(!valid);
        //Just in case, remove any remaining characters from the buffer...
        cin.ignore(10000, '\n'); // ... (if user typed some # and then some symbols, symbols may remain.)

        *(values + i) = amount;
    }
}

/* Perform an descending order selection sort on the array of floats */
void selSort(int *values, short size) {
    if(!sorted(values, size)) { // check if the sorting is ever needed
        short startAt, maxIndx;
        int maxVal;
        for(startAt=0; startAt<(size-1); startAt++) {
            maxIndx=startAt;
            maxVal = *(values + startAt); // same as values[startAt]
            // inside the scanned range, find the minimal value ant its index
            for(short i=startAt+1; i<size; i++) { 
                if( *(values+i) > maxVal ) {
                    // Check if the scanned value is less than the previous, set this value as a new minimal value
                    maxVal=*(values+i);
                    maxIndx=i; // ... and mark its index as an index of the minimal value
                }
            }
            *(values+maxIndx) = *(values+startAt); // exchange the first scanned element with the minimal value
            *(values+startAt) = maxVal; // Place the minimal value at the beginning element in scanned range
        }
    }
}

/* Before calling the selection sort function, why not to check if the array is already sorted?! */
bool sorted(int *array, short size) {
    for(short i=0; i<(size-1); i++) {
        // Check if the next scanned value is greater than the previous
        if( *(array+i) < *(array+i+1) ) {
            return false; // return that the array is not sorted yet
        }
    }
    return true; // if this executes, the array has already been in sorted order
}

// displays all elements in the array
void showArr(const int *values, short size) {
    if(!size) {	cout<<"Nothing to show...\n"; return; }
	
    for(short i=0; i<size; i++) { 
        if(i>0) cout<<", "; 
        cout<<*(values+i);
    }
    cout<<endl;
}