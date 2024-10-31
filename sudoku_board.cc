
#include "sudoku_board.h"

// constant
const std::set<int> SudokuBoard::POSSIBLE_CELL_VALUES = {1, 2, 3, 4, 5,
                                                         6, 7, 8, 9};
const int SudokuBoard::EMPTY_CELL_SIGN = 0;
const size_t SudokuBoard::CUBE_SIZE = 3;
const std::string SudokuBoard::OPTION_INVALID_ERR_MSG =
    "The givven value doesn't appear in the possible options.";
const std::string SudokuBoard::SIZE_INCOMPATIBALE_ERR_MSG =
    "The other board should be in the same size as this board.";

// constructors

SudokuBoard::SudokuBoard(size_t size)
    : m_size(size),
      m_board_values(size, std::vector<int>(size, EMPTY_CELL_SIGN)),
      m_possible_options(
          size, std::vector<std::set<int>>(size, std::set<int>(POSSIBLE_CELL_VALUES))) {}

SudokuBoard::SudokuBoard(std::vector<std::vector<int>> board_values)
    : m_size(board_values.size()), m_board_values(std::move(board_values)),
      m_possible_options(
          m_size, std::vector<std::set<int>>(m_size, std::set<int>(POSSIBLE_CELL_VALUES))) {
  empty_options_for_exiting_values();
  update_possible_options();
}

// getters

size_t SudokuBoard::get_size() const { return m_size; }

const std::vector<std::vector<int>> &SudokuBoard::get_board_values() const {
  return m_board_values;
}

const std::vector<std::vector<std::set<int>>> &
SudokuBoard::get_possible_options() const {
  return m_possible_options;
}

const std::set<int> &SudokuBoard::get_cell_options(size_t r, size_t c) const {
  return m_possible_options[r][c];
}

size_t SudokuBoard::get_missing_cells_amount() const {
  size_t missing_cells_amount = 0;
  for (size_t i = 0; i < m_size; i++) {
    missing_cells_amount += count(m_board_values[i].begin(),
                                  m_board_values[i].end(), EMPTY_CELL_SIGN);
  }
  return missing_cells_amount;
}

// setters

void SudokuBoard::set_cell_options(size_t r, size_t c,
                                   std::set<int> cell_options) {
  m_possible_options[r][c] = cell_options;
}

void SudokuBoard::set_cell_value(size_t r, size_t c, int val) {
  if (get_cell_options(r, c).count(val) <= 0) {
    throw std::invalid_argument(OPTION_INVALID_ERR_MSG);
  }
  m_board_values[r][c] = val;
  update_possible_options();
}

// operators

// TODO: do I need to add more functions (rule of 5)?
SudokuBoard &SudokuBoard::operator=(const SudokuBoard &other) {
  if (this->m_size != other.m_size) {
    throw std::invalid_argument(SIZE_INCOMPATIBALE_ERR_MSG);
  }
  if (this != &other) {
    m_possible_options = other.m_possible_options;
    m_board_values = other.m_board_values;
  }
  return *this;
}


// methods

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

bool SudokuBoard::is_empty_cell(size_t r, size_t c) const {
  return m_board_values[r][c] == EMPTY_CELL_SIGN;
}

std::set<int> SudokuBoard::calc_forbidden_values_in_cube(size_t r,
                                                         size_t c) const {
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

std::set<int> SudokuBoard::calc_forbidden_values_in_row(size_t r,
                                                        size_t c) const {
  std::set<int> values_in_row(m_board_values[r].begin(),
                              m_board_values[r].end());
  values_in_row.erase(EMPTY_CELL_SIGN);
  return values_in_row;
}

std::set<int> SudokuBoard::calc_forbbiden_values_in_col(size_t r,
                                                        size_t c) const {
  std::set<int> values_in_col{};
  for (size_t i = 0; i < m_size; i++) {
    values_in_col.insert(m_board_values[i][c]);
  }
  values_in_col.erase(EMPTY_CELL_SIGN);
  return values_in_col;
}

std::set<int> SudokuBoard::calc_forbidden_values(size_t r, size_t c) const {
  std::set<int> forbidden_values = calc_forbidden_values_in_row(r, c);
  forbidden_values.merge(calc_forbbiden_values_in_col(r, c));
  forbidden_values.merge(calc_forbidden_values_in_cube(r, c));
  return forbidden_values;
}

void SudokuBoard::update_cell_possible_options(size_t r, size_t c) {
  std::set<int> current_forbidden_values = calc_forbidden_values(r, c);
  std::set<int> old_possible_options = get_cell_options(r, c);
  std::set<int> new_possible_options({});
  std::set_difference(
      old_possible_options.begin(), old_possible_options.end(),
      current_forbidden_values.begin(), current_forbidden_values.end(),
      inserter(new_possible_options, new_possible_options.begin()));
  set_cell_options(r, c, new_possible_options);
}

void SudokuBoard::empty_options_for_exiting_values(){
  for (size_t i = 0; i < get_size(); i++)
  {
    for (size_t j = 0; j < get_size(); j++)
    {
      if (m_board_values[i][j] != EMPTY_CELL_SIGN){
        set_cell_options(i, j, std::set<int>({}));
      }
    }
    
  }
}
