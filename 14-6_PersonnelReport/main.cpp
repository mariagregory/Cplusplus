/**
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on May 4, 2018, 8:02 AM
 * Purpose: Store number of vacation and sick leave days for workers. 
 *          Determine # of paid and unpaid vacation and sick leave days.
 */

#include <iostream>
#include <iomanip>
#include <ctime> /// for random # generation
#include "TimeOff.h"
using namespace std;

///Function prototypes
void print(TimeOff*, short);

///Execution starts here
int main(int argc, char** argv) {
    srand(time(0));
    TimeOff workers[5] = { /// create an array of TimeOff class objects
        /// initialize each instance with ID, name, and # of months worked
        { "Jack", "2547979", rand()%13 }, /// worker 1 worked <=1 year, */
        { "Chris", "1112233", rand()%13+12 }, /// worker 2 <=2 years, and so on */
        { "Lance", "9998877", rand()%13+24 },
        { "Joey", "6554433", rand()%13+36 },
        { "Joshua", "2221199", rand()%13+48 },
    };
    for(short i=0; i<5; i++) { /// set # of used vacation and sick leave days for each worker
    	workers[i].setVac(rand()%(20*(i+1))); /// assuming a worker takes up to 20 vacation days a year
    	workers[i].setSick(rand()%(15*(i+1))); /// ... and gets sick for up to 15 days a year
    }
    print(workers, 5); /// call a function to display data on workers in a table
    workers[0].setMnths(rand()%61); /// change # of months worked by 1st worker....
    cout<<"\nAfter changing a number of months worked by "<<workers[0].getName()<<":\n";
    print(workers, 5); /// ... and see how earned vacations and sick leave update in a table
    return 0;
}
/// Display info on each worker's time off
void print(TimeOff *workers, short size) {
    ///    Display a table header
    cout<<right<<setw(9)<<"|"<<setw(21+9)<<"| Months |";
    cout<<setw(32)<<"Vacation Days        |"<<setw(31)<<"Sick Leave Days        "<<endl;
    cout << "  ID    |        Name        | Worked |";
    cout<<" Earned | Used | Paid | Unpaid | Earned | Used | Paid | Unpaid "<<endl;
    for(short i=0; i<9+21+9+32+31; i++) cout<<"-"; cout<<endl;
    for(short i=0; i<size; i++) { /// determine # of paid and unpaid vacation and sick leave days for each worker
        short vacErnd, vacUsed, vacPaid, vacUnpd, sckErnd, sckUsed, sckPaid, sckUnpd;
        vacErnd = workers[i].getMaxVac().gtDays();
        vacUsed = workers[i].getVac().gtDays();
        vacPaid = vacErnd>=vacUsed ? vacUsed : vacErnd;
        vacUnpd = vacErnd>=vacUsed ? 0 : vacUsed-vacErnd;
        sckErnd = workers[i].getMaxSick().gtDays();
        sckUsed = workers[i].getSick().gtDays();
        sckPaid = sckErnd>=sckUsed ? sckUsed : sckErnd;
        sckUnpd = sckErnd>=sckUsed ? 0 : sckUsed-sckErnd;
    ///    Display data in the table
        cout <<left<<setw(8)<<workers[i].getId()<<"| "<<setw(19)<<workers[i].getName()<<"| ";
        cout<<setw(7)<<workers[i].getMnths()<<"| ";
        cout<<setw(7)<<vacErnd<<"| "<<setw(5)<<vacUsed<<"| "<<setw(5)<<vacPaid<<"| "<<setw(7)<<vacUnpd<<"| ";
        cout<<setw(7)<<sckErnd<<"| "<<setw(5)<<sckUsed<<"| "<<setw(5)<<sckPaid<<"| "<<sckUnpd<<endl;
    }
    for(short i=0; i<9+21+9+32+31; i++) cout<<"-"; cout<<endl;
}    