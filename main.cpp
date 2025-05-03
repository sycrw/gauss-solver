#include <iostream>

int main() {
    std::cout << "Systems of linear equations Solver" << std::endl;
    std::cout << "Enter the amount of variables(x1,x2,...): ";
    u_int number;
    std::cout << "Enter an integer: ";

    while (!(std::cin >> number)) {
        std::cout << "Invalid input. Please enter a valid integer: ";
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
    }

    std::cout << "Enter Your coefficient matrix:";

    std::vector<std::vector<double>> A;

    return 0;
}