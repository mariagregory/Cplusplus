/* 
 * File:   task6.cpp
 * Author: Maria Gregory
 *
 * Created on April 20, 2018, 7:47 PM
 */
#include <cstdlib>
#include <iostream>
#include <iomanip> // setw, and to make sure it's not a scientific notation
#include <vector> // for getMode()
#include "floatSp.h"
using namespace std;

// Display two numbers in different base representation
void task6() {
    floatSp num1(2.875, "01011100000000000000000000000010", "5C000002", "10.111", "2.E", "2.7");
    floatSp num2(0.1796875, "01011100000000000000000011111110", "5C0000FE", ".0010111", ".2E", ".137");
    
    cout<<left<<fixed;
    cout<<setw(20)<<"Original Numbers"<<setw(35)<<num1.getNum()<<"|  "<<num2.getNum()<<endl;
    cout<<setw(20)<<"Float Binary"<<setw(35)<<num1.getBin()<<"|  "<<num2.getBin()<<endl;
    cout<<setw(20)<<"Float Hexadecimal"<<setw(35)<<num1.getHex()<<"|  "<<num2.getHex()<<endl;
    cout<<setw(20)<<"Raw Binary"<<setw(35)<<num1.getBRaw()<<"|  "<<num2.getBRaw()<<endl;
    cout<<setw(20)<<"Raw Hexadecimal"<<setw(35)<<num1.getHRaw()<<"|  "<<num2.getHRaw()<<endl;
    cout<<setw(20)<<"Raw Octal"<<setw(35)<<num1.getORaw()<<"|  "<<num2.getORaw()<<endl;
}