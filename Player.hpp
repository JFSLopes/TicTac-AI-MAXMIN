#ifndef PLAYER_H
#define PLAYER_H

struct Coordinates {
    int line;
    int column;
};

class Player{
private:
    char symbol;
public:
    Player(char symbol);

    char getSymbol() const;
    bool is_play_valid() const;
    void show_player() const;

    virtual Coordinates play() const = 0;
};

class AI : public Player{
public:
    AI(char symbol);
    Coordinates play() const;
};

class Human : public Player{
public:
    Human(char symbol);
    Coordinates play() const;
};

#endif