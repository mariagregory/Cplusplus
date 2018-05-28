/* 
 * File:   Profile.h
 * Author: Mariia Gregory
 *
 * Created on May 12, 2018, 9:44 PM
 * Purpose: Definition of Profile class, a base class for Player
 */

#ifndef PROFILE_H
#define PROFILE_H

using namespace std;
#include "Player.h" /// base class
#include <iostream>
#include <cstdlib>

class Player;/// Forward Player and Profile class declarations
class Profile;

/// Stream operator overloading function prototypes
fstream &operator<<(fstream&, Player&);

/// Global constant for a name size
const short nameSz = 20; /// Player name size. Used in main.cpp also

class Profile {
    protected:
        char name[nameSz];
        short Nplayed;
        short Nwon; // updates before fire() returns "true"
        float rate;
    public:
        Profile(); /// Default constructor
        Profile(const char *); /// Constructor accepting a name as an argument
        Profile(Player &); /// copy constructor
        void operator=(Player &); /// overloaded assignment operator
        void setName(const char *);/// set player's name
        void addNpld() { ++Nplayed; }
        short played() const { return Nplayed; }/// access # of games played
        short won() const { return Nwon; } /// access # of games won
        float getRate();
        const char *getName() const { return name; }/// access player's name
        
        /// Error-detecting classes
        /// class Err { public: virtual string str() = 0; }
        class NoFile { //An instance created only if trying to work with non-existing file
            private: 
                string s;
            public:
                NoFile() { 
                    s = "The input file does not exist or cannot be opened.\n"; 
                }
                string str() const { return s; }
        };
        class NoRead { //An instance created only if reading from a file fails
            private: 
                string s;    
            public:
                NoRead() { 
                    s = "Cannot read the file.\n"; 
                }
                string str() const { return s; }
        };
        class DivZero {
            private: 
                string s;
            public:
                DivZero(short denom) { 
                    s = "Cannot divide by "; 
                    s+=denom; 
                }
                string str() const { return s; }
        };
        virtual ~Profile() { } // Destructor
        /// friend function - file stream operator
        friend fstream &operator<<(fstream&, Player&);
};
#endif /* PROFILE_H */