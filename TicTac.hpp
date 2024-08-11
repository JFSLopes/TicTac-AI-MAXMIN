#ifndef TICTAC_H
#define TICTAC_H

enum Winner { X_WON, DRAW, O_WON, ON_GOING };
enum Player_Turn { PLAYER_X, PLAYER_Y };

class Board{
private:
    char board[3][3];

public:
    Board();
    void show() const;
    bool is_tile_valid(int line, int col) const;
    void play_symbol(char symbol, int line, int col);
    Player_Turn player_turn() const;
    Winner isGameDone() const;
};

#endif