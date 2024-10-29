
#include "sudoku_board.h"

// ------------------------------- public methods ----------------------------
const std::set<int> SudokuBoard::POSSIBLE_CELL_VALUES = {1, 2, 3, 4, 5,
                                                         6, 7, 8, 9};
const int SudokuBoard::EMPTY_CELL_SIGN = 0;
const size_t SudokuBoard::CUBE_SIZE = 3;

SudokuBoard::SudokuBoard(size_t size)
    : m_size(size),
      m_board_values(size, std::vector<int>(size, EMPTY_CELL_SIGN)),
      m_possible_options(
          size, std::vector(size, std::set<int>(POSSIBLE_CELL_VALUES))) {}

// todo: add a check if the given array is in a proper size
SudokuBoard::SudokuBoard(size_t size,
                         std::vector<std::vector<int>> board_values)
    : m_size(size), m_board_values(board_values),
      m_possible_options(
          size, std::vector(size, std::set<int>(POSSIBLE_CELL_VALUES))) {
  update_possible_options();
}

size_t SudokuBoard::get_size() const { return m_size; }

const std::vector<std::vector<int>> &SudokuBoard::get_board_values() const {
  return m_board_values;
}

const std::vector<std::vector<std::set<int>>> &
SudokuBoard::get_possible_options() const {
  return m_possible_options;
}

STATUS_OPTION SudokuBoard::calc_status() const {
  bool is_win = true;
  for (size_t i = 0; i < m_size; i++) {
    for (size_t j = 0; j < m_size; j++) {
      STATUS_OPTION cell_status = calc_cell_status(i, j);
      if (cell_status == LOSE) {
        return LOSE;
      } else if (cell_status == PROG) {
        is_win = false;
      }
    }
  }
  if (is_win) {
    return WIN;
  }
  return PROG;
}

STATUS_OPTION SudokuBoard::calc_cell_status(size_t r, size_t c) const {
  if (get_cell_options(r, c).empty()) {
    if (get_board_values()[r][c] == EMPTY_CELL_SIGN) {
      return LOSE;
    } else {
      return WIN;
    }
  }
  return PROG;
}

const std::set<int> &SudokuBoard::get_cell_options(size_t r, size_t c) const {
  return m_possible_options[r][c];
}

void SudokuBoard::set_cell_options(size_t r, size_t c,
                                   std::set<int> cell_options) {
  m_possible_options[r][c] = cell_options;
}

// todo: add a check to see if the value is in the possible options for this
// cell
void SudokuBoard::set_cell_value(size_t r, size_t c, int val) {
  m_board_values[r][c] = val;
  update_possible_options();
}

void SudokuBoard::update_possible_options() {
  for (size_t i = 0; i < m_size; i++) {
    for (size_t j = 0; j < m_size; j++) {
      update_cell_possible_options(i, j);
    }
  }
}

std::set<int>::iterator
SudokuBoard::erase_option(size_t guess_cell_r, size_t guess_cell_c,
                          std::set<int>::iterator option_iter) {
  return m_possible_options[guess_cell_r][guess_cell_c].erase(option_iter);
}

size_t SudokuBoard::get_missing_cells_amount() const {
  size_t missing_cells_amount = 0;
  for (size_t i = 0; i < m_size; i++) {
    missing_cells_amount += count(m_board_values[i].begin(),
                                  m_board_values[i].end(), EMPTY_CELL_SIGN);
  }
  return missing_cells_amount;
}

bool SudokuBoard::is_empty_cell(size_t r, size_t c) {
  return m_board_values[r][c] == EMPTY_CELL_SIGN;
}

/**
 * a copy assignment which assumes that other is in the same size of this.
 */
// todo: do I need to add more functions?
SudokuBoard &SudokuBoard::operator=(const SudokuBoard &other) {
  if (this != &other) {
    m_possible_options = other.m_possible_options;
    m_board_values = m_board_values;
  }
  return *this;
}

// int main(int argc, char const *argv[])
// {
//     return 0;
// }

// ------------------ private methods -------------------

void SudokuBoard::update_cell_possible_options(size_t r, size_t c) {
  std::set<int> current_forbidden_values = get_forbidden_values(r, c);
  std::set<int> old_possible_options = get_cell_options(r, c);
  std::set<int> new_possible_options({});
  std::set_difference(
      old_possible_options.begin(), old_possible_options.end(),
      current_forbidden_values.begin(), current_forbidden_values.end(),
      inserter(new_possible_options, new_possible_options.begin()));
  set_cell_options(r, c, new_possible_options);
}

std::set<int> SudokuBoard::get_forbidden_values_in_cube(size_t r, size_t c) {
  std::set<int> values_in_cube{};
  int cube_top_r = r - (r % CUBE_SIZE);
  int cube_left_c = c - (c % CUBE_SIZE);
  for (size_t i = cube_top_r; i < cube_top_r + CUBE_SIZE; i++) {
    for (size_t j = cube_left_c; j < cube_left_c + CUBE_SIZE; j++) {
      values_in_cube.insert(m_board_values[i][j]);
    }
  }
  values_in_cube.erase(EMPTY_CELL_SIGN);
  return values_in_cube;
}

std::set<int> SudokuBoard::get_forbidden_values_in_row(size_t r, size_t c) {
  std::set<int> values_in_row(m_board_values[r].begin(),
                              m_board_values[r].end());
  values_in_row.erase(EMPTY_CELL_SIGN);
  return values_in_row;
}

std::set<int> SudokuBoard::get_forbbiden_values_in_col(size_t r, size_t c) {
  std::set<int> values_in_col{};
  for (size_t i = 0; i < m_size; i++) {
    values_in_col.insert(m_board_values[i][c]);
  }
  values_in_col.erase(EMPTY_CELL_SIGN);
  return values_in_col;
}

std::set<int> SudokuBoard::get_forbidden_values(size_t r, size_t c) {
  std::set<int> forbidden_values = get_forbidden_values_in_row(r, c);
  forbidden_values.merge(get_forbbiden_values_in_col(r, c));
  forbidden_values.merge(get_forbidden_values_in_cube(r, c));
  return forbidden_values;
}



