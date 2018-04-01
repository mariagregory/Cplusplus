/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on March 28, 2018, 10:37 AM
 * Purpose: Create person's objects with name, age, address, and phone
 *          Define various constructors, mutator and accessor functions to set/retrieve data.
 *          Display info on people as a table.
 */
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Person.h"
using namespace std;
//User libraries
// Global constants: math, science, conversion factors, 2D array columns
// Function prototypes
void print(Person &, short = 10); // Display employee's data in a table
Person *getMore(); // Invites user's input on more employees

// Execution
int main(int argc, char** argv) {
    Person guy1("Chanel Sweety",22,"1234 Beverly Hills, LA, CA 90210", "789-123-5667");
    Person guy2("Maria Gregory",150,"Cloud #9, Middle of Nowhere","");
    Person guy3("Somebody Homeless", 55,"","");
    Person guy4("Someone without phone", 7, "1111 Where phones don\'t work, North Pole","");
    print(guy1);
    print(guy2);
    print(guy3);
    print(guy4);
    
    Person *guys = getMore(); // Invite user's input on more people
    delete guys; // release memory allocated in getMore() function
    return 0;
}
// Display people's data in a table
void print(Person &guy, short w) {
    static bool first = true;
    if(first) { // display the table header if the function is called for the 1st time
        cout<<left<<setw(w*3)<<"Name"<<setw(w/2)<<"Age"<<setw(w*5)<<"Address"<<setw(w*3)<<"Phone"<<endl;
        for(short i=0; i<(9*w); i++) cout<<"-";
        cout<<endl;
        first=false;
    }
    cout<<setw(w*3)<<guy.getName()<<setw(w/2)<<guy.getAge()<<setw(w*5)<<guy.getAddr()<<setw(w*3)<<guy.getPhon()<<endl;
}
// Invites user's input on more people
Person *getMore() {
    short count=2; // # of employees to add
    Person *people = new Person[count];
    char input[51]; // to store user's input before setting it as a value
    
    cout<<"\nNow enter info about "<<count<<" other people.\n";
    
    for(short i=0; i<count; i++) {
        cout<<"#"<<i+1<<endl;
        cout<<"\tName: ";
        cin.getline(input, 30);
        people[i].setName(input);
//      clear buffer in case user entered more chars than asked
        if(!cin) { cin.clear(); cin.ignore(1000, '\n'); } 
        cout<<"\tAge: ";
        cin.getline(input, 4);
        people[i].setAge(atoi(input));
        if(!cin) { cin.clear(); cin.ignore(1000, '\n'); }
        cout<<"\tAddress: ";
        cin.getline(input, 50);
        people[i].setAddr(input);
        if(!cin) { cin.clear(); cin.ignore(1000, '\n'); }
        cout<<"\tPhone: ";
        cin.getline(input, 20);
        people[i].setPhon(input);
        if(!cin) { cin.clear(); cin.ignore(1000, '\n'); }
    }
    cout<<endl;
    for(short i=0; i<count; i++) {
        print(people[i]);
    }
    return people;
}