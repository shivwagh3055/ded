#include <iostream>
using namespace std;

char board[3][3] = { {'1','2','3'},
                     {'4','5','6'},
                     {'7','8','9'} };

void display() {
    cout << "\n";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout << " " << board[i][j] << " ";
            if(j<2) cout << "|";
        }
        if(i<2) cout << "\n-----------\n";
    }
    cout << "\n\n";
}

bool checkWin(char ch) {
    // Rows & Columns
    for(int i=0;i<3;i++){
        if(board[i][0]==ch && board[i][1]==ch && board[i][2]==ch) return true;
        if(board[0][i]==ch && board[1][i]==ch && board[2][i]==ch) return true;
    }
    // Diagonals
    if(board[0][0]==ch && board[1][1]==ch && board[2][2]==ch) return true;
    if(board[0][2]==ch && board[1][1]==ch && board[2][0]==ch) return true;

    return false;
}

bool isFull() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

void playerMove() {
    int pos;
    cout << "Enter position (1-9): ";
    cin >> pos;

    int r = (pos-1)/3;
    int c = (pos-1)%3;

    if(board[r][c]=='X' || board[r][c]=='O') {
        cout << "Invalid Move! Try again.\n";
        playerMove();
    }
    else
        board[r][c] = 'X';
}

void computerMove() {
    // Just pick the first available spot (NO MINIMAX)
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] != 'X' && board[i][j] != 'O'){
                board[i][j] = 'O';
                return;
            }
        }
    }
}

int main() {
    while(true) {
        display();
        playerMove();

        if(checkWin('X')) {
            display();
            cout << "You Win!\n";
            break;
        }
        if(isFull()) {
            display();
            cout << "It's a Draw!\n";
            break;
        }

        computerMove();

        if(checkWin('O')) {
            display();
            cout << "Computer Wins!\n";
            break;
        }
        if(isFull()) {
            display();
            cout << "It's a Draw!\n";
            break;
        }
    }
    return 0;
}
