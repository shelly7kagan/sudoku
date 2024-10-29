#pragma once
#include "sudoku_board.h"
#include <tuple>

class SudokuSolver {
public:
  static void solve_board(SudokuBoard &board);

private:
  static void solve_board_with_max_guesses(SudokuBoard &board,
                                           int max_guess_amount);
  static std::tuple<size_t, size_t>
  get_cell_indices_for_guessing(const SudokuBoard& board);
};