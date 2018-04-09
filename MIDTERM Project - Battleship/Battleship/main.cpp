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
#include <fstream>
#include "Board.h"
#include "Ship.h"
#include "Player.h"
//#include "Round.h"
using namespace std;

// Function prototypes
void setGame(Board &);
void shwGrid(const Board &);
void setCrds(Ship &, short, Board &);
bool collisn(Ship &, short, Board &); // check if a generated ship location overlaps with any other ships
pair<short,short> takeGuess(const Board &);
pair<short,short> parseGuess(pair<char, char> &);
void fire(Board &, pair<short,short> &, bool &);
bool isHit(Ship &, const pair<short,short> &);
bool isSunk(const Ship &);
void destroy(Board &);
void wResult(fstream &, short, char*, short);
void readHis(fstream &);
void setProf(Player*, short);

// Execution starts here
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
//    Player object, one for each player, will show # of games played and # of them won
    Player *players = new Player[2] { 
        { "John", 0,0 }, { "Mary", 0,0 }
    };
    fstream hisFile("history.dat", ios::out | ios::binary);
    if(!hisFile) { cout<<"Cannot open the history file..."; return -1; }
    
    short round = 0;
    char again;
    
    do {
        round++;
        players[0].played++; players[1].played++;
        cout<<"************************************"<<endl;
        cout<<players[0].name<<" vs. "<<players[1].name;
        cout<<"\nROUND "<<round<<"!\n";
        bool won=false;//, compWon=false;
        Board board[2];
        pair<short,short> guess;
        short guesses[2] {0};
        bool myTurn = false;;
      
        for(short i=0; i<2; i++) {
            cout<<players[i].name<<"\'s board\n";
            setGame(board[i]); // define grid, allocate memory for ships
            shwGrid(board[i]); //display grid (with ships, for test), 
        }   

        do {
            cout<<players[myTurn].name<<"\'s turn:\n";
            guess = takeGuess(board[myTurn]);//  ask user for coordinates, validate input
//            cout<<"\t"<<players[myTurn].name<<" entered "<<guess.first<<guess.second<<endl;
            fire(board[!myTurn], guess, won); //check if coordinates match any of ship's.   
            guesses[myTurn]++;
            
            cout<<"\tEnemy ("<<players[!myTurn].name<<") board:\n";
            shwGrid(board[!myTurn]);
            if(!won) {
                if(myTurn) myTurn=false;
                else myTurn=true;
            }
        } while(!won);
        cout<<endl<<"And the WINNER is "<<players[myTurn].name<<endl;
        players[myTurn].won++;
        cout<<"\t"<<players[myTurn].name<<" beat "<<players[!myTurn].name;
        cout<<" in the round "<<round<<" with "<<guesses[myTurn]<<" guesses"<<endl;
        //  write data to a binary file
        wResult(hisFile, round, players[myTurn].name, guesses[myTurn]);
                
        for(short i=0; i<2; i++) destroy(board[i]);
        cout<<"\nDo you want to play again?\nYes (Y) or No (any other key): ";
        cin.get(again); cin.ignore(100, '\n');
        again = toupper(again);
    }while(again=='Y');
    
    hisFile.close();
//    cout<<"Reading the history...\n";
    readHis(hisFile); 
    
    setProf(players, 2);
//    Write and read back players' profiles
    cout<<"\n\nThat\'s it,\nBye.\n";
    
    delete [] players;
      
    return 0;
}

void setGame(Board &board) {
    short boardSz = 3, shipSz = 2, nuShips = 1;
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
        setCrds(board.ships[i], i, board); // generate starting x,y coordinates and allocate others based on direction and length
    }
}

void setCrds(Ship &ship, short index, Board &board) {
    ship.x = rand() % board.size; // x - column (horizonal movement)
    ship.y = rand() % board.size; // y - row (vertical movement)
    
    // the first ship cannot have collisions with any others, so don't even bother to check
    if(ship.vert) {
        if( (ship.y+ship.length) > board.size) {
            ship.y = board.size - ship.length;
        } // if the generated location collides with another ship, call the function recursively
        if(index && collisn(ship,index,board)) setCrds(ship, index, board);
//        else{
////            for(short y=ship.y; y<ship.y+ship.length; y++)
////                board.grid[y][ship.x]='1'+index; 
//        }
       
    } else {
        if( (ship.x+ship.length) > board.size) {
            ship.x = board.size - ship.length;
        }
// if the generated location collides with another ship, call the function recursively
        if(index && collisn(ship,index,board)) setCrds(ship, index, board);
//        else{
//            for(short x=ship.x; x<ship.x+ship.length; x++)
//                board.grid[ship.y][x]='1'+index;
//        }
    }
}
//check if a generated ship location overlaps with any other ships
bool collisn(Ship &ship, short index, Board &board) {
    if(ship.vert) { // in a vertical orientation, keep x constant and check all y values
        for(short i=0; i<index; i++) {
            if(board.ships[i].vert) { // compare vertical to horizontal vertical
                if(ship.x==board.ships[i].x) {
                    for(short y=board.ships[i].y; y<board.ships[i].y+board.ships[i].length; y++) {
                        if(y>=ship.y && y<=ship.y+ship.length-1) {
//                            cout<<"\tCollision with ship "<<i+1<<" on "<<ship.x<<y<<"!";
                            return true;
                        }
                    }
                }    
            } else { // if compare vertical ship to horizontal
                for(short y=ship.y; y<ship.y+ship.length; y++) {
                     if(y==board.ships[i].y) {
                         for(short x=board.ships[i].x; x<board.ships[i].x+board.ships[i].length; x++) {
                             if(ship.x==x) {
//                                 cout<<"\tCollision with ship "<<i+1<<" on "<<x<<y<<"!";
                                 return true;
                             }
                         }
                     }
                }
            }
        }
    } else { // if an argument ship is horizontal
        for(short i=0; i<index; i++) {
            if(board.ships[i].vert) { // compare horizontal with vertical
                for(short y=board.ships[i].y; y<board.ships[i].y+board.ships[i].length; y++) {
                    if(ship.y==y) {
                        for(short x=ship.x; x<ship.x+ship.length; x++) {
                            if(x==board.ships[i].x) {
//                                cout<<"\tCollision with ship "<<i+1<<" on "<<x<<y<<"!";
                                return true;
                            }
                        }
                    }
                }
            }else{// compare horizontal with horizontal; both have const y, but
                if(ship.y==board.ships[i].y) {
                    for(short x=ship.x; x<ship.x+ship.length; x++) {
                        if(ship.x>=board.ships[i].x && ship.x<=board.ships[i].x+board.ships[i].length-1) {
//                            cout<<"\tCollision with ship "<<i+1<<" on "<<x<<ship.y<<"!";
                            return true;
                        }
                    }
                }
            } 
        }
    }
    return false;
}

//Display the board with ships
void shwGrid(const Board &board) {
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
// see WHAT THE HECK???
pair<short,short> takeGuess(const Board &board) {
    pair<char,char> guess;
    string test="";
    bool valid = false;
    while(!valid) {
        cout<<"\tType a coordinate from A0 to "<<static_cast<char>('A'+board.size-1)<<board.size-1<<": ";
        getline(cin,test);
        if(test.length()!=2) {
            cout<<"\tError! No 2 chars were entered\n";
            continue;
        } else {
            test[0]=toupper(test[0]);
            if(!isalpha(test[0]) || test[0]<'A' || test[0]>('A'+board.size-1)) {
                cout<<"\tError!\n"; continue;
            } else if(!isdigit(test[1]) || test[1]<0 || test[1]>('0'+board.size-1)) {
                cout<<"\tError!\n"; continue;
            }
        } valid=true;
    }
    guess.first=test[0];
    guess.second=test[1];
    return parseGuess(guess);
}

// Adjust user's input so it is a pair of numeric x,y values, as indices for board.grid
pair<short,short> parseGuess(pair<char,char> &guess) {
    short x, y;
    x = static_cast<short>(guess.first-65); // since 'A' is 65 in ASCII table
    y = static_cast<short>(guess.second-48); // since '0' is 48 in ASCII table
    pair<short,short> result(x,y);
    return result;
}

// Compares user guess with enemy ships locations
void fire(Board &board, pair<short,short> &guess, bool &won) {
    cout<<"Fire"<<endl;
    while(board.grid[guess.second][guess.first]=='X' || board.grid[guess.second][guess.first]=='-') {
        cout<<"You already fired at this spot.\nTry another shot.\n";
        guess=takeGuess(board);
    }
//  board coordinates are [y][x] as row - vertical, col - horizontal
    for(short i=0; i<board.numShps; i++) {
        if(isHit(board.ships[i], guess)) { // mark on a grid, and also on a ship - set hit[] element to true
          board.grid[guess.second][guess.first]='X'; 
          if(isSunk(board.ships[i])) {
              board.numSunk++;
              cout<<"The ship "<<i+1<<" is sunk!\n";
              //  Then check if ALL ships are sunk
              if(board.numSunk==board.numShps) {
                  cout<<"All ships are sunk, so ----- GAME OVER!\n";
                  won=true;
                  return;
              }
          } else cout<<"Ship "<<i+1<<" is hit!\n";
          return;
        }
    }
    board.grid[guess.second][guess.first]='-'; // on a grid, mark as missed
    cout<<"Missed.\n";
}
//
bool isHit(Ship &ship, const pair<short,short> &guess) {
    bool ishit=false;
    if(ship.vert && guess.first==ship.x) {
        if(guess.second>=ship.y && guess.second<=ship.y+ship.length-1) {
            ship.hit[guess.second-ship.y] = true; // mark as hit on a ship
            return true; //ishit=true;
        }
    }else if(!ship.vert && guess.second==ship.y) {
//        cout<<"Position "<<ship.vert<<", y="<<ship.y<<endl;
        if(guess.first>=ship.x && guess.first<=ship.x+ship.length-1) {
            ship.hit[guess.first-ship.x] = true; // mark as hit on a ship
            return true; //ishit=true;
        }
    }
    return false;
//TEST:
//    if(ishit) { cout<<"Hits: ";
//       for(short i=0; i<ship.length; i++) cout<<ship.hit[i]<<" "; cout<<endl; 
//    } 
//    return ishit;
}

bool isSunk(const Ship &ship) {
    for(short i=0; i<ship.length; i++) { if(!ship.hit[i]) return false; }
    return true;
}

void destroy(Board &board) {
    //    release memory
    for(short i=0; i<board.size; i++) {
        delete [] board.grid[i];
    } delete [] board.grid;

    for(short i=0; i<board.numShps; i++) {
        delete [] board.ships[i].hit;
    } delete [] board.ships;
}

void wResult(fstream &file, short round, char *name, short guesses) {
    file.write(reinterpret_cast<char*>(&round), sizeof(round));
    file.write(reinterpret_cast<char*>(name), sizeof(name));
    file.write(reinterpret_cast<char*>(&guesses), sizeof(guesses));
//    cout<<"The result of round "<<round<<" is written to a file.\n";
}

void readHis(fstream &file){
    file.open("history.dat", ios::in | ios::binary);
    if(!file) { cout<<"Cannot open the file\n"; return; }
//    cout<<"Reading the game history from the file.\n";
    cout<<endl;
    short round, guesses, nameLen = 4;
    char *name = new char[nameLen];
    cout<<"  GAME HISTORY"<<endl;
    cout<<"___________________________"<<endl;
    cout<<" Round | Winner | Guesses |"<<endl;
    cout<<"___________________________"<<endl;
    do{
        file.read(reinterpret_cast<char*>(&round), sizeof(round));
        cout<<" "<<setw(3)<<right<<round<<setw(3)<<" ";
        file.read(reinterpret_cast<char*>(name), sizeof(name));
        cout<<"| "<<setw(6)<<left<<name<<" ";
        file.read(reinterpret_cast<char*>(&guesses), sizeof(guesses));
        cout<<"| "<<setw(4)<<right<<guesses<<setw(5)<<" |"<<endl;
        if(!file) break; // otherwise, reads the last portion 2 times 
    }while(file); // reads the last portion 2 times 
    cout<<"___________________________"<<endl;
    delete [] name;
    file.close();
}

// Write user profiles (names, # of games played, and # of games won)
// Then read back
void setProf(Player *players, short size) {
    fstream profile("profile.dat", ios::out | ios::binary);
    if(!profile) { cout<<"Cannot create profiles..."; return; }
//    cout<<"Writing players' profiles...\n";
    for(short i=0; i<size; i++) {
        profile.write(reinterpret_cast<char*>(&players[i]), sizeof(players[i]));
    }
    profile.close();
//    cout<<"Reading players' profiles...\n";
    if(!profile) { cout<<"Cannot read the profiles..."; return; }
    cout<<endl;
    cout<<" PLAYERS INFO"<<endl;
    cout<<"__________________________________________________"<<endl;
    cout<<"  Name  | Games Played | Games Won | Success Rate |"<<endl;   
    cout<<"__________________________________________________"<<endl;
    
    for(short i=0; i<size; i++) {
        profile.read(reinterpret_cast<char*>(&players[i]), sizeof(players[i]));
        cout<<" "<<setw(7)<<left<<players[i].name;
        cout<<"| "<<right<<setw(6)<<players[i].played<<setw(7)<<"";
        cout<<"| "<<setw(5)<<players[i].won<<setw(5)<<"";
        cout<<"| "<<setw(7);
        if(players[i].played) {
            cout<<fixed<<setprecision(0)<<100*players[i].won/players[i].played;
        } else {cout<<"--"; }
        cout<<setw(7)<<"|"<<endl;
    }
    profile.close();
    
    cout<<"___________________________________________________"<<endl;
}
