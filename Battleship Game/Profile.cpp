/* 
 * File:   Profile.cpp
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
    Nplayed = 0; 
    Nwon = 0;
    rate = -1.0;
}
Profile::Profile(const char *name) { // constructor --- assign a default name somehow....
    setName(name);
    Nplayed = 0; 
    Nwon = 0;
    rate = -1.0;
}
Profile::Profile(Player &p) {
    *this = p;
}
void Profile::operator=(Player &p) {
    setName(p.name);
    Nplayed = p.Nplayed;
    Nwon = p.Nwon;
    this->rate = p.getRate();
    //rate = rate;//this is what you had, and it doesn't do anything
    //rate = rightHandSideThing.rate; //this is more like what you want
}
void Profile::setName(const char *name) {
    strncpy(this->name, name, nameSz); //strcpy(this->name, name);
}
/// calculate and access % of success
float Profile::getRate() { 
    if(Nplayed>0) { 
        rate = 100.0*Nwon/Nplayed; 
        return rate; 
    } 
    else 
        return -1.0; ///throw DivZero(Nplayed);
}