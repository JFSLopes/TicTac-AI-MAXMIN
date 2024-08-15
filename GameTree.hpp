#ifndef GAME_TREE_H
#define GAME_TREE_H

class Player;
class AI;
class Human;
struct Coordinates;

#include <list>
#include <memory>
#include "TicTac.hpp"
#include "Player.hpp"

#define X_WILL_WIN 1
#define O_WILL_WIN -1
#define WILL_DRAW 0

class Node{
private:
    TicTac ptr;
    std::list<std::shared_ptr<Node>> l;
    bool visited;
    int will_win; /// will be used to represent what will happen on the state if played perfecly

public:
    Node(TicTac ptr);
    TicTac get_tictac();
    void add_Node(std::shared_ptr<Node> node);
    std::list<std::shared_ptr<Node>>& get_nodes();
    void set_who_will_win(int winner);
    int get_who_will_win() const;
    void set_visited(bool v);
    bool is_visited() const;

    void find_max();
    void find_min();

    Coordinates best_play();
    Coordinates difference_between_2_states(Node& node);

    int convert_Winner_to_int(Winner winner) const;
};



class GameTree{
private:
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> state_being_explred;

public:
    GameTree(Node first);
    void create_tree();
    void find_best_reachable_state() const; /// Will populate the 'will_win' in each node so the AI can find the best reachable state
    Coordinates find_best_move();
    void update_state_being_explored(TicTac& b);
    void reset();
};

#endif