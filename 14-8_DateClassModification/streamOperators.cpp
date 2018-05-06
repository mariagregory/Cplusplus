/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   streamOperators.cpp
 * Author: MariiAndreas
 *
 * Created on May 5, 2018, 8:17 PM
 */

#include "Date.h"
#include <iostream>
using namespace std;


ostream &operator<< (ostream &strm, const Date &date) {
    strm << date.getMonStr() << " " << date.getDay() <<", "<<date.getYear();
    return strm;
}
istream &operator>> (istream &strm, Date &date) {
    short m, d, y;
    if(strm >> m >> d >> y) {
        if(m>12) cout<<m<<" will be changed to 12!\n";
        else if(m<1) cout<<m<<" will be changed to 1!\n";
        if(d>31) cout<<d<<" will be changed to 31!\n";
        else if(d<1) cout<<d<<" will be changed to 1!\n";
        if(y>2100) cout<<y<<" will be changed to 2100!\n";
        else if(y<1600) cout<<y<<" will be changed to 1600!\n";
        date.setDate(m,d,y);
    }
    else {
        strm.clear(); strm.ignore(100, '\n');
        cout<<"Please don\'t try anything stupid!\n";
        cout<<"Enter a date in \"mm dd yyyy\" format:\n";
        operator>>(strm,date);
    }
}