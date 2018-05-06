/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on May 4, 2018, 8:02 AM
 * Purpose: Store number of vacation and sick leave days for workers. 
 *          Determine # of paid and unpaid vacation and sick leave days.
 */

#include <iostream>
#include "TimeOff.h"
#include "NumDays.h"
using namespace std;

int main(int argc, char** argv) {
    TimeOff workers[3] = { 
        { "Jack", "2547979", 21, 10 },
        { "Cruz", "1112233" },
        { "Sweety", "9998877", 28, 14 }
    };    
    for(short i=0; i<3; i++) {
        cout << workers[i].getName() << ", id "<<workers[i].getId()<<", took ";
        cout << workers[i].getVac().gtDays() << " paid vacation days,\n";
        cout << workers[i].getSick().gtDays() << " paid sick leave days,\nand ";
        cout << workers[i].getUnpd().gtDays() << " unpaid sick leave days.\n\n";
    }
    return 0;
}