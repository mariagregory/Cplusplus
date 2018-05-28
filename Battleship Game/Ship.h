/*! 
 * File:   Ship.h
 * Author: Mariia Gregory
 *
 * Created on April 3, 2018, 12:11 PM
 * Purpose: Class representing a ship
 *!*/

#ifndef SHIP_H
#define SHIP_H

#include "Board.h"
//#include <utility> /*! pair<T1, T2>, x,y coordinates on a grid*/
using namespace std;

class Ship { /// Class representing a single ship
    private:
        short length; // ship length in cells
        short x,y; // starting X,Y coordinates
        bool vert; // if 1 - vertical, if 0 - horizontal 
        bool *hit; // hit[length] - array of true/false (all false initially)
        bool sunk; // if all hit[] elements are true, sunk = true
    public:
        Ship(short); // Constructor accepts a length as an argument 
        void setLen(short);
        class NegLen {}; /// Error-detecting class. An instance created when <=0 length is provided as an argument
        void setX(short x) { this->x = x; };
        void setY(short y) { this->y = y; };
        short getLen() const { return length; }
        short getX() const { return x; }
        short getY() const { return y; }
        bool isVert() const { return vert; }
        bool isHit(short,short) const;
        bool isSunk() const;
        ~Ship();
};

#endif /* SHIP_H */