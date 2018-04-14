
/* 
 * File:   Ship.h
 * Author: rcc
 *
 * Created on April 3, 2018, 12:11 PM
 */

#ifndef SHIP_H
#define SHIP_H

struct Ship {
    short length; // will be 3
    short x,y; // starting coordinate
    bool vert; // if 1 - vertical, if 0 - horizontal 
    bool *hit; // hit[length] - array of true/false (all false initially)
    bool sunk; // if all hit[] elements are true, sunk = true
};

#endif /* SHIP_H */

