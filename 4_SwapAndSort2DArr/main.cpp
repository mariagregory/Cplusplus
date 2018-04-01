/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 * Created on March 9, 2018
 * Purpose:  Sorting a 2-D array of characters if row and columns match
 * Note:  This time you create the strcmp() function that takes into
 * account the new sort order.
 */

//System Libraries Here
#include <iostream>//cin,cout
#include <cstring> //strlen(),strcmp(),strcpy()
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Allowed like PI, e, Gravity, conversions, array dimensions necessary
const int COLMAX=80;//Only 20 required, and 1 for null terminator

//Function Prototypes Here
int  read(char [][COLMAX],int &);//Outputs row and columns detected from input
void sort(char [][COLMAX],int,int,const char[],const char[]);//Sort by row using strcmp();
void print(const char [][COLMAX],int,int);//Print the sorted 2-D array
int strcmp(char [],char [],const char [],const char []);//Replace sort order

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int ROW=30;             //Only 20 required
    char array[ROW][COLMAX];      //Bigger than necessary 
    int colIn,colDet,rowIn,rowDet;//Row, Col input and detected
    char replace[COLMAX],with[COLMAX];//New sort order
    
    //Input the new sort order then sort
    cout<<"Modify the sort order by swapping these characters."<<endl;
    cin>>replace;
    cout<<"With the following characters"<<endl;
    cin>>with;
    cout<<"Read in a 2 dimensional array of characters and sort by Row"<<endl;
    cout<<"Input the number of rows <= 20"<<endl;
    cin>>rowIn;
    cout<<"Input the maximum number of columns <=20"<<endl;
    cin>>colIn;
    
    //Now read in the array of characters and determine it's size
    rowDet=rowIn;
    cout<<"Now input the array."<<endl;
    colDet=read(array,rowDet);
    
    //Compare the size input vs. size detected and sort if same
    //Else output different size
    if(rowDet==rowIn&&colDet==colIn){
        sort(array,rowIn,colIn,replace,with);
        cout<<"The Sorted Array"<<endl;
        print(array,rowIn,colIn);
    }else{
        if(rowDet!=rowIn)
        cout<<(rowDet<rowIn?"Row Input size less than specified.":
            "Row Input size greater than specified.")<<endl;
        if(colDet!=colIn)
        cout<<(colDet<colIn?"Column Input size less than specified.":
            "Column Input size greater than specified.")<<endl;
    }
    //Exit
    return 0;
}

//Outputs row and columns detected from input
// It returns # of columns detected in a c-string
int  read(char chars[][COLMAX],int &rows) {
    int cols=0;
    
    for(int row=0; row<rows; row++) {
        cin>>chars[row];
        chars[row][strlen(*(chars+row))]='\0';
     }
    for(int row=0; row<rows; row++) {
        if(cols<strlen(*(chars+row))) 
            cols=strlen(*(chars+row));
    }
    return cols;
}

//Sort by row using strcmp(), the user-defined
void sort(char chars[][COLMAX],int rows,int cols,const char replace[],const char with[]) {
    // variables for selection sort
    short startAt; // will change with each iteration; it's the 1st scannable element index
    short minInd; // index of the row with the min value
    char minRow[cols];// the row with min value
    char swap[cols]; // temporary c-string to store the row for swapping
    
    // But first (!), perform Bubble sort, but only 1 iteration! 
    // This will ensure that Mark --> Mary will not --> Marx back again
    // Pass 2 c-strings at a time to overloaded strcmp function
    // and after comparing 1st & 2nd, compare 3rd & 4th. 
    // Don't compare 2nd and 3rd, so to avoid double-swapping in the 2nd row
    int i=0;
    while(i<rows-1) {
        if( ! (strcmp (chars[i+1], chars[i], replace, with) ) ) { 
            // will return 0 if chars[i+1] > chars[i]; otherwise 1
            strcpy(swap, chars[i]);
            strcpy(chars[i],chars[i+1]);
            strcpy(chars[i+1], swap);
        }
        i+=2; // jump 2 rows down, so we can compare the next pair
        if( rows%2==1 && i==rows-1) { 
        // If the # of rows is odd, and we are on the last element (will NOT pass i<rows-1 condition),
        // just replace its characters right here
            for(int col=0; col<cols; col++) {
                for(int j=0; j<strlen(replace); j++) {
                    if(chars[i][col]==replace[j]) {
                        chars[i][col]=with[j];
                        break;	// go to the next char in a string/row; avoid double-swapping
                    }
                }
            }
        }
    }
		
    // after that, I would perform selection sort, and I will use the standard strcmp(), 
    //with only 2 char* as arguments. This way, I don't risk swapping characters back again

    for(startAt=0; startAt<rows-1; startAt++) {
        strcpy(minRow,chars[startAt]);	 // set minRow to the first c-string in a scannable range
        minInd=startAt;                 // ... and its index to minInd

        for(int i=startAt+1; i<rows; i++) {
            if(strcmp(chars[i], minRow /*,replace,with*/) < 0) { 
        // returns a negative number if minRow is alphabetically > chars[i]    
        //It's a standard function from <cstring>, with smaller parameter list
                strcpy(minRow,chars[i]);
                minInd=i;		
            }
        }
        strcpy(swap,chars[startAt]);
        strcpy(chars[startAt],minRow);
        strcpy(chars[minInd],swap);
    }

    // and now, swap swapped characters back.....
    for(int row=0; row<rows; row++) {
        for(int col=0; col<cols; col++) {
            for(int j=0; j<strlen(with); j++) {
                if(chars[row][col]==with[j]) {
                    chars[row][col]=replace[j];
                    break;	
                }
            }
        }
    }	
}
////Print the sorted 2-D array
void print(const char chars[][COLMAX],int rows,int cols) {
    for(int row=0; row<rows; row++) {
        for(int col=0; col<cols; col++) {
            cout<<chars[row][col];
        }
        cout<<endl;
    }
}
//
//int strcmp(char a[],char b[],char replace[],char with[]){
int strcmp(char thisRow[],char nextRow[],const char replace[],const char with[]) {
    //if( strlen(thisRow)!=strlen(nextRow) || strlen(thisRow)!=strlen(nextRow) ) cout<<"Oh uh! The lengths of parallel c-strings are different\n";

    for(int i=0; i<strlen(thisRow); i++) {
        for(int j=0; j<strlen(replace); j++) {
            if(thisRow[i]==replace[j]) {
                thisRow[i]=with[j];
                break; // after we replaced a character, stop the loop so that this swapped char not replaced again
            }	// for example, "Marc", after we replace 'c' --> 'y', becomes "Mary". 
//		// If no break; 'y' would --> 'z', and "Mary" would turn into "Marz"..
        }
    }
    for(int i=0; i<strlen(nextRow); i++) {
        for(int j=0; j<strlen(replace); j++) {
            if(nextRow[i]==replace[j]) {
                nextRow[i]=with[j];
                break; // after we replaced a character, stop the loop so that this swapped char not replaced again
            }	// for example, "Marc", after we replace 'c' --> 'y', becomes "Mary". 
//		// If no break; 'y' would --> 'z', and "Mary" would turn into "Marz"..
        }
    }	

    for(int i=0; i<strlen(thisRow); i++) {
    //	Check if thisRow[i] is less than nextRow[i]
        if(thisRow[i]<nextRow[i]) {
            return 1;	
        }
    } return 0;
}