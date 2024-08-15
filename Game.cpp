#include "Game.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

Game::Game() : game_tree(std::make_shared<GameTree>(GameTree(Node(board)))) {}

void Game::run(){
    while (true){
        switch (state){
            case MENU:
                menu();
                break;

            case PLAYING:
                playing();
                break;

            case END:
                end();
                break;
            
            case CLOSE:
                return;
        }
    }
}

void Game::menu(){
    std::cout << "Wanna leave? [y/n]: ";
    std::string in;
    std::cin >> in;
    if (in == "y"){
        state = CLOSE;
        return;
    }

    state = PLAYING;
    std::cout << "Wanna play against an AI? [y/n]: ";
    std::cin >> in;
    if (in == "n"){
        player1 = std::make_unique<AI>('X');
        player2 = std::make_unique<AI>('O');
        return;
    }

    std::cout << "Choose player:\n"
              << "\t1. Player X\n"
              << "\t2. Player O\n";
    std::cout << "[1..2]: ";
    int num;
    std::cin >> num;
    if (num == 1){
        player1 = std::make_unique<Human>('X');
        player2 = std::make_unique<AI>('O');
    }
    else if (num == 2) {
        player1 = std::make_unique<AI>('X');
        player2 = std::make_unique<Human>('O');
    }
}

void Game::playing(){
    board.show();
    std::cout << "\n";
    if (winner == X_WON or winner == O_WON or winner == DRAW){
        state = END;
        return;
    }

    Player_Turn pt = board.player_turn();
    Coordinates c;
    if (pt == PLAYER_X){
        while(true){
            c = player1->play(game_tree);
            if (board.is_tile_valid(c.line, c.column)) break;
            std::cout << "Invalid Tile. ";
        }
    } else {
        while(true){
            c = player2->play(game_tree);
            if (board.is_tile_valid(c.line, c.column)) break;
            std::cout << "Invalid Tile. ";
        }
    }
    // Fill the board and update the state in the game tree
    board.play_symbol(pt == PLAYER_X ? player1->getSymbol() : player2->getSymbol(), c.line, c.column);
    game_tree->update_state_being_explored(board);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // Check if the game is over
    winner = board.isGameDone();
}

void Game::end(){
    if (winner == X_WON){
        std::cout << "X Won\n";
    }
    else if (winner == O_WON){
        std::cout << "O Won\n";
    }
    else if (winner == DRAW){
        std::cout << "It was a Draw\n";
    }
    // Reset variables
    board.reset();
    game_tree->reset();
    winner = ON_GOING;
    state = MENU;

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}