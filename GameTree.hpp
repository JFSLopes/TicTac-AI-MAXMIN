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

    /**
     * This function check the 'will_win' from the nodes in 'l' and then return the maximum value (see assets/points.png)
     */
    void find_max();
    /**
     * This function check the 'will_win' from the nodes in 'l' and then return the minimum value (see assets/points.png)
     */
    void find_min();
    /**
     * This function uses the 'will_win' of the current node and matches it with the 'will_win' of one of the chid node from 'l'. Then returns
     * what play must be done so the current state becomes the best state reachable.
     */
    Coordinates best_play();
    Coordinates difference_between_2_states(Node& node);

    int convert_Winner_to_int(Winner winner) const;
};



class GameTree{
private:
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> state_being_explored;

public:
    GameTree(Node first);
    /**
     * This function uses a BFS to generate all possible combinations. It is not optimized, so is generating the same states.
     */
    void create_tree();
    /**
     * This function is used to fill the non terminal states with the best possible outcome if all players play perfecly.
     * To do so, uses a Post-Order so it can start from the bottom (terminal states, meaning the game ended) to the top (non terminal states).
     * Uses function from the TicTac class to find if is either 'X' (maximize) or 'O' (minimize) turn. Then stores the best possible outcome in the node parameter
     * 'will_win' so it can be used in the future to allow the AI to choose one of the best option.
     */
    void find_best_reachable_state() const; /// Will populate the 'will_win' in each node so the AI can find the best reachable state
    /**
     * This function will find the next best move from the current 'state_being_explored'
     * There are 2 option:
     *      If is 'X' turn it will choose one state with the highest value
     *      If is 'O' turn it will choose one state with the highest value
     */
    Coordinates find_best_move();
    /**
     * This function updates 'state_being_explored' so it is easier to identify the current state of the game
     * @param b Contains the current game board that is used to know what path the AI or Human choose
     */
    void update_state_being_explored(TicTac& b);
    void reset();
};

#endif