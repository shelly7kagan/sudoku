#include "chrome_extension_interface.h"

int *solve_board(int *board_values, size_t board_size) {
  SudokuBoard board = convert_int_pointer_to_board(board_values, board_size);
  SudokuSolver::solve_board(board);
  return malloc_pointer_array_from_board(board);
}

SudokuBoard convert_int_pointer_to_board(int *board_values, size_t board_size) {
  std::vector<std::vector<int>> vector_board_values(
      board_size, std::vector<int>(board_size));
  for (size_t i = 0; i < board_size; i++) {
    for (size_t j = 0; j < board_size; j++) {
      vector_board_values[i][j] = board_values[i * board_size + j];
    }
  }
  return SudokuBoard(vector_board_values);
}

int *malloc_pointer_array_from_board(SudokuBoard &board) {
  int *board_values = new int[pow(board.get_size(), 2)];
  for (size_t i = 0; i < board.get_size(); i++) {
    for (size_t j = 0; j < board.get_size(); j++) {
      board_values[i * board.get_size() + j] = board.get_board_values()[i][j];
    }
  }
  return board_values;
}

void free_array(int *board_values) { delete[] board_values; }