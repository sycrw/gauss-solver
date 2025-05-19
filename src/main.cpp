#include <iostream>
#include "../include/userInput.hpp"
#include "../include/gauss.hpp"

int main() {
    std::cout << "Systems of linear equations Solver" << std::endl;
    std::cout << "Enter the amount of variables(x1,x2,...): ";
    int number = getInt();
    std::vector<std::vector<double> > A = getCoefficientMatrix(number);
    transform_matrix_to_reduced_row_echelon_form(A);
    int solution_amount = get_soultion_amount(A, number);
    if (solution_amount == 0) {
        std::cout << "No solution" << std::endl;
    } else if (solution_amount == 1) {
        get_single_result(A, number);
    } else if (solution_amount == 2) {
        get_inf_results(A);
    }


    return 0;
}
