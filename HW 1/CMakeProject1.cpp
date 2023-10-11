#include "CMakeProject1.h"
#include <iostream>
#include <cmath>

char solveQuadraticEquation(double a, double b, double c, double& x1, double& x2) {
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        x1 = (-b + std::sqrt(discriminant)) / (2 * a);
        x2 = (-b - std::sqrt(discriminant)) / (2 * a);
        return '2';
    }
    else if (discriminant == 0) {
        x1 = -b / (2 * a);
        return '1'; 
    }
    else {
        return '0'; 
    }
}

int main() {
    double a, b, c;
    std::cout << "ax^2 + bx + c = 0:" << std::endl;
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    std::cout << "c = ";
    std::cin >> c;

    double x1, x2;
    char numRoots = solveQuadraticEquation(a, b, c, x1, x2);
    
    switch (numRoots)
    {
        case '0':
            std::cout << "no roots" << std::endl;
        case '1':
            std::cout << "1 root: x = " << x1 << std::endl;
        case '2':
            std::cout << "2 roots: x1 = " << x1 << ", x2 = " << x2 << std::endl;
    }
}
