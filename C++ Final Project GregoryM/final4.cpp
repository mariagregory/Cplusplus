/*
 *            PROGRAMMER: Mariia Gregory
 *         PROBLEM TITLE: Final Project - 4
 *    PROBLEM DEFINITION: Write a program to prompt the user for the name of a file to input as a binary file 
 							to read in the two dimensional array of float data type.
 							and another filename for the name of the output file that will be outputting the 2D array 
							after it has been sorted.
							Load in the data from the original binary file and ask the user which column would he/she like to sort by.
							Sort the 2D array based on the column the user specifies, and output the sorted 2D array to the output file.
 *                  DATE: 5/31/16
 *     SYSTEM - HARDWARE: Windows
 *            - SOFTWARE: Dev-Cpp
 *         Input Devices: Keyboard, Binary files
 *        Output Devices: Terminal screen, Binary file
 * 
 *  PROGRAM ASSUMPTIONS:  1. variables for:
  							a. "filename" and "sortedFilename" as strings to store a name of input and output files
							  	respectively, input by user.
							b. "file" and "sortedFile" as file stream objects for input data from and output data to 
								respectively.
							c. rows and cols as integers to store number of rows and columns in 2D-array, read from input file. 
							d. **arr2Dptr as pointer to 2D-array of floats, or a pointer to a pointer to an array of floats.
								This 2D-array stores rows*cols elements, read from input file.					
						 2. Functions: 
							a. setSortCol(int&, int) to take and validate user's input for sortCol.
							b. setOrder(char&) to take and validate user's input for sortOrder (A or D).
							c. bool isSorted(float**, char, int, int) to determine if the array has already been sorted.
							d. selectionDescSort(float**, int, int, int) to sort in descending order (if sortOrder == 'D')
							e. selectionAscSort(float**, int, int, int) to sort in ascending order (if sortOrder == 'A').
							f. displayArray(float**, int, int) to display the array's contents on the screen.
						 3. Process:
							a. User is asked for the name of a binary file ("filename") to read the data from,
				 				then he/she is asked for a name of a binary file ("sortedFilename") to write the data to.
								Then the input file is opened, and its contents is read from it in the
								folliwing order: the first two values are number of rows and columns respectively. 
						  		The remaining data is the 2D array's elements stored as floating point values.
						  	b. User is aksed for a column number which he/she would like to sort the data by.
						  		User is also offered to specify the order (A-ascending or D-descending) which he/she
						  		would like to sort the data in the specified column in.
						  		All inputs are validated. If any entered value is not valid, it is rejected, and user 
						  		is asked to re-enter the value.
						  	c. Boolean isSorted function checks if the data in the specified column has already
							  	been sorted. If it's not, selection sort function is called to sort data either in 
								descending or ascending order, according to user's chose.
							d.  With the data sorted by specified column, all array's contents is written to the output file,
								name of which was specified by user in step (a).
								
*/

#include <iostream>
#include <fstream>
#include <cstdlib> // for atoi() and atof() functions
#include <cctype> // for toupper() function
#include <iomanip> // for setprecision(), setw(), left and right output manipulators
#include <string> //for length() function
using namespace std;

// Function prototypes
void setSortCol(int&, int); // to take and validate user's input for sortCol
void setOrder(char&); // to take and validate user's input for sortOrder (A or D)
bool isSorted(float**, char, int, int); // to determine if the array has already been sorted 
void selectionDescSort(float**, int, int, int); // to sort in descending order (if sortOrder == 'D')
void selectionAscSort(float**, int, int, int); // to sort in ascending order (if sortOrder == 'A')
void displayArray(float**, int, int); // to display the array's contents on the screen

int main() {
	// declare variables for filename and sortedFilename as strings to store names of input and output file respectively 
	string filename, sortedFilename; 
	fstream file, sortedFile; // declare fstream objects, "file" and "sortedFile"
	int rows, cols, sortCol; // declare variables for rows and cols to store number of rows and columns in 2D-array,
							// and sortCol to store user's choice of a column # which the array is to be sorted by.
	char sortOrder; // declare "sortOrder' as char to store user's choice of sorting order (A for ascending or D for descending) 
	float **arr2Dptr = nullptr; // declare a pointer to 2D-array and initialize it with nullptr 
	// display a greeting message 
	cout << "Hello!\nThis program reads in the 2D-array of float numbers,\nsorts the data by the column the user specifies,\n";
	cout << "and outputs the sorted 2D array to the output file.\nLet\'s get started.\n"; 
	cout << "Enter the file name to read data from: "; // Prompt user for input file name
	cin >> filename; // store user's input as "filename" string
	cout << "Enter the file name to write the sorted data to: "; // Prompt user for output file name
	cin >> sortedFilename; // store user's input as "sortedFilename" string
	file.open(filename.c_str(), ios::binary | ios::in); // open the input file in binary mode
	if(!file) { // if the file was not successfully opened...
		cout << "Error opening the file!\n"; // .. display error message,
		delete arr2Dptr; arr2Dptr = nullptr; // free the portions of memory taken by pointers with dynamic memory allocation
		return -1; 							// return -1 and terminate the program.
	} 										// Otherwise, read the contents of the input file
	file.read( reinterpret_cast<char*>(&rows), sizeof(int)); // read a number representing # of rows
	file.read( reinterpret_cast<char*>(&cols), sizeof(int)); // read a number representing # of columns
	// allocate a portion of memory for a pointer to array with "rows" elements and assign it to our 2D-array
	arr2Dptr = new float*[rows];
	// initialize all array elements with another array, i.e., create 2D array
	for (int row = 0; row<rows;row++) { // step through "rows" elements ...
		*(arr2Dptr+row) = new float[cols]; // ...and assign each element another array, with "cols" elements
		for (int col=0; col<cols; col++) { // withing each row, step through each of "cols" elements
			// read the following float-sized value from a binary file assigning it to each 2D-array element
			file.read(reinterpret_cast<char *>(*(arr2Dptr+row)+col), sizeof(float)); 
		} 
	} 
	file.close(); //After we're done with the input file, close it.
	
	// display array's elements as a table by calling displayArray function
	cout << "Here is the contents of \"" << filename << "\".\n";
	// First, display a message on how many rows and columns the 2D-array contains
	cout << "It contains " << rows << " rows and " << cols << " columns.\n\n";
	displayArray(arr2Dptr, rows, cols); 
	// Prompt the user to specify the column # which data should be sorted by
	cout << "Enter the column # which you want to sort the data by: ";
	setSortCol(sortCol, cols); // take and validate user's input for sortCol
	// Prompt the user for "sortOrder" to specify the sorting order ('a" or 'D')
	cout << "In ascending (type A) or descending order (type D)?: ";
	setOrder(sortOrder); // take and validate user's input for sortOrder ('A' or 'D')
	// Depending on specified sortOrder, funtion isSorted determines whether the data has already been sorted by specified sortCol
	
	if(isSorted(arr2Dptr, sortOrder, rows, sortCol)) { // if data has already been sorted...
		cout << "The array is already sorted!\n"; // display the message that the data has already been sorted
	} else { // if data is unsorted...
		if(sortOrder == 'A') { // if user chose ascending order ...
			// call selectionAscSort function to sort data in specified column in ascending order
			selectionAscSort(arr2Dptr, rows, cols, sortCol); 
			// display the message that sorting process is successfully completed
			cout << "The data is sorted in ascending order by column " << sortCol << "\n";
		}
		else { // otherwise, if user chose descending order ...
			// call selectionDescSort function to sort data in specified column in descending order
			selectionDescSort(arr2Dptr, rows, cols, sortCol);
			// display the message that sorting process is successfully completed
			cout << "The data is sorted in descending order by column " << sortCol << "\n";
		}
		// To visualize what happened, display the sorted 2D-array by calling displayArray function.
		cout << "Here is the contents of the sorted array\n";
		displayArray(arr2Dptr, rows, cols);
	} 

	// Open the output file in binary mode
	sortedFile.open(sortedFilename.c_str(), ios::binary | ios::out);
	if(sortedFile) { // if the file was successfully opened, ...
		cout << "Writing data to \"" << sortedFilename << "\"....\n"; // display the message that data is to be written to this file
		sortedFile.write( reinterpret_cast<char*>(&rows), sizeof(int)); // write a number representing # of rows
		sortedFile.write( reinterpret_cast<char*>(&cols), sizeof(int)); // write a number representing # of cols
		for (int row=0; row<rows; row++) { // step through each of "rows" elements
			for (int col=0; col<cols; col++) { // withing each row, step through each of "cols" elements
				// write the following float-sized value to the binary file assigning it to each 2D-array element
				sortedFile.write(reinterpret_cast<const char *>(*(arr2Dptr+row)+col), sizeof(float));
			} // repeat for each col inside a row
		} // repeat for each row
		cout << "The data was successfully written to \"" << sortedFilename << "\"\n\n";
		sortedFile.close(); // After we're done with the output file, close it.
	} else cout << "Error opening the file!\n\n"; // if the sortedFile could not be opened, display error message
	// free the portions of memory taken by pointers with dynamic memory allocation
	delete arr2Dptr; arr2Dptr = nullptr;
	// Display a nice goodbye message
	cout << "That\'s it!\n\tBest wishes,\n\tMariia Gregory\n";
}
/* Definition of setSortCol function. It accepts an address of "sortCol" variable and # of columns as arguments.
 	It takes and validates user's input for # of a column which the data is to be sorted by. If user enters anything 
	 other than a digit, or entered column # is not in a range of an array, the input is rejected, and user is
	 offered to re-enter the value. */
void setSortCol(int &col, int cols) {
	string input; // declare a variable for input as string to store user's initial input
	bool validInput; // declare variable for validInput as boolean, which will indicate whether the input is valid or not
	do {
		validInput = true; // set/reset validInput to true
		cin >> input; // store user's input in input string variable
		for(char sym : input) { // step through all characters of user's input
			if (!isdigit(sym)) { // if at least one non-digit character is found
				cout << "Invalid column! Try again: "; // display error message
				validInput = false; // set validInput to false
				break; // immediately terminate the foor-loop
			}
		}
		if(validInput) { // user's input is valid (all digits were entered), 
			col = atoi(input.c_str()); // store user's input as "col" after converting it to integer type.
			if(col<0 || col-1>cols) { // in case "col" has a negative value or a value larger than the largest column # in our array,
                 // display error message and offer to user to re-enter the searched column #
				cout << "This column doesn't exist in the array!\nChoose another column #: "; // display error message
				validInput = false; // set validInput to false
			}
		}
	} while (!validInput); // if validInput was changed to false, start over from do {... 
}
/* Definition of setOrder function. It accepts an address of "sortOrder" variable as argument.
 	It takes and validates user's choice on which order, ascending or descending, the data is to be sorted by.
	 If user enters anything other than 'A', or 'a', or 'D', or 'd', the input is rejected, and user is
	 offered to re-enter the choice as an alphabetic character. */
void setOrder(char &order) {
	string temp; // declare a local variable for "temp" as string to store user's initial input
	bool validInput; // declare variable for validInput as boolean, which will indicate whether the input is valid or not
	do {
		validInput = true; // set/reset validInput to true
		cin >> temp; // store user's input in input string variable
		if(temp.length() > 1) { // In case user entered more than one character,
			cout << "Invalid choice! Enter only ONE letter, A or D: "; // display error message
			validInput = false; // set validInput to false
		}
		else { // otherwise, check if the character entered is either 'A' or "D' in its uppercase form.
			for(char sym : temp) { 
				if(toupper(sym) != 'A' && toupper(sym) != 'D')  { // if the character entered is neither 'A' nor 'D' in uppercase form,
					cout << "Invalid choice! Enter either A or D: "; // display error message
			        validInput = false; // set validInput to false
				}
			}
		}
	} while(!validInput); // if validInput was changed to false, start over from do {... 
	order = toupper(temp.c_str()[0]); // after input validation is complete, store user's choice in "order" variable
}
/* Definition of isSorted function. It accepts pointer to 2D-array, number of rows it contains, the column # which the data
   is to be sorted by, and sorting order character as arguments. Based on the sort order specified ('A' for ascending, 'D' for descending)),
   the function, by comparing each element with the following element in this column, determines whether elements are sorted 
   in specified order. Function returns true if data is sorted or false if not */
bool isSorted(float **arr2Dptr, char order, int rows, int col) {
	for(int row = 1; row < rows; row++) { // check all elements in the specified column by stepping through each row
        if(order == 'A') { // in case of ascending order choice,
            // as soon as at least one element smaller than the following is found,
			if( *(*(arr2Dptr+row)+col) < *(*(arr2Dptr+row-1)+col) ) { 
				return false; // return false and exit the function
			}
		} else { // in case of descending order choice,
		    // as soon as at least one element larger than the following is found,
			if( *(*(arr2Dptr+row)+col) > *(*(arr2Dptr+row-1)+col) ) {
				return false; // return false and exit the function
			}
		}
	}
	return true; // if all elements are sorted in order, return true
}
/* Definition of selectionDescSort function. It accepts pointer to 2D-array, number of rows and cols, and number of a column, which 
   the data is to be sorted by as arguments. It performs a descending order selection sort on 2D-array by specified column. 
   Every time the function moves the largest value to the top, it moves the whole row which this value is found in. */
void selectionDescSort(float **arr2Dptr, int rows, int cols, int sortCol) {
	unsigned int startAt, maxRow; // declare variables for startAt and maxRow as unsigned integers
	float maxValue, elemtoMove; // declare variable for maxValue and elemtoMove as floats
	// step through all elements in the specified searched column in order to search for maximum value and a row # where this value is found
	for (startAt=0; startAt<rows-1; startAt++) {
		maxValue = *(*(arr2Dptr+startAt)+sortCol); // initialize maxValue with the value of 1st unordered element in this column
		maxRow = startAt; // ... and maxRow with the # of a row where the 1st unordered element is located
		for (int row = startAt+1; row < rows; row++) {
			// step through all elements of yet unordered segment
			if( *(*(arr2Dptr+row)+sortCol) > maxValue) {
				// every time an element considered appears to be greater than initially set maxValue,
				// change "maxValue" to this element's value 
				maxValue = *(*(arr2Dptr+row)+sortCol); 
				maxRow = row; // ... and maxRow to the # of the row which maxValue is found in
			}
		}
        // after finishing stepping through all elements in the column, swap the first unordered value and newfound maxValue,
        // i.e. place the newfound maxValue at the top of the currently considered segment (just below the last ordered element). 
        // The first unordered element is placed in a row where maxValue was previously located.
		*(*(arr2Dptr+maxRow)+sortCol) = *(*(arr2Dptr+startAt)+sortCol); 
		*(*(arr2Dptr+startAt)+sortCol) = maxValue;
		// Next, exchange all elements in maxRow (the row where maxValue was found) with all elements in the row
        // where the previously unordered element was located (the row where maxValue has just been placed)
		for(int col=0; col<cols; col++) { // step through each column...
			if(col != sortCol) { // (skip the column which the data is being sorted by (maxValue is already there))
				elemtoMove = *(*(arr2Dptr+maxRow)+col); // Temporarily, assign each element in maxRow to "elemToMove" variable
				// swap the element in the row where maxValue has just been placed to with the element in maxRow
				*(*(arr2Dptr+maxRow)+col) = *(*(arr2Dptr+startAt)+col); 
				*(*(arr2Dptr+startAt)+col) = elemtoMove;
			}
		}
	} // After that, return to the outer loop and continue sorting starting from the 1st unordered element in the sorted column.
}
/* Definition of selectionAscSort function. It accepts pointer to 2D-array, number of rows and cols, and number of a column, which 
   the data is to be sorted by as arguments. It performs a ascending order selection sort on 2D-array by specified column. 
   Every time the function moves the smallest value to the top, it moves the whole row which this value is found in. */
void selectionAscSort(float **arr2Dptr, int rows, int cols, int sortCol) {
	unsigned int startAt, minRow; // declare variables for startAt and maxRow as unsigned integers
	float minValue, elemtoMove; // declare variable for minValue and elemToMove as floats
	// step through all elements searching for minimum value a row # where this value is found
	for (startAt=0; startAt<rows-1; startAt++) {
		minValue = *(*(arr2Dptr+startAt)+sortCol); // initialize minValue with the value of 1st unordered element in the sorted column
		minRow = startAt; // ... and minRow with the # of a row where the 1st unordered element is located
		for (int row = startAt+1; row < rows; row++) {
			// step through all elements of yet unordered segment
			if( *(*(arr2Dptr+row)+sortCol) < minValue) {
				// every time an element considered appears to be less than initially set minValue,
				// change "minValue" to this element's value 
				minValue = *(*(arr2Dptr+row)+sortCol); 
				minRow = row; // ... and minRow to # of the row which minValue is found in
			}
		} // after we finishing stepping through all elements in the column, swap the first unordered value and newfound minValue,
        // i.e. place the newfound minValue at the top of the currently considered segment (just below the last ordered element). 
        // The first unordered element is placed in a row where minValue was previously located. 
		*(*(arr2Dptr+minRow)+sortCol) = *(*(arr2Dptr+startAt)+sortCol);
		*(*(arr2Dptr+startAt)+sortCol) = minValue;
	    // Next, exchange all elements in minRow (the row where minValue was found) with all elements in the row
        // where the previously unordered element was located (the row where minValue has just been placed)
		for(int col=0; col<cols; col++) { // step through each column...
			if(col != sortCol) { // (skip the column which the data is being sorted by (minValue is already there))
				elemtoMove = *(*(arr2Dptr+minRow)+col); // Temporarily, assign each element in minRow to "elemToMove" variable
				// swap the element in the row where minValue has just been placed to with the element in minRow
				*(*(arr2Dptr+minRow)+col) = *(*(arr2Dptr+startAt)+col);
				*(*(arr2Dptr+startAt)+col) = elemtoMove;
			}
		}
	} // After that, return to the outer loop and continue sorting starting from the 1st unordered element in sortCol column.
}

/* Definition of displayArray function. It accepts our 2D-array (a pointer) and its size in rows and cols as arguments.
	The array's contents is output as a table, in presentable form. The first horizontal line is column headers,
	the first vertical line is row headers. The contents is displayed with 2 digits of decimal precision. */
void displayArray(float **arr2Dptr, int rows, int cols) {
	// skip 9 spaces, so the 1st column header is placed exactly above the 1st element
	cout << setw(15) << right << "Col 0";
	// complete the first line by displaying other column headers on equal distance
	for(int col=1; col<cols; col++) { // step through each of "cols" elements
		cout << setw(7) << "Col " << col; // display a current column header
	} 
	cout << "\n"; // go to the next line
	// display row headers and all values in a row on equal distance, with 2 digits of decimal precision 
	for(int row=0; row<rows; row++) { // step through each of "rows" elements
		cout << "Row " << setw(3) << left << row << ": " << fixed << setprecision(2); // display the row header
		for(int col=0; col<cols; col++) { // within this row, step through each of "cols" elements
			// display elements in a row on same distance, with 2 digits of decimal precision
			cout << left << setw(8) << *(*(arr2Dptr+row)+col); 
		} 
		cout << "\n"; // go to the next line
	} 
	cout << "\n"; // go to the next line
}
