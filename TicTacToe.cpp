#include "TicTacToe.h"

TicTacToe::TicTacToe() {
    board = Board();
}
void TicTacToe::start() {
    while (true) {
        board.make_move();
        if (board.any_winner()) {
            Logs::announce_winner(board.get_symbol());

        }
        else if (board.is_full()) {
            Logs::draw();
        }

    }
}
