#ifndef PLAYER_H
#define PLAYER_H

class Game;
class GameTree;

#include "TicTac.hpp"
#include "Game.hpp"
#include "GameTree.hpp"

struct Coordinates {
    int line;
    int column;
};

class Player{
private:
    char symbol;
public:
    Player(char symbol);

    virtual ~Player() = default; // Virtual destructor

    char getSymbol() const;
    bool is_play_valid() const;
    void show_player() const;

    virtual Coordinates play(std::shared_ptr<GameTree>& game_tree) = 0;
};

class Human : public Player{
public:
    Human(char symbol);
    Coordinates play(std::shared_ptr<GameTree>& game_tree);
};

class AI : public Player{
public:
    AI(char symbol);
    Coordinates play(std::shared_ptr<GameTree>& game_tree);
};

#endif