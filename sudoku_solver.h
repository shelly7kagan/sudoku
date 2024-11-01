#pragma once
#include "sudoku_board.h"
#include <optional>
#include <tuple>

/**
 * a tools class which can be used to solve a sudoku board.
 */
class SudokuSolver {
public:
  /**
   * gets a board and fills inplace the empty cells with values, so the board
   * will be in a WIN state. if its possible, returns the board.
   * if the board doesnt have a solution, returns an empty optional object.
   */
  static std::optional<SudokuBoard> solve_board(SudokuBoard &board);

private:
  /**
   * fills as many places as it can, subject to having less than
   * max_guess_amount cells which where filled by a guess.
   */
  static void solve_board_with_max_guesses(SudokuBoard &board,
                                           int max_guess_amount);

  /**
   * fills place by making a guess, and solves the other part of the board
   * regulary.
   */
  static void make_guess(SudokuBoard &board, int max_guess_amount);

  /**
   * returns the empty cell indices, which has the smallest options-set.
   * assumes that the board is not in a winning state.
   */
  static std::tuple<size_t, size_t>
  get_cell_indices_for_guessing(const SudokuBoard &board);

  /**
   * fills cells which have only one option
   */
  static void fill_trivial_cells(SudokuBoard &board);
};