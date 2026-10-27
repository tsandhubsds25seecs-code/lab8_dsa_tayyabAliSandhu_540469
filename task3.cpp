#include <iostream>
#include <stack>
using namespace std;

int main() {
    int N;
    cout << "Enter number of disks (N): ";
    cin >> N;

    // We use 3 stacks to represent the 3 pegs. 
    // Index 0 = Peg A, Index 1 = Peg B, Index 2 = Peg C.
    stack<int> pegs[3];

    // Initialize Peg A (index 0) with disks.
    // Push largest disk first so it stays at the bottom of the stack.
    for (int d = N; d >= 1; d--) {
        pegs[0].push(d);
    }

    char pegName[3] = {'A', 'B', 'C'};
    int smallestPeg = 0; // The smallest disk starts on Peg A (index 0)
    
    int totalMoves = (1 << N) - 1; // Formula: 2^N - 1
    int moveCount = 0;

    cout << "\nSequence of Moves:\n";

    while (moveCount < totalMoves) {
        
        // ==========================================
        // STEP 1: Move the smallest disk
        // ==========================================
        int nextPeg;
        // If N is even, direction is A->C->B->A
        // If N is odd, direction is A->B->C->A
        if (N % 2 == 0) {
            nextPeg = (smallestPeg + 2) % 3; 
        } else {
            nextPeg = (smallestPeg + 1) % 3; 
        }

        // Pop from current peg and push to the next peg
        int smallDisk = pegs[smallestPeg].top();
        pegs[smallestPeg].pop();
        pegs[nextPeg].push(smallDisk);

        cout << "Move disk " << smallDisk << " from " 
             << pegName[smallestPeg] << " to " << pegName[nextPeg] << "\n";
        
        smallestPeg = nextPeg; // Update the location of the smallest disk
        moveCount++;

        if (moveCount == totalMoves) break; // Stop if we are done

        // ==========================================
        // STEP 2: Make the only other legal move
        // ==========================================
        // This move happens between the two pegs NOT holding the smallest disk.
        int p1 = (smallestPeg + 1) % 3;
        int p2 = (smallestPeg + 2) % 3;

        // Check the top disk of p1 and p2. 
        // If a peg is empty, treat its top disk as infinitely large (9999).
        int top1 = pegs[p1].empty() ? 9999 : pegs[p1].top();
        int top2 = pegs[p2].empty() ? 9999 : pegs[p2].top();

        int fromPeg, toPeg;
        
        // The legal move is moving the smaller disk onto the larger one
        if (top1 < top2) {
            fromPeg = p1;
            toPeg = p2;
        } else {
            fromPeg = p2;
            toPeg = p1;
        }

        // Execute the move
        int diskToMove = pegs[fromPeg].top();
        pegs[fromPeg].pop();
        pegs[toPeg].push(diskToMove);

        cout << "Move disk " << diskToMove << " from " 
             << pegName[fromPeg] << " to " << pegName[toPeg] << "\n";
             
        moveCount++;
    }

    cout << "\nTotal moves made: " << moveCount 
         << " (Expected: " << totalMoves << ")\n";

    return 0;
}