#include <iostream>
#include <vector>
#include <limits>

using namespace std;

vector<char> board(9, ' '); 
int nodesVisitedMinimax = 0;
int nodesVisitedAlphaBeta = 0;

void drawBoard() {
    cout << endl;
    for (int i = 0; i < 3; i++) {
        cout << board[i * 3] << " | " << board[i * 3 + 1] << " | " << board[i * 3 + 2] << endl;
        if (i < 2) cout << "--+---+--" << endl;
    }
    cout << endl;
}

bool isWinner(char player) {
    vector<vector<int>> winPositions = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };
    for (auto pos : winPositions) {
        if (board[pos[0]] == player && board[pos[1]] == player && board[pos[2]] == player)
            return true;
    }
    return false;
}

bool isDraw() {
    for (char c : board) {
        if (c == ' ') return false;
    }
    return true;
}

int minimax(bool isMaximizing) {
    nodesVisitedMinimax++;

    if (isWinner('O')) return 10;
    if (isWinner('X')) return -10;
    if (isDraw()) return 0;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'O';
                int score = minimax(false);
                board[i] = ' ';
                bestScore = max(bestScore, score);
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'X';
                int score = minimax(true);
                board[i] = ' ';
                bestScore = min(bestScore, score);
            }
        }
        return bestScore;
    }
}

int minimaxAlphaBeta(bool isMaximizing, int alpha, int beta) {
    nodesVisitedAlphaBeta++;

    if (isWinner('O')) return 10;
    if (isWinner('X')) return -10;
    if (isDraw()) return 0;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'O';
                int score = minimaxAlphaBeta(false, alpha, beta);
                board[i] = ' ';
                bestScore = max(bestScore, score);
                alpha = max(alpha, bestScore);
                if (beta <= alpha) break;
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'X';
                int score = minimaxAlphaBeta(true, alpha, beta);
                board[i] = ' ';
                bestScore = min(bestScore, score);
                beta = min(beta, bestScore);
                if (beta <= alpha) break;
            }
        }
        return bestScore;
    }
}

int findBestMoveMinimax() {
    int bestScore = numeric_limits<int>::min();
    int move = -1;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = 'O';
            int score = minimax(false);
            board[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

int findBestMoveAlphaBeta() {
    int bestScore = numeric_limits<int>::min();
    int move = -1;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = 'O';
            int score = minimaxAlphaBeta(false, numeric_limits<int>::min(), numeric_limits<int>::max());
            board[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

void playGame() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    char player;
    cout << "Choose your marker (X goes first, O goes second): ";
    cin >> player;

    char ai = (player == 'X') ? 'O' : 'X';
    string method;
    cout << "Use Alpha-Beta Pruning? (yes/no): ";
    cin >> method;

    char currentPlayer = 'X';

    drawBoard();

    while (true) {
        if (currentPlayer == player) {
            int pos;
            cout << "Enter your move (0-8): ";
            cin >> pos;
            if (pos >= 0 && pos < 9 && board[pos] == ' ') {
                board[pos] = player;
                drawBoard();
                if (isWinner(player)) {
                    cout << "You win!" << endl;
                    break;
                } else if (isDraw()) {
                    cout << "It's a draw!" << endl;
                    break;
                }
                currentPlayer = ai;
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        } else {
            cout << "AI is thinking..." << endl;
            int move;
            if (method == "yes") {
                move = findBestMoveAlphaBeta();
            } else {
                move = findBestMoveMinimax();
            }
            board[move] = ai;
            drawBoard();
            if (isWinner(ai)) {
                cout << "AI wins!" << endl;
                break;
            } else if (isDraw()) {
                cout << "It's a draw!" << endl;
                break;
            }
            currentPlayer = player;
        }
    }

    cout << "\n--- Game Over ---" << endl;
    cout << "Nodes visited with Minimax: " << nodesVisitedMinimax << endl;
    cout << "Nodes visited with Alpha-Beta Pruning: " << nodesVisitedAlphaBeta << endl;
}

int main() {
    playGame();
    return 0;
}