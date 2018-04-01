/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on March 28, 2018, 10:37 AM
 * Purpose: Create retail item's objects with description, units, and price
 *          Define various constructors, mutator and accessor functions to set/retrieve data.
 *          Display info on items as a table.
 */
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Retail.h"
using namespace std;
//User libraries
// Global constants: math, science, conversion factors, 2D array columns
// Function prototypes
void print(Retail &, short = 10);// Display employee's data in a table

// Execution
int main(int argc, char** argv) {
    short n = 3; // # of items to enter data for
    Retail items[n];
    char input[31]; // to store user's input before setting it as a value
    cout<<"Hi\nPlease enter the info for "<<n<<" retail items.\n";
    for(short i=0; i<n; i++) {
        cout<<"Item #"<<i+1<<endl;
        cout<<"\tDescription: ";
        cin.getline(input, 30);
        items[i].setDesc(input);
//      clear buffer in case user entered more chars than expected
        if(!cin) { cin.clear(); cin.ignore(100, '\n'); }
        cout<<"\tUnits on hand: ";
        cin.getline(input, 5);
        items[i].setQnty(atoi(input));
        if(!cin) { cin.clear(); cin.ignore(100, '\n'); }
        cout<<"\tPrice: ";
        cin.getline(input, 8);
        items[i].setPrce(atof(input));
        if(!cin) { cin.clear(); cin.ignore(100, '\n'); }
    }
    cout<<"Thank you.\n\n";
//     print info on all items
    for(short i=0; i<n; i++) print(items[i]);
    return 0;
}
// Display retail item's data in a table
void print(Retail &thing, short w) {
    static bool first = true;
    static short num = 1;
    if(first) { // display the table header if the function is called for the 1st time
        cout<<right<<setw(w*4.5)<<"Units"<<endl;
        cout<<left<<setw(w)<<"Item #"<<setw(w*3)<<"Description"<<setw(w*2)<<"On Hand"<<setw(w)<<"Price, $"<<endl;
        for(short i=0; i<(7*w); i++) cout<<"-";
        cout<<endl;
        first=false;
    }
    cout<<setw(w)<<num<<setw(w*3)<<thing.getDesc()<<setw(w*2)<<thing.getQnty()<<setw(w*5)<<fixed<<setprecision(2)<<thing.getPrce()<<endl;
    num++;
}
