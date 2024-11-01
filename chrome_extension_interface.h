#pragma once
#include "sudoku_solver.h"
#include <cmath>

extern "C" {
    /**
     * gets a flat array which represents the board values, and returns a flat array
     * of the solved board.
     */
    int *solve_board(int *board_values, size_t board_size);

    void free_array(int *board_values);
}

/**
 * converts a flat array into a SudokuBoard object.
 */
SudokuBoard convert_int_pointer_to_board(int *board_values, size_t board_size);

/**
 * mallocs a flat array which contains the values of board and returns it.
 */
int *malloc_pointer_array_from_board(SudokuBoard &board);
