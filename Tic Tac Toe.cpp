#include <iostream>
#include <string>
#include <vector>


void draw_board(std::vector<std::string> &board) {

  /**
  -----------------------
 |       |       |       |
 |   1   |   2   |   3   |
 |       |       |       |
 | --------------------  |
 |       |       |       |
 |   4   |   5   |   6   |
 |       |       |       |
 | --------------------  |
 |       |       |       |
 |   7   |   8   |   9   |
 |       |       |       |
  -----------------------
  **/
  for (auto row : board) {
    for (auto col : row) {
      std::cout << col;
    }
    std::cout << '\n';
  }

}

void toggle_player(char &current) {
  if (current == 'X') current = 'O';
  else current = 'X';
}

void update_board(char &current, std::vector<std::string> &board, int &choice,
                  std::vector<std::pair<int, int>> &choice_position, std::vector<std::string> &plays) {
  int row = choice_position[choice].first;
  int col = choice_position[choice].second;
  board[row][col] = current;
  switch (choice) {
  case 1:
    plays[0][0] = current;
    break;
  case 2:
    plays[0][1] = current;
    break;
  case 3:
    plays[0][2] = current;
    break;
  case 4:
    plays[1][0] = current;
    break;
  case 5:
    plays[1][1] = current;
    break;
  case 6:
    plays[1][2] = current;
    break;
  case 7:
    plays[2][0] = current;
    break;
  case 8:
    plays[2][1] = current;
    break;
  case 9:
    plays[2][2] = current;
    break;
  }

}

bool valid_move(int &choice, std::vector<bool> &taken) {
  return 1 <= choice && choice <= 9 && !taken[choice];
}

void handle_input(char &current, std::vector<bool> &taken, std::vector<std::string> &plays
                  ,std::vector<std::pair<int, int>> &choice_position
                  ,std::vector<std::string> &board) {
  std::cout << "Enter a number between [1, 9] (inclusive).\n";
  std::cout << "It's " << current << " turn\n";
  int choice;
  std::cin >> choice;
  while(!valid_move(choice, taken)) {
    std::cout << "Invalid choice\n";
    std::cin >> choice;
  }
  taken[choice] = true;
  update_board(current, board, choice, choice_position, plays);
  toggle_player(current);
}



std::string winner(std::vector<std::string> &plays) {
  // check rows
  std::string winner;
  for (int i = 0; i < 3; i++) {
    int cnt = 0;
    for (int j = 0; j < 3; j++) {
      if (plays[i][j] == plays[i][0])
          cnt++;
    }
    if (cnt == 3 && plays[i][0] != '.') {
      winner += plays[i][0];
      winner += " wins the game.";
      return winner;
    }
  }
  // check columns
  for (int i = 0; i < 3; i++) {
    int cnt = 0;
    for (int j = 0; j < 3; j++) {
      if (plays[j][i] == plays[0][i])
          cnt++;
    }
    if (cnt == 3 && plays[0][i] != '.') {
      winner += plays[0][i];
      winner += " wins the game.";
      return winner;
    }
  }
  // check diagonals
  if (plays[0][0] == plays[1][1] && plays[1][1] == plays[2][2] && plays[1][1] != '.') {
    winner += plays[1][1];
    winner += " wins the game";
    return winner;
  }
  if (plays[0][2] == plays[1][1] && plays[1][1] == plays[2][0] && plays[1][1] != '.') {
    winner += plays[1][1];
    winner += " wins the game";
    return winner;
  }
  return "-1"; // no winner
}
void handle_winner(std::vector<std::string> &plays, std::vector<std::string> &board,
                   std::vector<std::pair<int, int>> &choice_position);

void start_game(std::vector<std::string> &board, std::vector<std::pair<int, int>> &choice_position) {
  // initial state of the game
  char current = 'X';
  std::vector<std::string> plays(3);
  plays[0] = plays[1] = plays[2] = "...";
  std::vector<bool> taken(10);
  board = {" ------------------------", "|       |       |        |", "|   1   |   2   |   3    |",
  "|       |       |        |", " ------------------------", "|       |       |        |", "|   4   |   5   |   6    |",
  "|       |       |        |", " ------------------------", "|       |       |        |", "|   7   |   8   |   9    |",
  "|       |       |        |", " ------------------------"
  };
  while (true) {
    draw_board(board);
    handle_input(current, taken, plays, choice_position, board);
    handle_winner(plays, board, choice_position);

  }
}
void handle_winner(std::vector<std::string> &plays, std::vector<std::string> &board,
                   std::vector<std::pair<int, int>> &choice_position) {
  if (winner(plays) != "-1") {
    std::cout << winner(plays);
    std::cout << "Do you want to play another game?\n";
    std::cout << "Enter 0 to exit, 1 to continue\n";
    int choice;
    std::cin >> choice;
    if (choice == 0)
      exit(0);
    start_game(board, choice_position);
  }
}



int main() {
  std::vector<std::string> board{" ------------------------", "|       |       |        |", "|   1   |   2   |   3    |",
  "|       |       |        |", " ------------------------", "|       |       |        |", "|   4   |   5   |   6    |",
  "|       |       |        |", " ------------------------", "|       |       |        |", "|   7   |   8   |   9    |",
  "|       |       |        |", " ------------------------"
  };
  std::vector<std::pair<int, int>> choice_position(10);
  // locations of numbers on the board
  choice_position[1] = {2, 4}; 
  choice_position[2] =  {2, 12};
  choice_position[3] = {2, 20};
  choice_position[4] = {6, 4};
  choice_position[5] = {6, 12};
  choice_position[6] = {6, 20};
  choice_position[7] = {10, 4};
  choice_position[8] = {10, 12};
  choice_position[9] = {10, 20};
  start_game(board, choice_position);
  return 0;
}
