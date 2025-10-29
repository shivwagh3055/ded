#include <iostream>
using namespace std;

char board[3][3] = {
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '}
};

void printBoard() {
    cout << "\n";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout << "[" << board[i][j] << "]";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool movesLeft() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]==' ')
                return true;
    return false;
}

int evaluate() {
    // Rows
    for(int i=0;i<3;i++){
        if(board[i][0] != ' ' && board[i][0]==board[i][1] && board[i][1]==board[i][2]){
            if(board[i][0]=='X') return 10;
            else return -10;
        }
    }

    // Columns
    for(int j=0;j<3;j++){
        if(board[0][j] != ' ' && board[0][j]==board[1][j] && board[1][j]==board[2][j]){
            if(board[0][j]=='X') return 10;
            else return -10;
        }
    }

    // Diagonals
    if(board[1][1] != ' '){
        if(board[0][0]==board[1][1] && board[1][1]==board[2][2]){
            if(board[1][1]=='X') return 10;
            else return -10;
        }
        if(board[0][2]==board[1][1] && board[1][1]==board[2][0]){
            if(board[1][1]=='X') return 10;
            else return -10;
        }
    }

    return 0; // no winner yet
}

// Forward declarations
int maxMove();
int minMove();

int maxMove() { // AI turn (X)
    int score = evaluate();
    if(score == 10 || score == -10) return score;
    if(!movesLeft()) return 0;

    int best = -1000;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' '){
                board[i][j] = 'X';
                best = max(best, minMove());
                board[i][j] = ' ';
            }
        }
    }
    return best;
}

int minMove() { // Player turn (O)
    int score = evaluate();
    if(score == 10 || score == -10) return score;
    if(!movesLeft()) return 0;

    int best = 1000;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' '){
                board[i][j] = 'O';
                best = min(best, maxMove());
                board[i][j] = ' ';
            }
        }
    }
    return best;
}

void bestMove() { // AI chooses best position
    int bestVal = -1000;
    int r = 0, c = 0;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' '){
                board[i][j]='X';
                int moveVal = minMove();
                board[i][j]=' ';

                if(moveVal > bestVal){
                    bestVal = moveVal;
                    r = i;
                    c = j;
                }
            }
        }
    }

    board[r][c] = 'X';
}

int main(){
    int r,c;

    while(true){
        printBoard();
        cout << "Your move (row col): ";
        cin >> r >> c;

        if(r<0 || r>2 || c<0 || c>2 || board[r][c] != ' '){
            cout << "Invalid move, try again!\n";
            continue;
        }

        board[r][c] = 'O';

        if(evaluate() == -10){
            printBoard();
            cout << "You Win!\n";
            break;
        }
        if(!movesLeft()){
            printBoard();
            cout << "Draw!\n";
            break;
        }

        bestMove();

        if(evaluate() == 10){
            printBoard();
            cout << "AI Wins!\n";
            break;
        }
        if(!movesLeft()){
            printBoard();
            cout << "Draw!\n";
            break;
        }
    }

    return 0;
}
