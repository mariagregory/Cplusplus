/* 
 * File:   main.cpp
 * Author: Mariia Gregory
 *
 * Created on April 3, 2018, 10:37 AM
 * Purpose: Battleship game with the use of structures, dynamic arrays, strings, chars, and binary files
    * Structures: 
       * Player: 2 instances, one for each player
       * Board: one for each player, for each round
       * Ship: some # of ships of specified length for each board
    * File stream objects:
        * history file - results of each round: winner, # of guesses to win
        * profile - info on each player: how many games played and how many won
 */

#include <cstdlib>
#include <iostream>
#include <iomanip> // setw()
#include <ctime> // rand(), srand()
#include <cctype> // isdigit(), isalpha(), toupper()
#include <cstring> // strlen()
#include <string> // to store a crazy-user's input
#include <utility> // pair<T1, T2>, x,y coordinates on a grid
#include <fstream> // game history file and user profiles file
#include "Board.h" // a grid with ships on it
#include "Ship.h" // a ship itself
#include "Player.h" 
using namespace std;

// Function prototypes
void setBrd(Board &); // define grid, allocate memory for ships
void setCrds(Ship &, short, Board &); // using random numbers, set ship direction (vertical or horizontal) and coordinates
bool collisn(Ship &, short, Board &); // check if a generated ship location overlaps with any other ships
void shwGrid(const Board &); // Display the board of the player, with ships marks (hit or miss, unharmed ships hidden)
pair<short,short> takeGuess(const Board &); // Take x,y coordinates as a player's guess, like A1
pair<short,short> parseGuess(pair<char, char> &); // Adjust a guess to a pair of numeric x,y values, as indices [row][col]
void fire(Board &, pair<short,short> &, bool &); // Check if user hit or missed enemy ships
bool isHit(Ship &, const pair<short,short> &); // compare user-guessed x,y coordinates with enemy ship locations
bool isSunk(const Ship &); // Check if all the ship's spots are hit. If yes, mark the ship as sunk
void mrkSunk(Board *, const Ship &);
void destroy(Board &); //    release memory allocated for pointers in the Board object: Ship, grid
void wResult(fstream &, short, char*, short); // Write the game results to a file: round #, winner, # of guesses
void readHis(fstream &); // Read the game history file. Display info as a table 
void setProf(Player*, short); // Write user profiles (names, # games played, # games won) to a binary file; read back
void wave(); // design thing: display a "sea wave"

// Execution starts here
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
//    Player object, one for each player, will show # of games played and # of them won
    fstream hisFile("history.dat", ios::out | ios::binary);
    if(!hisFile) { cout<<"Cannot open the history file..."; return -1; }
    
    Player *players = new Player[2] { 
        { "John", 0,0 }, { "Mary", 0,0 }
    };
    short round = 0;
    char again;
    
    cout<<" ~ ~ ~ Welcome to ~ ~ * * * S E A ~ ~ B A T T L E * * * ~ ~ ~\n\n";
    for(short i=0; i<2; i++) {
        char input[nameSze];
        cout<<"Player "<<i+1<<" name: ";
        cin.getline(input, nameSze-1); 
        if(!strlen(input)) cout<<"It\'s OK, we\'ll call you "<<players[i].name<<".\n";
        else {
            strcpy(players[i].name, input);
            cout<<"Nice to meet you "<<players[i].name<<"!\n";
        } 
    }
    cout<<endl<<players[0].name<<" vs. "<<players[1].name<<"!"<<endl;
    
    do { // for each round
        round++;
        players[0].played++; players[1].played++; // increment # of rounds player by each player
        cout<<"\n\nROUND "<<round<<"!\n";
        Board board[2]; // one for each player
        // define grid, allocate memory for ships
        for(short i=0; i<2; i++) setBrd(board[i]); 
        cout<<board[0].numShps<<" ships "<<board[0].ships[0].length<<" cells each are created for each player.\n";
        pair<short,short> guess; // an x,y coordinate on a grid, where ships are located
        short guesses[2] {0}; // # of guesses players madewave(); // display a "wave"
        bool won = false; // whether there is a winner; if true, then the game is over
        bool myTurn = false; // 0 - false, 1st player's turn; 1 - true - 2nd player's turn 
        
        do { // for each user guess
            wave();
            cout<<"Press Enter to ";
            if(guesses[myTurn]==0 && !myTurn) cout<<"start a game.\n"; else cout<<"continue.\n";
            cin.get(); // pause until user presses Enter    
            // announce a player's turn and show the enemy's board
            cout<<players[myTurn].name<<"\'s turn:\n"; 
            cout<<"\tEnemy ("<<players[!myTurn].name<<") board:\n";
            shwGrid(board[!myTurn]);
            guess = takeGuess(board[myTurn]);//  ask user for coordinates, validate input
            guesses[myTurn]++;
            fire(board[!myTurn], guess, won); //check if coordinates match any of enemy ships.   
            if(!won) { // switch turns
                if(myTurn) myTurn=false;
                else myTurn=true;
            }
        } while(!won);
        players[myTurn].won++;
        cout<<endl<<"And the WINNER is "<<players[myTurn].name<<endl;
        cout<<"\t"<<players[myTurn].name<<" beat "<<players[!myTurn].name;
        cout<<" in the round "<<round<<" with "<<guesses[myTurn]<<" guesses"<<endl;
        //  write data to a binary file
        wResult(hisFile, round, players[myTurn].name, guesses[myTurn]);
//         release memory for Board objects       
        for(short i=0; i<2; i++) destroy(board[i]);
        do { cout<<"\nDo you want to play again?\nYes (Y) or No (any other key): ";
            cin.get(again); cin.ignore(100, '\n'); // so the remaining char(s) are not stored as a guess if the game continues
        }while(isspace(again) && again=='\n'); // skip accidental white spaces and newlines
        again = toupper(again);
    }while(again=='Y');
    
    hisFile.close();
    readHis(hisFile); // Reopen and read the history file. Display info as a table 
    setProf(players, 2); // Write both players data (name, # of games player and won)

    cout<<"\n\nThat\'s it,\nBye.\n";
    delete [] players;
    return 0;
}
// specify board dimensions, # and size of ships, allocate memory for ships and set ship parameters
void setBrd(Board &board) {
    short boardSz = 7, shipSz = 3, nuShips = 5;
    board.size = boardSz; // will be boardSz*boardSz squared grid
    board.numShps = nuShips;
    board.numSunk = 0; // initially, no ships are sunk
    board.ships = new Ship[nuShips];//    allocate memory for ships
    board.grid = new char*[boardSz]; //    allocate memory for grid
    for(short i=0; i<boardSz; i++) {
        board.grid[i] = new char[boardSz]; // will contain marks for ships, hit or miss
        for(short j=0; j<boardSz; j++) board.grid[i][j]=' '; // When hit or miss, spaces will be replaced with 'X' or '-'
    }
    for(short i=0; i<nuShips; i++) {
        board.ships[i].length = shipSz; // how many cells ship occupies
        board.ships[i].hit = new bool[shipSz]{false}; // when hit, the ship 'cell' becomes true 
        board.ships[i].sunk = false; // when all ship spots are hit, becomes true
        board.ships[i].vert = rand()%2 ? false : true; // Direction: 1 - vertical, 0 - horizontal
        setCrds(board.ships[i], i, board); // generate starting x,y coordinates and allocate others based on direction and length
    }
}
// using random number generation, set ship direction (vertical or horizontal) and locations
void setCrds(Ship &ship, short index, Board &board) {
    ship.x = rand() % board.size; // x - column (horizonal movement)
    ship.y = rand() % board.size; // y - row (vertical movement)
    
    // the first ship cannot have collisions with any others, so don't even bother to check
    if(ship.vert) {
        if( (ship.y+ship.length) > board.size) {
            ship.y = board.size - ship.length;
        } // if the generated location collides with another ship, call the function recursively       
    } else {
        if( (ship.x+ship.length) > board.size) {
            ship.x = board.size - ship.length;
        }
// if the generated location collides with another ship, call the function recursively
    } if(index && collisn(ship,index,board)) setCrds(ship, index, board);
//    ************* TEST for ship allocations **********
//  	if(ship.vert) { for(short y=ship.y; y<ship.y+ship.length; y++) board.grid[y][ship.x]='1'+index;}
//		else { for(short x=ship.x; x<ship.x+ship.length; x++) board.grid[ship.y][x]='1'+index; }
}
//check if a generated ship location overlaps with any existing ships
bool collisn(Ship &ship, short index, Board &board) {
    if(ship.vert) { // in a vertical orientation, ship.x is constant
        for(short i=0; i<index; i++) {
            if(board.ships[i].vert) { // compare vertical to horizontal vertical
                if(ship.x==board.ships[i].x) {
                    for(short y=board.ships[i].y; y<board.ships[i].y+board.ships[i].length; y++) {
                        if(y>=ship.y && y<ship.y+ship.length) {
//                            cout<<"\tCollision with ship "<<i+1<<" on "<<ship.x<<y<<"!";
                            return true;
                        }
                    }
                }    
            } else { // if compare vertical ship to horizontal
                for(short y=ship.y; y<ship.y+ship.length; y++) {
                     if(y==board.ships[i].y) { // board.ships[i].y is constant for a horizontal ship
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
    } else { // if an argument ship is horizontal, so ship.y is constant
        for(short i=0; i<index; i++) {
            if(board.ships[i].vert) { // compare horizontal with vertical; in vertical, ship.x is constant
                for(short y=board.ships[i].y; y<board.ships[i].y+board.ships[i].length; y++) {
                    if(ship.y==y) { // if y-coordinate coincides at some point
                        for(short x=ship.x; x<ship.x+ship.length; x++) {
                            if(x==board.ships[i].x) {
//                                cout<<"\tCollision with ship "<<i+1<<" on "<<x<<y<<"!";
                                return true;
                            }
                        }
                    }
                }
            }else{// compare horizontal with horizontal; both have const y
                if(ship.y==board.ships[i].y) {
                	// check if x-coordinates coincide at some point
                    for(short x=ship.x; x<ship.x+ship.length; x++) {
                        if( x >= board.ships[i].x && x < board.ships[i].x+board.ships[i].length) {
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
//Display the board of the player, with ships marks (hit or miss, unharmed ships hidden)
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
            cout<<"| "<<board.grid[i][j]<<" "; // either ' ', or 'X', or '-'
        }
        cout<<"|\n";
    }
    cout<<setw(4)<<"";
    for(int j=0; j<board.size; j++) cout<<"+---"; cout<<"+\n";
}
// Takes x,y coordinates as a player's guess
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
            } else if(!isdigit(test[1]) || test[1]<'0' || test[1]>('0'+board.size-1)) {
                cout<<"\tError!\n"; continue;
            }
        } valid=true;
    }
    guess.first=test[0]; // a letter, x-coordinate = col #
    guess.second=test[1]; // a digit, y-coordinate = row #
    return parseGuess(guess); // convert to short-type numbers and return the result
}
// Adjust user's input so it is a pair of numeric x,y values, as indices for board.grid
pair<short,short> parseGuess(pair<char,char> &guess) {
    short x, y;
    x = static_cast<short>(guess.first-65); // since 'A' is 65 in ASCII table
    y = static_cast<short>(guess.second-48); // since '0' is 48 in ASCII table
    pair<short,short> result(x,y);
    return result;
}
// Checks if user guess matches any of enemy ships locations. If yes, mark the spot as hit; otherwise, as missed. 
// Check if all ship's spots are hit. If yes, mark the ship as sunk. 
// Check if all ships are sunk. If yes, set "won" flag to true.
void fire(Board &board, pair<short,short> &guess, bool &won) {
    cout<<"\tFire!"<<endl;
    while(board.grid[guess.second][guess.first]=='X' || board.grid[guess.second][guess.first]=='-' 
            || board.grid[guess.second][guess.first]=='S') {
        cout<<"\tYou already fired at this spot.\n\tTry another shot.\n";
        guess=takeGuess(board);
    }
//  board coordinates are [y][x] as row - vertical, col - horizontal
    for(short i=0; i<board.numShps; i++) {
        if(isHit(board.ships[i], guess)) { // mark on a grid, and also on a ship - set hit[] element to true
          board.grid[guess.second][guess.first]='X';
          if(isSunk(board.ships[i])) { // Then check if the newly hit ship is gone
              mrkSunk(&board, board.ships[i]); // mark the whole ship as sunk
              board.numSunk++; shwGrid(board);
              cout<<"\tThe ship is sunk!\n";
              if(board.numSunk==board.numShps) { //  Then check if ALL ships are sunk
                  cout<<"\tAll ships are sunk, so ----- GAME OVER!\n";
                  won=true;
                  return;
              }
          } else {
              shwGrid(board);
              cout<<"\tThe ship is hit!\n"; // if not sunk, then at least hit
          }
          return;
        }
    }
    board.grid[guess.second][guess.first]='-'; // on a grid, mark as missed
    shwGrid(board);
    cout<<"\tMissed.\n";
}
// compares user-specified x,y coordinates with any of the enemy ships locations
bool isHit(Ship &ship, const pair<short,short> &guess) {
    if(ship.vert && guess.first==ship.x) { // in vertically placed ships, x-coordinate is constant
        if(guess.second>=ship.y && guess.second<=ship.y+ship.length-1) {
            ship.hit[guess.second-ship.y] = true; // mark as hit on a ship
            return true; //ishit=true;
        }
    }else if(!ship.vert && guess.second==ship.y) {  // in horizontal ships, y-coordinate is constant
        if(guess.first>=ship.x && guess.first<=ship.x+ship.length-1) {
            ship.hit[guess.first-ship.x] = true; // mark as hit on a ship
            return true; //ishit=true;
        }
    } return false;
}
// Check if all the ship's spots are hit. If yes, the ship is sunk
bool isSunk(const Ship &ship) {
    for(short i=0; i<ship.length; i++) { if(!ship.hit[i]) return false; }
    return true;
}
void mrkSunk(Board *board, const Ship &ship) {
    board->grid[ship.y][ship.x]='S';
    for(short i=1; i<ship.length; i++) {
        if(ship.vert) {
            board->grid[ship.y+i][ship.x]='S';
        } else {
            board->grid[ship.y][ship.x+i]='S';
        }
    }
}
//    release memory allocated for pointers in the Board object 
void destroy(Board &board) {
    for(short i=0; i<board.size; i++) {
        delete [] board.grid[i];
    } delete [] board.grid; board.grid=nullptr;

    for(short i=0; i<board.numShps; i++) {
        delete [] board.ships[i].hit;
    } delete [] board.ships; board.ships=nullptr;
}
// Write the game results to a file
void wResult(fstream &file, short round, char *name, short guesses) {
    file.write(reinterpret_cast<char*>(&round), sizeof(round));
    file.write(reinterpret_cast<char*>(name), sizeof(name));
    file.write(reinterpret_cast<char*>(&guesses), sizeof(guesses));
}
// Reading the game history from the file.
void readHis(fstream &file){
    file.open("history.dat", ios::in | ios::binary);
    if(!file) { cout<<"Cannot open the file\n"; return; }
    
    short round, guesses;
    char *name = new char[nameSze]; //nameSze is declared in Player.h
    cout<<"\n  GAME HISTORY"<<endl;
    cout<<"____________________________"<<endl;
    cout<<" Round |   Winner  | Guesses "<<endl;
    cout<<"____________________________"<<endl;
    do {
        file.read(reinterpret_cast<char*>(&round), sizeof(round));
        if(file) {
            cout<<" "<<setw(3)<<right<<round<<setw(3)<<" ";
            file.read(reinterpret_cast<char*>(name), sizeof(name));
            cout<<"| "<<setw(10)<<left<<name;
            file.read(reinterpret_cast<char*>(&guesses), sizeof(guesses));
            cout<<"| "<<setw(4)<<right<<guesses<<endl;
        }
    }while(file);
    cout<<"____________________________"<<endl;
    delete [] name;
    file.close();
}
// Write user profiles (names, # of games played, and # of games won). Then read back
void setProf(Player *players, short size) {
    fstream profile("profile.dat", ios::out | ios::binary);
    if(!profile) { cout<<"Cannot create profiles..."; return; }
//    Writing players' profiles
    for(short i=0; i<size; i++)
        profile.write(reinterpret_cast<char*>(&players[i]), sizeof(players[i]));
    profile.close();
    
    Player *newPlrs = new Player[2]; // allocate new portion of memory for 2 new instances of Player
    char *name = new char[nameSze]; // allocate new pointer to set the size of c-string to read
//    Reopen the file, but this time in reading mode
    profile.open("profile.dat", ios::in | ios::binary);
    if(!profile) { cout<<"Cannot read the profiles..."; return; }
//    A table header
    cout<<"\n PLAYERS INFO"<<endl;
    cout<<"______________________________________________________"<<endl;
    cout<<" "<<left<<setw(nameSze/2)<<"Name"<<"| Games Played | Games Won | Success Rate"<<endl;   
    cout<<"______________________________________________________"<<endl;
//    Reading players profiles
    for(short i=0; i<size; i++) {
        profile.read(reinterpret_cast<char*>(&newPlrs[i]), sizeof(newPlrs[i]));
        cout<<" "<<left<<setw(nameSze/2)<<newPlrs[i].name;
        cout<<"| "<<right<<setw(6)<<newPlrs[i].played<<setw(7)<<"";
        cout<<"| "<<setw(5)<<newPlrs[i].won<<setw(5)<<"";
        cout<<"| "<<setw(7);
        if(newPlrs[i].played) { // calculate % of success as games won/played
            cout<<fixed<<setprecision(0)<<100*newPlrs[i].won/newPlrs[i].played<<"%"<<endl;
        } else {cout<<"--\n"; } // in case the function is called before any game is played...
    } cout<<"_____________________________________________________"<<endl;
    profile.close();
    delete [] newPlrs; newPlrs = nullptr; // release memory for 2 new Player instances
    delete [] name; // .... and a local dynamically created c-string
}
// show something looking like a sea wave
void wave() {
    for(short i=0; i<100; i++) {
        if(!(i%4)) cout<<"~";
        else cout<<" ";
    } cout<<endl;
    for(short i=0; i<100; i++) {
        if(!(i%3)) cout<<"~";
        else cout<<" ";
    } cout<<endl;
    for(short i=0; i<100; i++) {
        if(!(i%2)) cout<<"~";
        else cout<<" ";
    } cout<<endl;
}
