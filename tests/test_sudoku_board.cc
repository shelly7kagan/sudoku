#include "test_sudoku_board.h"

void TestSudokuBoard::print_board_values() {
  SudokuBoard test_board(9);
  for (int i = 0; i < test_board.get_size(); i++) {
    for (int j = 0; j < test_board.get_size(); j++) {
      std::cout << test_board.get_board_values()[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void TestSudokuBoard::print_possible_options() {
  SudokuBoard test_board(9);
  int board_size = test_board.get_size();

  for (int i = 0; i < board_size; i++) {
    for (int j = 0; j < board_size; j++) {
      std::set<int> possible_options = test_board.get_possible_options()[i][j];
      for (auto possible_option : possible_options) {
        std::cout << possible_option << " ";
      }
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}

void TestSudokuBoard::test_get_values_in_cube() {
  SudokuBoard test_board(9);

  std::set<int> expected_restult({});
  assert(test_board.get_forbidden_values_in_cube(0, 0) == expected_restult);

  test_board.update_cell_value(0, 1, 1);
  expected_restult.insert(1);
  assert(test_board.get_forbidden_values_in_cube(0, 0) == expected_restult);

  test_board.update_cell_value(0, 4, 2);
  assert(test_board.get_forbidden_values_in_cube(0, 0) == expected_restult);

  test_board.update_cell_value(5, 1, 3);
  assert(test_board.get_forbidden_values_in_cube(0, 0) == expected_restult);

  test_board.update_cell_value(0, 0, 4);
  expected_restult.insert(4);
  assert(test_board.get_forbidden_values_in_cube(0, 0) == expected_restult);
}

void TestSudokuBoard::test_get_values_in_row() {
  SudokuBoard test_board(9);

  std::set<int> expected_restult({});
  assert(test_board.get_forbidden_values_in_row(0, 0) == expected_restult);

  test_board.update_cell_value(0, 1, 1);
  expected_restult.insert(1);
  assert(test_board.get_forbidden_values_in_row(0, 0) == expected_restult);

  test_board.update_cell_value(0, 8, 2);
  expected_restult.insert(2);
  assert(test_board.get_forbidden_values_in_row(0, 0) == expected_restult);

  test_board.update_cell_value(5, 0, 3);
  assert(test_board.get_forbidden_values_in_row(0, 0) == expected_restult);

  test_board.update_cell_value(0, 0, 4);
  expected_restult.insert(4);
  assert(test_board.get_forbidden_values_in_row(0, 0) == expected_restult);
}

void TestSudokuBoard::test_get_values_in_col() {
  SudokuBoard test_board(9);

  std::set<int> expected_restult({});
  assert(test_board.get_forbbiden_values_in_col(0, 0) == expected_restult);

  test_board.update_cell_value(1, 0, 1);
  expected_restult.insert(1);
  assert(test_board.get_forbbiden_values_in_col(0, 0) == expected_restult);

  test_board.update_cell_value(8, 0, 2);
  expected_restult.insert(2);
  assert(test_board.get_forbbiden_values_in_col(0, 0) == expected_restult);

  test_board.update_cell_value(0, 5, 3);
  assert(test_board.get_forbbiden_values_in_col(0, 0) == expected_restult);

  test_board.update_cell_value(0, 0, 4);
  expected_restult.insert(4);
  assert(test_board.get_forbbiden_values_in_col(0, 0) == expected_restult);
}

void TestSudokuBoard::test_get_forbidden_values() {
  SudokuBoard test_board(9);

  std::set<int> expected_restult({});
  assert(test_board.get_forbidden_values(4, 2) == expected_restult);

  test_board.update_cell_value(3, 0, 1);
  expected_restult.insert(1);
  assert(test_board.get_forbidden_values(4, 2) == expected_restult);

  test_board.update_cell_value(5, 0, 2);
  expected_restult.insert(2);
  assert(test_board.get_forbidden_values(4, 2) == expected_restult);

  test_board.update_cell_value(1, 4, 3);
  assert(test_board.get_forbidden_values(4, 2) == expected_restult);

  test_board.update_cell_value(4, 6, 4);
  expected_restult.insert(4);
  assert(test_board.get_forbidden_values(4, 2) == expected_restult);

  test_board.update_cell_value(8, 2, 5);
  expected_restult.insert(5);
  assert(test_board.get_forbidden_values(4, 2) == expected_restult);
}

void TestSudokuBoard::print_int_set(std::set<int> input) {
  for (auto item : input) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

// todo: run again after writing the update function
void TestSudokuBoard::test_get_status() {
  // std::vector<std::vector<int>> win_values =
  //     std::vector({std::vector<int>({7, 8, 5, 9, 3, 1, 4, 6, 2}),
  //                  std::vector<int>({2, 4, 3, 8, 5, 6, 9, 7, 1}),
  //                  std::vector<int>({6, 9, 1, 7, 2, 4, 5, 8, 3}),
  //                  std::vector<int>({4, 5, 7, 6, 1, 2, 3, 9, 8}),
  //                  std::vector<int>({9, 6, 8, 5, 7, 3, 2, 1, 4}),
  //                  std::vector<int>({1, 3, 2, 4, 9, 8, 6, 5, 7}),
  //                  std::vector<int>({3, 7, 9, 2, 8, 5, 1, 4, 6}),
  //                  std::vector<int>({5, 2, 4, 1, 6, 7, 9, 3, 9}),
  //                  std::vector<int>({8, 1, 6, 3, 4, 9, 7, 2, 4})});
  // SudokuBoard win_test_board(9, win_values);
  // win_test_board.empty_options(); // this is for checking without the update
  //                                 // function - needs to be deleted!
  // assert(win_test_board.get_status() == WIN);

  // std::vector<std::vector<int>> loss_row_values =
  //     std::vector({std::vector<int>({7, 8, 5, 9, 3, 1, 4, 6, 2}),
  //                  std::vector<int>({2, 4, 3, 8, 5, 6, 9, 7, 1}),
  //                  std::vector<int>({6, 9, 1, 7, 2, 4, 5, 8, 3}),
  //                  std::vector<int>({4, 5, 7, 6, 1, 2, 3, 9, 8}),
  //                  std::vector<int>({9, 6, 8, 5, 7, 3, 2, 1, 4}),
  //                  std::vector<int>({1, 3, 2, 4, 9, 8, 6, 5, 7}),
  //                  std::vector<int>({3, 7, 9, 2, 8, 5, 1, 4, 6}),
  //                  std::vector<int>({5, 2, 4, 1, 6, 7, 9, 3, 9}),
  //                  std::vector<int>({8, 1, 6, 3, 4, 9, 7, 2, 4})});
}

void TestSudokuBoard::test_update_possible_options() {
  SudokuBoard test_board(9);
  std::vector<std::vector<std::set<int>>> expected_options =
      std::vector<std::vector<std::set<int>>>(
          test_board.get_possible_options());

  test_board.update_cell_value(3, 3, 1);
  for (int i = 0; i < test_board.get_size(); i++) {
    expected_options[3][i].erase(1);
  }
  for (int i = 0; i < test_board.get_size(); i++) {
    expected_options[i][3].erase(1);
  }
  for (int i = 3; i < 6; i++) {
    for (int j = 3; j < 6; j++) {
      expected_options[i][j].erase(1);
    }
  }
  assert(test_board.get_possible_options() == expected_options);

  test_board.update_cell_value(4, 5, 2);
  for (int i = 0; i < test_board.get_size(); i++) {
    expected_options[4][i].erase(2);
  }
  for (int i = 0; i < test_board.get_size(); i++) {
    expected_options[i][5].erase(2);
  }
  for (int i = 3; i < 6; i++) {
    for (int j = 3; j < 6; j++) {
      expected_options[i][j].erase(2);
    }
  }
  assert(test_board.get_possible_options() == expected_options);

  std::set<int> empty_test_expected_options({});
  test_board.update_cell_value(3, 4, 3);
  test_board.update_cell_value(3, 5, 4);
  test_board.update_cell_value(4, 3, 5);
  test_board.update_cell_value(4, 4, 6);
  test_board.update_cell_value(5, 3, 7);
  test_board.update_cell_value(5, 4, 8);
  test_board.update_cell_value(5, 5, 9);
  for (int i = 3; i < 6; i++) {
    for (int j = 3; j < 6; j++) {
      assert(test_board.get_cell_options(i, j) == empty_test_expected_options);
    }
  }
}

int main(int argc, char const *argv[]) {
  // TestSudokuBoard::print_board_values();
  // TestSudokuBoard::print_possible_options();
  TestSudokuBoard::test_get_values_in_cube();
  TestSudokuBoard::test_get_values_in_row();
  TestSudokuBoard::test_get_values_in_col();
  TestSudokuBoard::test_get_forbidden_values();
  TestSudokuBoard::test_get_status();
  TestSudokuBoard::test_update_possible_options();
  std::cout << "PASSED ALL TESTS" << std::endl;
  return 0;
}
