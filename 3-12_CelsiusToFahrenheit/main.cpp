/* 
 * File:   3.12 Celsius to Fahrenheit
 * Author: Mariia Gregory
 * Purpose: Convert Celsius temperature to that of Fahrenheit
 *
 * Created on February 26, 2018, 10:53 AM
 */

#include <iostream>
using namespace std;


int main(int argc, char** argv) {
    short cels, fahr;
    cout<<"Hi!\nType the temperature in Celsius, and I will convert it to Fahrenheit for you: ";
    cin>>cels;
    fahr = 9*cels/5 + 32;
    cout<<cels<<" degrees Celsius equals " << fahr<<" degrees Fahrenheit."<<endl;
    cout<<"Thank you for using this program.\nBye!";
    return 0;
}

