/* 
 * File:   Profile.h
 * Author: Mariia Gregory
 *
 * Created on May 12, 2018, 9:44 PM
 * Purpose: Specification file for Profile class
 */

#include "Player.h"
#include "Profile.h"
#include <cstring> // strcpy(,)
#include <fstream> 
#include <iostream> // *************testing
using namespace std;

Profile::Profile() {
    setName("Jane Doe");///Tried -- string n = "Jane Doe"; setName(n.c_str()); -- but it didn't work -- segmentation fault
    Nplayed = 0; Nwon = 0;
}
Profile::Profile(const char *name) { // constructor --- assign a default name somehow....
    setName(name);
    Nplayed = 0; Nwon = 0;
}
Profile::Profile(Player &p) {
    *this = p;
}
void Profile::operator=(Player &p) {
    setName(p.name);
    Nplayed = p.Nplayed;
    Nwon = p.Nwon;
}
void Profile::setName(const char *name) {
    strncpy(this->name, name, nameSz); //strcpy(this->name, name);
}
// Overloaded stream operators
fstream &operator<<(fstream &file, Player &player) { /// write Profile data to a file
    Profile prof = player; // cout<<"Profile has "<<sizeof(Profile)<<" bytes."<<endl;
    if(file) {
        file.write(reinterpret_cast<char*>(&prof), sizeof(prof)); /*!    Writing players' profiles*/
//        cout<<"Now on byte "<<file.tellp()<<endl;
//        cout<<"Wrote "<<prof.getName()<<endl;
        return file;
    } else throw Profile::NoFile();
}