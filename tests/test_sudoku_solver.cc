#include "test_sudoku_solver.h"

void TestSudokuSolver::test_solve_board() {
  std::vector<std::vector<int>> initial_board_values(
      {std::vector<int>(
           {5, 3, SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN, 7,
            SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN}),
       std::vector<int>(
           {6, SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN, 1, 9,
            5, SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN}),
       std::vector<int>(
           {SudokuBoard::EMPTY_CELL_SIGN, 9, 8, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, 6, SudokuBoard::EMPTY_CELL_SIGN}),
       std::vector<int>(
           {8, SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, 6, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN, 3}),
       std::vector<int>(
           {4, SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN, 8,
            SudokuBoard::EMPTY_CELL_SIGN, 3, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, 1}),
       std::vector<int>(
           {7, SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, 2, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN, 6}),
       std::vector<int>(
           {SudokuBoard::EMPTY_CELL_SIGN, 6, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, 2, 8, SudokuBoard::EMPTY_CELL_SIGN}),
       std::vector<int>(
           {SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, 4, 1, 9, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, 5}),
       std::vector<int>(
           {SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN,
            SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN, 8,
            SudokuBoard::EMPTY_CELL_SIGN, SudokuBoard::EMPTY_CELL_SIGN, 7,
            9})});
  std::vector<std::vector<int>> final_board_values(
      {std::vector<int>({5, 3, 4, 6, 7, 8, 9, 1, 2}),
       std::vector<int>({6, 7, 2, 1, 9, 5, 3, 4, 8}),
       std::vector<int>({1, 9, 8, 3, 4, 2, 5, 6, 7}),
       std::vector<int>({8, 5, 9, 7, 6, 1, 4, 2, 3}),
       std::vector<int>({4, 2, 6, 8, 5, 3, 7, 9, 1}),
       std::vector<int>({7, 1, 3, 9, 2, 4, 8, 5, 6}),
       std::vector<int>({9, 6, 1, 5, 3, 7, 2, 8, 4}),
       std::vector<int>({2, 8, 7, 4, 1, 9, 6, 3, 5}),
       std::vector<int>({3, 4, 5, 2, 8, 6, 1, 7, 9})});

  SudokuBoard test_board(9, initial_board_values);
  SudokuBoard solved_board(9, final_board_values);
  std::cout << "1" << std::endl;
  SudokuSolver::solve_board(test_board);
  std::cout << "10" << std::endl;
  assert(test_board.get_board_values() == solved_board.get_board_values());
}

int main(int argc, char const *argv[])
{
    TestSudokuSolver::test_solve_board();
    std::cout << "PASSED ALL" << std::endl;
    return 0;
}
