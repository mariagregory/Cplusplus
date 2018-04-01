/* 
 * File:   11.7 Customer Accounts
 * Author: Mariia Gregory
 *
 * Created on March 18, 2018, 8:39 PM
 * Purpose: Store info on accounts in an array of structures. 
 *          Use menu-driven interface to print or change data.
 */
//System libraries
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include "Account.h"
using namespace std;

Account* fillAry(Account [], short ) ;
void shwMenu(Account [], short);
void printAry(Account [], short );
void change(Account *, short);
float getFloat();
//char *getDate(char*);
char gotChar(); // it was frustrating validating char input every time for 3 functions, so...
void destroy(Account []);

int main(int argc, char** argv) {
    short size=3;//10;
    Account *accnts = nullptr;
    accnts = fillAry(accnts, size);
    shwMenu(accnts, size);
            
    return 0;
}

Account* fillAry(Account *records, short size) {//, short size) {
    if(!size || size<0) {
        cout<<"Oh uh! Cannot create array for " << size<<" records.\n";
        exit(EXIT_FAILURE);
    }
    records = new Account[size];
    
    for(short i=0; i<size; i++) {
        cout<<"Account #"<<i<<": \n";
        cout<<"\tName: ";
        cin.getline((records+i)->name, sizeof((records+i)->name)-1); // or fgets(records->name, sizeof(records->name), stdin);
        cout<<"\tAddress line 1 (Apt#, House#, Street): ";
        cin.getline((records+i)->addrs_1, sizeof((records+i)->addrs_1)); 
        cout<<"\tAddress line 2 (City, State, ZIP): ";
        cin.getline((records+i)->addrs_2, sizeof((records+i)->addrs_2));         
        cout<<"\tPhone: ";
        cin.getline((records+i)->phone, sizeof((records+i)->phone));
        cout<<"\tAccount balance: ";
        (records+i)->balance = getFloat();
        cout<<"\tDate of last payment: ";
        cin.getline( (records+i)->payDate, sizeof((records+i)->payDate) );
//        strcpy( (records+i)->payDate, getDate((records+i)->payDate) );
    }
    return records;
}
// Displays a menu with choices to: Print or Change the structures, or to exit the program
void shwMenu(Account records[], short size) {
    char choice;
    bool valid;
    cout<<"\nWhat would you like to do next?\n";
    cout<<"\t1 - Print records\n\t2 - Change records\n\t3 - Exit the Program\n";
    
    choice = gotChar();
    
    if(choice<'1' || choice>'3') {    
        cout<<"Invalid choice!\nRefer to the menu:\n";
        //cin.ignore();//1000, '\n'); //- before using cin.get() or cin.getline()
        shwMenu(records,size);
    }
    switch(choice) {
        case '1': {
           printAry(records,size);
           break;
        }
        case '2': {
            change(records,size);
            break;
        }
        default: {
            cout << "Thank you for using this program.\nBye!\n"; 
            destroy(records);
        }
    }    
}
// Allows user to choose a record to print
void printAry(Account records[], short size) {//, short size) {
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
        printAry(records, size);
    }
    if(choice=='X') shwMenu(records, size); 
    // 4 lines above, the "Invalid choice!" displays, and then this line executes... HOW it sees 'x' in double way???
    if(choice=='E') {
        for(short i=0; i<size; i++) {
            cout<<"Account #" << i<<":\n";
            cout<<"\tName: " << (records+i)->name<<"\n";
            cout<<"\tAddress line 1: " << (records+i)->addrs_1<<"\n";
            cout<<"\tAddress line 2: " << (records+i)->addrs_2<<"\n";
            cout<<"\tPhone: " << (records+i)->phone<<"\n";
            cout<<"\tBalance: " << (records+i)->balance<<"\n";
            cout<<"\tDate of last payment: " << (records+i)->payDate<<"\n";
            cout<<endl;
        }
    } else {
        index=static_cast<short>(choice-48);// static_cast<int>(choice) - stores ascii code as int. For ex, '0' is stored as 48
        if(index>=0 && index<size) {
            cout<<"Account #" << index<<":\n";
            cout<<"\tName: " << (records+index)->name<<"\n";
            cout<<"\tAddress line 1: " << (records+index)->addrs_1<<"\n";
            cout<<"\tAddress line 2: " << (records+index)->addrs_2<<"\n";
            cout<<"\tPhone: " << (records+index)->phone<<"\n";
            cout<<"\tBalance: " << (records+index)->balance<<"\n";
            cout<<"\tDate of last payment: " << (records+index)->payDate<<"\n";
        } else {
            cout<<"Invalid record number!\n";
            cout<<"Records are in a range 0 - "<<size-1<<".\n";
            printAry(records, size);
        }
    }
    cout<<"\nPress Enter to see the menu.\n";
    cin.ignore();
    cin.get(); // doesn't work!!!! DAMN IT!!!!!!!!
    shwMenu(records,size);
}
// Allows user to choose a record and fields in this record to change
// User can also delete a record..... but I'm working on it
void change(Account records[], short size) {
    short index;
//    string rwIndex; //raw index, in case user enters 
//    index=static_cast<short>(getInteger("Which record do you want to change (0-"<<size-1<<")? ", "A number in a range 0-"<<size-1<<": "));
    cout<<"Which record do you want to change (starting at 0)? ";
    while(!(cin>>index)) {// && (index>=0 && index<size) ) {
        //if(input.fail()) {
            cout<<"Did you enter a digit? I don\'t think so...\nTry again: ";
            cin.clear(); cin.ignore(1000, '\n');
    }
    if(index>=0 && index<size) {
        char choice;
        cout<<"What exactly do you want to change?\n";
        cout<<"\t1 - Name\t2-Address\t3 - Phone\n\t4 - Date of last payment";
        cout<<"\t5 - Balance\n\tX - Cancel\n"; // 27 is Esc, 127 is Del in https://www.asciitable.com/
        choice = gotChar();
        choice = toupper(choice); // doesn't always work!!!!!!
//        cout<<"You typed "<<choice<<endl; // just TEST!!!!
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
                cin.getline((records+index)->name, sizeof((records+index)->name));
            } else if(choice=='2') {
                cout<<"Address line 1 (Apt#, House#, Street): ";
                cin.getline((records+index)->addrs_1, sizeof((records+index)->addrs_1)); 
                cout<<"Address line 2 (City, State, ZIP): ";
                cin.getline((records+index)->addrs_2, sizeof((records+index)->addrs_2)); 
            } else if(choice=='3') {
                cout<<"New phone: ";
                cin.ignore(); 
                cin.getline((records+index)->phone, sizeof((records+index)->phone));
            } else if(choice=='5') {
                cout<<"The current balance is " << (records+index)->balance << ".\nThe new balance: $";
                (records+index)->balance = getFloat();
//              Book says "no negative account balances should be accepted."
//              So I will not subtract from balance...
            } else {
                cout<<"\tNew date of payment: ";
                cin.ignore(); 
                cin.getline((records+index)->payDate, sizeof((records+index)->payDate) );
//                strcpy( (records+index)->payDate, getDate( (records+index)->payDate ) );
            }
            
        }
        cout<<"The data are modified.\n";
    } else {
        cout<<"Invalid record number!\n";
        cout<<"Records are in a range 0 - "<<size-1<<".\n";
        change(records, size);
    }
    cout<<"\nPress Enter to see the menu.\n";
//  !!!! Not sure if I should use the next statement....!!
    cin.ignore(); //it does cin.get(' ') for the next statement if I don't cin.ignore(). DAMN IT!!!!!!!!
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
// Takes and validates user's input for date. 
//char *getDate(char *test) {
//    string test;
//    bool valid;
//    
//    do{
//        valid = false;
//        cout<<"Please enter the date in the format yyyy/mm/dd: ";
//        cin.getline(test, 10);
//        for(short i=0; i<10; i++) {
//            if( (i<4 || i==5 || i==6 || i>7) && !(isdigit(test[i])) ) {
//                break; // break the innermost for loop and start do-while again
//            } else if( i==0 && (test[i]>2 || test[i]<1) ) {
//                cout<<"Invalid year!\n";
//                break;
//            } else if( (i==5 && test[i]>1) || (i==6 && test[i]>2) ) {
//                cout<<"Invalid month!\n";
//                break;
//            } else if( (i==4 || i==7) && test[i]!='/') {
//                cout<<"Invalid separator.\n";
//                break;
//            }
//            valid=true;
//        }
//    }while(!valid);
//    return test;
//}

// Takes and validates user's input for menu option as char. 
char gotChar() {
    char choice;
    bool valid=false;
    //cin.ignore(100, '\n'); // stores ' ' or '\n' if I don't do it.... stupid!
    
    do{
       valid=false;
       if(!(cin.get(choice)) ) {
           cin.clear(); cin.ignore();
       } else if(!(isalnum(choice))) {
//           cout<<"Oh sorry... Type it again please: ";
           continue;
       } else valid=true;
    }while(!valid);
    
//    cout<<"You typed "<<choice<<endl; //TEST
    return choice;
}

void destroy(Account records[]) {
    delete [] records;
    records=nullptr;
    exit(EXIT_SUCCESS);
}