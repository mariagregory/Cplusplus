/* 
 * File:   Streams.h
 * Author: Mariia Gregory
 *
 * Created on May 27, 2018, 8:11 PM
 */

#ifndef STREAMS_H
#define STREAMS_H

#include <iostream> // operator <<
#include "Round.h"
#include "Profile.h"
using namespace std;

class Round;

// Overloaded output-stream operator
ostream &operator<<(ostream &strm, const Round &round) { // displays a round data on the screen
    static bool called = false;
    if(!called) {  /// If the function is called the 1st time, display a table header
        strm<<"\n  GAME HISTORY"<<endl;
        strm<<"________________________________________"<<endl;
        strm<<" Round # | ";
        strm<<setw((nameSz+6)/2)<<"Winner";
        strm<<setw((nameSz-6)/2)<<""<<"| Guesses"<<endl;
        strm<<"________________________________________"<<endl;
        called = true;
    }
    strm << " "<<setw(5)<<right<<round.getNum()<<setw(3)<<" ";
    strm << "| "<<setw(nameSz)<<left<<round.getWnnr();
    strm << "| "<<setw(4)<<right<<round.getNgss()<<endl;
    return strm;
}
// Overloaded file-stream operators
/// write Round data to a file
fstream &operator<<(fstream &file, Round &r) { 
    if(file) {
        file.write(reinterpret_cast<char*>(&r), sizeof(r));
        return file;
    } 
    else 
        throw Profile::NoFile();
    return file;
}
/// read Round data from a file
fstream &operator>>(fstream &file, Round &r) { 
    if(file) {
        file.read(reinterpret_cast<char*>(&r), sizeof(r)); //    cout<<"Read!\n";
        while(file) {
            cout<<r; //"Read guesses = "<<round->getNgss()<<", winner = "<<round->getWnnr()<<endl;
            file.read(reinterpret_cast<char*>(&r), sizeof(r));
        }
        cout<<"________________________________________"<<endl;
        file.close();
        return file;
    } 
    else
        throw Profile::NoFile();
    return file;
}
/// Overloaded file stream operator, to write Profile data to a file
fstream &operator<<(fstream &file, Player &player) {
    Profile prof = player; // cout<<"Profile has "<<sizeof(Profile)<<" bytes."<<endl;
    if(file) {
        file.write(reinterpret_cast<char*>(&prof), sizeof(prof)); /*!    Writing players' profiles*/
//        cout<<"Now on byte "<<file.tellp()<<endl;
        return file;
    } 
    else throw Profile::NoFile();
}
#endif /* STREAMS_H */