/* 
 * File:   Round.cpp
 * Author: Mariia Gregory
 *
 * Created on May 9, 2018, 12:07 PM
 * Purpose: Round class specification
 */

#include <cstring> /// for strcpy(,)
#include "Player.h" /// setWnnr(Player *p)
#include "Round.h"
using namespace std;

short Round::Nround_s = 0; // initializaion of a static class variable

/// Constructor
Round::Round() { 
    Nround_s++;
    Nround = Nround_s;  
    guesses=0; 
}
/// Set a winner name for the round
void Round::setWnnr(Player *p) {
    strncpy(winner, p->getName(), nameSz);  
}
/// Set a number of guesses made by a player
void Round::setNgss(short gss) { 
    if(gss>0) 
        guesses=gss; 
}