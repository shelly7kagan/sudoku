#include "user_interface.h"

const std::string INPUT_FILE_PATH = "board_input.txt";
const std::string FILE_ERR_MSG = "Error opening the input file.";
const std::string START_MSG = "the entered board is:";
const std::string PRE_SOLUTION_PRESENTATION_MSG = "the solved board is:";
const std::string NO_SOLUTION_MSG = "the board doesn't have a solution";
const char EMPTY_PRINT_SIGN = '_';
const char VERTICAL_WALL_PRINT = '|';
const char HORIZONTAL_WALL_PRINT = '-';
const char BETWEEN_CELLS_CHAR = ' ';
const size_t BETWEEN_CELLS_SIZE_FACTOR = 2;
const char BASE_INPUT_CHAR = '0';
const int FAILED = 1;
const int SUCCESS = 0;

std::optional<SudokuBoard> readBoard() {
  // TODO: manage illegal input
  std::string inputLine;
  std::ifstream inputFile(INPUT_FILE_PATH);
  inputFile >> inputLine;
  int size = inputLine.size();
  std::vector<std::vector<int>> board_values(
      size, std::vector<int>(size, SudokuBoard::EMPTY_CELL_SIGN));
  if (!inputFile.is_open()) {
    std::cerr << FILE_ERR_MSG << std::endl;
    return {};
  }
  for (size_t i = 0; i < size; i++) {
    std::transform(inputLine.begin(), inputLine.end(), board_values[i].begin(),
                   [](char c) {
                     return (c == EMPTY_PRINT_SIGN
                                 ? SudokuBoard::EMPTY_CELL_SIGN
                                 : (c - BASE_INPUT_CHAR));
                   });
    inputFile >> inputLine;
  }

  return SudokuBoard(board_values);
}

void printBoard(const SudokuBoard &board) {
  for (size_t i = 0; i < board.get_size(); i++) {
    if (i != 0 && i % SudokuBoard::CUBE_SIZE == 0) {
      std::cout << std::string(board.get_size() * BETWEEN_CELLS_SIZE_FACTOR +
                                   SudokuBoard::CUBE_SIZE,
                               HORIZONTAL_WALL_PRINT)
                << std::endl;
    }
    for (size_t j = 0; j < board.get_size(); j++) {
      if (j != 0 && j % SudokuBoard::CUBE_SIZE == 0) {
        std::cout << VERTICAL_WALL_PRINT << BETWEEN_CELLS_CHAR;
      }
      int board_value = board.get_board_values()[i][j];
      if (board_value == SudokuBoard::EMPTY_CELL_SIGN) {
        std::cout << EMPTY_PRINT_SIGN << BETWEEN_CELLS_CHAR;
      } else {
        std::cout << board_value << BETWEEN_CELLS_CHAR;
      }
    }
    std::cout << std::endl;
  }
}

int main(int argc, char const *argv[]) {
  std::optional<SudokuBoard> board = readBoard();
  if (!board.has_value()) {
    return FAILED;
  }
  std::cout << std::endl;
  std::cout << START_MSG << std::endl;
  printBoard(*board);
  std::optional<SudokuBoard> solved_board = SudokuSolver::solve_board(*board);
  std::cout << std::endl;
  if (solved_board.has_value()) {
    std::cout << std::endl << PRE_SOLUTION_PRESENTATION_MSG << std::endl;
    printBoard(*solved_board);
  } else {
    std::cout << NO_SOLUTION_MSG << std::endl;
  }
  return SUCCESS;
}
