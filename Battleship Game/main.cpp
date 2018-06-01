/** File:   main.cpp
  *Author: Mariia Gregory
 
  *Created on May 3, 2018, 10:37 AM
  *Purpose: Battleship game with the use of structures, dynamic arrays, strings, chars, and binary files
  *   Structures: 
    *    Player: 2 instances, one for each player
   *     Board: one for each player, for each round
   *     Ship: some # of ships of specified length for each board
   *  File stream objects:
    *     history file - results of each round: winner, # of guesses to win
    *     profile - info on each player: how many games played and how many won 
 */

#include <cstdlib>
#include <iostream> /*! input/output */
#include <iomanip> /*! setw()*/
#include <ctime> /*! rand(), srand()*/
#include <cctype> /*! isdigit(), isalpha(), toupper()*/
#include <cstring> /*! strlen()*/
#include <string> /*! to handle a crazy-user's input*/
#include <utility> /*! pair<T1, T2>, x,y coordinates on a grid*/
#include <fstream> /*! game history file and user profiles file*/
#include "Round.h" /*! a game round */
#include "Player.h" /*! a player */
#include "Board.h" /*! a grid with ships on it*/
#include "Ship.h" /*! a ship itself*/
#include "Streams.h"
using namespace std;

/*! Function prototypes */
pair<short,short> takeGuess(short);//, Player&, Player&); /*! Take x,y coordinates as a player's guess, like A1*/
/// ****** With 2 players as arguments, you can reveal all ships on the enemy's board by typing 0 as a guess
pair<short,short> parseGuess(pair<char, char> &); /*! Adjust a guess to a pair of numeric x,y values, as indices [row][col]*/
void readProf(fstream &); /// Read player profiles from a file and display them on the screen
void wave(); /*! display a "sea wave"*/
string takeName(short);

/*! Execution starts here */
int main(int argc, char** argv) {
    srand(static_cast<unsigned>(time(0)));
    char fName[12]="history.dat";
    char prfName[12] = "profile.dat";
    fstream almanac, profiles;
    almanac.open(fName, ios::out | ios::binary);
    
    /*! Player object, one for each player, will show # of games played and # of them won */ 
    Player **players = new Player*[2]; //array of 2 pointers to Player
    for(short i=0; i<2; i++) {
       string name = takeName(i);
       try { //  cout<<"Player "<<i+1<<endl;
           players[i] = new Player(name.c_str());
       /// When players are created, their boards are set and ships are allocated
       }
       catch(Ship::NegLen n) {
            cout << n.str();
            return -1;
        }
    }
    cout<<"\n       ~  ~  ~  Welcome to  ~  ~ \n~ ~ ~ ~     S E A  ~ ~  B A T T L E    ~ ~ ~ ~\n\n";
    cout<<endl<<players[0]->getName()<<" vs. "<<players[1]->getName()<<"!"<<endl;
    Round *round;
    short turn = 0; // if turn==0, 1st player's turn; if turn==1, it's 2nd player's turn
    char again;
    
    do { /*! repeat for each round*/
        round = new Round;// ++Nround;
        players[0]->addNpld(); 
        players[1]->addNpld(); /*! increment # of rounds player by each player*/
        cout<<"\nROUND "<<round->getNum()<<"!\n";
        cout<<players[0]->NShips()<<" ships are created for each player.\n";
        pair<short,short> guess; /*! an x,y coordinate on a grid, where ships are located*/
        bool gamOver = false; /*! whether there is a winner; if true, then the game is over*/
        
        do { /*! for each user guess*/
            wave();
            cout<<"Press Enter to ";
            if( !(players[0]->getNGss()) && !turn ) {
                cout<<"start a game.\n"; 
            } 
            else cout<<"continue.\n";
            
            cin.get(); /*! pause until user presses Enter    
            /*! announce a player's turn and show the enemy's board*/
            cout<<players[turn]->getName()<<"\'s turn:\n";
            cout<<"\tFiring on "<<players[!turn]->getName()<<"\'s board:\n";
            cout<<"\t("<<players[!turn]->NLeft()<<" ships left.)\n";
            players[!turn]->showBrd(); 
            cout<<"\n\t~~~~ Fire! ~~~~ "<<endl;
            gamOver = players[turn]->fire(*(players[!turn]), guess); /*!check if coordinates match any of enemy ships.  */ 
            if(!gamOver)
                turn = !turn; /// switch turns
        } while(!gamOver);
        
        round->setWnnr(players[turn]);
        round->setNgss(players[turn]->getNGss());
        cout<<endl<<"And the WINNER is "<<round->getWnnr()<<endl;
        cout<<"\t"<<round->getWnnr()<<" beat "<<players[!turn]->getName();
        cout<<" in the round "<<round->getNum()<<" with "<<round->getNgss()<<" guesses"<<endl;
        /*!  write data to a binary file*/
        try { 
            almanac << *round; 
        }
        catch(Profile::NoFile) { 
            cout<<"The output file cannot be opened.\n"; 
            return 1; 
        }
        delete round;
        
        cout<<"\nDo you want to play again?\nYes (Y) or No (any other key): ";
        cin>>again; //do { cin.get(again); }while(isspace(again)); /// skip accidental spaces until some char is entered
//        cin.ignore(); /*! skip the remaining char(s), if any, so nothing is left in a buffer if the game continues*/
        again = toupper(again);
        if(again=='Y') { 
            players[0]->reset(); 
            players[1]->reset(); 
        }
    }while(again=='Y');
    
    almanac.close();
    almanac.open(fName, ios::in | ios::binary); /// reopen the file, this time for input
    //almanac.seekg(0L, ios::beg); // if open in both input and output modes, the old content is NOT erased
    try { almanac >> *round; } // read rounds back from the binary file
    catch(Profile::NoFile error) {
        cout<<error.str();
        return -1;
    }
    almanac.close();
    
    profiles.open(prfName, ios::out | ios::binary);//profiles.open(prfName, ios::out | ios::in | ios::binary);
    /*! Write both players data (name, # of games player and won)*/
    try {
        profiles<<*(players[0]); 
        profiles<<*(players[1]);
        profiles.close();
    
        profiles.open(prfName, ios::in | ios::binary);//profiles.seekg(0L, ios::beg);  /// rewind the file
        /// if open for both input and output, but the file doesn't exist, it's NOT created.
        /// So I had to open it for output only, then close, and then reopen for input only
        readProf(profiles);
        profiles.close();
    } 
    catch(Profile::NoFile err) {
        cout<<err.str();
        return -1;
    } 
    catch(Profile::DivZero err) {
        cout<<err.str()<<endl;
        return -1;
    }
    delete [] players;
    cout<<"\n\nThat\'s it,\nBye.\n";
    return 0;
}

/*! Takes x,y coordinates as a player's guess*/
pair<short,short> takeGuess(short size) {//, Player &p1, Player &p2) { /// TESTING mode: uncomment parameters 2 and 3 (two Player instances) 
//With 2 players as arguments, you can reveal all ships on the enemy's board by typing 0 as a guess
    pair<char,char> guess;
    string test;
    bool valid = false;
    while(!valid) {
        cout<<"\tType a coordinate from A0 to ";
        cout<<static_cast<char>('A'+size-1)<<size-1<<": ";
        getline(cin,test);
        // ************** TESTS
        //if(test=="x") p1.reset();     // in TESTING mode
        //if(test=="0") p1.reveal(p2);  // in TESTING mode
        // ***************** end of TESTS
        if(test.length()!=2) {
            cout<<"\tError! No 2 chars were entered\n";
            continue;
        } 
        else {
            test[0]=toupper(test[0]);
            if(!isalpha(test[0]) || test[0]<'A' || test[0]>('A'+size-1)) {
                cout<<"\tError!\n"; 
                continue;
            } 
            else if(!isdigit(test[1]) || test[1]<'0' || test[1]>('0'+size-1)) {
                cout<<"\tError!\n"; 
                continue;
            }
        } 
        valid=true;
    }
    guess.first=test[0]; /*! a letter, x-coordinate = col #*/
    guess.second=test[1]; /*! a digit, y-coordinate = row #*/
    return parseGuess(guess); /*! convert to short-type numbers and return the result*/
}

/*! Adjust user's input so it is a pair of numeric x,y values, as indices for board.grid*/
pair<short,short> parseGuess(pair<char,char> &guess) {
    short x, y;
    x = static_cast<short>(guess.first-65); /*! since 'A' is 65 in ASCII table*/
    y = static_cast<short>(guess.second-48); /*! since '0' is 48 in ASCII table*/
    pair<short,short> result(x,y);
    return result;
}

/// Read player profiles from a file and display them on the screen
void readProf(fstream &file) {
/// Check for the file availability first	
    if(!file) { throw Profile::NoFile(); }
    /// Declare Profile instance and "rate" as float
    Profile prof;
    float rate; 
    ///*!    A table header*/
    cout<<"\n PLAYERS INFO"<<endl;
    cout<<"________________________________________________"<<endl;
    cout<<" "<<left<<setw(20)<<"Name";
    cout<<"| Games Won | Success Rate"<<endl;   
    cout<<"________________________________________________"<<endl;
    /*!    Reading players profiles*/  
    for(short i=0; i<2; i++) {
//        cout<<"Now on byte "<<file.tellp()<<endl; // *********** TEST
        file.read(reinterpret_cast<char*>(&prof), sizeof(prof));
        if(!file) { throw Profile::NoRead(); }
        cout<<" "<<left<<setw(20)<<prof.getName();
        cout<<"| "<<right<<setw(5)<<prof.won();
        cout<<setw(7)<<"| "<<setw(6);
        /*! calculate % of success as games won/played*/
        if(prof.played()) { /*! in case the function is called before any game is played...*/
            cout<<fixed<<setprecision(0)<<prof.getRate()<<"%"<<endl;
        } 
        else 
            cout<<"--\n";  
    } 
    cout<<"________________________________________________"<<endl;
    cout<<"Total games played: "<<prof.played()<<endl;
} /// When only 1 round was played, the rate is not calculated, for some reason

/// Take and validate user's input for a name
string takeName(short i) {
    // Prompt for player names, verify, and store in Player class
    string input; // temporary 2 strings to store player names
    cout<<"Player "<<i+1<<" name: ";
    getline(cin, input, '\n');
    if(!(input.length())) { 
       input = i ? "Mary" : "John"; 
       cout<<"It\'s OK, we\'ll call you " <<input;
    } 
    else {
       cout<<"Nice to meet you "<<input;
    } 
    cout<<endl;
    return input;
}

/*! show something looking like a sea wave*/
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