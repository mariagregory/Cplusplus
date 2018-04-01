/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 * Created on 03/05/18 10:45pm
 * Purpose:  Even, Odd Vectors and Array Columns Even, Odd
 * Note:  Check out content of Sample conditions in Hacker Rank
 * Input size of integer array, then array, output columns of Even, Odd
 * Vectors then Even, Odd 2-D Array
 */

//System Libraries Here
#include <iostream>//cin,cout
#include <vector>  //vectors<>
#include <iomanip> //Format setw(),right
#include <string> // for getline() and others, to take and work with the user's input of integers
#include <cstdlib> // for getline() and others, to take and work with the user's input of integers
#include <sstream> // for converting the usr's input as string to an array of integers
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Allowed like PI, e, Gravity, conversions, array dimensions necessary
const int COLMAX=2;//Only 2 columns needed, even and odd

//Function Prototypes Here
void read(vector<int> &, vector<int> &);
void copy(vector<int>, vector<int>,int [][COLMAX]);
void prntVec(vector<int>, vector<int>,int);//int n is the format setw(n)
void prntAry(const int [][COLMAX],int,int,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int ROW=80;           //No more than 80 rows
    int array[ROW][COLMAX];     //Really, just an 80x2 array, even vs. odd
    vector<int> even(0),odd(0); //Declare even,odd vectors
    
    //Input data and place even in one vector odd in the other
    read(even,odd);
    
    //Now output the content of the vectors
    //          setw(10)
    prntVec(even,odd,10);//Input even, odd vectors with setw(10);
    
    //Copy the vectors into the 2 dimensional array
    copy(even,odd,array);
    
    //Now output the content of the array
    //                              setw(10)
    prntAry(array,even.size(),odd.size(),10);//Same format as even/odd vectors
    
    //Exit
    return 0;
}
void read(vector<int> &even, vector<int> &odd) {
    string input;//, item;
   //stringstream ssInput;
	//char *input; 
    int *storage = NULL;
	int elems;
    
	//int input;
	cout<<"Input the number of integers to input.\n";
	cin>>elems;
	storage=new int[elems];
	
	cout<<"Input each number.\n";
	getline(cin,input);
	// split the string, using a whitespace as a delimiter
	//ssInput<<input;
	
	for(int i=0; i<elems; i++) {
		cin >> storage[i];//item;
		//*storage=atoi(item.c_str());
		//storage++;
	}
	
	for(int i=0; i<elems; i++) {
		if(storage[i]%2) { odd.push_back(storage[i]); }//cout<<storage[i]<<" is odd\n"; }
		else if (storage[i]%2==0) { even.push_back(storage[i]); }//cout<<storage[i]<<" is even\n"; }	
		else  cout<<"Oh un! Non-number was entered.\n";
	}
	even.push_back(0);
	odd.push_back(0);
	
	delete [] storage;
}
void copy(vector<int> even, vector<int> odd, int arr[][COLMAX]) {
    int rows;
    bool evenEnd=false, oddEnd=false; // signal if the end of either vector was reached
    if(even.size()>=odd.size()) rows=even.size();
    else rows=odd.size();
    
    for(int i=0; i<rows; i++) {
        if(i==even.size()) evenEnd=true;
		if(i==odd.size()) oddEnd=true;
		arr[i][0]= !evenEnd ? even[i] : 0; 
        //cout<<"arr["<<i<<"][0]"<<" is "<<arr[i][0]<<endl;
        arr[i][1] = !oddEnd ? odd[i] : 0;
        //cout<<"storing "<<arr[i][0]<<" and "<<arr[i][1]<<endl;
    }
}
void prntVec(vector<int> even, vector<int> odd, int width) {
    int rows = even.size()>=odd.size() ? even.size() : odd.size();
    bool evenEnd=false, oddEnd=false;
	cout<<setw(width)<<"Vector";
    cout<<setw(width)<<"Even"<<setw(width+1)<<"Odd\n";
    for(int i=0; i<rows-1; i++) { // don't know why but if I used "i<rows" as a condition, an extra line was printed
        cout<<setw(width)<<""<<setw(width);
		if(!evenEnd && even[i]) {
			cout<<even[i];
		} else { 
			cout<<""; 
			evenEnd=true;
		}
		cout<<setw(width)<<right;
		if(!oddEnd && odd[i]) {
			cout<<odd[i];	
		} else { 
			cout<<""; 
			oddEnd=true; 
		}
		cout<<endl;
    }
}
//int n is the format setw(n)
void prntAry(const int arr[][COLMAX], int evenSze, int oddSze, int width) {
   int rows;
   bool evenEnd=false, oddEnd=false;
    if(evenSze>=oddSze) rows=evenSze;
    else rows=oddSze;
    cout<<setw(width)<<"Array";
    cout<<setw(width)<<"Even"<<setw(width+1)<<"Odd\n";
    for(int i=0; i<rows; i++) {
        cout<<setw(width)<<""<<setw(width);
		if(!evenEnd && arr[i][0]) { 
			cout<<arr[i][0];
		} else { 
			cout<<""; 
			evenEnd=true;
		}
		cout<<setw(width)<<right;
		if(!oddEnd && arr[i][1]) {
			cout<<arr[i][1];	
		} else { 
			cout<<""; 
			oddEnd=true; 
		}
		cout<<endl;
    }
}