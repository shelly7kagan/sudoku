#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

enum STATUS_OPTION { WIN, LOSE, PROG };

/**
 *
 */
class SudokuBoard {

public:
  static const int EMPTY_CELL_SIGN;
  static const size_t CUBE_SIZE;
  static const std::set<int> POSSIBLE_CELL_VALUES;

  SudokuBoard(size_t size);
  SudokuBoard(size_t size, std::vector<std::vector<int>> board_values);
  size_t get_size() const;
  const std::vector<std::vector<int>> &get_board_values() const;
  const std::vector<std::vector<std::set<int>>> &get_possible_options() const;
  const std::set<int> &get_cell_options(size_t r, size_t c) const;
  STATUS_OPTION get_status() const;
  STATUS_OPTION get_cell_status(size_t r, size_t c) const;
  void update_cell_value(size_t r, size_t c, int val);
  void update_possible_options();

  friend class TestSudokuBoard;

private:
  const size_t m_size;
  std::vector<std::vector<int>> m_board_values;
  std::vector<std::vector<std::set<int>>> m_possible_options;

  std::set<int> get_forbidden_values_in_cube(size_t r, size_t c);
  std::set<int> get_forbidden_values_in_row(size_t r, size_t c);
  std::set<int> get_forbbiden_values_in_col(size_t r, size_t c);
  std::set<int> get_forbidden_values(size_t r, size_t c);
  void update_cell_possible_options(size_t r, size_t c);
  void set_cell_options(size_t r, size_t c, std::set<int> cell_options);
  void empty_options();
};