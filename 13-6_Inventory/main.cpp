/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on March 28, 2018, 10:37 AM
 * Purpose: Create inventory item's objects with item #, quantity, and cost.
 *          Calculate total cost as cost per unit * units
 *          Define various constructors, mutator and accessor functions to set/retrieve data.
 *          Display info on items as a table.
 */
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Invntry.h"
using namespace std;
//User libraries
// Global constants: math, science, conversion factors, 2D array columns
// Function prototypes
void print(Invntry &, short = 10);// Display employee's data in a table

// Execution
int main(int argc, char** argv) {
    short n = 3; // # of items to enter data for
    Invntry items[n];
    char input[8]; // to store user's input before setting it as a value
    
    cout<<"Hi\nPlease enter the info for "<<n<<" inventory items.\n";
    for(short i=0; i<n; i++) {
        cout<<"#"<<i+1<<endl;
        cout<<"\tItem #: ";
        cin.getline(input, 5);
        items[i].setItNo(static_cast<short>(atoi(input)));
//      clear buffer in case user entered more chars than expected
        if(!cin) { cin.clear(); cin.ignore(100, '\n'); }
        cout<<"\tQuantity: ";
        cin.getline(input, 5);
        items[i].setQnty(static_cast<short>(atoi(input)));
        if(!cin) { cin.clear(); cin.ignore(100, '\n'); }
        cout<<"\tCost: $";
        cin.getline(input, 7);
        items[i].setCost(atof(input));
        if(!cin) { cin.clear(); cin.ignore(100, '\n'); }
    }
    cout<<"\nThank you.\n\n";
//     print info on all items
    for(short i=0; i<n; i++) print(items[i]);
    return 0;
}
//Display info on items as a table.
void print(Invntry &thing, short w) {
    static bool first = true;
    if(first) {// display the table header if the function is called for the 1st time
        cout<<left<<setw(w)<<"Item #"<<setw(w)<<"Quantity"<<setw(w)<<"Cost, $"<<setw(w)<<"Total, $"<<endl;
        for(short i=0; i<(4*w); i++) cout<<"-";
        cout<<endl;
        first=false;
    }
    cout<<setw(w)<<thing.getItNo()<<setw(w)<<thing.getQnty();
    cout<<setw(w)<<fixed<<setprecision(2)<<thing.getCost()<<setw(w)<<thing.getTot()<<endl;
}
