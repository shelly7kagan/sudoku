#pragma
#include <algorithm>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

enum STATUS_OPTION { WIN, LOSE, PROG };

class SudokuBoard {
private:
  const int m_size;
  std::vector<std::vector<int>> m_board_values;
  std::vector<std::vector<std::set<int>>> m_possible_options;

  std::set<int> get_forbidden_values_in_cube(int r, int c);
  std::set<int> get_forbidden_values_in_row(int r, int c);
  std::set<int> get_forbbiden_values_in_col(int r, int c);
  std::set<int> get_forbidden_values(int r, int c);
  void update_cell_possible_options(int r, int c);
  void set_cell_options(int r, int c, std::set<int> cell_options);
  void empty_options();

public:
  static const int EMPTY_CELL_SIGN;
  static const int CUBE_SIZE;
  static const std::set<int> POSSIBLE_CELL_VALUES;

  SudokuBoard(int size);
  SudokuBoard(int size, std::vector<std::vector<int>> board_values);
  int get_size() const;
  const std::vector<std::vector<int>> &get_board_values() const;
  const std::vector<std::vector<std::set<int>>> &get_possible_options() const;
  const std::set<int> &get_cell_options(int r, int c) const;
  STATUS_OPTION get_status() const;
  STATUS_OPTION get_cell_status(int r, int c) const;
  void update_cell_value(int r, int c, int val);
  void update_possible_options();

  friend class TestSudokuBoard;
};