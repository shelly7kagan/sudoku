#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

/**
 * enum which represents the state of the board.
 * * WIN - the board is solved correctly.
 * * LOSE - the board is invalid, there are no more legal moves that can be
 *    done.
 * * PROG - the board is not solved yet, but there are legal moves that can be
 *    done.
 */
enum STATUS_OPTION { WIN, LOSE, PROG };

/**
 * class which represents a sudoku board object.
 * a soduku board is a square in the size m_size X m_size which it's length is
 * divisible by CUBE_SIZE.
 * a cube inside a soduku board is a sub-square inside the board, in the size of
 * CUBE_SIZE X CUBE_SIZE. each cell is contained in a single cube. a board can
 * contain only one number from POSSIBLE_CELL_VALUES in each cell of it. if its
 * empty, it contains the EMPTY_CELL_SIGN. a legal board doesn't has the same
 * number twice in one of it's rows, cols or cubes.
 *
 * * EMPTY_CELL_SIGN - a number which represents that the cell hasn't been
 *    filled yet.
 * * CUBE_SIZE - a number which represents the size of each cube.
 * * POSSIBLE_CELL_VALUES - the valid numbers which can appear in a filled cell.
 * * m_size - the length of the board (hight & width)
 * * m_board_values - 2-d vector which contains the values of the filled cells.
 * * m_possible_options - 2-d vector which contains vector. in each cell, there
 *    are the numbers that can be wrriten in the cell in order to perform a
 *    legal move.
 */
class SudokuBoard {

public:
  static const int EMPTY_CELL_SIGN;
  static const size_t CUBE_SIZE;
  static const std::set<int> POSSIBLE_CELL_VALUES;

  SudokuBoard(size_t size);
  SudokuBoard(size_t size, std::vector<std::vector<int>> board_values);
  // getters
  size_t get_size() const;
  const std::vector<std::vector<int>> &get_board_values() const;
  const std::vector<std::vector<std::set<int>>> &get_possible_options() const;
  const std::set<int> &get_cell_options(size_t r, size_t c) const;
  size_t get_missing_cells_amount() const;
  // setters
  void set_cell_value(size_t r, size_t c, int val);
  // operators
  SudokuBoard &operator=(const SudokuBoard &other);
  // methods
  STATUS_OPTION calc_status() const;
  STATUS_OPTION calc_cell_status(size_t r, size_t c) const;
  void update_possible_options();
  std::set<int>::iterator erase_option(size_t r, size_t c,
                                       std::set<int>::iterator option_iter);
  bool is_empty_cell(size_t r, size_t c) const;

  friend class TestSudokuBoard;

private:
  const size_t m_size;
  std::vector<std::vector<int>> m_board_values;
  std::vector<std::vector<std::set<int>>> m_possible_options;

  /**
   * calculates which values cannot appear in a specific cell, as a result of
   * collapse with another value in the cube.
   */
  std::set<int> calc_forbidden_values_in_cube(size_t r, size_t c) const;
  /**
   * calculates which values cannot appear in a specific cell, as a result of
   * collapse with another value in the row.
   */
  std::set<int> calc_forbidden_values_in_row(size_t r, size_t c) const;
  /**
   * calculates which values cannot appear in a specific cell, as a result of
   * collapse with another value in the col.
   */
  std::set<int> calc_forbbiden_values_in_col(size_t r, size_t c) const;
  /**
   * calculates all the values that cannot appear in a specific cell.
   */
  std::set<int> calc_forbidden_values(size_t r, size_t c) const;
  void update_cell_possible_options(size_t r, size_t c);
  void set_cell_options(size_t r, size_t c, std::set<int> cell_options);
};