/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on April 3, 2018, 10:37 AM
 * Purpose: Battleship game with the use of structures, dynamic arrays, strings, chars, and binary files
 */

#include <cstdlib>
#include <iostream>
#include <iomanip> // setw()
#include <ctime> // rand(), srand()
#include <cctype> // isdigit(), isalpha(), toupper()
#include <cstring> // strlen()
#include <sstream> // to handle crazy-user's input
#include <string> // to work with stringstream object
#include <utility> // pair<T1, T2>
#include "Board.h"
#include "Ship.h"
#include "Player.h"
using namespace std;

// Function prototypes
void setGame(Board &);
void shwGrid(const Board &);
void setCrds(Ship &, Board &);
bool collisn(Ship &, short, Board &); // check if a generated ship location overlaps with any other ships
pair<short,short> takeGuess(const Board &);
pair<short,short> parseGuess(pair<char, char> &);
void fire(const Board &, pair<short,short> &, bool &);
bool isHit(Ship &, const pair<short,short> &);
bool isSunk(const Ship &);
bool isOver(Ship*, short);

// Execution starts here
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    Board board;
//    Player user = {"User",0,0,0};//, comp("Computer",0,0,0);
    pair<short,short> guess;
    short guesses=0;
//    char again; 
    bool userWon=false;//, compWon=false;
  
    setGame(board); // define grid, allocate memory for ships
    shwGrid(board); //display grid (with ships, for test), 
    
    do {
        guess=takeGuess(board);//  ask user for coordinates, validate input

//        cout<<"User entered "<<guess.first<<guess.second<<endl;
        fire(board, guess, userWon); //check if coordinates match any of ship's. 
        guesses++;
    //    If hit, mark by setting hit[i] = true, and display 'X' on a grid
    //       check if other spots on the ship are hit. If yes, flag this ship as sunk and increment numSunk
    //    if sunk, check if all other ships are sunk. If yes - game over!
        shwGrid(board);
    //   !!! and make sure user doesn't fire on the same cell twice!!!!!
    } while(!userWon);
//  ...
    cout<<"You won with "<<guesses<<" guesses."<<endl;
//    release memory
    for(short i=0; i<board.size; i++) {
        delete [] board.grid[i];
    } delete [] board.grid;

    for(short i=0; i<board.numShps; i++) {
        delete [] board.ships[i].hit;
    } delete [] board.ships;
    
    return 0;
}

void setGame(Board &board) {
    //    static short round=1;
    short boardSz = 7, shipSz = 3, nuShips = 3;
    board.size = boardSz;
    board.numShps = nuShips;
    board.numSunk = 0;
    board.ships = new Ship[nuShips];
    
//    allocate memory for grid
    board.grid = new char*[boardSz]; 
    for(short i=0; i<boardSz; i++) {
        board.grid[i] = new char[boardSz]; // will contain marks for ships, hit or miss
        for(short j=0; j<boardSz; j++) board.grid[i][j]=' ';
    }
 
    for(short i=0; i<nuShips; i++) {
        board.ships[i].length = shipSz;
        board.ships[i].hit = new bool[shipSz]{false};
        board.ships[i].sunk = false;
        board.ships[i].vert = rand()%2 ? false : true; // Direction: 1 - vertical, 0 - horizontal
        setCrds(board.ships[i], board); // generate starting x,y coordinates and allocate others based on direction and length
    }
}

void setCrds(Ship &ship, Board &board) {
    static short i=1;
//    cout<<"Setting ship "<<i<<" coordinates..."<<endl;
    ship.x = rand() % board.size; // x - column (horizonal movement)
    ship.y = rand() % board.size; // y - row (vertical movement)
//    cout<<"\tInitially, x="<<ship.x<<", y="<<ship.y<<endl;
    
    // the first ship cannot have collisions with any others, so don't even bother to check
    if(ship.vert) {
        if( (ship.y+ship.length) > board.size) {
            ship.y = board.size - ship.length;
//            cout<<"\tAdjusted y="<<ship.y<<endl;
//          if the generated location collides with another ship, call the function anew
        }
        if(i>1 && collisn(ship,i-1,board)) setCrds(ship, board);
        else{
            for(short y=ship.y; y<ship.y+ship.length; y++)
                board.grid[y][ship.x]='0'+i; 
            i++;
        }
       
    } else {
        if( (ship.x+ship.length) > board.size) {
            ship.x = board.size - ship.length;
//            cout<<"\tAdjusted x="<<ship.x<<endl;
            //          if the generated location collides with another ship, call the function anew
        }
        if(i>1 && collisn(ship,i-1,board)) setCrds(ship, board);
        else{
            for(short x=ship.x; x<ship.x+ship.length; x++)
                board.grid[ship.y][x]='0'+i;
             i++;
        }
    }
//    i++; // For unknown reason...
}

bool collisn(Ship &ship, short index, Board &board) {
//    cout<<"\tcheck if a generated ship location overlaps with any other ships\n";
    if(ship.vert) { // in a vertical orientation, keep x constant and check all y values
//        cout<<"\tvertical\n";
        for(short i=0; i<index; i++) {
            if(board.ships[i].vert) { // compare vertical to horizontal vertical
                if(ship.x==board.ships[i].x) {
                    for(short y=board.ships[i].y; y<board.ships[i].y+board.ships[i].length; y++) {
                        if(y>=ship.y && y<=ship.y+ship.length) {
//                            cout<<"Collision with ship "<<i+1<<" on "<<ship.x<<y<<"!";
                            return true;
                        }
                    }
                }    
            } else { // if compare vertical ship to horizontal
                for(short y=ship.y; y<ship.y+ship.length; y++) {
                     if(y==board.ships[i].y) {
                         for(short x=board.ships[i].x; x<board.ships[i].x+board.ships[i].length; x++) {
                             if(ship.x==x) {
//                                 cout<<"Collision with ship "<<i+1<<" on "<<x<<y<<"!";
                                 return true;
                             }
                         }
                     }
                }
            }
        }
    } else { // if an argument ship is horizontal
//        cout<<"\thorizontal\n";
        for(short i=0; i<index; i++) {
            if(board.ships[i].vert) { // compare horizontal with vertical
                for(short y=board.ships[i].y; y<board.ships[i].y+board.ships[i].length; y++) {
                    if(ship.y==y) {
                        for(short x=ship.x; x<ship.x+ship.length; x++) {
                            if(x==board.ships[i].x) {
//                                cout<<"Collision with ship "<<i+1<<" on "<<x<<y<<"!";
                                return true;
                            }
                        }
                    }
                }
            }else{// compare horizontal with horizontal; both have const y, but
                if(ship.y==board.ships[i].y) {
                    for(short x=ship.x; x<ship.x+ship.length; x++) {
                        if(ship.x>=board.ships[i].x && ship.x<=board.ships[i].x+board.ships[i].length) {
//                            cout<<"Collision with ship "<<i+1<<" on "<<x<<ship.y<<"!";
                            return true;
                        }
                    }
                }
            } 
        }
    }
    return false;
}

void shwGrid(const Board &board) {
//    cout<<"Show grid"<<endl;
    char col, row;
    cout<<setw(4)<<"";
    for(int i=0; i<board.size; i++) {
        col='A'+i;
        cout<<"  "<<col<<" ";
    } cout<<endl;
    for(int i=0; i<board.size; i++) {
        cout<<setw(4)<<"";
        for(int j=0; j<board.size; j++) {
            cout<<"+---";
        } 
        cout<<"+\n";
        row='0'+i;
        cout<<" "<<row<<"  ";
        for(int j=0; j<board.size; j++) {
            cout<<"| "<<board.grid[i][j]<<" ";
        }
        cout<<"|\n";
    }
    cout<<setw(4)<<"";
    for(int j=0; j<board.size; j++) cout<<"+---"; cout<<"+\n";
}

pair<short,short> takeGuess(const Board &board) {
    pair<char,char> guess;
    string test="";
    if(!test.empty()) test.clear();
    cout<<"Type a coordinate (letter and number): ";
    getline(cin,test);
//    cout<<"\tYou entered "<<test.length()<<" chars.\n";
    if(test.length()!=2) {
        cout<<"\tError!\nNo 2 chars were entered\nTry again: ";
        takeGuess(board);
    } else {
        test[0]=toupper(test[0]);
        if(!isalpha(test[0]) || test[0]<'A' || test[0]>('A'+board.size-1) || !isdigit(test[1]) || test[1]<0 || test[1]>('0'+board.size-1)) {
            cout<<"\tError!\n";
            cout<<"\tEnter a coordinate in a format <A-"<<static_cast<char>('A'+board.size-1)<<"><0-"<<board.size-1<<": ";
            takeGuess(board);
        }
    }
//    WHAT THE HECK???? - this is repeated 2 times if user first enters an illegal input
//    as if i call the function again.... but I don't!
//    static short errCount = 1;
//    cout<<errCount<<" time: \n";
//    cout<<"\ttest[0] = "<<test[0]<<"\n\ttest[1]="<<test[1]<<endl;
//    errCount++;
    guess.first=test[0];
    guess.second=test[1];
//    cout<<"\tguess is "<<guess.first<<guess.second<<endl;
// ****** END OF ---- WHAT THE HECK
    return parseGuess(guess);
}

pair<short,short> parseGuess(pair<char,char> &guess) {
//    cout<<"Parsing guess...\n";
    short x, y;
    x = static_cast<short>(guess.first-65);
//    cout<<"\tParsed x="<<x<<endl;
    y = static_cast<short>(guess.second-48);
//    cout<<"\tParsed y="<<y<<endl;
    pair<short,short> result(x,y);
    return result;
}
//
void fire(const Board &board, pair<short,short> &guess, bool &won) {
    cout<<"Fire"<<endl;
    while(board.grid[guess.second][guess.first]=='X' || board.grid[guess.second][guess.first]=='/') {
        cout<<"You already fired at this spot.\nTry another shot.\n";
        guess=takeGuess(board);
    }
//    guess is y-coord, x-coord
    for(short i=0; i<board.numShps; i++) {
        if(isHit(board.ships[i], guess)) {
            cout<<"Ship "<<i+1<<" is hit!\n";
////          mark a ship\' part as hit\nOtherwise - as missed.
          board.grid[guess.second][guess.first]='X'; // on a grid, and also on a ship - set hit[] element to true
          if(isSunk(board.ships[i])) {
              cout<<"The ship "<<i+1<<" is sunk!\n";
              //  Then check if ALL ships are sunk
              if(isOver(board.ships, board.numShps)) {
                  cout<<"Game over!\n";
                  won=true;
                  return;
              }
          }
          return;
        }
    }
    board.grid[guess.second][guess.first]='/'; // on a grid, mark as missed
    cout<<"You missed.\n";
}
//
bool isHit(Ship &ship, const pair<short,short> &guess) {
    bool ishit=false;
    if(ship.vert && guess.first==ship.x) {
        if(guess.second>=ship.y && guess.second<=ship.y+ship.length) {
            ship.hit[guess.second-ship.y] = true;
            ishit=true;
        }
    }else if(!ship.vert && guess.second==ship.y) {
        if(guess.first>=ship.x && guess.first<=ship.x+ship.length) {
            ship.hit[guess.first-ship.x] = true;
            ishit=true;
        }
    }
//TEST:
    if(ishit) {
       cout<<"Hits: ";
        for(short i=0; i<ship.length; i++) {
            cout<<ship.hit[i]<<" ";
        } cout<<endl; 
    }
     
//  ***********  
    return ishit;
}

bool isSunk(const Ship &ship) {
    for(short i=0; i<ship.length; i++) {
        if(!ship.hit[i]) return false;
    }
    return true;
}

bool isOver(Ship *ships, short size) {
//    cout<<"Check if the game is over.\n";
    for(short i=0; i<size; i++) {
        if( !isSunk(ships[i]) ) return false; // if not all spots on all ships are  hit, the game continues
    }
    return true;
}
