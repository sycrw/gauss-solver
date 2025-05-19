#pragma once
#include <vector>
int transform_matrix_to_reduced_row_echelon_form(std::vector<std::vector<double>>& matrix);
int get_soultion_amount(std::vector<std::vector<double>>& matrix, int variable_amount);
void get_single_result(const std::vector<std::vector<double>>& matrix, int variable_amount);
void get_inf_results(const std::vector<std::vector<double>>& matrix);
