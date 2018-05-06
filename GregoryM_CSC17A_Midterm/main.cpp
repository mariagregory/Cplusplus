/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on April 21, 2018, 8:39 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip> // to make sure numbers are displayed as integers, if re-prompting user for a menu choice
#include <cstring> // atof
#include <string> // length()
#include <cctype> // isdigit
using namespace std;

/*! Function prototypes */
void Menu();
void task1(); void task2();
void task3(); void task4();
void task5(); void task6(); void task7();
float takeNum(float, float);

/*! Execution starts here */
int main(int argc, char** argv) {
    short choice;
    do {
        Menu(); 
        // to make sure menu choices numbers are shown as integers, if re-prompting user for a choice
        cout<<fixed<<setprecision(0); 
        choice = takeNum(0,7); cout<<endl;
        switch(choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 7: task7(); break;
            default: cout<<"Thank you for using this program.\nBYE!\n";
        }
    }while(choice);
    
    
    return 0;
}
// Display the menu with available choices
void Menu() {
    cout<<"\n* * * Here is the menu: * * *\n\n"
        "\t1: Account Checking\n\t2: Employee Paycheck\n"
        "\t3: Statistical Analysis\n\t4: Encryption and Decryption\n"
        "\t5: Highest Factorials\n\t6: Number Representation\n"
        "\t7: Factoring by Prime Numbers.\n\t0: EXIT.\n";
    cout<<"Choose: ";
}

// Take and validate a numeric value from user's input. 
// Initially, store the input as string and then convert to float (can be type-cast to an integer later)
// ... so that the keyboard input buffer is not trashed by accident.
float takeNum(float min, float max) {
    float result;
    string input;
    bool valid;
    do {
        valid = false;
        getline(cin, input);
        for(short i=0; i<input.length(); i++) {
            if(!isdigit(input[i]) && input[i]!='.' && input[i]!='-') { 
                cout<<"\tError! Numbers only please: "; break; 
            } if(i==input.length()-1) valid = true; // if it's the last char in input, then all are digits
        }
        if(valid) {;
            result = atof(input.c_str());
            if(result < min || result > max) {
                valid = false;
                cout<<"\tError! Numbers from "<<min<<" to "<<max<<" please: ";
            }
        }
    }while(!valid);
    return result;
}