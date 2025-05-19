#include <iostream>
#include <vector>

namespace {
    int calculate_r(std::vector<std::vector<double> > &matrix) {
        int r = 0;
        for (int i = 0; i < matrix.size(); ++i) {
            bool isInREF = true;
            bool isPivotElementReached = false;
            for (int j = 0; i < matrix[i].size(); ++j) {
                if (!isPivotElementReached) {
                    if (matrix[i][j] != 0) {
                        isPivotElementReached = true;
                    }
                    //check that below is 0
                    bool isAllZero = true;
                    for (int k = i + 1; k < matrix.size(); ++k) {
                        if (matrix[k][j] != 0) {
                            isAllZero = false;
                            break;
                        }
                    }
                    if (!isAllZero) {
                        isInREF = false;
                        break;
                    }
                } else {
                    break; // stop after finding pivot
                }
            }
            if (isInREF) {
                ++r;
            } else {
                break; // only have all the top rows in REF
            }
        }
        return r;
    }

    int find_col_with_furthers_left_pivot_element(std::vector<std::vector<double> > &matrix, int r) {
        int col = -1;
        for (int j = 0; j < matrix[0].size(); ++j) {
            bool isAllZero = true;
            for (int i = r; i < matrix.size(); ++i) {
                if (matrix[i][j] != 0) {
                    isAllZero = false;
                    break;
                }
            }
            if (!isAllZero) {
                col = j;
                break;
            }
        }
        return col;
    }

    void create_zero_under_pivot_element(std::vector<std::vector<double> > &matrix, int pivot_row, int pivot_col) {
        //take the row of the pivot element and add a multiple of it to all rows below it so that all elements under the pivot element are 0
        //assume that all elements to the left and bottom of the pivot element are already 0(we always search for the most left element), else this would not work
        auto pivot_value = matrix[pivot_row][pivot_col];
        for (int i = pivot_row + 1; i < matrix.size(); ++i) {
            auto scalar = -matrix[i][pivot_col] / pivot_value;
            //multiple pivot row by scalar and add to row i
            if (scalar != 0) {
                for (int j = pivot_col; j < matrix[i].size(); ++j) {
                    matrix[i][j] += scalar * matrix[pivot_row][j];
                }
            }
        }
    }

    void create_zero_above_pivot_element(std::vector<std::vector<double> > &matrix, int pivot_row, int pivot_col) {
        auto pivot_value = matrix[pivot_row][pivot_col];
        for (int i = pivot_row; i > 0; --i) {
            auto scalar = -matrix[i - 1][pivot_col] / pivot_value;
            if (scalar != 0) {
                for (int j = pivot_col; j < matrix[i - 1].size(); ++j) {
                    matrix[i - 1][j] += scalar * matrix[pivot_row][j];
                }
            }
        }
    }

    void print_matrix(std::vector<std::vector<double> > &matrix) {
        std::cout << "[";
        for (size_t i = 0; i < matrix.size(); ++i) {
            std::cout << "[";
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                std::cout << matrix[i][j];
                if (j != matrix[i].size() - 1) {
                    std::cout << ",";
                }
            }
            std::cout << "]";
            if (i != matrix.size() - 1) {
                std::cout << ",\n";
            }
        }
        std::cout << "]" << std::endl;
    }

    void normalize_strong_row_echelon_form(std::vector<std::vector<double> > &matrix) {
        for (int i = 0; i < matrix.size(); ++i) {
            auto pivot_found = false;
            double scalar = 0;
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (pivot_found) {
                    matrix[i][j] *= scalar;
                } else if (matrix[i][j] != 0) {
                    pivot_found = true;
                    //pivot
                    scalar = 1 / matrix[i][j];
                    matrix[i][j] *= scalar;
                }
            }
        }
    }

    void remove_zero_lines(std::vector<std::vector<double> > &matrix) {
        for (int i = matrix.size() - 1; i > 0; --i) {
            bool isAllZero = true;
            for (int j = 0; j < matrix.size(); ++j) {
                if (matrix[i][j] != 0) {
                    isAllZero = false;
                    break;
                }
            }
            if (isAllZero) {
                matrix.pop_back();
            } else {
                break;
            }
        }
    }
}


int transform_matrix_to_reduced_row_echelon_form(std::vector<std::vector<double> > &matrix) {
    int MAX_CYCLES = 10;

    int r = calculate_r(matrix);
    int cycles = 0;
    while (r != matrix.size() && cycles <= 10) {
        r = calculate_r(matrix);
        auto col = find_col_with_furthers_left_pivot_element(matrix, r);
        if (col == -1) {
            break; // no more pivot elements
        }
        //move row with the pivot element to the r row
        if (r != col) {
            std::swap(matrix[r], matrix[col]);
        }
        //create 0 s under the pivot element
        create_zero_under_pivot_element(matrix, r, col);
        print_matrix(matrix);
        std::cout << std::endl;
        cycles++;
    }
    if (cycles == MAX_CYCLES) {
        std::cerr << "Max cycles reached" << std::endl;
        return 0;
    }
    std::cout << "In Row echelon form" << std::endl;
    // matrix is now in row echelon form -> transform to strong echelon form
    //for each pivot element, if there are none 0 s above it -> remove them
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] != 0) {
                //pivot element
                create_zero_above_pivot_element(matrix, i, j);
                print_matrix(matrix);
                std::cout << std::endl;
                break;
            }
        }
    }
    //normalize so that each pivot element is 1
    normalize_strong_row_echelon_form(matrix);
    print_matrix(matrix);
    remove_zero_lines(matrix);
    std::cout << std::endl;
    print_matrix(matrix);
    return 1;
}

//0 -> no solution
//1 -> 1 solution
//2 -> inf solutions
//matrix needs to be strong row echelon form without 0 lines
int get_soultion_amount(std::vector<std::vector<double> > &matrix, int variable_amount) {
    //check for row with only one value in the last row -> no solution
    bool unsolvable = false;
    for (int i = (matrix.size() - 1); i >= 0; --i) {
        if (matrix[i][matrix[i].size() - 1] != 0) {
            //check all further values that on is not 0
            bool found_not_zero = false;
            for (int j = matrix[i].size() - 1; j >= 0; --j) {
                if (matrix[i][j] != 0) {
                    found_not_zero = true;
                    break;
                }
            }
            if (!found_not_zero) {
                unsolvable = true;
                break;
            }
        }
    }
    if (unsolvable) return 0;
    if (matrix.size() < variable_amount) {
        //rg(matrix) < variable amount
        return 2;
    }
    return 1;
}

void get_single_result_vector(const std::vector<std::vector<double> > &matrix, int variable_amount) {
    //from the bottom most pivot element we can get the value of the first variable
    for (int i = 1; i <= variable_amount; ++i) {
        std::cout << "x" << i << ": " << matrix[i-1][matrix[i-1].size() - 1] << " ";
    }
    std::cout << std::endl;
}
