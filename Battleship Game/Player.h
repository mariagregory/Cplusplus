/* 
 * File:   Player.h
 * Author: Maria Gregory
 *
 * Created on April 6, 2018, 3:07 PM
 * Purpose: Definition of Player class, derived from Profile
 *!*/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream> // ************ testing
#include <cstring> // strcpy(,)
#include "Board.h"
#include "Profile.h"
using namespace std;

class Profile;/// Forward Profile and Board class declarations
class Board;

// Function prototype - used in Player::reset()
template<class T> T* alloc(const short &);

/// Class representing a player, derived from Profile
class Player : public Profile {
    private:
        Board *board;
        short guesses; // updates every time fire() is called
    public:
        Player(const char*);
        void showBrd() { board->display(); }
        bool fire(Player&, pair<short, short>&); // returns true if the game is over, false if 
        short getNGss() { return guesses; }
        short NShips() { return board->gtNShps(); }
        short NSunk() { return board->gtNSunk(); }
        short NLeft() { return NShips()-NSunk(); }
        void reset();
        // ***********TEST ********************
//        void reveal(Player &rival) { rival.board->reveal(); } 
        // ***********end of TEST ********************
        ~Player(); /// destructor
};
#endif /* PROFILE_H */
