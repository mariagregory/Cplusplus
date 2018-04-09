/* 
 * File:   Ship.h
 * Author: rcc
 *
 * Created on April 3, 2018, 10:38 AM
 */


#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"

struct Board {
    short size; // let is be 7, then the grid will be 7 X 7 (rows X cols)
    char **grid; // will be grid[size][size], datatype can be anything, to display ship marks, hit or miss flags
    short numShps; // let is be 3
    Ship *ships; // will be ships[numShps]
    short numSunk; // a counter for sunk ships (the ones in which all elements of hits[] are set to '1' or whatever
};


#endif /* MODEL_H */

