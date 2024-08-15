#include "GameTree.hpp"
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>

Node::Node(TicTac ptr) : ptr(ptr), visited(false) {}

std::list<std::shared_ptr<Node>>& Node::get_nodes(){
    return l;
}

TicTac Node::get_tictac(){
    return ptr;
}

void Node::add_Node(std::shared_ptr<Node> node){
    l.push_back(node);
}

void Node::set_who_will_win(int winner){
    will_win = winner;
}

int Node::get_who_will_win() const{
    return will_win;
}

void Node::set_visited(bool v){
    visited = v;
}

bool Node::is_visited() const{
    return visited;
}

int Node::convert_Winner_to_int(Winner winner) const{
    switch (winner)
    {
    case X_WON:
        return 1;
    
    case O_WON:
        return -1;
    
    case DRAW:
        return 0;

    default:
        return 2;
    }
}

void Node::find_max(){
    int ans = -1;
    for (const std::shared_ptr<Node>& ptr : l){
        ans = std::max(ans, ptr->get_who_will_win());
    }
    will_win = ans;
}

void Node::find_min(){
    int ans = 1;
    for (const std::shared_ptr<Node>& ptr : l){
        ans = std::min(ans, ptr->get_who_will_win());
    }
    will_win = ans;
}

Coordinates Node::best_play(){
    for (const std::shared_ptr<Node>& ptr : l){
        if (ptr->get_who_will_win() == will_win){ // Found the best possible state the AI can choose
            return difference_between_2_states(*ptr);
        }
    }
    return {-1, -1};
}

Coordinates Node::difference_between_2_states(Node& node){
    std::vector<std::vector<char>> curr_board = ptr.get_board();
    std::vector<std::vector<char>> next_board = node.get_tictac().get_board();
    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 3; k++){
            if (curr_board[i][k] != next_board[i][k]){
                return {i + 1, k + 1};
            }
        }
    }
    return {-1, -1};
}


GameTree::GameTree(Node first) : first(std::make_shared<Node>(first)) {
    create_tree();
    find_best_reachable_state();
    state_being_explored = this->first;
}

bool a = true;
void GameTree::create_tree(){
    // Construct the game tree (Using a BFS to construct the hole possible tree)
    std::queue<std::shared_ptr<Node>> q;
    q.push(this->first);

    while (!q.empty()){
        std::shared_ptr<Node> node = q.front();
        char ch = node->get_tictac().player_turn() == PLAYER_X ? 'X' : 'O';
        std::vector<std::vector<char>> curr_board = node->get_tictac().get_board();
        q.pop();
        Winner winner = node->get_tictac().isGameDone();
        if (winner == ON_GOING){ // Only computes new states if the current one is not terminal
            for (int i = 0; i < 3; i++){
                for (int k = 0; k < 3; k++){
                    if (curr_board[i][k] == ' '){
                        TicTac new_board(curr_board, i, k, ch);
                        std::shared_ptr<Node> new_node = std::make_shared<Node>(new_board);
                        node->add_Node(new_node);
                        q.push(new_node);

                    }
                }
            }
        } else { // Store in node who won
            node->set_who_will_win(node->convert_Winner_to_int(winner));
        }
    }
}

void GameTree::find_best_reachable_state() const{
    std::stack<std::shared_ptr<Node>> s;
    s.push(first);
    while (!s.empty()){
        bool jump = false; // Used to ensure the Post-order
        std::shared_ptr<Node> top = s.top();
        top->set_visited(true);
        
        for (const std::shared_ptr<Node>& ptr : top->get_nodes()){
            if (!ptr->is_visited()){
                s.push(ptr);
                jump = true;
                break;
            }
        }

        if (jump) continue;

        if (!top->get_nodes().empty()){ /// It is not a terminal state, so we check who will win or not from that state onwards

            // If is the 'X' player then we wants to find the state with the maximum outcome and 'O' otherwise
            switch(top->get_tictac().player_turn()){
                case PLAYER_X:
                    top->find_max();
                    break;
                case PLAYER_Y:
                    top->find_min();
                    break;
            }
        }
        s.pop();
    }
}

Coordinates GameTree::find_best_move(){
    Player_Turn pt = state_being_explored->get_tictac().player_turn();
    switch(pt){
        case PLAYER_X:
            return state_being_explored->best_play();
        case PLAYER_Y:
            return state_being_explored->best_play();
    }
}

void GameTree::update_state_being_explored(TicTac& b){
    for (const std::shared_ptr<Node>& node : state_being_explored->get_nodes()){
        if (node->get_tictac() == b){
            state_being_explored = node;
            return;
        }
    }
}

void GameTree::reset(){
    state_being_explored = first;
}