#ifndef GAME_H
#define GAME_H

#include "TicTac.hpp"
#include "Player.hpp"
#include <memory>

enum Game_State { MENU, PLAYING, END, CLOSE};

class Game{
private:
    Board board;
    Game_State state;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    Winner winner = ON_GOING;

public:
    Game();

    void run();
    void menu();
    void playing();
    void end();
};

#endif