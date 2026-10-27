#include <iostream>
using namespace std;

int N;
int board[100][100];

int dx[8] = { 2,  1, -1, -2, -2, -1,  1,  2 };
int dy[8] = { 1,  2,  2,  1, -1, -2, -2, -1 };

bool canGo(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

bool solveBasic(int x, int y, int step) {
    if (step == N * N) return true; // All squares visited!

    // Just try all 8 moves blindly
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (canGo(nx, ny)) {
            board[nx][ny] = step;
            if (solveBasic(nx, ny, step + 1)) return true;
            board[nx][ny] = -1; // Backtrack
        }
    }
    return false;
}

int main() {
    cout << "Enter Board Size (N) - Keep it 5 or lower!: ";
    cin >> N;

    int startX, startY;
    cout << "Enter Start Position (x y): ";
    cin >> startX >> startY;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = -1;

    board[startX][startY] = 0;

    if (solveBasic(startX, startY, 1)) {
        cout << "\nTour Found:\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%3d ", board[i][j]);
            }
            cout << "\n";
        }
    } else {
        cout << "No tour exists from this starting position.\n";
    }

    return 0;
}