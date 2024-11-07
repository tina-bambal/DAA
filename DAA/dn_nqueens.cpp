#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void printBoard(const vector<string> &board, int startRow, int startCol) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                cout<<board[i][j]<<" ";
            }
            cout << endl;
        }
    }
    
    bool solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        int startRow, startCol;
        cout << "Enter the coordinates (row and column) to place the first Queen (0-indexed): ";
        cin >> startRow >> startCol;
        while (startRow < 0 || startRow >= n || startCol < 0 || startCol >= n)
        {
            cout << "Coordinates out of bounds! Please enter valid coordinates (0 to " << n - 1 << "): ";
            cin >> startRow >> startCol;
        }

        board[startRow][startCol] = 'Q';

        printBoard(board, startRow, startCol);
        // Attempt to solve starting from the next row
        if (!solve(board, startRow + 1, n, startRow)) {
            cout << "No solution found starting from the given coordinates.\n";
            return false;
        }

        cout << "One of the possible solutions is:\n";
        printBoard(board, startRow, startCol);
        return true;
    }

private:
    bool solve(vector<string> &board, int row, int n, int startRow) {
        if (row == n) {
            return solve(board, 0, n, startRow); // Solution found
        }

        // Skip the manually placed queen's row
        if (row == startRow) {
            return true;
        }

        for (int col = 0; col < n; col++) {
            if (isSafe(board, row, col, n)) {
                board[row][col] = 'Q';
                if (solve(board, row + 1, n, startRow)) return true;
                board[row][col] = '.'; // Backtrack
            }
        }

        return false; // No valid placement found in this row
    }

    bool isSafe(const vector<string> &board, int row, int col, int n) {
        // Check all rows in this column
        for (int i = 0; i < n; i++) {
            if (board[i][col] == 'Q') return false;
        }

        // Check all columns in this row
        for (int j = 0; j < n; j++) {
            if (board[row][j] == 'Q') return false;
        }

        // Check the top-left to bottom-right diagonal
        for (int i = 0; i < n; i++) {
            int j = col - row + i;
            if (j >= 0 && j < n && board[i][j] == 'Q') return false;
        }

        // Check the top-right to bottom-left diagonal
        for (int i = 0; i < n; i++) {
            int j = col + row - i;
            if (j >= 0 && j < n && board[i][j] == 'Q') return false;
        }

        return true;
    }
};

int main() {
    int n;
    cout << "Enter the size of the board (n): ";
    cin >> n;

    Solution solution;
    while (!solution.solveNQueens(n)) {
        cout << "Try entering a new starting position.\n";
    }

    return 0;
}