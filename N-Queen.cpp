/*

Name : BIT NA YOON
Pnumber : P313284

This C++ program solves the n-Queen problem using a Depth-first Search algorithm, Backtracking. This is a simple and primitive solution that simply uses the brute force approach. Which just means, go down every possible path and find the path which satisfies our rules. The n-Queen problem is a more generalised form of the 8-Queen problem, in which the aim is to place 8 queens on a standard chessboard in a way that no queen is under attack, using standard chess queen moves. By under attack we mean that no two queens are placed in the same row, column or diagonal. The solution to the 8-Queen problem can then be extended to the generalised form of the problem, finding a solution, if one exists, for any “N” value.

The main flow of this program is as follows: Place queens one by one in different rows and columns, starting from the very top row and left column. However, before a queen is placed, we check to see if it is safe to do so, or will it be under attack by an already placed queen. If we find that it won’t be under attack then there is no clash, we mark this row and column as part of the solution. However, if a clash is found, we backtrack and continue.
*/

#include <iostream>
#include <sstream>
#include <stdio.h>

using std::cout;
using std::endl;

// How many queens to position on a board size of N*N
#define N 8

/*
print_grid is the function that prints out the queen locations. This is not needed for the program to function, it'll help me see if the soultion in the array is correct.
*/
void print_array(int array[], std::string array_label) {
  cout << array_label << ": [";
  for (int i = 0; i < N; i++) {
    cout << array[i];
    if (i != (N - 1))
      cout << ", ";
  }
  cout << "]" << endl;
  }

/*
print_grid is the function that prints out the queen locations, in a somewhat grid state.
*/
void print_grid(int x[], int y[]) {

  print_array(x, "X");
  print_array(y, "Y");

  // Two double forloops to go through every cell. (row x column)
  for (int i = 0; i < N; i++) {
    cout << " " << endl;
    cout << std::string(N * 2, '-');
    cout << endl;

    for (int j = 0; j < N; j++) {
      // The x[] & y[] arrays together hold the location of each queen.
      // So when we are going through each cell, we check if x[i] or y[i] hold the coordinates of the cell that is currently being checked.
      if (x[i] == i && y[i] == j) {
        cout << 'X';
      } else {
        cout << " ";
      }

      cout << "|";
    }
    }

  cout << endl << std::string(N * 2, '-') << endl;
}

/* 
used_in_row: Find if there is a queen (queen row locations are in x[]) in the row of
interest. Returns false, if it haven't been used in the row and true if it has been used in that row. 
*/
int used_in_row(int row, int x[]) {
  for (int i = 0; i < N; i++) {
    if (x[i] == row) {
      return true;
}
}
  
  return false;
}

/* 
used_in_col: Find if there is a queen (queen column locations are in y[]) in the column of interest. Returns false, if haven't been used in the column and 1 (true if it has been used in that column.
*/
int used_in_col(int col, int y[]) {
  for (int i = 0; i < N; i++) {
    if (y[i] == col) {
      return true;
    }
   }
  
  return false;
}

/* used_in_diagonalL: Find if there is a queen (queen locations are in x[] and y[]) in the diagonal of interest. Returns false, if it haven't been used in the diagonal and true, if it has been used in that diagonal.
*/
bool used_in_diagonalL(int row, int col, int x[], int y[]) {
  // Going diagonally down increases both row and col no.
  for (int i = row, j = col; i <= N, j < N; i++, j++) {
    // Check every queen's location
    for (int k = 0; k < N; k++) {
      if (x[k] == i && y[k] == j) {
        return true;
    }
   }
}
  // Going diagonally up reduces both row and col no.
  for (int i = row, j = col; i >= 0, j >= 0; i--, j--) {
    for (int k = 0; k < N; k++) {
      if (x[k] == i && y[k] == j) {
        return true;
    }
    }
   }
  return false;
}

/*
used_in_diagonalR: Find if there is a queen (queen locations are in x[] and y[]) in the diagonal of interest. Returns false, if it haven't been used in the diagonal and
true if it has been used in that diagonal.
*/
bool used_in_diagonalR(int row, int col, int x[], int y[]) {
  // up
  for (int i = row, j = col; i >= 0, j < N; i--, j++) {
    for (int k = 0; k < N; k++) {
      if (x[k] == i && y[k] == j) {
        return true;
    }
    }
  }

  // down
  for (int i = row, j = col; i < N, j >= 0; i++, j--) {
    for (int k = 0; k < N; k++) {
      if (x[k] == i && y[k] == j) {
        return true;
    }
}
}
  return false;
}

/* is_safe: This function calls used_in_row, used_in_col, used_in_diagonalL, and used_in_diagonalR functions to check if all of them return a false indicating that it is safe to position the new queen in [row, col] location given the current queen locations stored in x[] and y[].
*/
bool is_safe(int row, int col, int x[], int y[]) {
  return !used_in_row(row, x) && 
         !used_in_col(col, y) &&
         !used_in_diagonalL(row, col, x, y) &&
         !used_in_diagonalR(row, col, x, y);
}

/* 
nQueenSolver is the function that implements depth first search. 
Queens argument indicate how many queens are left to position, so a check to see if there is any.
Next, go through every single cell on the chessboard and find the next cell that does not invalidate any rules and "is safe" to position the queen.
If it is safe to position, do so by changing the x and y array values to include the new queens location, remove the number of queens left to position and then call nQueenSolver function with the new information. If it fails to return a true (all queens have been positioned), then we need to remove the last positioned queen by increasing the number of queens left and indicating that the queen no longer exists in the list.
*/
bool nQueenSolver(int queens, int x[], int y[]) {
  // Check whether there is queen in the left or not, call print_grid
  if (queens == 0) {
    print_grid(x, y);
    return true;
}

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (is_safe(i, j, x, y)) {
        // We update the location with our current safe queen
        x[N - queens] = i;
        y[N - queens] = j;

        queens--;

        // Call nQueenSolver with the remaining queen and the current locations of the queens inside the x & y arrays.
        if (nQueenSolver(queens, x, y)) {
          // Solved! so return true
          return true;
} else {
          // We couldn't place a queen that won't be attach, so we reset it's location and add it back to the list of queens that still needs to be placed
          queens++;
          x[N - queens] = -1;
          y[N - queens] = -1;
        }
      }          
    }
    }

  return false;
}

int main() {
  // Initialise the array that will hold the location of our queens, this is based on.
  int x[N];
  int y[N];

  // Fill out array with locations that are not possible to be on the grid.
  for (int i = 0; i < N; i++) {
    x[i] = -1;
    y[i] = -1;
}

  /*
   This calls the DFS function.
  */
  if (nQueenSolver(N, x, y) == false) {
    cout << "Solution does not exist" << endl;
  }

  return 0;
}