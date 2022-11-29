#include "Board.h"

Board::Board() { Board::reset(); }

void Board::make_move() {
  draw();
  Logs::current_turn(player_symbol);
  Logs::prompt_to_play();
  int choice;
  std::cin >> choice;

  int row_index = (choice - 1) / height;
  int col_index = (choice - 1) % width;
  if (is_valid_move(row_index, col_index)) {
    update_cell(row_index, col_index);
    increase_moves();
    if (is_game_over()) {
      draw();

      if (any_winner()) {
        Logs::announce_winner(player_symbol);
      } else {
        Logs::draw();
      }
      Logs::another_game();
      std::string res;
      std::cin >> res;
      if (tolower(res[0]) == 'y') {
        reset();
        make_move();
      } else {
        exit(0);
      }
    }
  } else {
    Logs::invalid_cell();
  }
  make_move();
}

bool Board::is_full() { return moves == width * height; }

void Board::draw() {
  for (const auto &row : board) {
    for (const auto &cell : row) {
      std::cout << cell << " ";
    }
    std::cout << std::endl;
  }
}

void Board::reset() {
  width = 3;
  height = 3;
  board.assign(height, std::vector<char>(width));
  char current = '1';
  for (auto &row : board) {
    for (auto &cell : row) {
      cell = current++;
    }
  }
  difference_row = std::vector<short>(3);
  difference_col = std::vector<short>(3);
  difference_diagonal = std::vector<short>(2);
  moves = 0;
  player_symbol = 'X';
}

size_t Board::get_height() { return height; }

size_t Board::get_width() { return width; }

bool Board::is_game_over() { return Board::any_winner() || Board::is_full(); }

void Board::increase_moves() {
  moves++;
  // don't toggle player unless game is over, this will help us to announce
  // winner
  if (!is_game_over()) {
    toggle_player();
  }
}

bool Board::is_valid_move(int row, int col) {
  return !(row < 0 || row >= height || col < 0 || col >= width ||
           board[row][col] == 'X' || board[row][col] == 'O');
}

void Board::update_cell(int row, int col) {
  board[row][col] = player_symbol;
  int add = (player_symbol == 'X' ? +1 : -1);
  difference_row[row] += add;
  difference_col[col] += add;
  if (row == col) {
    difference_diagonal[0] += add;
  }
  if (row + col == height - 1) {
    difference_diagonal[1] += add;
  }
}

void Board::toggle_player() {
  player_symbol = (player_symbol == 'X' ? 'O' : 'X');
}
bool Board::any_winner() {
  for (int i = 0; i < 3; i++) {
    if (i < 2 && abs(difference_diagonal[i]) == 3) {
      return true;
    }
    if (abs(difference_row[i]) == 3 || abs(difference_col[i] == 3)) {
      return true;
    }
  }
  return false;
}
