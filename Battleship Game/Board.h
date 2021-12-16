/*!
 * File:   Board.h
 * Author: Mariia Gregory
 *
 * Created on April 3, 2018, 10:38 AM
 * Purpose: Class representing a board - a grid with ships
 **/

#ifndef BOARD_H
#define BOARD_H

#include <string>
#include "Ship.h"
using namespace std;

class Ship; // forward Ship class declaration

class Board { // Board class definition
    private:
        short size; /// Say, the size is 7, then the grid is 7 X 7 (rows X cols) */
        char **grid; //*! will be grid[size][size], datatype can be anything, to display ship marks, hit or miss flags
        short Nships; //*! # of ships
        short Nsunk; //*! # of ships sunk
        Ship **ships; //*! will be an array of pointers to Ship objects
    public:
        Board();
        void setCrds(Ship *, short);
        bool collisn(Ship *, short); // a ship of specified length, as an element of "ships" array
        short getSize() const { return size; } /// access a board size
        short gtNShps() const { return Nships; } /// access a # of ships
        short gtNSunk() const { return Nsunk; } /// access a # of sunk ships
        Ship *getShip(short index) const; /// access a particular ship on the grid
        void mrkHit(short, short); /// marks the spot as hit, with 'X'
        void mrkMiss(short, short); /// marks the spot as missed, with '-'
        void mrkSunk(const Ship*); /// marks all ship spots with 'S' and increments Nsunk
        bool isEmpty(short x, short y) { 
            return grid[y][x]==' '; 
        }
        string str() const;
        void display();
        void reveal(); /*! ****** TEST for ship allocations ***** Called in testing mode ****/ 
        ~Board();
};
#endif /* BOARD_H */
