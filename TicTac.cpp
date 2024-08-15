#include "TicTac.hpp"
#include <iostream>

TicTac::TicTac() : board(std::vector<std::vector<char>>(3, std::vector<char>(3, ' '))) {
    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 3; k++){
            board[i][k] = ' ';
        }
    }
}

TicTac::TicTac(std::vector<std::vector<char>>& board, int line, int col, char symbol) : board(std::vector<std::vector<char>>(3, std::vector<char>(3, ' '))){
    for (int i = 0; i < 3; i++){
        for (int k =  0; k < 3; k++){
            this->board[i][k] = board[i][k];
        }
    }
    this->board[line][col] = symbol;
}

void TicTac::reset(){
    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 3; k++){
            board[i][k] = ' ';
        }
    }
}

int TicTac::convert_symbols_int(char symbol) const{
    if (symbol == ' ') return 0;
    else if (symbol == 'X') return 1;
    else return -1;
}

std::vector<std::vector<char>>& TicTac::get_board(){
    return board;
}

void TicTac::show() const{
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

bool TicTac::operator==(const TicTac& b) const{
    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 3; k++){
            if (board[i][k] != b.board[i][k]) return false;
        }
    }
    return true;
}

Player_Turn TicTac::player_turn() const{
    int num_X = 0, num_O = 0;
    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 3; k++){
            if (board[i][k] == 'X') num_X++;
            else if (board[i][k] == 'O') num_O++;
        }
    }
    return num_X == num_O ? PLAYER_X : PLAYER_Y;
}

void TicTac::play_symbol(char symbol, int line, int col){
    board[line - 1][col - 1] = symbol;
}

bool TicTac::is_tile_valid(int line, int col) const{
    return (board[line - 1][col - 1] == ' ');
}

/**
 * The char 'O' will receive a negative value of 1, 'X' will be equal to 1 and ' ' will be 0. This allows to easyly check if any line, column or diagonal is done
 */
Winner TicTac::isGameDone() const{
    for (int i = 0; i < 3; i++){
        int sum = 0;
        for (int k = 0; k < 3; k++){
            sum += convert_symbols_int(board[i][k]);
        }

        if (sum == -3) return O_WON;
        else if (sum == 3) return X_WON;
    }

    // Check if any collumn is full
    for (int i = 0; i < 3; i++){
        int sum = 0;
        for (int k = 0; k < 3; k++){
            sum += convert_symbols_int(board[k][i]);
        }
        if (sum == -3) return O_WON;
        else if (sum == 3) return X_WON;
    }

    // Check the diagonal
    int sum = 0;
    for (int i = 0; i < 3; i++){
        sum += convert_symbols_int(board[i][i]);
    }
    if (sum == -3) return O_WON;
    else if (sum == 3) return X_WON;


    // Check other diagonal
    sum = 0;
    for (int i = 0; i < 3; i++){
        sum += convert_symbols_int(board[i][2-i]);
    }
    if (sum == -3) return O_WON;
    else if (sum == 3) return X_WON;

    // Check if the game is happening
    int num_symbols = 0;
    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 3; k++){
            if (board[i][k] != ' '){ // To check how many times was played
                num_symbols++;
            }
        }
    }
    if (num_symbols != 9) return ON_GOING;

    return DRAW;
}
