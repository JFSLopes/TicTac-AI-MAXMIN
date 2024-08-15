#ifndef GAME_H
#define GAME_H

class Player;
class AI;
class Human;
struct Coordinates;

#include "TicTac.hpp"
#include "Player.hpp"
#include "GameTree.hpp"
#include <memory>

enum Game_State { MENU, PLAYING, END, CLOSE};

class Game{
private:
    TicTac board;
    Game_State state = MENU;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    Winner winner = ON_GOING;
    std::shared_ptr<GameTree> game_tree;

public:
    Game();

    void run();
    void menu();
    void playing();
    void end();
};

#endif