#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include <cmath>

int calculateJulianDate(int day, int month, int year);

int main() {
    std::ifstream inputFile;
    inputFile.open("data.txt");
    
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file" << std::endl;
        return 1;
    }
    
    std::ofstream outputFile;
    outputFile.open("Answer3_Hemantika_datafile.csv");
    
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file" << std::endl;
        inputFile.close();
        return 1;
    }
    
    outputFile << "day(int);month(int);year(int);JulianDay(int);MaxTemp(double);MinTemp(double)" << std::endl;

    std::string line;
    std::string previousYear = "";
    
    while (std::getline(inputFile, line)) {
        if (line.empty() || !std::isdigit(line[0])) {
            continue;
        }
        
        std::istringstream lineStream(line);
        std::string dateStr;
        std::getline(lineStream, dateStr, '\t');
        
        std::istringstream dateStream(dateStr);
        std::string dayStr, monthStr, yearStr;
        std::getline(dateStream, dayStr, '-');
        std::getline(dateStream, monthStr, '-');
        std::getline(dateStream, yearStr);
        
        if (previousYear != "" && previousYear != yearStr) {
            outputFile << std::endl;
        }
        previousYear = yearStr;
        
        int day = std::stoi(dayStr);
        int month = std::stoi(monthStr);
        int year = std::stoi(yearStr);
        int julianDay = calculateJulianDate(day, month, year);
        
        std::string maxTemp, minTemp;
        std::getline(lineStream, maxTemp, '\t');
        std::getline(lineStream, minTemp);
        
        outputFile << day << ";" << month << ";" << year << ";" 
                   << julianDay << ";" << maxTemp << ";" << minTemp << std::endl;
    }

    inputFile.close();
    outputFile.close();
    
    std::cout << "Conversion complete. Output written to Answer3_Hemantika_datafile.csv" << std::endl;
    
    return 0;
}

int calculateJulianDate(int day, int month, int year) {
    if (month <= 2) {
        year -= 1;
        month += 12;
    }
    
    int A = year / 100;
    int B = A / 4;
    int C = 2 - A + B;
    int E = static_cast<int>(365.25 * (year + 4716));
    int F = static_cast<int>(30.6001 * (month + 1));
    
    int julianDate = C + day + E + F - 1524;
    
    return julianDate;
}
