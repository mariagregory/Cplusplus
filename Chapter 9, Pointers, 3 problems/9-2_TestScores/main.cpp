/* 
 * File:  9.2 Test Scores #1
 Author: Mariia Gregory
 *
 * Created on March 4, 2018, 9:48 PM
 * Purpose: Dynamically allocate an array large enough to hold u user-defined # of test scores
 			Once all the scores are entered, sort them in ascending order.
 			Then calculate the average score.
 */
//System libraries
#include <iostream>
#include <cctype> // for isdigit()
#include <iomanip> // for fixed and setprecision()
using namespace std;

//User libraries

// Global constants: math, science, conversion factors, 2D array columns

// Function prototypes
short getNum(); // user input validation for # of scores
void fillArr(float*, short); // take and validate the user's input for scores
void sortArr(float*, short); // selection sort algorithm
bool sorted(float*, short); // to check if the array is already in ascending order
void showArr(float*, short); // TO TEST how the array is sorted
float getAver(float *, short ); // calculates average score

//execution starts here
int main() {
    short nScores;
    float *scores=nullptr;
    cout<<"This program creates a dynamic array of test scores,\n";
    cout<<"sorts them in ascending order, and calculated the average score.\n";
    cout<<"How many scores are you going to enter? ";
    nScores=getNum();

    /*
    // *********DEBUG**********
    short testNum; cout<<"Type some number to see if cin.ignore worked: "; cin>>testNum;
    cout<<"If "<<testNum<<" is what you've just entered, the buffer is clean!\n";
    // *********END-OF-DEBUG*********
    */
    scores=new float[nScores];
    cout<<"Now please enter scores, one by one.\n";
    fillArr(scores, nScores);

    sortArr(scores, nScores);	
    cout<<"Here is the sorted array:\n";
    showArr(scores, nScores);

    cout<<"The average score is "<<fixed<<setprecision(1)<<getAver(scores, nScores)<<endl<<endl;
    cout<<"Thank you,\nBye!\n";

    delete [] scores;
    scores=nullptr;

    return 0;
}
// Takes and validates user's input for the # of elements in the array
short getNum() {
    short input;
    bool valid; // flag for valid input (an integer between 1 and 20, not inclusive)

    do {
        valid = false; // the input is assumed to be invalid initially
        if(!(cin>>input) ) { // take the user's input and check if it went OK
            cout<<"Numbers only please! "; // if it were't, it means something other than a number was entered
            cin.clear(); // clear cin.bad() flag...
            cin.ignore(10000, '\n'); // ignore the next 1000 characters or everything until the newline character
        } else if(input<1 || input>20) { // if the number was entered but negative, 0, or larger than 20...
            cout<<"Enter a number in a range from 1 to 20 please: ";
        } else valid = true; // indicate that the input is correct
    } while(!valid);
    
    //Just in case, remove any remaining characters from the buffer...
    cin.ignore(10000, '\n'); // ... (if user typed some # and then some symbols, symbols may remain in buffer.)
    return input;
}

/* Perform an ascending order selection sort on the array of floats */
void sortArr(float *values, short size) {
    if(!sorted(values, size)) { // check if the sorting is ever needed
        short startAt, minIndx;
        float minVal;
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
}
/* Before calling the selection sort function, why not to check if the array is already sorted?! */
bool sorted(float *array, short size) {
    for(short i=0; i<(size-1); i++) {
        // Check if the scanned value is greater than the next one
        if( *(array+i) > *(array+i+1) ) {
            return false; // return that the array is not sorted yet
        }
    }
    return true;
}

// displays all elements in the array
void showArr(float *values, short size) {
    for(short i=0; i<size; i++) { 
        if(i>0) cout<<", "; 
            cout<<fixed<<setprecision(1)<<*(values+i);
    }
    cout<<endl;
}

/* Fill the array with test scores entered by user */
void fillArr(float *values, short size) {
    float score;
    bool valid;
    for(short i=0; i<size; i++) {
        cout<<"Score " << i+1 << ": ";
        // Input validation loop
        do {
            valid = false; // the input is assumed to be invalid initially
            if( ! (cin >> score ) ) { // take the user's input and check if it went OK
                cout<<"Numbers only please!"; // if it were't, it means something other than a number was entered
                cin.clear(); // clear cin.bad() flag...
                cin.ignore(10000, '\n'); // ignore the next 1000 characters or everything until the newline character
            } else if(score<0 || score>100) { // if the number was entered but negative or 0
                cout<<"Enter a value from 0 to 100 please: ";
            } else valid = true; // indicate that the input is correct
        } while(!valid);
        //Just in case, remove any remaining characters from the buffer...
        cin.ignore(10000, '\n'); // ... (if user typed some # and then some symbols, symbols may remain.)

        *(values + i) = score;
        cout<<endl;
    }
    cout<<"Here is the initial, unsorted, array:\n";
    showArr(values, size);
}
// calculates average value of the array values
float getAver(float *values, short size) {
    if(!size) return 0; // if the size == 0, return 0 to avoid division by 0

    float total=*values; // initialize total with the value of the first element
    float average;

    for(short i=1; i<size; i++) {
            total+=*(values+i);
    }
    average=total/size;

    return average;
}