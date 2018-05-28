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
//#include "Streams.h"
using namespace std;

class Round { // Round class declaration with functions defined in-line
    private:
        static short Nround_s;/// static variable, updates every time the new instance of Round is created
        short Nround; /// a round number
        char winner[nameSz]; /// char *winner; - was problematic because read a wrong name from a file
        short guesses; /// a number of guesses
    public:
        Round();/// Constructors
        void setWnnr(Player *); /// set a winner name
        void setNgss(short); /// set # of guesses
        short getNum() const { return Nround; } /// access a round number
        const char *getWnnr() const { return winner; } /// access a winner name
        short getNgss() const { return guesses; } /// access # of guesses
        ~Round() { } /// Destructor
        /// Friend functions - Stream operators
        friend ostream &operator<< (ostream&, const Round&);
        friend fstream &operator<<(fstream&, Round&);
        friend fstream &operator>>(fstream&, Round&);
};
#endif /* ROUND_H */