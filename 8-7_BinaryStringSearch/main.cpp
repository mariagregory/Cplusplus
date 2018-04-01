/* 
 * File:  8.7 Binary String Search
 Author: Mariia Gregory
 *
 * Created on February 26, 2018, 9:48 PM
 * Purpose: Search an array of strings (sorted) using a binary search algorithm
 */
//System libraries
#include <iostream>
#include <string> // to compare strings alphabetically
#include <typeinfo> // for typeid(_).name() function to verify a variable data type
using namespace std;

//User libraries

// Global constants: math, science, conversion factors, 2D array columns

// Function prototypes
short binarySearch(string[], short, string);
void selectionSort(string[], short);
bool sorted(string[], short);
void showSortedArr(string[], short); // TO TEST how the array is sorted

// Execution begins here
int main(int argc, char** argv) {
    const int NUM_NAMES = 20;
    string names[NUM_NAMES] = {"Jennifer", "Tony", "Josh", "Lindsey", "Mark", "Matt", "Keri", "JC", "Tasha",
        "Mylin", "Tera", "Nita", "Rhona", "Ilana", "Nikki", "Christina", "Dan", "Chase", "Dale", "Kevin"};
    string lookup;
    short result;
    /*for(int name=0; name<NUM_NAMES; name++) {
        cout<<"Name "<<name+1<<": ";
        cin>>names[name];
    }*/
    
    cout<<"Type the name you want to search for?\n(Capitalize the first letter please): ";
    cin>>lookup;
    result=binarySearch(names, NUM_NAMES, lookup);
    if(result<0) cout<<"Sorry, there is no "<<lookup<<" in the list.\n";
    else cout<<"Bingo! "<<lookup<<" is found at position "<<result+1<<".\n";
    return 0;
}
/* Search the array of strings for a particular name */
short binarySearch(string list[], short size, string value) {
    // check if the list is sorted in ascending order
    cout<<"\nChecking if the list is sorted...\n";
    if(!sorted(list, size)) { // if not, call the selection sort function
        selectionSort(list, size);
    } else { cout<<"Wow, it is already!\n"; }
   
    short first = 0, 
        last = size-1,
        middle;
    bool found = false;
    
    while(!found && first<=last) {
        middle = (first+last)/2;
        //cout<<"Middle is now "<<middle<<endl;
        if(list[middle]==value) { // !list[middle].compare(value) will return 0, which is actually 'true'
            found = true;
            return middle;
        } else if (list[middle]>value) {
        // if the name is alphabetically upper in the list, limit the search to the 1st half
            last = middle-1;
            cout<<list[middle]<<" is greater than "<<value<<", so middle becomes "<<middle<<endl;
        } else {
            first = middle+1; // limit the search to the 2nd half
            cout<<list[middle]<<" is lesser than "<<value<<", so middle becomes "<<middle<<endl;
        }
    }
    return -1;
}

/* Perform an ascending order selection sort on the array */
void selectionSort(string list[], short size) {
    cout<<"Entering selectionSort function with the array of "<<size<<" "<<typeid(*list).name()<<"...\n";
    short startScan, minIndex;
    string minValue;

    for(startScan=0; startScan<(size-1); startScan++) {
        minIndex=startScan;
        minValue=list[startScan];
        // inside the scanned range, find the minimal value ant its index
        for(short i=startScan+1; i<size; i++) { 
            //if(list[i]<list[startScan]) {
            if(list[i]<minValue) {
                minValue=list[i];
                minIndex=i;
            }
        }
        list[minIndex]=list[startScan]; // exchange the first scanned element with the minimal value
        list[startScan]=minValue; // Place the minimal value at the beginning element in scanned range
    }
    showSortedArr(list, size);
}
/* Before calling the selection sort function, why not to check if the array is already sorted?! */
bool sorted(string arr[], short size) {
    cout<<"\nEntering isSorted function...\n";
    for(short i=0; i<(size-1); i++) {
        cout<<"Checking if "<<arr[i]<<" is larger than "<<arr[i+1]<<"...\n";
        if(arr[i]>arr[i+1]) {
            cout<<"Oh yes it is!\n";
            return false;
        }
    }
    return true;
}

void showSortedArr(string list[], short size) {
    cout<< "\nHere is the sorted array: \n";
    for(short i=0; i<size; i++) { 
        cout<<i+1<<" "<<list[i]<<"\n";
    }
}