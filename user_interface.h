#pragma once
#include "sudoku_solver.h"
#include <iostream>
#include <fstream>

std::optional<SudokuBoard> readBoard();
void printBoard(const SudokuBoard& board);

