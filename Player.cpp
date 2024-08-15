#include "Player.hpp"
#include <iostream>


/***************************** Player *****************************/
Player::Player(char symbol) : symbol(symbol) {}
char Player::getSymbol() const{
    return symbol;
}
void Player::show_player() const{
    std::cout << "Player '" << symbol << "' playing.\n";
}


/***************************** Human *****************************/
Human::Human(char symbol) : Player(symbol) {};

Coordinates Human::play(std::shared_ptr<GameTree>& game_tree){
    Coordinates c;
    std::cout << "Enter the tile you want to play (Ex:. 'a b' means line 'a' colunm 'b'): ";
    std::cin >> c.line >> c.column;
    return c;
    
}


/***************************** AI *****************************/
AI::AI(char symbol) : Player(symbol) {};


Coordinates AI::play(std::shared_ptr<GameTree>& game_tree){
    show_player();
    return game_tree->find_best_move();
}
