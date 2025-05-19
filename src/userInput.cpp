#include <iostream>
#include <sstream>

int getInt() {
    int number;
    while (!(std::cin >> number)) {
        std::cout << "Invalid input. Please enter a valid integer: ";
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
    }
    std::cout << "You entered: " << number << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return number;
}

std::vector<std::vector<double>> getCoefficientMatrix(int variableAmount) {
    std::vector<std::vector<double>> matrix;
    std::cout << "Enter the coefficients for the matrix (row by row; seperated by spaces; enter to complete row; ):" << std::endl;
    while (true) {
        std::string line;
        std::getline(std::cin, line);

        if (line.empty()) {
            break;
        }
        std::vector<double> row;
        std::istringstream iss(line);
        std::string word;
        while (iss>>word) {
            try {
                double value = std::stod(word);
                row.push_back(value);
            } catch (const std::invalid_argument& e) {
                std::cout << "Invalid input. Please enter valid numbers." << std::endl;
                row.clear();
                break;
            }
        }
        //if enter break
        if (row.empty()) {
            break;
        }

        if (row.size() != variableAmount+1) {
            std::cout << "Invalid input. Please enter " << variableAmount + 21 << " numbers." << std::endl;
            row.clear();
            continue;
        }
        matrix.push_back(row);
    }
    //print matrix like [[1,2,3],\n[4,5,6]]
    std::cout << "Matrix:" << std::endl;
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
            std::cout << ","<<std::endl;
        }
    }
    std::cout << "]" << std::endl;
    return matrix;
}
