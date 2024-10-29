#pragma once
#include "sudoku_board.h"
#include <tuple>

class SudokuSolver {
public:
  static SudokuBoard &solve_board(SudokuBoard &board);

private:
  static void choose_name(SudokuBoard &board, int max_guess_amount);
  static std::tuple<size_t, size_t> get_cell_indices_for_guessing();
};