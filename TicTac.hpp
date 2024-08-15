#ifndef TICTAC_H
#define TICTAC_H

#include <vector>

enum Winner { X_WON, DRAW, O_WON, ON_GOING };
enum Player_Turn { PLAYER_X, PLAYER_Y };

class TicTac{
private:
    std::vector<std::vector<char>> board;

    int convert_symbols_int(char symbol) const;
public:
    TicTac();
    TicTac(std::vector<std::vector<char>>& board, int line, int col, char symbol);

    std::vector<std::vector<char>>& get_board();
    void show() const;
    bool is_tile_valid(int line, int col) const;
    void play_symbol(char symbol, int line, int col);
    Player_Turn player_turn() const;
    Winner isGameDone() const;

    void reset();
    bool operator==(const TicTac& b) const;
};

#endif