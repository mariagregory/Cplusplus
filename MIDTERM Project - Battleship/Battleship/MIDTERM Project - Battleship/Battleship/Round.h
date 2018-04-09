/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Round.h
 * Author: admin
 *
 * Created on April 6, 2018, 3:11 PM
 */

#ifndef ROUND_H
#define ROUND_H

#include "Player.h"

struct Round {
    short count;
//    char *winner; // will be Player's name
    Player *winner;
    short guesses;
};

#endif /* ROUND_H */

