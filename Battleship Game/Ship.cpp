/*!
 * File:   Board.h
 * Author: Mariia Gregory
 *
 * Created on April 3, 2018, 10:38 AM
 * Purpose: Specification file for Ship class
 **/

#include "Ship.h" /*! a ship itself*/
//#include <utility> /*! pair<T1, T2>, x,y coordinates on a grid*/
#include <ctime> // for rand() in ship direction generation
#include <cstdlib>
using namespace std;

//class NegLen;

Ship::Ship(short length) {
    setLen(length);
    hit = new bool[length]{false}; /*! when hit, the ship 'cell' becomes true */
    sunk = false; /*! when all ship spots are hit, becomes true*/
    vert = rand()%2 ? false : true; /*! Direction: 1 - vertical, 0 - horizontal*/
    /// set coordinates - call from board
}
void Ship::setLen(short l) { 
    if(l>0) length = l; 
    else throw NegLen();
}
/*! compares user-guessed x,y coordinates with an enemy ship locations */
bool Ship::isHit(short x, short y) const {
    if(vert && this->x==x) { /*! in vertically placed ships, x-coordinate is constant*/
        if(y >= this->y && y <= (this->y + length-1) ) {
            hit[y - this->y] = true; /*! mark as HIT on the (x,y) ship spot */
            return true;
        }
    }else if(!vert && this->y == y) {  /*! in horizontal ships, y-coordinate is constant*/
        if(x >= this->x && x <= this->x +length-1) {
            hit[x - this->x] = true; /*! mark as hit on a ship*/
            return true; 
        }
    } return false;
}
/*! Check if all the ship's spots are hit. If yes, the ship is sunk*/
bool Ship::isSunk() const { // Checks if all "hit" elements are true
    for(short i=0; i<length; i++) { 
        if(!hit[i]) return false; 
    } return true;
}
Ship::~Ship() { /// Destructor
    delete [] hit; hit = NULL;
}