/* 
 * File:   11.8 Search for Customer Accounts
 * Author: Mariia Gregory
 *
 * Created on March 19, 2018, 7:39 PM
 * Purpose: Store info on accounts in an array of structures. 
 *          Use menu-driven interface to print or change data.
            Allow user to search the structure array for a particular 
            customer's account with a name that matches it.
 */
//System libraries
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <vector> // used in srchAcc(), to store indices of records where the name patter was found
#include "Account.h"
using namespace std;

Account* fillAry(Account [], short ) ;
void shwMenu(Account [], short);
void printAr(Account [], short );
void prntRec(Account [], short);
void change(Account *, short);
void srchAcc(Account *,short, char*);
float getFloat();
char gotChar(); // it was frustrating validating char input every time for 3 functions, so...
void destroy(Account [], short);

int main(int argc, char** argv) {
    short size=10;
    Account *accnts = nullptr;
    accnts = fillAry(accnts, size);
    shwMenu(accnts, size);
            
    return 0;
}
// Search for records whose 'name' property contains a pattern the user searches for 
void srchAcc(Account *records, short size, char *name) {
    vector<short> inds;
    short count=0;
    
    for(short i=0; i<size; i++) {
//        Search for the 1st occurrence of 'name' in 'records[i]->name' and returns a pointer to it.
//        Otherwise, returns nullptr (address 0)
        if(strstr((records+i)->name, name)) {
            count++;
            inds.push_back(i);
        }
    }
    if(count) {
        cout<<"Found "<<name<<" in "<<count<<" records.\n";
        for(short i=0; i<count; i++) {
            prntRec(records,inds[i]);
        }
    } else cout<<"Sorry, no account matches the name "<<name<<".\n";
}

Account* fillAry(Account *records, short size) {//, short size) {
    if(!size || size<0) {
        cout<<"Oh uh! Cannot create array for " << size<<" records.";
        exit(EXIT_FAILURE);
    }
    records = new Account[size];
    short mxChars=100;
    
    for(short i=0; i<size; i++) {
        // allocate memory for c-strings in an element of the array
        (records+i)->name = new char[mxChars];
        (records+i)->addrs_1 = new char[mxChars];
        (records+i)->addrs_2 = new char[mxChars];
        (records+i)->phone = new char[mxChars];
        (records+i)->payDate = new char[mxChars];
        
        cout<<"Account #"<<i<<": \n";
        cout<<"\tName: ";
        cin.getline((records+i)->name, mxChars-1); // or fgets(records->name, sizeof(records->name), stdin);
        cout<<"\tAddress line 1 (Apt#, House#, Street): ";
        cin.getline((records+i)->addrs_1, mxChars-1); 
        cout<<"\tAddress line 2 (City, State, ZIP): ";
        cin.getline((records+i)->addrs_2, mxChars-1);         
        cout<<"\tPhone: ";
        cin.getline((records+i)->phone, mxChars-1);
        cout<<"\tBalance: $";
        (records+i)->balance = getFloat();
        cout<<"\tDate of last payment: ";
        cin.getline( (records+i)->payDate, mxChars-1 );
    }
    return records;
}
// Displays a menu with choices to: Print or Change the structures, or to exit the program
void shwMenu(Account records[], short size) {
    char choice;
    bool valid;
    cout<<"\nWhat would you like to do next?\n";
    cout<<"\t1 - Print records\n\t2 - Change records\n";
    cout<<"\t3 - Search for a record\n\t4 - Exit the Program\n";
    
    choice = gotChar();
    
    if(choice<'1' || choice>'4') {    
        cout<<"Invalid choice!\nRefer to the menu:\n";
        //cin.ignore();//1000, '\n'); //- before using cin.get() or cin.getline()
        shwMenu(records,size);
    }
    switch(choice) {
        case '1': {
           printAr(records,size);
           break;
        }
        case '2': {
            change(records,size);
            break;
        }
        case '3': {
            char topic[50];
            cout<<"Enter an account owner's name: ";
            cin.ignore();
            cin.getline(topic, 50);
            srchAcc(records,size,topic);
            cout<<"\nPress Enter to see the menu.\n";
//            cin.ignore();
            cin.get(); // doesn't work!!!! DAMN IT!!!!!!!!
            shwMenu(records,size);
        }
        default: {
            cout << "Thank you for using this program.\nBye!\n"; 
            destroy(records,size);
        }
    }    
}
// Allows user to choose a record to print
void printAr(Account records[], short size) {//, short size) {
    short index;
    char choice;
    cout<<"Which record do you want to print?\n\tType # in a range 0 - "<<size-1<<", \n";
    cout<<"\tE - print Everything\tX - return to menu.\n";
//    cin.ignore(); // I don't know how to make it NOT to store ' ' in this freaking choice ...
    choice = gotChar();
    choice = toupper(choice);

    if(!isdigit(choice) && choice!='E' && toupper(choice)!='X') { // choice!='X' doesn't work!!!!!!!
        //cin.ignore(1000, '\n');
        cout<<"Invalid choice!\n"; // WHY when I type 'x', this message appears and then - shwMenu()???? 
        printAr(records, size);
    }
    if(choice=='X') shwMenu(records, size); 
    // 4 lines above, the "Invalid choice!" displays, and then this line executes... HOW it sees 'x' in double way???
    if(choice=='E') {
        for(short i=0; i<size; i++) {
            prntRec(records,i);
        }
    } else {
        index=static_cast<short>(choice-48);// static_cast<int>(choice) - stores ascii code as int. For ex, '0' is stored as 48
        if(index>=0 && index<size) {
            prntRec(records,index);
        } else {
            cout<<"Invalid record number!\n";
            cout<<"Records are in a range 0 - "<<size-1<<".\n";
            printAr(records, size);
        }
    }
    cout<<"\nPress Enter to see the menu.\n";
    cin.ignore();
    cin.get(); // doesn't work!!!! DAMN IT!!!!!!!!
    shwMenu(records,size);
}
// Display just one record
void prntRec(Account records[], short i) {
    cout<<"Account #" << i<<":\n";
    cout<<"\tName: " << (records+i)->name<<"\n";
    cout<<"\tAddress line 1: " << (records+i)->addrs_1<<"\n";
    cout<<"\tAddress line 2: " << (records+i)->addrs_2<<"\n";
    cout<<"\tPhone: " << (records+i)->phone<<"\n";
    cout<<"\tBalance: $" << (records+i)->balance<<"\n";
    cout<<"\tDate of last payment: " << (records+i)->payDate<<"\n";
}

// Allows user to choose a record and fields in this record to change
// User can also delete a record..... but I'm working on it
void change(Account records[], short size) {
    short index;

    cout<<"Which record do you want to change (starting at 0)? ";

    while(!(cin>>index)) {// && (index>=0 && index<size) ) {
        cout<<"Did you enter a digit? I don\'t think so...\nTry again: ";
        cin.clear(); cin.ignore(1000, '\n');
    }
    if(index>=0 && index<size) {
        char choice;
        short mxChars=100;
        cout<<"What exactly do you want to change?\n";
        cout<<"\t1 - Name\t2 - Address\n\t3 - Phone\t4 - Date of last payment";
        cout<<"\n\t5 - Balance\tX - Cancel\n";
        choice = gotChar();
        choice = toupper(choice); // doesn't always work!
        if(toupper(choice) == 'X') shwMenu(records, size);
        else {
            if(choice<'1' || choice>'5') {
                cout<<"Invalid choice!\n";
    //            cin.ignore(1000, '\n'); //- before using cin.get() or cin.getline()
                change(records, size);
            }
            if(choice=='1') {
                cout<<"New name: ";
                cin.ignore(); 
                cin.getline((records+index)->name, mxChars-1);
            } else if(choice=='2') {
                cout<<"Address line 1 (Apt#, House#, Street): ";
                cin.getline((records+index)->addrs_1, mxChars-1); 
                cout<<"Address line 2 (City, State, ZIP): ";
                cin.getline((records+index)->addrs_2, mxChars-1); 
            } else if(choice=='3') {
                cout<<"New phone: ";
                cin.ignore(); 
                cin.getline((records+index)->phone, mxChars-1);
            } else if(choice=='5') {
                cout<<"The current balance is " << (records+index)->balance << ".\nThe new balance: $";
                (records+index)->balance = getFloat();
//              Book says "no negative account balances should be accepted."
//              So I will not subtract from balance...
            } else {
                cout<<"\tNew date of payment: ";
                cin.ignore(); 
                cin.getline((records+index)->payDate, mxChars-1 );
            }
        }
        cout<<"The data are modified.\n";
    } else {
        cout<<"Invalid record number!\n";
        cout<<"Records are in a range 0 - "<<size-1<<".\n";
        change(records, size);
    }
    cout<<"\nPress Enter to see the menu.\n";
    cin.get(); // Pause until user presses Enter
    shwMenu(records,size);
}

// Takes and validates user's input for account balance. 
float getFloat() {
    float result;
    bool valid;
//    cin.ignore();
    do {
        valid=false;
        if(!(cin>>result)) { 
            cout<< "Numbers only please: ";
            cin.clear(); cin.ignore(100, '\n');
        } else if(result<0) {
            cout<<"ERROR:\nPlease enter a non-negative amount: ";
        } else valid=true;
    } while(!valid);
    cin.clear(); cin.ignore(1000, '\n');
    return result;
}

// Takes and validates user's input for menu option as char. 
char gotChar() {
    char choice;
    bool valid=false;
    
    do{
       valid=false;
       if(!(cin.get(choice)) ) {
           cin.clear(); cin.ignore();
       } else if(!(isalnum(choice))) {
           continue;
       } else valid=true;
    }while(!valid);
    
    return choice;
}

// release memory allocated for pointers
void destroy(Account records[], short size) {
    for(short i=0; i<size; i++) {
        delete [] (records+i)->name;
        delete [] (records+i)->addrs_1; 
        delete [] (records+i)->addrs_2;
        delete [] (records+i)->phone;
        delete [] (records+i)->payDate;
    }
    delete [] records;
    records=NULL;
    exit(EXIT_SUCCESS);
}