#include <iostream>
using namespace std;

int N;
int board[100][100];

// The 8 possible L-shaped moves
int dx[8] = { 2,  1, -1, -2, -2, -1,  1,  2 };
int dy[8] = { 1,  2,  2,  1, -1, -2, -2, -1 };

// Check if a square is on the board and hasn't been visited yet
bool canGo(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// How many moves can the knight make FROM this square?
int countOnward(int x, int y) {
    int count = 0;
    for (int k = 0; k < 8; k++) {
        if (canGo(x + dx[k], y + dy[k])) count++;
    }
    return count;
}

bool solve(int x, int y, int step) {
    if (step == N * N) return true; // All squares visited!

    // Find the move with the SMALLEST onward count (Warnsdorff's Rule)
    int bestK = -1;
    int bestCount = 999;

    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (canGo(nx, ny)) {
            int c = countOnward(nx, ny);
            if (c < bestCount) {
                bestCount = c;
                bestK = k;
            }
        }
    }

    if (bestK == -1) return false; // Dead end

    // Try the best move
    int nx = x + dx[bestK];
    int ny = y + dy[bestK];

    board[nx][ny] = step;
    if (solve(nx, ny, step + 1)) return true;
    
    board[nx][ny] = -1; // Undo (backtrack)
    return false;
}

int main() {
    cout << "Enter Board Size (N): ";
    cin >> N;

    int startX, startY;
    cout << "Enter Start Position (x y): ";
    cin >> startX >> startY;

    // Fill board with -1 (meaning unvisited)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = -1;

    board[startX][startY] = 0; // Start position is step 0

    if (solve(startX, startY, 1)) {
        cout << "\nTour Found:\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%3d ", board[i][j]); // %3d makes it look neat
            }
            cout << "\n";
        }
    } else {
        cout << "No tour exists from this starting position.\n";
    }

    return 0;
}