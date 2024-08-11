#include "Player.hpp"
#include <iostream>

Player::Player(char symbol) : symbol(symbol) {}
char Player::getSymbol() const{
    return symbol;
}
void Player::show_player() const{
    std::cout << "Player '" << symbol << "' playing.\n";
}



AI::AI(char symbol) : Player(symbol) {};

Coordinates AI::play() const{
    show_player();
    Coordinates c;
    c.line = 3;
    c.column = 3;
    return c;
}



Human::Human(char symbol) : Player(symbol) {};

Coordinates Human::play() const{
    Coordinates c;
    std::cout << "Enter the tile you want to play (Ex:. 'a b' means line 'a' colunm 'b'): ";
    std::cin >> c.line >> c.column;
    return c;
    
}