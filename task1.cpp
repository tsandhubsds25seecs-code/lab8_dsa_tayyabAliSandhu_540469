#include <iostream>
using namespace std;

int n;
int grid[100][100];

int findMaxRow(int col) {
    int bestRow = 0;
    for (int r = 1; r < n; r++)
        if (grid[r][col] > grid[bestRow][col])
            bestRow = r;
    return bestRow;
}

int main() {
    cout << "Enter n: ";
    cin >> n;

    cout << "Enter the " << n << "x" << n << " grid:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    int leftCol = 0, rightCol = n - 1;
    int peakRow = -1, peakCol = -1;

    while (leftCol <= rightCol) {
        int midCol = (leftCol + rightCol) / 2;
        int row = findMaxRow(midCol);
        int value = grid[row][midCol];

        int leftVal  = (midCol > 0)     ? grid[row][midCol - 1] : -1;
        int rightVal = (midCol < n - 1) ? grid[row][midCol + 1] : -1;

        if (value >= leftVal && value >= rightVal) {
            peakRow = row; peakCol = midCol;
            break;
        }
        else if (value < leftVal) rightCol = midCol - 1;
        else                      leftCol  = midCol + 1;
    }

    if (peakRow != -1)
        cout << "Peak at (" << peakRow << ", " << peakCol
             << ") = " << grid[peakRow][peakCol] << endl;
    else
        cout << "No peak found\n";

    return 0;
}