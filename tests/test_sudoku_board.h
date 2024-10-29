#pragma once
#include "../sudoku_board.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <iterator>


class TestSudokuBoard {
public:
  static void print_board_values();
  static void print_possible_options();
  static void test_get_values_in_cube();
  static void test_get_values_in_row();
  static void test_get_values_in_col();
  static void test_get_forbidden_values();
  static void test_get_status();
  static void test_update_possible_options();

private:
  static void print_int_set(std::set<int> input);
};
