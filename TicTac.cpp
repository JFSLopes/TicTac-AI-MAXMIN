#include "TicTac.hpp"
#include <iostream>

Board::Board(){
    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 3; k++){
            board[i][k] = ' ';
        }
    }
}

void Board::show() const{
    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 3; k++){
            std::cout << board[i][k];
            if (k != 2){
                std::cout << " | ";
            } else {
                std::cout << "\n";
            }
        }
        if (i != 2) std::cout << "---------\n";
    }
}

Winner Board::isGameDone() const{
    int num_symbols = 0;
    // Check if any line is full
    for (int i = 0; i < 3; i++){
        char prev = 'z';
        for (int k = 0; k < 3; k++){

            if (board[i][k] != ' '){ // To check how many times was played
                num_symbols++;
            }

            if (prev == 'z'){
                prev = board[i][k];
            }
            else if (board[i][k] != prev){ // The line has different symbols
                break;
            }
            else if (k == 2 and prev != ' '){
                return prev == 'X' ? X_WON : O_WON;
            }
        }
    }

    // Check if any collumn is full
    for (int i = 0; i < 3; i++){
        char prev = 'z';
        for (int k = 0; k < 3; k++){
            if (prev == 'z'){
                prev = board[k][i];
            }
            else if (board[k][i] != prev){ // The line has different symbols
                break;
            }
            else if (k == 2 and prev != ' '){
                return prev == 'X' ? X_WON : O_WON;
            }
        }
    }

    return num_symbols == 9 ? DRAW : ON_GOING;
}

Player_Turn Board::player_turn() const{
    int num_X = 0, num_O = 0;
    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 3; k++){
            if (board[i][k] == 'X') num_X++;
            else if (board[i][k] == 'O') num_O++;
        }
    }
    return num_X == num_O ? PLAYER_X : PLAYER_Y;
}

void Board::play_symbol(char symbol, int line, int col){
    board[line - 1][col - 1] = symbol;
}

bool Board::is_tile_valid(int line, int col) const{
    return (board[line - 1][col - 1] == ' ');
}
