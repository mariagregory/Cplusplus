/*
 * File:   Player.cpp
 * Author: Mariia Gregory
 *
 * Created on May 12, 2018, 9:44 PM
 * Purpose: Specification file for Player class
 */

#include "Player.h"
#include "Board.h"
#include <iostream> /// for feedback messages in fire())
#include <utility> /*! pair<T1, T2>, x,y coordinates on a grid. Used in fire() */
using namespace std;

/// Function prototype - used in fire()
pair<short,short> takeGuess(short);//, Player&, Player&); // defined in main.cpp

/*! Check if all ships are sunk. If yes, set "won" flag to true.*/
Player::Player(const char *name) : Profile(name) {   //cout<<"Creating a player\n";
    board = new Board();
    guesses = 0;
}
/*! Checks if user guess matches any of enemy ships locations. If yes, mark the spot as hit; otherwise, as missed. */
bool Player::fire(Player &rival, pair<short,short> &guess) {
    guesses++; // or addNgss(); // first, update 
    short x,y;
    do {
        guess = takeGuess(board->getSize());//, *this, rival);/*!  ask user for coordinates, validate input*/ 
        x = guess.first;
        y = guess.second;
        if(!(rival.board->isEmpty(x,y))) { // checks if there is any mark (hit/miss/sunk)
            cout<<"\tYou already fired at this spot.\n\tTry another one.\n";
        }
    }while(!(rival.board->isEmpty(x,y)));
///*!  board coordinates are [y][x] as row - vertical, col - horizontal*/
    for(short i=0; i<rival.board->gtNShps(); i++) {
        if(rival.board->getShip(i)->isHit(x,y)) { /*! mark on a grid, and also on a ship - set hit[] element to true*/
          rival.board->mrkHit(x,y);
          
          if(rival.board->getShip(i)->isSunk() ) { /*! Then check if the newly hit ship is gone*/
              rival.board->mrkSunk(rival.board->getShip(i)); /*! mark the whole ship as sunk*/
              rival.showBrd();
              cout<<"\tThe ship is sunk!\n";
              if(!(rival.NLeft())) { /*!  Then check if ALL ships are sunk*/
                  cout<<"\tAll ships are sunk, so ----- GAME OVER!\n";
                  Nwon++; // update # of games won
                  return true;
              } 
              else 
                  return false;
          } 
          else {
              rival.showBrd();
              cout<<"\tThe ship is hit!\n"; /*! if not sunk, then at least hit*/
              return false;
          }
        }
    }
    rival.board->mrkMiss(x,y); /*! on a grid, mark as missed*/
    rival.showBrd(); cout<<"\tMissed!\n"; /*! if not sunk, then at least hit*/
    return false;
}
/// Set a new board for a player. Called before each new round
void Player::reset() { 
    delete board;
    board = new Board();
    guesses = 0;
}
/// Destructor
Player::~Player() {
    delete board;
    board = NULL; 
} 