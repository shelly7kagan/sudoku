#include "user_interface.h"

std::optional<SudokuBoard> readBoard() {
  // TODO: manage illegal input
  // TODO: remove magic numbers
  int size;
  std::string inputLine;
  std::cout << "Pls enter the board size. it should be a positive number which "
               "divides by 3."
            << std::endl;
  std::cin >> size;
  std::vector<std::vector<int>> board_values(
      size, std::vector<int>(size, SudokuBoard::EMPTY_CELL_SIGN));
  std::cout << "Reading the board from 'board_input.txt'." << std::endl;
  std::ifstream inputFile("board_input.txt");
  if (!inputFile.is_open()) {
    // todo: manage this case
    std::cerr << "Error opening the input file." << std::endl;
    return {};
  }
  for (int i = 0; i < size; i++) {
    inputFile >> inputLine;
    std::transform(inputLine.begin(), inputLine.end(), board_values[i].begin(),
                   [](char c) {
                     return (c == '_' ? SudokuBoard::EMPTY_CELL_SIGN
                                      : (c - '0'));
                   });
  }

  return SudokuBoard(board_values);
}

void printBoard(const SudokuBoard &board) {
  for (size_t i = 0; i < board.get_size(); i++) {
    if (i != 0 && i % SudokuBoard::CUBE_SIZE == 0) {
      std::cout << std::string(board.get_size() + SudokuBoard::CUBE_SIZE - 1, '-') << std::endl;

    }
    for (size_t j = 0; j < board.get_size(); j++) {
      if (j != 0 && j % SudokuBoard::CUBE_SIZE == 0) {
        std::cout << "|";
      }
      int board_value = board.get_board_values()[i][j];
      if (board_value == SudokuBoard::EMPTY_CELL_SIGN) {
        std::cout << "_";
      } else {
        std::cout << board_value;
      }
    }
    std::cout << std::endl;
  }
}

int main(int argc, char const *argv[]) {
  std::optional<SudokuBoard> board = readBoard();
  if (!board.has_value()) {
    return 1;
  }
  std::cout << std::endl;
  std::cout << "the entered board is:" << std::endl;
  printBoard(*board);
  std::optional<SudokuBoard> solved_board = SudokuSolver::solve_board(*board);
  std::cout << std::endl;
  if (solved_board.has_value()) {
    std::cout << std::endl << "the solved board is:" << std::endl;
    printBoard(*solved_board);
  } else {
    std::cout << "the board doesn't have a solution" << std::endl;
  }
  return 0;
}
