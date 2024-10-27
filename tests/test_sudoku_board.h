#pragma
#include <vector>
#include <iostream>
#include <memory>
#include <cassert>
#include "../sudoku_board.h"

class TestSudokuBoard{
public:
    static void print_board_values();
    static void print_possible_options();
    static void test_get_values_in_cube();
    static void test_get_values_in_row();
    static void test_get_values_in_col();
    static void test_get_forbidden_values();
    static void test_get_status();

private:
    static void print_int_set(std::set<int> input);
};
