/*
 *            PROGRAMMER: Mariia Gregory
 *         PROBLEM TITLE: Final Project - 3
 *    PROBLEM DEFINITION: Write a program to prompt the user for the name of a file to input as a binary file 
 							to read in the two dimensional array of float data type.
						  Output the contents of the two dimensional array to the screen..
 *                  DATE: 5/31/16
 *     SYSTEM - HARDWARE: Windows
 *            - SOFTWARE: Dev-Cpp
 *         Input Devices: Keyboard, Binary file
 *        Output Devices: Terminal screen
 * 
 *  PROGRAM ASSUMPTIONS:  1. variables for:
 							a. "filename" as string to store a name of output file, input by user.
							b. "file" as fstream object for inputting data from.
							c. rows and cols as integers to store number of rows and columns in 2D-array, read from input file. 
							d. **arr2Dptr as pointer to 2D-array of floats, or a pointer to a pointer to an array of floats.
								This 2D-array stores rows*cols elements, read from input file.					
						2. Process:
							a. User is asked for the name of a binary file ("filename") to read the data from.
							b. The input file is opened, and its contents is read from it in the folliwing order:
								the first two values are number of rows and columns respectively. 
						  		The remaining data is the 2D array's elements stored as floating point values.
						  	c. All data just read from the input file is displayed on the screen.
*/

#include <iostream>
#include <fstream>
#include <iomanip> // setprecision(), setw(), and left
using namespace std;

int main() {
	string filename; // declare a variable for filename as string to store a name of input file
	fstream file; // declare "file" as fstream object for output data to
	int rows, cols; // declare variables for rows and cols to store number of rows and columns in 2D-array
	float **arr2Dptr = nullptr; // declare a pointer to 2D-array and initialize it with nullptr
	// display a greeting message
	cout << "Hello!\nThis program reads in the 2D-array of float data type\n";
	cout << "from a binary file and outputs array's content on the screen\nin a table form.\n"; // display a greeting message
	// Prompt user for the name of a binary file to read the data from 
	cout << "Enter the file name to read data from: ";
	cin >> filename; // store user's input in filename variable
	file.open(filename.c_str(), ios::binary | ios::in);  // open the file in binary mode for input
	if(!file) { // if the file could not be opened
		cout << "Error opening the file!\n"; // display error message
		delete arr2Dptr; arr2Dptr = nullptr; // free the memory taken by dynamic pointers before exitting the program
		return -1; // return -1 and exit the program
	}
	file.read( reinterpret_cast<char*>(&rows), sizeof(int));  // read a number representing # of rows
	file.read( reinterpret_cast<char*>(&cols), sizeof(int)); // read a number representing # of cols
	// allocate a portion of memory for a pointer to array with "rows" elements and assign it to our 2D-array
	arr2Dptr = new float*[rows];
	// initialize all array elements with another array, i.e., create 2D array
	for (int row = 0; row<rows;row++) { // step through "rows" elements ...
		*(arr2Dptr+row) = new float[cols]; // ...and assign each element another array, with "cols" elements
		// read the following contents of a binary file and store it as our array's elements
		for (int col=0; col<cols; col++) { // withing each row, step through each of "cols" elements
			// read the following float-sized value to the binary file assigning it to each 2D-array element
			file.read(reinterpret_cast<char *>(*(arr2Dptr+row)+col), sizeof(float));
		}
	}
	file.close(); //After we're done with the input file, close it.
	
	// display array's elements as a table with rows and columns
	cout << "Here is the contents of \"" << filename << "\".\n";
	// First, display a message on how many rows and columns the 2D-array contains
	cout << "It contains " << rows << " rows and " << cols << " columns.\n\n";
	// display the top line with column numbers. First, display "Col 0" exactly above the 1st element 
	cout << setw(15) << right << "Col 0";
	// Then, on equal distance, display other column headers
	for(int col=1; col<cols; col++) {
		cout << setw(7) << "Col " << col;
	}
	cout << "\n"; // go to the next line
	for(int row=0; row<rows; row++) { // step through each of "rows" elements
										// display current row header 
		cout << "Row " << left << setw(2) << row << ": " << fixed << setprecision(2);
		for(int col=0; col<cols; col++) {
			// display elements in a row on same distance, with 2 digits of decimal precision
			cout << setw(8) << *(*(arr2Dptr+row)+col);
		}
		cout << "\n"; // go to the next line
	}
	// free the portions of memory taken by pointers with dynamic memory allocation
	delete arr2Dptr; arr2Dptr = nullptr;
	// Display a nice goodbye message
	cout << "\nThat\'s it!\n\tBest wishes,\n\tMariia Gregory\n";
}
