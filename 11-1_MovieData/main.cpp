/* 
 * File:   11.1 Movie Data
 * Author: Mariia Gregory
 *
 * Created on March 17, 2018, 9:54 PM
 * Purpose: Store information about 2 movies in structures. 
 *          Pass their members to a function that displays the information in a clearly formatted manner
 */
//System libraries
#include <cstdlib>
#include <iostream>
#include <iomanip> // for setw
#include <cctype> // for isdigit()
#include <cstring> // for strlen()
#include "Movie.h"
using namespace std;

//User libraries

// Global constants: math, science, conversion factors, 2D array columns

// Function prototypes
void setInfo(Movie *);
void shwInfo(Movie *);
short validNo(short, short);
void destroy(char *);

//execution starts here
int main(int argc, char** argv) {
    Movie film1, film2;
    
    setInfo(&film1);
    setInfo(&film2);
    
    cout<<"Here are movies' data:\n";
    shwInfo(&film1);
    shwInfo(&film2);
    
    destroy(film1.title);
    destroy(film1.directr);
    destroy(film2.title);
    destroy(film2.directr);
    return 0;
}

void setInfo(Movie *movie) {
    static short count=0;
    char title[100], dir[100];
    cout<<"Please provide info for a movie "<<count+1<<endl;
    cout<<"Title: ";
    cin.getline(title, sizeof(title));
    movie->title = new char[strlen(title)+1];
    strcpy(movie->title, title);
    movie->title[strlen(title)]='\0';
    
    cout<<"Director: ";
    cin.getline(dir, sizeof(dir));
    movie->directr = new char[strlen(dir)+1];
    strcpy(movie->directr, dir);
    movie->directr[strlen(dir)]='\0';

    cout<<"Year: ";
    movie->year = validNo(1895, 2018); 
//   https://headsup.boyslife.org/what-was-the-first-movie-ever-made/ - Arrival of a Train (1895)
    cout<<"Duration (in minutes): ";
    movie->minutes = validNo(1,32767); //https://en.wikipedia.org/wiki/List_of_longest_films
    cout<<"Thank you.\n\n";
    count++;
}

void shwInfo(Movie *film) {
    static short rows=0;
    if(!rows) {
        cout<<endl;
        cout<<left<<setw(3)<<"#"<<setw(30)<<"Title"<<setw(20)<<"Director";
        cout<<setw(7)<<"Year"<<setw(9)<<"Minutes"<<endl; // when it was "Minutes\n" the 1st movie row was shifted to the right
    }
    
    cout<<left<<setw(3)<<rows+1<<setw(30)<<film->title<<setw(20)<<film->directr;
    cout<<setw(7)<<film->year<<setw(9)<<film->minutes<<endl;

    rows++;
}

short validNo(short min, short max) { //short digits, 
    char *input = new char[100];
    short result;
//    bool valid{true};
	
//    do{ 
        cin.getline(input, 100);
	size_t len = strlen(input);
        for(size_t i=0; i<len; i++) {
            if(!isdigit(input[i])) {
                cout<<"Invalid input!\nNumbers only please: ";
				destroy(input);
                validNo(min, max);
            }
        }

            if(atoi(input)<min || atoi(input)>max) {
            cout<<"Invalid input!\nPlease enter the number in a range "<<min<<" - "<<max<<": ";
            destroy(input);
            validNo(min, max);
        }
//    } while(!valid);
//    cin.clear(); cin.ignore(100, '\n'); // because user may need to enter info for other movies using getline()
    result = static_cast<short>(atoi(input));
    return result;
}

void destroy(char cstrPtr[]) {
	delete [] cstrPtr;
	cstrPtr = nullptr;
}
