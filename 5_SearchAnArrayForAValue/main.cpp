/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 * Created on 03/06/2018
 * Purpose:  Searching for multiple occurrence of patterns
 * Note:  cout proceeds to null terminator, cin reads to end of line
 *        for character arrays
 * 
 */

//System Libraries Here
#include <iostream>//cin,cout,getline()
#include <cstring> //strlen()
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//PI, e, Gravity, or conversions

//Function Prototypes Begins Here
//srch1 utility function Input->start position, Output->position found or not
//srch1 is a simple linear search function, repeat in srchAll till all found
//srch1 Input->sentence, pattern, start position Output-> position found
//Remember arrays start at index/position 0
//srchAll Input->sentence, pattern Output->position array
int  srch1(const char [],const char [],int);//Search for 1 occurrence
void srchAll(const char [],const char [],int []);//Search for all occurrences
void print(const char []);//Print the character arrays
void print(const int []); //Print the array of indexes where the pattern found

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int LINE=81;               //Size of sentence or pattern to find
    char sntnce[LINE],pattern[LINE]; //80 + null terminator
    int match[LINE] {-1};                 //Index array where pattern was found
    
    //Input a sentence and a pattern to match
    cout<<"Match a pattern in a sentence."<<endl;
    cout<<"Input a sentence"<<endl;
    cin.getline(sntnce,LINE);

    cout<<"Input a pattern."<<endl;
    cin.getline(pattern,LINE);
    
    //Search for the pattern
    //Input the sentence and pattern, Output the matching positions
    //Remember, indexing starts at 0 for arrays.
    srchAll(sntnce,pattern,match);
    
    //Display the inputs and the Outputs
    cout<<endl<<"The sentence and the pattern"<<endl;
    print(sntnce);
    print(pattern);
    cout<<"The positions where the pattern matched"<<endl;
    print(match);
    
    //Exit
    return 0;
}

int  srch1(const char source[],const char pattern[],int position) {//Search for 1 occurrence {
    //if(*(sntnce+i)==*pattern) { // find the 1st character of pattern inside the sentence
        int j=0;                // ... then check if the following characters also match
        while(j<strlen(pattern)) {
            if(*(source+position+j)!=*(pattern+j)) {
                return -1; //break; // not all characters in the pattern match a passage from the sentence, so forget it....
            } else j++;
        }
        return position;
}

void srchAll(const char sntnce[],const char pattern[],int match[]) {//Search for all occurrences 
    if(strlen(pattern)<=strlen(sntnce)) {
        int count=0, index; // index will hold the position where (and if) the pattern is found
        bool matched = false;

        for(int i=0; i<strlen(sntnce); i++) {
            if(*(sntnce+i)==*pattern) { // find the 1st character of pattern inside the sentence
                index=srch1(sntnce, pattern, i); // ... then check if the following characters also match 
                if(index>=0) { // if the pattern is not there, will return -1
                    matched=true; // signal that all characters from pattern matched the sentence portion
                    match[count]=index; // store the position the pattern is found in "match" array
                    count++;
                    i+=strlen(pattern); // update counter, so it jumps forward after pattern
                }
            } 
        }
    }
}
void print(const char sntnce[]) {//Print the character arrays 
    int i=0;
    //cout<<"strlen of "<<sntnce<<" is "<<strlen(sntnce)<<endl;
	while(i<strlen(sntnce)) {
        cout<<*(sntnce+i);
        i++;
    }
    cout<<endl;
}
void print(const int match[]) { //Print the array of indexes where the pattern found
    int i=0;
    if(match[i]>=0) {
        do {
            cout<<match[i]<<endl;
            i++;
        } while(match[i]>0);
    } else { cout<<"None"; }
}