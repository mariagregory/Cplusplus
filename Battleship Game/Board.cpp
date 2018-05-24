/*!
 * File:   Board.h
 * Author: Mariia Gregory
 *
 * Created on April 3, 2018, 10:38 AM
 * Purpose: Specification file for Board class
 **/

#include "Board.h" /*! a ship itself*/
#include "Ship.h"
#include <ctime> // for ship length generation
#include <cstdlib> // so rand() is recognized
#include <iomanip> // setw() in display()
#include <iostream> // setw(_) in display()
#include "Templates.h"
using namespace std;

Board::Board() {// : Round() {
    this->size = 6; // 2 for testing purposes  //else return; // error handler here!
    short shipL = 3; // 2 for test
    Nships = 3; // 1 for test// size*size / (3*(2+shipL));
    Nsunk = 0;
    ships = alloc<Ship*>(Nships);//new Ship*[Nships]; /// generate as many ship objects

    for(short i=0; i<Nships; i++) { // shipL = rand()%3+2; /// set a random ship length, from 2 to 4
        ships[i] = new Ship(shipL);
        setCrds(ships[i], i); // sending a pointer and a ship index
    }
    grid = alloc<char*>(size);//new char*[size]; /*!    allocate memory for grid*/
    for(short i=0; i<size; i++) {
        grid[i] = alloc<char>(size);//new char[size]; /*! will contain marks for ships, hit or miss*/
        for(short j=0; j<size; j++) *(*(grid+i)+j)=' ';//' '; /*! same as grid[i][j] */
    }/*! When hit or miss, spaces will be replaced with 'X' or '-' */
}
// Generating ship coordinates
void Board::setCrds(Ship *ship, short index) {
    short xCrd = rand()%size;
    short yCrd = rand()%size;
    if(ship->isVert()) {
        if( (yCrd+ship->getLen()) > size) { yCrd = size - ship->getLen(); } 
    } else {
        if( (xCrd+ship->getLen()) > size) { xCrd = size - ship->getLen(); }
    }
    ship->setX(xCrd); /*! x - column (horizonal movement)*/
    ship->setY(yCrd); /*! y - row (vertical movement)*/
    if(index && collisn(ship,index)) setCrds(ship, index);
    /*! if the generated location collides with another ship, call the function recursively */
     /*! the first ship cannot have collisions with any others, so don't even bother to check*/
}
/// check for collisions
bool Board::collisn(Ship *ship, short index) {
    short thisX, thisY, thisL; // this ship starting coordinates and length
    thisX = ship->getX();  thisY = ship->getY();  thisL = ship->getLen();//cout<<"This ship is #"<<index+1<<": thisX="<<thisX<<", thisY="<<thisY<<", thisL="<<thisL<<endl;
    short xi, yi, len_i; // other ship starting coordinates and length
    
    for(short i=0; i<index; i++) {
        xi = ships[i]->getX();  yi = ships[i]->getY();  len_i = ships[i]->getLen();//cout<<"Ship "<<i+1<<": xi="<<xi<<", yi="<<yi<<", len_i="<<len_i<<endl;
        if(ship->isVert()) { /*! in a vertical orientation, "thisX" is constant*/
            if(ships[i]->isVert()) { /*! compare vertical to vertical, so both "thisX" and "xi are constant */
                if(thisX >= xi-1 && thisX <= xi+1 ) {
                    for(short y = yi; y < yi+len_i; y++) {
                        if(y>= thisY-1 && y<= thisY+thisL+1 ) { /*! cout<<"Collision with ship "<<i+1<<" on "<<thisX<<y<<"!";*/
                            return true;
                        }
                    }
                }    
            } else { /*! if comparing vertical-to-horizontal -- ships[i].y is constant*/
                for(short y=thisY; y<thisY+thisL; y++) {
                    if(y>=yi-1 && y<=yi+1) { /*! ships[i].y is constant for a horizontal ship*/
                        for(short x=xi; x<xi+len_i; x++) {
                            if(thisX>=x-1 && thisX<=x+1) { /*!cout<<"Collision with ship "<<i+1<<" on "<<thisX<<y<<"!\n";*/
                                return true;
                            }
                        }
                    }
                }
            }
        } else { /*! if an argument ship is horizontal, so "thisY" is constant*/
            if(ships[i]->isVert()) { /*! compare horizontal-to-vertical; in vertical, "xi" is constant*/
                for(short y=yi; y<yi+len_i; y++) {
                    if(thisY>=y-1 && thisY<=y+1) { /*! if y-coordinate coincides at some point*/
                        for(short x=thisX; x<thisX+thisL; x++) {
                            if(x>=xi-1 && x<=xi+1) {  /*!cout<<"Collision with ship "<<i+1<<" on "<<x<<y<<"!\n";*/
                                return true;
                            }
                        }
                    }
                }
            }else{/*! compare horizontal-to-horizontal; both have const y*/
                if(thisY>=yi-1 && thisY<=yi+1) {
                    /*! check if x-coordinates coincide at some point*/
                    for(short x=thisX; x<thisX+thisL; x++) {
                        if( x >= xi-1 && x <= xi+len_i+1) { /*!cout<<"Collision with ship "<<i+1<<" on "<<x<<thisY<<"!\n";*/
                            return true;
                        }
                    }
                }
            } 
        } 
    } return false; //cout<<"No collisions\n"; 
}
void Board::mrkHit(short x, short y) { /// marks the spot as hit, with 'X'
    grid[y][x]='X';
}
void Board::mrkMiss(short x, short y) { /// marks the spot as missed, with '-'
    grid[y][x]='-';
}
void Board::mrkSunk(const Ship *ship) { /*! Check if all ship's spots are hit. If yes, mark the ship as sunk, with 'S'.*/
    Nsunk++; /// First, increment nSunk
    grid[ship->getY()][ship->getX()]='S';
    for(short i=1; i<ship->getLen(); i++) {
        if(ship->isVert()) {
            grid[ship->getY()+i][ship->getX()]='S';
        } else {
            grid[ship->getY()][ship->getX()+i]='S';
        }
    }
}
Ship *Board::getShip(short index) const { // Grab a particular ship by its index
    try {
        if (index<0 || index >= Nships) {
            throw "null ship";
        }
        return ships[index]; //don't grab ships from out of bounds
    } catch(string s) {
        cout<<"Cannot grab s null ship\n";
        return 0;
    }
}
/*! Display the board of the player, with ships marks (hit or miss, unharmed ships hidden)*/
void Board::display() {
    char col, row;
    cout<<setw(4)<<""; /// skip 4 spaces
    for(int i=0; i<size; i++) {
        col='A'+i; /// determine a column #
        cout<<"  "<<col<<" "; /// display the column header as a letter
    } cout<<endl;
    for(int i=0; i<size; i++) {
        cout<<setw(4)<<""; /// skip 4 spaces
        for(int j=0; j<size; j++) {
            cout<<"+---";
        } 
        cout<<"+\n";
        row='0'+i; /// determine a row #
        cout<<" "<<row<<"  "; /// display the row header as a letter
        for(int j=0; j<size; j++) {
            cout<<"| "<<grid[i][j]<<" "; /*! either ' ', or 'X', or '-'*/
        }
        cout<<"|\n";
    }
    cout<<setw(4)<<"";
    for(int j=0; j<size; j++) cout<<"+---"; cout<<"+\n";
}
/*!    ************* TEST for ship allocations ***********/
void Board::reveal() { // called by typing '0' as a guess in Player::fire() - takeGuess()
    for(short i=0; i<Nships; i++) {
        short x = ships[i]->getX(), y = ships[i]->getY(), len = ships[i]->getLen();
        if(ships[i]->isVert()) {
            for(short yi=y; yi<y+len; yi++) grid[yi][x]='1'+i;
        } else {
            for(short xi=x; xi<x+len; xi++) grid[y][xi]='1'+i;
        }
    } display();
} // ************* end of TEST
/*!    release memory allocated for pointers in the Board object */
Board::~Board() {
        for(short i=0; i<size; i++) {
            delete [] grid[i];
        } delete [] grid; grid=NULL;

        for(short i=0; i<Nships; i++) {
            delete ships[i]; // call a destructor, so it deletes a dynamic "hit" array
        } delete [] ships; ships=NULL;
}