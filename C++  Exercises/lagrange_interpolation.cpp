#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <iomanip>

long double inputFunction(long double p);

class LagrangeInterpolation {
private:
    std::vector<long double> xPoints;
    std::vector<long double> yPoints;

public:
    LagrangeInterpolation(const std::vector<long double>& x, const std::vector<long double>& y)
        : xPoints(x), yPoints(y) 
    {
        if (x.size() != y.size()) {
            throw std::length_error("Arrays must have the same length");
        }
        if (x.empty()) {
            throw std::invalid_argument("Arrays cannot be empty");
        }
    }

    long double evaluate(long double x) const {
        long double result = 0;
        
        for (std::size_t i = 0; i < xPoints.size(); ++i) {
            long double term = yPoints[i];
            
            for (std::size_t k = 0; k < xPoints.size(); ++k) {
                if (k != i) {
                    if (std::fabs(xPoints[i] - xPoints[k]) < 1e-12) {
                        return yPoints[i];
                    }
                    term *= (x - xPoints[k]) / (xPoints[i] - xPoints[k]);
                }
            }
            result += term;
        }
        
        return result;
    }
};

int main() {
    int N;
    std::cout << "Enter the value for N here: ";
    std::cin >> N;
    
    if (N < 1) {
        throw std::domain_error("N must be greater than 0");
    }
    
    std::vector<long double> x, y, interpX, interpY;
    
    const long double step = M_PI / 2.0;
    for (int i = 0; i <= 4; ++i) {
        long double val = -M_PI / 2.0 + i * step;
        x.push_back(val);
        y.push_back(inputFunction(val));
    }

    std::cout << "Original points:" << std::endl;
    std::cout << std::fixed << std::setprecision(10);
    for (std::size_t i = 0; i < x.size(); ++i) {
        std::cout << "x=" << x[i] << ", y=" << y[i] << std::endl;
    }
    
    LagrangeInterpolation interpolator(x, y);

    for (int i = 1; i <= N; ++i) {
        long double val = -M_PI / 2.0 + (2.0 * M_PI * i) / (N + 1);
        interpX.push_back(val);
        interpY.push_back(interpolator.evaluate(val));
    }

    std::ofstream outFile;
    outFile.open("Answer2_Hemantika_Generated_Points.csv");
    outFile << std::fixed << std::setprecision(10);
    outFile << "X,Y" << std::endl;
    
    std::cout << "\nInterpolated points:" << std::endl;
    for (std::size_t i = 0; i < interpX.size(); ++i) {
        std::cout << "x=" << interpX[i] << ", y=" << interpY[i] << std::endl;
        outFile << interpX[i] << "," << interpY[i] << std::endl;
    }
    outFile.close();
    
    return 0;
}

long double inputFunction(long double p) {
    return std::sin(p * p);
}
