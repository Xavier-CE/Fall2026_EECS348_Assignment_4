/*
Program Name: Assignment 4 - Sudoku Solver

Description:
This program uses a Sudoku class and recursive backtracking
to solve five Sudoku puzzles. It prints the original puzzle
and all valid solutions, or a message if no solution exists.

Inputs:
Five text files named puzzle1.txt through puzzle5.txt.
Each file contains a 9x9 Sudoku puzzle with underscores
representing empty cells.

Outputs:
The original puzzle and all valid solutions for each file.
If a puzzle has no solution, the program prints
"No solution found".

Collaborators:
None.

Other Sources:
Copilot and Gemini were used to generate
and compare the original program versions. The final code
was tested and improved by Xavier Eddins.

Author: Xavier Eddins
Creation Date: October 15, 2026
*/

#include <iostream> // include the iostream library for input and output
#include <fstream>// include the fstream library for file input and output
#include <string>// include the fstream library for file input and output

using namespace std;// use the standard namespace to avoid prefixing std:: to standard library names


class Sudoku// start of the Sudoku class definition
{
private:// The private members of the class
    // Constants used throughout the program
    static const int SIZE = 9; // declaring a constant integer SIZE with a value of 9
    static const int BLOCK_SIZE = 3;// declaring a constant integer BLOCK_SIZE with a value of 3

    int board[SIZE][SIZE];// declaring a 2D array with size SIZE x SIZE to represent the Sudoku board
    int solutionCount;// declaring an integer variable to keep track of the number of solutions found

    // Checks if a number can be placed in a cell
    bool isValid(int row, int col, int num) const// start of the isValid function definition
    {
        // Check the row
        for (int c = 0; c < SIZE; c++)// loop through each column in the specified row
        {
            if (board[row][c] == num)// check if the number is already present in the row
            {
                return false;// if the number is found in the row, return false
            }
        }

        // Check the column
        for (int r = 0; r < SIZE; r++)// loop through each row in the specified column
        {
            if (board[r][col] == num)// check if the number is already present in the column
            {
                return false;// if the number is found in the column, return false
            }
        }

        // Find the top-left corner of the 3x3 block
        int startRow = row - row % BLOCK_SIZE;// declare an int variable startRow that calculates the starting row index of the 3x3 block containing the specified cell
        int startCol = col - col % BLOCK_SIZE;// declare an int variable startCol that calculates the starting column index of the 3x3 block containing the specified cell

        // Check the 3x3 block
        for (int r = startRow; r < startRow + BLOCK_SIZE; r++)// loop through each row in the 3x3 block
        {
            for (int c = startCol; c < startCol + BLOCK_SIZE; c++)// loop through each column in the 3x3 block
            {
                if (board[r][c] == num)// check if the number is already present in the 3x3 block
                {
                    return false;// if the number is found in the 3x3 block, return false
                }
            }
        }

        return true;// if the number is not found in the row, column, or 3x3 block, return true
    }// end of the isValid function definition

    // Checks whether the original puzzle follows Sudoku rules
    bool isPuzzleValid()// start of the isPuzzleValid function definition
    {
        for (int r = 0; r < SIZE; r++)// loop through each row in the Sudoku board
        {
            for (int c = 0; c < SIZE; c++)// loop through each column in the Sudoku board
            {
                if (board[r][c] != 0)// check if the cell is not empty (not equal to 0)
                {
                    int num = board[r][c];// store the number in the cell in a variable num

                    // Temporarily remove the number so it does
                    // not conflict with itself during the check
                    board[r][c] = 0;// temporarily set the cell to 0 (empty) to avoid conflicts when checking validity

                    bool valid = isValid(r, c, num);// check if the number is valid in its position by calling the isValid function

                    // Restore the original number
                    board[r][c] = num;// restore the original number in the cell after checking validity

                    if (!valid)// if the number is not valid in its position, return false
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }// end of the isPuzzleValid function definition


    void solveRecursive()// start of the solveRecursive function definition
    {
        int bestRow = -1;// declare an ineger variable bestRow and set its value to -1 to indicate that no empty cell has been found yet
        int bestCol = -1;// declare an ineger variable bestCol and set its value to -1 to indicate that no empty cell has been found yet
        int fewestChoices = SIZE + 1;// declare an ineger variable fewestChoices and set its value to SIZE + 1 to keep track of the fewest valid choices for an empty cell

        // Find the empty cell with the fewest valid choices
        for (int r = 0; r < SIZE; r++)// loop through each row in the Sudoku board
        {
            for (int c = 0; c < SIZE; c++)// loop through each column in the Sudoku board
            {
                if (board[r][c] == 0)// check if the cell is empty (equal to 0)
                {
                    int choices = 0;// declare an integer variable choices and set its value to 0 to count the number of valid choices for the empty cell

                    // Count how many numbers can go in this cell
                    for (int num = 1; num <= SIZE; num++)// loop through each number from 1 to SIZE to check if it can be placed in the empty cell
                    {
                        if (isValid(r, c, num))// check if the number is valid in the empty cell by calling the isValid function
                        {
                            choices++;// increment the choices counter if the number is valid in the empty cell
                        }
                    }

                    // No number can go here, so this path fails
                    if (choices == 0)// check if there are no valid choices for the empty cell
                    {
                        return;// return from the function to backtrack and try a different path in the recursive search
                    }

                    // Save the cell with the fewest choices
                    if (choices < fewestChoices)// check if the number of valid choices for the current empty cell is less than the fewest choices found so far
                    {
                        fewestChoices = choices;// update the fewestChoices variable to the current number of valid choices
                        bestRow = r;// update the bestRow variable to the current row index of the empty cell
                        bestCol = c;// update the bestCol variable to the current column index of the empty cell
                    }
                }
            }
        }

        // No empty cells remain, so a solution was found
        if (bestRow == -1)// if no empty cell was found, Sudoku board is completely filled, indicating a valid solution has been found
        {
            solutionCount++;// increment the solutionCount variable to keep track of the number of solutions found

            cout << "\nSolution " << solutionCount << ":\n";// print the solution number to the console
            printBoard();// print the current state of the Sudoku board to the console

            return;
        }

        // Try every valid number in the selected cell
        for (int num = 1; num <= SIZE; num++)// loop through each number from 1 to SIZE to try placing it in the empty cell with the fewest valid choices
        {
            if (isValid(bestRow, bestCol, num))// check if the number is valid in the empty cell by calling the isValid function
            {
                board[bestRow][bestCol] = num;// place the valid number in the empty cell on the Sudoku board

                // Recursively solve the remaining puzzle
                solveRecursive();// call the solveRecursive function recursively to continue solving the Sudoku puzzle with the updated board state

                // Undo the choice to look for other solutions
                board[bestRow][bestCol] = 0;// rest the emplty cell back to 0
            }
        }
    }// end of the solveRecursive function definition

public:// start of the public members of the class
    // Initializes the board and solution count
    Sudoku()// start of the Sudoku constructor definition
    {
        solutionCount = 0;// initialize the solutionCount variable to 0 to keep track of the number of solutions found

        for (int r = 0; r < SIZE; r++)// loop through each row in the Sudoku board
        {
            for (int c = 0; c < SIZE; c++)// loop through each column in the Sudoku board
            {
                board[r][c] = 0;// initialize each cell in the Sudoku board to 0, indicating that it is empty
            }
        }
    }

    // Reads the puzzle and checks the input format
    bool loadPuzzle(string filename)// start of the loadPuzzle function definition
    {
        ifstream infile(filename);// create an input file stream object named infile and open the specified file for reading

        if (!infile)// check if the file was successfully opened; if not, print an error message and return false
        {
            cout << "Error: Could not open " << filename << endl;// print an error message to the console indicating that the file could not be opened
            return false;
        }

        string entry;// declare a string variable named entry to store each entry read from the file

        for (int r = 0; r < SIZE; r++)// loop through each row in the Sudoku board
        {
            for (int c = 0; c < SIZE; c++)// loop through each column in the Sudoku board
            {
                // Make sure another entry exists
                if (!(infile >> entry))// check if there is another entry to read from the file; if not, print an error message and return false
                {
                    cout << "Error: " << filename << " does not contain 81 entries." << endl;
                    return false;
                }

                if (entry == "_")// check if the entry is an underscore, indicating an empty cell; if so, set the corresponding cell in the board to 0
                {
                    board[r][c] = 0;
                }
                else if (entry.length() == 1 && entry[0] >= '1' && entry[0] <= '9')// check if the entry is a single digit between '1' and '9'; if so, convert it to an integer and set the corresponding cell in the board
                {
                    board[r][c] = entry[0] - '0';
                }
                else// if the entry is invalid, print an error message and return false
                {
                    cout << "Error: Invalid entry in " << filename << ": " << entry << endl;
                    return false;
                }
            }
        }

        // Make sure the file does not contain extra entries
        if (infile >> entry)// check if there are any extra entries in the file after reading 81 entries; if so, print an error message and return false
        {
            cout << "Error: " << filename << " contains more than 81 entries." << endl;
            return false;
        }

        infile.close();// close the input file stream after reading all entries from the file

        // Check for duplicate numbers in the original puzzle
        if (!isPuzzleValid())// check if the original puzzle is valid by calling the isPuzzleValid function; if not, print an error message and return false
        {
            cout << "Error: " << filename << " violates Sudoku rules." << endl;
            return false;
        }

        return true;
    }// end of the loadPuzzle function definition

    // Prints the board with numbers and empty cells
    void printBoard() const// start of the printBoard function definition
    {
        for (int r = 0; r < SIZE; r++)// loop through each row in the Sudoku board
        {
            for (int c = 0; c < SIZE; c++)// loop through each column in the Sudoku board
            {
                if (board[r][c] == 0)// check if the cell is empty (equal to 0); if so, print an underscore to represent the empty cell
                {
                    cout << "_ ";
                }
                else// if the cell is not empty, print the number in the cell
                {
                    cout << board[r][c] << " ";
                }

                // Separate each 3x3 block
                if ((c + 1) % BLOCK_SIZE == 0 && c != SIZE - 1)// if the current column is the last column of a 3x3 block and not the last column of the board, print a vertical separator to visually separate the blocks
                {
                    cout << "| ";
                }
            }

            cout << endl;

            // Separate each group of three rows
            if ((r + 1) % BLOCK_SIZE == 0 && r != SIZE - 1)// if the current row is the last row of a 3x3 block and not the last row of the board, print a horizontal separator to visually separate the blocks
            {
                cout << "------+-------+------" << endl;
            }
        }
    }// end of the printBoard function definition

    // Starts solving and reports the results
    void solve()// start of the solve function definition
    {
        solutionCount = 0;// initialize the solutionCount variable to 0 before starting the solving process

        solveRecursive();// call the solveRecursive function to start the recursive backtracking algorithm to find all valid solutions for the Sudoku puzzle

        if (solutionCount == 0)// if no solutions were found after the solving process, print a message indicating that no solution was found
        {
            cout << "\nNo solution found." << endl;
        }
        else// if at least one solution was found, print the total number of solutions found
        {
            cout << "\nTotal solutions found: "
                 << solutionCount << endl;
        }
    }
};// end of the Sudoku class definition

int main()// start of the main function definition
{
    const int NUM_PUZZLES = 5;// declare a constant integer NUM_PUZZLES with a value of 5 to represent the number of Sudoku puzzles to solve

    for (int i = 1; i <= NUM_PUZZLES; i++)// loop through each puzzle file from 1 to NUM_PUZZLES
    {
        string filename = "puzzle" + to_string(i) + ".txt";// construct the filename for the current puzzle file by concatenating "puzzle", the puzzle number, and ".txt"

        cout << "\n================================\n";
        cout << "File: " << filename << endl;
        cout << "================================\n";

        Sudoku puzzle;// create an instance of the Sudoku class named puzzle to represent the current Sudoku puzzle

        if (!puzzle.loadPuzzle(filename))// check if the puzzle was successfully loaded from the file by calling the loadPuzzle function; if not, print an error message and skip to the next puzzle file
        {
            // Skip this file if its input is invalid
            continue;
        }

        cout << "\nOriginal Puzzle:\n";
        puzzle.printBoard();// 

        cout << "\nSearching for solutions...\n";
        puzzle.solve();// solve the puzzle by calling the solve function, which will find and print all valid solutions or indicate if no solution exists
    }

    return 0;
}// end of the main function definition

