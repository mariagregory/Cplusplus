/* 
 * File:   Player.h
 * Author: Maria Gregory
 *
 * Created on April 6, 2018, 3:07 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

const short nameSze=6;

struct Player {
    char name[nameSze];
    short played;
    short won;
};

#endif /* PLAYER_H */

