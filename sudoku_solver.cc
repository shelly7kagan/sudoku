#include "sudoku_solver.h"
#include "user_file_interface.h"

std::optional<SudokuBoard> SudokuSolver::solve_board(SudokuBoard &board) {
  solve_board_with_max_guesses(board, board.get_missing_cells_amount());
  if (board.calc_status() == WIN) {
    return board;
  }
  return {};
}

void SudokuSolver::solve_board_with_max_guesses(SudokuBoard &board,
                                                int max_guess_amount) {
  if (board.calc_status() != PROG) {
    return;
  }
  // TODO: possible to add more here logical steps
  fill_trivial_cells(board);

  make_guess(board, max_guess_amount);
}

void SudokuSolver::make_guess(SudokuBoard &board, int max_guess_amount) {
  SudokuBoard board_without_guesses = board;
  auto [guess_cell_r, guess_cell_c] = get_cell_indices_for_guessing(board);
  const std::set<int> &possible_options =
      board_without_guesses.get_cell_options(guess_cell_r, guess_cell_c);

  for (int allowed_guess_amount = 1; allowed_guess_amount < max_guess_amount;
       allowed_guess_amount++) {

    auto option = possible_options.begin();
    while (option != possible_options.end()) {
      board.set_cell_value(guess_cell_r, guess_cell_c, *option);
      solve_board_with_max_guesses(board, allowed_guess_amount - 1);
      if (board.calc_status() == WIN) {
        return;
      }
      // TODO: I do alot of copying in here, is there a more officient way?
      if (board.calc_status() == LOSE) {
        option = board_without_guesses.erase_option(guess_cell_r, guess_cell_c,
                                                    option);
      } else {
        option++;
      }
      board = board_without_guesses;
    }
  }
}

std::tuple<size_t, size_t>
SudokuSolver::get_cell_indices_for_guessing(const SudokuBoard &board) {
  size_t min_options_r = 0, min_options_c = 0;
  size_t min_options_val = SudokuBoard::POSSIBLE_CELL_VALUES.size();
  for (size_t i = 0; i < board.get_size(); i++) {
    for (size_t j = 0; j < board.get_size(); j++) {
      if (board.is_empty_cell(i, j) &&
          board.get_cell_options(i, j).size() < min_options_val) {
        min_options_r = i;
        min_options_c = j;
        min_options_val = board.get_cell_options(i, j).size();
      }
    }
  }

  return {min_options_r, min_options_c};
}

void SudokuSolver::fill_trivial_cells(SudokuBoard &board) {
  for (size_t i = 0; i < board.get_size(); i++) {
    for (size_t j = 0; j < board.get_size(); j++) {
      const std::set<int> &current_cell_options = board.get_cell_options(i, j);
      if (current_cell_options.size() == 1) {
        board.set_cell_value(i, j, *current_cell_options.begin());
        i = 0;
        j = 0;
      }
    }
  }
}