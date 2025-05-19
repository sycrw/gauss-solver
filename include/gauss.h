#pragma once
#include <vector>
void transform_matrix_to_reduced_row_echelon_form(std::vector<std::vector<double>>& matrix);
int get_soultion_amount(std::vector<std::vector<double>>& matrix, int variable_amount);
void get_single_result_vector(const std::vector<std::vector<double>>& matrix, int variable_amount);
