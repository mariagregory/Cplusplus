/*
 *            PROGRAMMER: Mariia Gregory
 *         PROBLEM TITLE: Final Project - 1
 *    PROBLEM DEFINITION: Write a program that prompts the user for the name of a file to output as a binary file 
 							that will hold a 2D array of the FLOAT data type.
						  Have the user specify the number of rows and the number of columns for the 2D array.
						  Have the user enter the values for each row and column element in the 2D array.
						  Write the 2D array out as a BINARY file. You will want the file format to be as follows: 
						  	the first two values stored in the file is the number of rows and the number of columns. 
						  	The remaining data is to be the 2D array being stored as floating point values.
 *                  DATE: 5/31/16
 *     SYSTEM - HARDWARE: Windows
 *            - SOFTWARE: Dev-Cpp
 *         Input Devices: Keyboard
 *        Output Devices: Terminal screen, Binary file
 * 
 *  PROGRAM ASSUMPTIONS:  1. variables for:
 							a. "filename" as string to store a name of output file, input by user.
							b. "file" as fstream object for output data to
							c. rows and cols as integers to store number of rows and columns in 2D-array, input by user 
								Must be greater than 0. 
							d. **arr2Dptr as pointer to 2D-array of floats, or a pointer to a pointer to an array of floats.
								This 2D-array stores rows*cols elements, entered by user.					
						 2. Functions: 
							a. setSize(int&, int&) to take and validate user's input for rows and cols.
							b. getValue() to take and validate user's input for each array's element.
							c. displayArray(float**, int, int) to display the array's contents on the screen.
						3. Process:
							a. User is asked for number of rows, then for number of columns. Each input is validated.
							   If a value entered is rejected (contains non-digit characters, is negative or too high),
							   user as allowed to re-enter a value.
							b. a portion of memory required for storing rows*cols floating point values is allocated,
							 	and this memory is assigned to our pointer to 2D-array.
							c. While program steps through all array's elements, user is asked to enter values for each element
								of our 2D-array. Each input is validated. If a value entered is rejected (contains anything 
								other than digit, dot or dash), user is allowed to re-enter a value.
							d. When all values are taken from user's input, all array's content is displayed on the screen 
								for user's (and our) convenience.
							e. User is asked for the name of a binary file ("filename") to write the data to. If the file 
								with this name is successfully opened in a binary mode, the data is written to it in the
								folliwing order: the first two values are number of rows and columns respectively. 
						  		The remaining data is the 2D array's elements stored as floating point values.
*/

#include <iostream>
#include <fstream>
#include <cstdlib> // for atof() and atoi() functions
#include <cctype> // for toupper() and isdigit() functions
#include <iomanip> // for setw(), setprecision(), left and right output manipulators
using namespace std;

// Function prototypes
void setSize(int&, int&); // to take and validate user's input for number of rows and columns
float getValue(); // to take and validate user's input for each array's element
void displayArray(float**, int, int); // to display the array's contents on the screen

int main() {
	string filename; // declare a variable for filename as string to store a name of output file
	fstream file; // declare "file" as fstream object for output data to
	int rows, cols; // declare variables for rows and cols to store number of rows and columns in 2D-array
	float **arr2Dptr = nullptr; // declare a pointer to 2D-array and initialize it with nullptr
	// display a greeting message
	cout << "Hello!\nThis program creates a 2D-array of floating point numbers\nand saves its contents in a binary file.\n"; 
	// Prompt user for number of rows and columns and verify input by calling setSize function
	setSize(rows,cols);
	// allocate a portion of memory for a pointer to array with "rows" elements and assign it to our 2D-array
	arr2Dptr = new float*[rows];
	// initialize all array elements with another array, i.e., create 2D array
	for (int row = 0; row<rows;row++) { // step through "rows" elements ...
		*(arr2Dptr+row) = new float[cols]; // ...and assign each element another array, with "cols" elements
		for (int col = 0; col<cols;col++) { // withing each row, step through each of "cols" elements
			// Prompt user for values for each 2D-array's element
			cout << "Enter the value for row " << row << ", column " << col << ": ";
			// call getvalue function to get and validate user's input, then store its result as floating point value of the array element
			*(*(arr2Dptr+row)+col) = getValue();
		}
	}
	cout << "Thank you.\n\n";
	// display array's elements as a table by calling displayArray function
	cout << "Here is the contents of your 2D array: \n\n";
	displayArray(arr2Dptr, rows, cols);
	// Prompt user for the name of a binary file to write the data to 
	cout << "Enter the file name to write this array to: ";
	cin >> filename; // store user's input in filename variable
	file.open(filename.c_str(), ios::binary | ios::out); // open the file in binary mode for output
	if(file) { // if the file is successfully opened
		cout << "Writing data to " << filename << "....\n"; // display the message that data is to be written to this file
		file.write( reinterpret_cast<char*>(&rows), sizeof(int)); // write a number representing # of rows
		file.write( reinterpret_cast<char*>(&cols), sizeof(int)); // write a number representing # of cols
		for (int row=0; row<rows; row++) { // step through each of "rows" elements
			for (int col=0; col<cols; col++) { // withing each row, step through each of "cols" elements
				// write the following float-sized value to the binary file assigning it to each 2D-array element
				file.write(reinterpret_cast<const char *>(*(arr2Dptr+row)+col), sizeof(float));
			} // repeat for each col inside a row
		} // repeat for each row
		// Inform the user that data is successfully written to the file
		cout << "The data was successfully written to " << filename << ".\n";
		file.close(); // after we're done with the file, close it
	} else cout << "Error opening the file!\n";	// if the file failed to open, inform user about it

	//free the portions of memory taken by pointers with dynamic memory allocation
	delete arr2Dptr; arr2Dptr = nullptr;
	cout << "\nThat\'s it!\n\tBest wishes,\n\tMariia Gregory\n";
}

/* Definition of setSize function. It consists of two do-while loops. One for "rows" and one for "cols". 
	First, it takes user's input for "rows". If anything other than a digit was entered, the input is rejected, and user is asked
	to try again. Otherwise, it verifies that "rows" value is withing a range from 1 to 1000, so to make sure there is at least one element
	in the array, and array is not too large. 
	The same is repeated for "cols", but the "cols"'largest value is 100, so to make sure that the total # of elements 
	does not exceed 1000, so all array's element will not take more than 4 Mb of memory, and the program will not crash. */
void setSize(int &rows, int &cols) {
	string input; // declare a variable for input as string to store user's initial input
	bool validInput; // declare variable for validInput as boolean, which will indicate whether the input is valid or not
	
	do { // the 1st loop is for taking and validating user's input for "rows" 
		validInput = true; // set/reset validInput to true
		cout << "Enter number of rows in your 2D-array: "; // prompt user for # of rows
		cin >> input; // store user's input in input string variable
		for(char sym : input) { // step through all characters of user's input
			if (!isdigit(sym)) { // if at least one non-digit character is found
				cout << "Invalid number! Try again.\n"; // display error message
				validInput = false; // set validInput to false
				break; // immediately terminate the foor-loop
			}
		}  
		if(validInput) { // user's input is valid (all digits were entered), 
			rows = atoi(input.c_str()); // store user's input as "rows" after converting it to integer type
			if(rows<0)  { // if "rows" value is negative, display error message
				cout << "No no no! It has to be at least one element in an array.\nTry another number.\n";
				validInput = false; // set validInput to false
			} else if(rows>100) { // otherwise, if it's bigger than 1000,
				cout << "It's too much! Try smaller number.\n"; // display error message
				validInput = false; // set validInput to false
			}
		}
	} while (!validInput); // if validInput was changed to false, start over from do {...
	
	do { // the 2nd do-while loop is identical, but it's for taking and validating user's input for "cols" 
		validInput = true; // set/reset validInput to true
		cout << "Enter number of columns in your 2D-array: "; // prompt user for # of columns
		cin >> input; // store user's input in input string variable
		for(char sym : input) { // step through all characters of user's input
			if (!isdigit(sym)) { // if the character is not a digit
				cout << "Invalid number! Try again.\n"; // display error message
				validInput = false; // set validInput to false
				break; // immediately stop this for-loop
		 	}	
		}
		if(validInput) { // If the input was successfully validated so far,
			cols = atoi(input.c_str()); // store user's input as "cols" after converting it to integer type
			if(cols<0)  { // if # of cols is negative, display error message...
				cout << "No no no! It has to be at least one element in an array.\nTry another number.\n";
				validInput = false; // ... and set validInput to false
			} else if (cols > 100) { // otherwise, if it's bigger than 100,
				cout << "It's too much! Try smaller number.\n"; // display error message
				validInput = false; // set validInput to false
			}
		}
	} while (!validInput); // if validInput was changed to false, start over from the 2nd do {...
}

/* Definition of getValue function. It has no arguments. function validates user's input for each of array's elements.
	If anything other than a digit, dot, or dash (minus) was entered, the input is rejected, and user is asked to try again. 
	Otherwise, inout is converted to "float" data type and is stored in array's element variable.*/
float getValue() {
	float input; // declare a variable for "input" as float, to store the validated user's input for array's element
	string temp; // declare a variable for "temp" as string to store user's initial input (not yet validated)
	bool validInput; // declare variable for validInput as boolean, which will indicate whether the input is valid or not
	do { 
		validInput = true; // set/reset validInput to true
		cin >> temp; // store user's input in "temp" string variable
		for (char symbol : temp) { // step through all characters of user's "temp" input
			if (!isdigit(symbol) && symbol != '.' && symbol != '-') { // if the character is neither a digit nor '.' nor '-',
				cout << "This is not a number!\nEnter another value: "; // display error message
				validInput = false; // set validInput to false
				break; // immediately stop this for-loop
			}
		}
	} while(!validInput); // if validInput was changed to false, start over from do {...
	input = (float)atof(temp.c_str()); // store user's input as "input" after converting it to "float" type ("atof()" returns "double")
	return input; // return "input", then it will be assigned to our array element's value
}

/* Definition of displayArray function. It accepts our 2D-array (a pointer) and its size in rows and cols as arguments.
	The array's contents is output as a table, in presentable form. The first horizontal line is column headers,
	the first vertical line is row headers. The contents is displayed with 2 digits of decimal precision. */
void displayArray(float **arr2Dptr, int rows, int cols) {
	// skip 9 spaces, so the 1st column header is placed exactly above the 1st element
	cout << setw(14) << right << "Col 0";
	// complete the first line by displaying other column headers on equal distance
	for(int col=1; col<cols; col++) { // step through each of "cols" elements
		cout << setw(6) << "Col " << col; // display a current column header
	} // repeat for each column
	cout << "\n"; // go to the next line
	// display row headers and all values in a row on equal distance, with 2 digits of decimal precision 
	for(int row=0; row<rows; row++) { // step through each of "rows" elements
		cout << "Row " << setw(3) << left << row << ": " << fixed << setprecision(2); // display the row header
		for(int col=0; col<cols; col++) { // within this row, step through each of "cols" elements
			// display elements in a row on same distance, with 2 digits of decimal precision
			cout << left << setw(7) << *(*(arr2Dptr+row)+col); 
		} // repeat for each column
		cout << "\n"; // go to the next line
	} // repeat for each row
	cout << "\n"; // go to the next line
}
