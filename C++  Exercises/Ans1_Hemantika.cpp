#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

constexpr int MAX_ITERATIONS = 1000;

double bisectionMethod(double a, double b, double tolerance);
double func(double x);

int main() {
    std::string answer;

    do {
        double a;
        double b;
        double tolerance;

        std::cout << "Please enter the value of tolerance: " << std::endl;
        std::cin >> tolerance;
        std::cout << "Please enter the value of initial point: " << std::endl;
        std::cin >> a;
        std::cout << "Please enter the value of final point: " << std::endl;
        std::cin >> b;

        bool validInput = false;
        while (!validInput) {
            if (a >= b) {
                std::cout << "The initial point has to be smaller than the final point." << std::endl;
                std::cout << "Please enter the value of initial point again: " << std::endl;
                std::cin >> a;
                std::cout << "Please enter the value of final point again: " << std::endl;
                std::cin >> b;
                continue;
            }
            if (tolerance <= 0) {
                std::cout << "The value of tolerance should be positive. " << std::endl;
                std::cout << "Please enter the value of tolerance again: ";
                std::cin >> tolerance;
                continue;
            }
            if (func(a) * func(b) > 0) {
                std::cout << "The root doesn't lie between " << a << " and " << b << "." << std::endl;
                std::cout << "Please enter the value of initial point: " << std::endl;
                std::cin >> a;
                std::cout << "Please enter the value of final point: " << std::endl;
                std::cin >> b;
                continue;
            }
            validInput = true;
        }

        double root = bisectionMethod(a, b, tolerance);
        
        std::cout << "Do you want to try again? (type yes/no)" << std::endl;
        std::cin >> answer;

    } while (answer == "yes" || answer == "Yes" || answer == "YES");

    return 0;
}

double bisectionMethod(double a, double b, double tolerance) {
    int iterations = 0;
    double midPoint = a;

    while (iterations < MAX_ITERATIONS) {
        midPoint = (a + b) / 2.0;
        double fMid = func(midPoint);
        
        if (std::fabs(fMid) < tolerance || (b - a) / 2.0 < tolerance) {
            std::cout << std::fixed << std::setprecision(10);
            std::cout << "Root: " << midPoint << std::endl;
            std::cout << "f(root): " << fMid << std::endl;
            std::cout << "Number of iterations: " << iterations << std::endl;
            return midPoint;
        }

        if (func(a) * fMid > 0) {
            a = midPoint;
        } else {
            b = midPoint;
        }
        
        iterations++;
    }

    std::cout << "Maximum iterations reached without convergence." << std::endl;
    std::cout << "Current values: a=" << a << ", b=" << b << ", midPoint=" << midPoint << std::endl;
    return midPoint;
}

double func(double x) {
    return std::sin(x * x);
}
