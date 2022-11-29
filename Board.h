#pragma once
#include <vector>
#include <iostream>
namespace Logs {
    inline void announce_winner(char winner) {

        std::cout << "Game Over! " << winner << " wins the game\n";
    }

    inline void draw() {
        std::cout << "Game Over! .. Draw\n";
    }

    inline void already_chosen() {
        std::cout << "The cell is already chosen, please try again.\n";
    }
    inline void prompt_to_play() {
        std::cout
            << "Please enter a number between 1 and 9 inclusive that is not chosen\n";
    }
    inline void invalid_cell() {
        std::cout << "Invalid choice. ";
        prompt_to_play();
    }

    inline void current_turn(char player_symbol) {
        std::cout << "It's " << player_symbol << " turn\n";
    }

    inline void another_game() {
        std::cout << "Do you want to play another game? Y - N\n";
    }

};
class Board {
private:
    size_t width, height;
    // number of Xs minus number of Os, if +3 X wins, -3 O wins
    std::vector<short> difference_row;
    std::vector<short> difference_col;
    std::vector<short> difference_diagonal;
    unsigned moves;
    std::vector<std::vector<char>> board;
    char player_symbol;
public:
    Board();
    bool is_full();

    void make_move();

    void draw();
    void reset();
    size_t get_width();
    size_t get_height();
    bool is_game_over();
    void increase_moves();
    bool is_valid_move(int row, int col);

    void update_cell(int row, int col);

    void toggle_player();

    bool any_winner();

    char get_symbol() {
        return player_symbol;
    }

};
