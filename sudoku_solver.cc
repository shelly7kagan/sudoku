#include "sudoku_solver.h"

void SudokuSolver::solve_board_with_max_guesses(SudokuBoard &board,
                                                int max_guess_amount) {
  if (board.calc_status() != PROG) {
    return;
  }
  // todo: possible to add here logical steps

  SudokuBoard board_without_guesses = board;
  auto [guess_cell_r, guess_cell_c] = get_cell_indices_for_guessing();
  const std::set<int> &possible_options =
      board.get_cell_options(guess_cell_r, guess_cell_c);

  for (int allowed_guess_amount = 1; allowed_guess_amount < max_guess_amount;
       allowed_guess_amount++) {
    auto option = possible_options.begin();
    while (option != possible_options.end()) {
      board.set_cell_value(guess_cell_r, guess_cell_c, *option);
      solve_board_with_max_guesses(board, allowed_guess_amount - 1);
      if (board.calc_status() == WIN) {
        return;
      }
      // todo: I do alot of copying in here, is there a more officient way?
      if (board.calc_status() == LOSE) {
        option = board_without_guesses.erase_option(guess_cell_r, guess_cell_c,
                                                    option);
      } else {
        option++;
      }
      board = board_without_guesses;
    }
  }
  // forloop over the options and call this function with max guess amount - 1
}

std::tuple<size_t, size_t> SudokuSolver::get_cell_indices_for_guessing() {
  // todo: implement as "getting the cell which has the shortest options and
  // doesnt have value"
  size_t r, c = 0; // todo: implement
  return {r, c};
}
