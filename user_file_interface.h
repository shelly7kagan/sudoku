#pragma once
#include "sudoku_solver.h"
#include <fstream>
#include <iostream>

extern const std::string INPUT_FILE_PATH;
extern const std::string FILE_ERR_MSG;
extern const std::string START_MSG;
extern const std::string PRE_SOLUTION_PRESENTATION_MSG;
extern const std::string NO_SOLUTION_MSG;
extern const char EMPTY_PRINT_SIGN;
extern const char VERTICAL_WALL_PRINT;
extern const char HORIZONTAL_WALL_PRINT;
extern const char BETWEEN_CELLS_CHAR;
extern const char BASE_INPUT_CHAR;
extern const int FAILED;
extern const int SUCCESS;

/**
 * reads input from the file INPUT_FILE_PATH, stores it inside a board and
 * returns it. the input should be in the format - legal values without spaces,
 * _ for empty space.
 */
std::optional<SudokuBoard> readBoard();
void printBoard(const SudokuBoard &board);
