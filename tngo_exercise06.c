/********Prologue**********
 
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 6
 Topic: Tic Tac Toe
 FileName: tngo_exercise06.c
 Date: May 10, 2017
 Objective: usage of MultiDimensional Array
 Comments:
 
 **************************
 Acceptance Criteria:
 
 Assignment 6 is an involved assignment but not difficult. This assignment deals with implementation of the tic-tac-toe with a 4x4 grid. You may follow the algorithm in the course material for implementation.  No more screen shots now onwards, your program has to write output to an output file. The input will be read by prompting the user. Each successive board status has to be displayed after each player has played the move.
 
 I would like to see 3 outputs, one of them is a draw, the other two are each player winning. You can get best success by coding a small segment and adding more to a successful code. Coding the whole problem solution and finding it not working is not a good methodology for success.
 
 Your expected to be well commented to explain the logic. The main code will have only the major logic calling functions to do the detailed logic. Output should display the user prompts and their responses in addition to each board status change after the play.
 
 The solution will become easy if the main program is simple and calls functions for each task. Print output of tic-tac-toe after each play. Three kinds of output is expected, one is player 1 wins, player 2 wins and the third one is a draw. Preferably one output file necessary repeating the game for three times with different outcome.
 
 This assignment will get you full average credit.
 Write output to a file.
 
**************************
 */

void initializeChessBoard(char* cb_ptr);
void printChessBoard(char board[4][4]);
int verticallySameValueX(char board[4][4]);
int verticallySameValueO(char board[4][4]);
int HorizontallySameValueX(char board[4][4]);
int HorizontallySameValueO(char board[4][4]);
int diagonal_UL_LR_X(char board[4][4]);
int diagonal_UL_LR_O(char board[4][4]);
int diagonal_LL_UR_X(char board[4][4]);
int diagonal_LL_UR_O(char board[4][4]);
int allCellsAreFilled (char board[4][4]);
int checkGame(char chessBoard[4][4]);
void processGameResult(int gameResult);
void player1MakesAMove(char chessBoard[4][4]);
void player2MakesAMove(char chessBoard[4][4]);


#include <stdio.h>
FILE *pFile1;

// Main program
int main(int argc, const char * argv[]) {
    int quitGame = 0;
    pFile1 = fopen("trngo_TicTacToe_06_output.txt", "w");
    if (pFile1 != NULL) {
        do {
            printf("\n\nTic Tac Toe Game\n");
            fprintf(pFile1, "\n\nTic Tac Toe Game\n");
            char chessBoard[4][4];
            char* cb_ptr = &chessBoard[0][0];
            initializeChessBoard(cb_ptr);
            printChessBoard(chessBoard);
            int gameResult = 0;
            //continue playing while no one is winning
            while (gameResult == 0) {
                player1MakesAMove(chessBoard);
                printChessBoard(chessBoard);
                gameResult = checkGame(chessBoard);
                //if player1 wins or game is a tie
                if (gameResult != 0) {
                    processGameResult(gameResult);
                    break;
                }
                
                player2MakesAMove(chessBoard);
                printChessBoard(chessBoard);
                gameResult = checkGame(chessBoard);
                //if player2 wins or game is a tie
                if (gameResult != 0) {
                    processGameResult(gameResult);
                    break;
                }
            }
           
            printf("\nDo you want to play another game (-1 to quit; 1 to continue): ");
            fprintf(pFile1, "\nDo you want to play another game (-1 to quit; 1 to continue): ");
            scanf("%d", &quitGame);
            fprintf(pFile1, "%d\n", quitGame);
        } while (quitGame != -1);
    }
    printf("\nGood Bye.\n");
    fprintf(pFile1, "\nGood Bye.\n");
    fclose(pFile1);
}



// initilize all elements of chess board to "space"
void initializeChessBoard(char* cb_ptr) {
    for (int i = 0; i < 16; i++) {
            cb_ptr[i] = ' ';
    }
}

// print the chess board
void printChessBoard(char board[4][4]) {
    fprintf(pFile1, "     0 ");
    printf("     0 ");
    for (int i = 1; i < 4; i++) {
        fprintf(pFile1, "  %d ", i);
        printf("  %d ", i);
    }
    fprintf(pFile1, "\n");
    printf("\n");
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == 0) {
                fprintf(pFile1, " %d ", i);
                printf(" %d ", i);
            }
            fprintf(pFile1, "| %c ", board[i][j]);
            printf("| %c ", board[i][j]);
        }
        fprintf(pFile1, "|");
        fprintf(pFile1, "\n\n");
        printf("|");
        printf("\n\n");
    }
}
// **********************************************
// check for winning along y axis for Player1
int verticallySameValueX(char board[4][4]) {
    int player1Winsi = 0;
    int player1Winsj = 0;
    int player1Winsk = 0;
    int player1Winsl = 0;
    
    for (int i = 0; i < 4; i++) {
        if (board[i][0] == 'x') {
            player1Winsi += 1;
        }
        if (board[i][1] == 'x') {
            player1Winsj += 1;
        }
        if (board[i][2] == 'x') {
            player1Winsk += 1;
        }
        if (board[i][3] == 'x') {
            player1Winsl += 1;
        }
    }
    if (player1Winsi == 4 || player1Winsj == 4 || player1Winsk == 4 || player1Winsl == 4) {
        return 1;
    } else {
        return 0;
    }
}

// check for winning along y axis for Player2
int verticallySameValueO(char board[4][4]) {
    int player2Winsi = 0;
    int player2Winsj = 0;
    int player2Winsk = 0;
    int player2Winsl = 0;
    
    for (int i = 0; i < 4; i++) {
        if (board[i][0] == 'O') {
            player2Winsi += 1;
        }
        if (board[i][1] == 'O') {
            player2Winsj += 1;
        }
        if (board[i][2] == 'O') {
            player2Winsk += 1;
        }
        if (board[i][3] == 'O') {
            player2Winsl += 1;
        }
    }
    if (player2Winsi == 4 || player2Winsj == 4 || player2Winsk == 4 || player2Winsl == 4) {
        return 1;
    } else {
        return 0;
    }
}
// **********************************************
// check for winning along x axis for Player1
int HorizontallySameValueX(char board[4][4]) {
    int player1Winsi = 0;
    int player1Winsj = 0;
    int player1Winsk = 0;
    int player1Winsl = 0;
    for (int i = 0; i < 4; i++) {
        if (board[0][i] == 'x') {
            player1Winsi += 1;
        }
        if (board[1][i] == 'x') {
            player1Winsj += 1;
        }
        if (board[2][i] == 'x') {
            player1Winsk += 1;
        }
        if (board[3][i] == 'x') {
            player1Winsl += 1;
        }
    }
    if (player1Winsi == 4 || player1Winsj == 4 || player1Winsk == 4 || player1Winsl == 4) {
        return 1;
    } else {
        return 0;
    }
}
// check for winning along x axis for Player2
int HorizontallySameValueO(char board[4][4]) {
    int player2Winsi = 0;
    int player2Winsj = 0;
    int player2Winsk = 0;
    int player2Winsl = 0;
    for (int i = 0; i < 4; i++) {
        if (board[0][i] == 'O') {
            player2Winsi += 1;
        }
        if (board[1][i] == 'O') {
            player2Winsj += 1;
        }
        if (board[2][i] == 'O') {
            player2Winsk += 1;
        }
        if (board[3][i] == 'O') {
            player2Winsl += 1;
        }
    }
    if (player2Winsi == 4 || player2Winsj == 4 || player2Winsk == 4 || player2Winsl == 4) {
        return 1;
    } else {
        return 0;
    }
}

// **********************************************
// check for winning along diagonal axis for Player1
int diagonal_UL_LR_X(char board[4][4]) {
    int player1Wins = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][i] == 'x') {
            player1Wins += 1;
        }
    }
    if (player1Wins == 4) {
        return 1;
    } else {
        return 0;
    }
}
// check for winning along diagonal axis for Player2
int diagonal_UL_LR_O(char board[4][4]) {
    int player2Wins = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][i] == 'O') {
            player2Wins += 1;
        }
    }
    if (player2Wins == 4) {
        return 1;
    } else {
        return 0;
    }
}
// **********************************************
// check for winning along diagonal axis for Player1
int diagonal_LL_UR_X(char board[4][4]) {
    int player1Wins = 0;
    if (board[3][0] == 'x') {
        player1Wins += 1;
    }
    if (board[0][3] == 'x') {
        player1Wins += 1;
    }
    if (board[2][1] == 'x') {
        player1Wins += 1;
    }
    if (board[1][2] == 'x') {
        player1Wins += 1;
    }
    if (player1Wins == 4) {
        return 1;
    } else {
        return 0;
    }
}
// check for winning along diagonal axis for Player2
int diagonal_LL_UR_O(char board[4][4]) {
    int player2Wins = 0;
    if (board[3][0] == 'O') {
        player2Wins += 1;
    }
    if (board[0][3] == 'O') {
        player2Wins += 1;
    }
    if (board[2][1] == 'O') {
        player2Wins += 1;
    }
    if (board[1][2] == 'O') {
        player2Wins += 1;
    }
    if (player2Wins == 4) {
        return 1;
    } else {
        return 0;
    }
}
// **********************************************
// check if all cells are filled with data
int allCellsAreFilled (char board[4][4]) {
    int cellCounter = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != ' ') {
                ++cellCounter;
            }
        }
    }
    if (cellCounter == 16) {
        return 1;
    } else {
        return 0;
    }
    
}

//if player 1 wins (return 1)
//if player 2 wins (return 2)
//if game is tied  (return 3)
//if the game is not over (return 0)
int checkGame(char chessBoard[4][4]) {
    if (verticallySameValueX(chessBoard) || HorizontallySameValueX(chessBoard) || diagonal_UL_LR_X(chessBoard) || diagonal_LL_UR_X(chessBoard)) {
        return 1;
    } else if (verticallySameValueO(chessBoard) || HorizontallySameValueO(chessBoard) || diagonal_UL_LR_O(chessBoard) || diagonal_LL_UR_O(chessBoard)) {
        return 2;
    } else if (allCellsAreFilled(chessBoard)) {
        return 3;
    } else {
        return 0;
    }
}


// print out game result
void processGameResult(int gameResult) {
    switch (gameResult) {
        case 1:
            fprintf(pFile1, "Player1 Wins\n");
            printf("Player1 Wins\n");
            break;
        case 2:
            fprintf(pFile1, "Player2 Wins\n");
            printf("Player2 Wins\n");
            break;
        case 3:
            fprintf(pFile1, "Game is tied.\n");
            printf("Game is tied.\n");
            break;
    }
}

// Player1 makes a move "X"
void player1MakesAMove(char chessBoard[4][4]) {
    int row_location, col_location;
    fprintf(pFile1, "Player1: your turn.  Please enter location [row][column]: \n");
    printf("Player1: your turn.  Please enter location [row][column]: \n");
    fprintf(pFile1, "Row = ");
    printf("Row = ");
    scanf("%d", &row_location);
    fprintf(pFile1, "%d\n", row_location);
    fprintf(pFile1, "Col = ");
    printf("Col = ");
    scanf("%d", &col_location);
    fprintf(pFile1, "%d\n", col_location);
    while (chessBoard[row_location][col_location] == 'x' || chessBoard[row_location][col_location] == 'O' ||
           row_location <0 || row_location >3 || col_location <0 || col_location >3) {
        
        printf("Invalid index or Cell is already used.  Enter another location: \n");
        printf("Row = ");
        fprintf(pFile1, "Invalid index or Cell is already used.  Enter another location: \n");
        fprintf(pFile1, "Row = ");
        scanf("%d", &row_location);
        fprintf(pFile1, "%d", row_location);
        printf("Col = ");
        fprintf(pFile1, "Col = ");
        scanf("%d", &col_location);
        fprintf(pFile1, "%d", col_location);
    }
    chessBoard[row_location][col_location] = 'x';
}


// Player2 makes a move "O"
void player2MakesAMove(char chessBoard[4][4]) {
    int row_location, col_location;
    fprintf(pFile1, "Player2: your turn.  Please enter location [row][column]: \n");
    printf("Player2: your turn.  Please enter location [row][column]: \n");
    fprintf(pFile1, "Row = ");
    printf("Row = ");
    scanf("%d", &row_location);
    fprintf(pFile1, "%d\n", row_location);
    fprintf(pFile1, "Col = ");
    printf("Col = ");
    scanf("%d", &col_location);
    fprintf(pFile1, "%d\n", col_location);
    while (chessBoard[row_location][col_location] == 'x' || chessBoard[row_location][col_location] == 'O' ||
           row_location <0 || row_location >3 || col_location <0 || col_location >3) {
        
        printf("Invalid index or Cell is already used.  Enter another location: \n");
        printf("Row = ");
        fprintf(pFile1, "Invalid index or Cell is already used.  Enter another location: \n");
        fprintf(pFile1, "Row = ");
        scanf("%d", &row_location);
        fprintf(pFile1, "%d\n", row_location);
        printf("Col = ");
        fprintf(pFile1, "Col = ");
        scanf("%d", &col_location);
        fprintf(pFile1, "%d\n", col_location);
    }
    chessBoard[row_location][col_location] = 'O';
}

