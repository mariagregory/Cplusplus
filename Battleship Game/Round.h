/* 
 * File:   Round.h
 * Author: Mariia Gregory
 *
 * Created on May 9, 2018, 12:07 PM
 * Purpose: Round class definition
 */

#ifndef ROUND_H
#define ROUND_H

#include <iostream> // operator <<
#include <fstream>
#include <iomanip> ///setw()
#include <cstring> /// for strcpy(,)
#include "Player.h" /// setWnnr(Player *p)
using namespace std;

class Round;

ostream &operator<< (ostream&, const Round&);
fstream &operator<<(fstream&, Round&);
fstream &operator>>(fstream&, Round&);
        
class Round { // Round class declaration with functions defined in-line
    private:
        static short Nround_s;// static variable, updates every time the new instance of Round is created
        short Nround;
        char winner[nameSz]; // char *winner; - was problematic because read a wrong name from a file
        short guesses;
    public:
        Round(short r = 0) { Nround = r;  guesses=0; Nround_s++; }//winner = new char[nameSz]; }
        void setWnnr(Player *p) { strncpy(winner, p->getName(), nameSz);  }
        void setNgss(short gss) { if(gss>0) guesses=gss; }
        short getNum() const { return Nround; }
        const char *getWnnr() const { return winner; }
        short getNgss() const { return guesses; }
        ~Round() { }
};

short Round::Nround_s = 0; // initlalizaion of a static class variable

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
    } else throw Profile::NoFile();
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
    } else throw Profile::NoFile();
}
#endif /* ROUND_H */
