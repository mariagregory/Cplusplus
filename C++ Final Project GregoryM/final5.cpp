/*
 *            PROGRAMMER: Mariia Gregory
 *         PROBLEM TITLE: Final Project - 5
 *    PROBLEM DEFINITION: Write a program to prompt the user for the name of a file to input as a binary file 
 							to read in the two dimensional array of float data type.
 							Load in the data for the two dimensional array.
							Prompt the user to enter the column they wish to search by, and the value to find. 
							Implement binary search to find the value (the column specified must be sorted).
 *                  DATE: 5/31/16
 *     SYSTEM - HARDWARE: Windows
 *            - SOFTWARE: Dev-Cpp
 *         Input Devices: Keyboard, Binary files
 *        Output Devices: Terminal screen, Binary file
 * 
 *  PROGRAM ASSUMPTIONS:  1. variables for:
  							a. "filename" as string to store a name of output file, input by user.
							b. "file" and "sortedFile" as fstream objects for input data from and output data to respectively.
							c. rows and cols as integers to store number of rows and columns in 2D-array, read from input file. 
							d. **arr2Dptr as pointer to 2D-array of floats, or a pointer to a pointer to an array of floats.
								This 2D-array stores rows*cols elements, read from input file.					
						 2. Functions: 
							a. setTarget(float &) - to take and validate user's input for targetValue to be searched
                            b. setSearchCol(int&, int) - to take and validate user's input for the # of a column
                               which targetValue is searched in.
                            c. isSorted(float**, int, int) - to determine if the array has already been sorted in ascending order
                            d. selectionAscSort(float**, int, int, int) - to sort in ascending order (if !isSorted)
                            e. binarySearch(float**, int, int, float) - to search for targetValue in searchCol
                               and return targetPosition (a row # whiche targetValue is found in) or -1 if it is not.
                            f. displayArray(float**, int, int) - to display the array's contents on the screen.
						3. Process:
							a. User is asked for the name of a binary file ("filename") to read the data from.
								If the input file is successfully opened, its contents is read from it in the
								folliwing order: the first two values are number of rows and columns respectively. 
						  		The remaining data is the 2D array's elements stored as floating point values.
						  	b. User is aksed for a target value he/she wants to search. 
							  	User is also asked for a column number which he/she would like to search this value in.
						  		All inputs are validated. If the targetValue contain anything other than digits,
								  dot, or dash, and if searched column # is out of an array's range, input is rejected,
								  and user is asked to re-enter the value.
						  	c. Boolean isSorted function checks if the data in the specified column has already
							  	been sorted. If it's not, selection sort function is called to sort data either in 
								descending or ascending order, according to user's chose.
							d.  With the data in the searched column sorted in ascending order, binarySearch function
								is called to find the approximate match of the targetValue with one of array's elements
								(deflection is +/-0.01). If the match is found, binarySearch returns the row # in which 
								the targetValue is found within the specified column #.
*/

#include <iostream>
#include <fstream>
#include <cstdlib> // for atof() and atoi() functions
#include <cctype> // for isdigit() function
#include <iomanip> // for setw and setprecision
using namespace std;

// Function prototypes
void setTarget(float &); // to take and validate user's input for targetValue to be searched
void setSearchCol(int&, int); // to take and validate user's input for the # of a column which targetValue is searched in
bool isSorted(float**, int, int); // to determine if the array has already been sorted  in ascending order
void selectionAscSort(float**, int, int, int); // to sort in ascending order (if !isSorted)
int binarySearch(float**, int, int, float); // to search for targetValue in searchCol and return targetPosition (a row #) 
                                            // where targetValue is found (or -1 if it is not)
void displayArray(float**, int, int); // to display the array's contents on the screen

int main() {
	string filename; // declare variable for filename as string to store name of the output file 
	fstream file; // declare a file stream object
	int rows, cols, searchCol, targetPosition; // declare variables for rows and cols to store number of rows and columns in 2D-array,
	// searchCol to store the # of a column which the searched value is to be found (if it is there),
    // and targetPosition to store a row # where targetValue is found (or -1 if it is not found)
	float targetValue; // declare variable for targetValue as a float to store a value to be searched in the array
	float **arr2Dptr = nullptr; // declare a pointer to 2D-array and initialize it with nullptr 
	// display a greeting message
	cout << "Hello!\nThis program loads in the 2D-array\nof floating point values from a binary file,\n";
	cout << "searches a specified value by a specified column\nusing the binary search algorithm.\nLet\'s get started.\n"; 
	cout << "Enter the file name to read data from: "; // Prompt user for input file name
	cin >> filename; // Prompt user for input file name
	file.open(filename.c_str(), ios::binary | ios::in); // open the input file in binary mode
	if(!file) { // if the file was not successfully opened...
		cout << "Error opening the file!\n"; // .. display error message,
		delete arr2Dptr; arr2Dptr = nullptr; // free the portions of memory taken by pointers with dynamic memory allocation
		return -1;                  // return -1 and terminate the program.
	} 
	file.read( reinterpret_cast<char*>(&rows), sizeof(int)); // read a number representing # of rows
	file.read( reinterpret_cast<char*>(&cols), sizeof(int)); // read a number representing # of columns
	// allocate a portion of memory for a pointer to array with "rows" elements and assign it to our 2D-array
	arr2Dptr = new float*[rows];
	// initialize all array elements with another array, i.e., create 2D array
	for (int row = 0; row<rows;row++) { // step through "rows" elements ...
		*(arr2Dptr+row) = new float[cols]; // ...and assign each element another array, with "cols" elements
		for (int col=0; col<cols; col++) { // step through each of "cols" elements within the row
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
	// Prompt the user for targetValue, i.e. the value the user wants to search in the array
	cout << "Enter the value you want to search for: ";
	setTarget(targetValue); // take and validate user's input by calling setTarget function
	// Prompt the user to specify the column # which targetValue should be searched by
	cout << "Enter the column # which you want to search this value in: ";
	setSearchCol(searchCol, cols); // take and validate user's input by calling setSearchCol function
	// Determine whether the data has already been sorted in ascending order by searchCol column by calling isSorted function
	if(!isSorted(arr2Dptr, rows, searchCol)) { // if data is unsorted...
		selectionAscSort(arr2Dptr, rows, cols, searchCol); // sort data in ascending order by calling selectionAscSort function 
		cout << "First, let's sort our data in ascending order...\nSorted data:\n"; // inform user that data is being sorted
		// Display the sorted 2D-array by calling displayArray function.
		displayArray(arr2Dptr, rows, cols);		
	}
	// search the array for targetValue by searchCol by calling binarySearch function and assign its return value to targetPosition 
	targetPosition = binarySearch(arr2Dptr, rows, searchCol, targetValue);
	if(targetPosition) { // if target is found, targerPosition (the row #) is a non-negative number
        // Display a joyful message that the value is found and what position (which row) it is found at.
		cout << "BINGO! We found " << targetValue << " in a row " << targetPosition << " of the column " << searchCol << "\n";
	} else { // otherwise, inform user that the target is not found
		cout << "Sorry, the value is not found.\n";
	}
	// free the portions of memory taken by pointers with dynamic memory allocation
	delete arr2Dptr; arr2Dptr = nullptr;
	// Display a nice goodbye message
	cout << "\nThat\'s it!\n\tBest wishes,\n\tMariia Gregory\n";
}
/* Definition of setTarget function. It accepts an address of "targetValue" as argument.
 	It takes and validates user's input for a value to be searched in the array. If user enters anything other than a digit,
     dot, or dash, the input is rejected, and user is offered to re-enter the value. */
void setTarget(float &target) {
	string input; // declare a variable for input as string to store user's initial input
	bool validInput; // declare variable for validInput as boolean, which will indicate whether the input is valid or not
	do { 
		validInput = true; // set/reset validInput to true
		cin >> input; // store user's input in input string variable
		for (char symbol : input) { // step through all characters of user's input
		    // if anything other than a digit, dot, or dash was entered,
			if (!isdigit(symbol) && symbol != '.' && symbol != '-') {
				cout << "This is not a number!\nEnter another value: "; // display error message
				validInput = false; // set validInput to false
				break; // immediately terminate the foor-loop
			}
		}
	} while(!validInput); // if validInput was changed to false, start over from do {... 
	// after input validation is successfully completed, store the value in "target" variable having converted it to float data type
	target = static_cast<float>(atof(input.c_str())); 
}
/* Definition of setSearchCol function. It accepts an address of "searchCol" and number of columns in the array as arguments.
 	It takes and validates user's input for a column # which the target value is to be searched by in the array. 
     If user enters anything other than a digit, the input is rejected, and user is offered to re-enter the column #. */
void setSearchCol(int &col, int cols) {
	string input; // declare a variable for input as string to store user's initial input
	bool validInput; // declare variable for validInput as boolean, which will indicate whether the input is valid or not
	do { 
		validInput = true; // set/reset validInput to true
		cin >> input; // store user's input in input string variable
		for (char symbol : input) { // step through all characters of user's input
			if (!isdigit(symbol)) { // if anything other than a digit was entered,
				cout << "This is not a number!\nEnter another value: "; // display error message
				validInput = false; // set validInput to false
				break; // immediately terminate the foor-loop
			}
		}
		if (validInput) { // if user's input is valid,
    		// store user's input in "col" variable having converted it to integer data type
			col = atoi(input.c_str());
			if(col<0 || col+1>cols) { // in case "col" has a negative value or a value larger than the largest column # in our array,
				cout << "This column doesn't exist in the array!\nChoose another column #: "; // display error message
				validInput = false; // set validInput to false
			}
		}
	} while(!validInput); // if validInput was changed to false, start over from do {... 
}
/* Definition of isSorted function. It accepts pointer to 2D-array, number of rows it contains, and the column # which the data
   is to be sorted by as arguments. By comparing each element with the following, the function determines whether all elements 
   in the specified column are sorted in ascending order. Function returns true if data is sorted or false if not */
bool isSorted(float **arr2Dptr, int rows, int col) {
	for(int row = 1; row < rows; row++) { // check all elements in the specified column by stepping through each row
        // as soon as at least one element smaller than the following is found,
		if( *(*(arr2Dptr+row)+col) < *(*(arr2Dptr+row-1)+col) ) {
			return false; // return false and exit the function
		}
	}
	return true; // if all elements are sorted in ascending order, return true
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
/* Definition of binarySearch function. It accepts pointer to 2D-array, number of rows it contains, number of a column which 
   the target value is to be searched by, and the target value itself as arguments. The function searches for the
   approximate match of the target value with one of array's elements (deflection is +/-0.01). 
   If the match is found, binarySearch returns the row # in which the targetValue is found within the specified column. */
int binarySearch(float **arr2Dptr, int rows, int col, float target) {
	// Display the message that the value is to be searched...
	cout << "Let's search for " << target << " in the column " << col << "...\n";
	// declare the variable for iterations and initialize it with 0
	int iterations = 0;
	// declare variables for first, last and middle indice, within which targetValue is presumably located.
	int first = 0, last = rows-1, middle;
	while(first <= last) { // repeat as long as the first index is no less than the last index
		middle = (first+last)/2; // calculate middle index as average of first and last indice
		
		//******** MANUAL DEBUG
		iterations++; // increment iterations variable
		// Display the message about what's going on...
		cout << "Iteration #" << iterations << ": first = " << first << ", last = " << last << ", middle " << middle << ".\n";
		cout << setw(14) << " " << "Checking if " << target << " equals to " << *(*(arr2Dptr+middle)+col) << "...\n";
		// ********* ENG OF MANUAL DEBUG
		
		// if target equals to the median element +/- 0.01, retun middle as a search result.
		if(target < *(*(arr2Dptr+middle)+col)+0.01 && target > *(*(arr2Dptr+middle)+col)-0.01) {
			return middle;
		} else if(target > *(*(arr2Dptr+middle)+col)) { // otherwise, if the targetValue is greater than the median element,
			first = middle+1; // discard lower half of the search area and search only in upper half.
		} else { // otherwise, discard lower half of the current search area and search only in upper half 
			last = middle-1;
		}
	}
	// if the function is still active, it means that first > last, and the value is not found
	return -1;
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
