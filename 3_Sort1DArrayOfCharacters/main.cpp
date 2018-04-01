/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 * Created on March 5, 2018
 * Purpose:  Sorting an array of characters if specified correctly
 */

//System Libraries Here
#include <iostream>//cout,cin
#include <cstring> //strlen()
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
int  read(char []);
void sort(char [],int);
void print(const char [],int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int SIZE=80;//Larger than needed
    char array[SIZE]; //Character array larger than needed
    int sizeIn,sizeDet;//Number of characters to be read, check against length
    
    //Input the size of the array you are sorting
    cout<<"Read in a 1 dimensional array of characters and sort"<<endl;
    cout<<"Input the array size where size <= 20"<<endl;
    cin>>sizeIn;
    
    //Now read in the array of characters and determine it's size
    cout<<"Now read the Array"<<endl;
    sizeDet=read(array);//Determine it's size
    
    //Compare the size input vs. size detected and sort if same
    //Else output different size to sort
    if(sizeDet==sizeIn){
        sort(array,sizeIn); //Sort the array
        print(array,sizeIn);//Print the array
    }else{
        cout<<(sizeDet<sizeIn?"Input size less than specified.":
            "Input size greater than specified.")<<endl;
    }
    
    //Exit
    return 0;
}

//read user's input
int read(char array[]) {
    int count=0;
    char input;
    cin.clear(); cin.ignore(1000, '\n');
	cin.get(input);
    
    do{
       if(input=='\n') break;
	   if(isalnum(input)) {
			array[count]=input;
			count++;
		} 
    } while(cin.get(input) );	    //cout<<"Got "<<array<<endl;
    return count;
}

// selection sort algorithm
void sort(char array[],int size){
    char minVal;
    int minInd, startAt;
    for(startAt=0; startAt<size-1; startAt++) {
        minVal=array[startAt];
        minInd=startAt;
        for(int i=startAt+1; i<size; i++) {
            if(array[i]<minVal) {
                minVal=array[i];
                minInd=i;
            }
        }
        array[minInd]=array[startAt];
        array[startAt]=minVal;
    }
}
//display the text, one character at a time
void print(const char a[],int size){
    for(int i=0; i<size; i++) {
        cout<<a[i];
    }
}
