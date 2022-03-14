#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <limits>

class DailyMeteoEvent {
private:
    std::string cityName;
    int day;
    int month;
    int year;
    int julianDate;
    double maxTemp;
    double minTemp;

public:
    DailyMeteoEvent() : day(0), month(0), year(0), julianDate(0), maxTemp(0.0), minTemp(0.0) {}

    void setCityName(const std::string& name) { cityName = name; }
    void setDay(int d) { day = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }
    void setJulianDate(int jd) { julianDate = jd; }
    void setMaxTemp(double t) { maxTemp = t; }
    void setMinTemp(double t) { minTemp = t; }

    std::string getCityName() const { return cityName; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    int getJulianDate() const { return julianDate; }
    double getMaxTemp() const { return maxTemp; }
    double getMinTemp() const { return minTemp; }

    double getMeanTemp() const {
        return (maxTemp + minTemp) / 2.0;
    }
};

DailyMeteoEvent parseLine(const std::string& line) {
    DailyMeteoEvent event;
    
    std::istringstream ss(line);
    std::string dayStr, monthStr, yearStr, julianStr, maxStr, minStr;
    
    std::getline(ss, dayStr, ';');
    std::getline(ss, monthStr, ';');
    std::getline(ss, yearStr, ';');
    std::getline(ss, julianStr, ';');
    std::getline(ss, maxStr, ';');
    std::getline(ss, minStr);
    
    try {
        event.setDay(std::stoi(dayStr));
        event.setMonth(std::stoi(monthStr));
        event.setYear(std::stoi(yearStr));
        event.setJulianDate(std::stoi(julianStr));
        event.setMaxTemp(std::stod(maxStr));
        event.setMinTemp(std::stod(minStr));
    } catch (const std::exception&) {
        event.setDay(-1);
    }
    
    return event;
}

std::vector<DailyMeteoEvent> readMeteoData(const std::string& filename) {
    std::vector<DailyMeteoEvent> events;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return events;
    }
    
    std::string line;
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        if (line.empty() || !std::isdigit(line[0])) {
            continue;
        }
        DailyMeteoEvent event = parseLine(line);
        if (event.getDay() > 0) {
            events.push_back(event);
        }
    }
    
    file.close();
    return events;
}

DailyMeteoEvent findByDate(const std::vector<DailyMeteoEvent>& events, const std::string& query) {
    DailyMeteoEvent result;
    
    for (const auto& event : events) {
        std::ostringstream dateOSS;
        dateOSS << event.getDay() << "-" << event.getMonth() << "-" << event.getYear();
        
        if (dateOSS.str() == query || std::to_string(event.getJulianDate()) == query) {
            result = event;
            break;
        }
    }
    
    return result;
}

void analyzeYearlyMinMax(const std::vector<DailyMeteoEvent>& events) {
    const int startYear = 1960;
    const int numYears = 61;
    
    std::vector<double> maxTemps(numYears, -std::numeric_limits<double>::infinity());
    std::vector<double> minTemps(numYears, std::numeric_limits<double>::infinity());
    
    for (const auto& event : events) {
        int yearIndex = event.getYear() - startYear;
        if (yearIndex >= 0 && yearIndex < numYears) {
            maxTemps[yearIndex] = std::max(maxTemps[yearIndex], event.getMaxTemp());
            minTemps[yearIndex] = std::min(minTemps[yearIndex], event.getMinTemp());
        }
    }
    
    std::ofstream outFile("AbsoluteYearlyMinMax.txt");
    outFile << std::fixed << std::setprecision(2);
    outFile << "Year,MaxTemp,MinTemp" << std::endl;
    
    double absoluteMax = -std::numeric_limits<double>::infinity();
    double absoluteMin = std::numeric_limits<double>::infinity();
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Yearly Absolute Max/Min Temperatures:" << std::endl;
    
    for (int i = 0; i < numYears; ++i) {
        int year = startYear + i;
        std::cout << year << ": " << maxTemps[i] << ", " << minTemps[i] << std::endl;
        outFile << year << "," << maxTemps[i] << "," << minTemps[i] << std::endl;
        
        absoluteMax = std::max(absoluteMax, maxTemps[i]);
        absoluteMin = std::min(absoluteMin, minTemps[i]);
    }
    
    std::cout << "Absolute maximum: " << absoluteMax << std::endl;
    std::cout << "Absolute minimum: " << absoluteMin << std::endl;
    
    outFile.close();
}

void analyzeMonthlyAverages(const std::vector<DailyMeteoEvent>& events) {
    const int numMonths = 12;
    std::vector<double> sumMax(numMonths, 0.0);
    std::vector<double> sumMin(numMonths, 0.0);
    std::vector<int> count(numMonths, 0);
    
    for (const auto& event : events) {
        int monthIndex = event.getMonth() - 1;
        if (monthIndex >= 0 && monthIndex < numMonths) {
            sumMax[monthIndex] += event.getMaxTemp();
            sumMin[monthIndex] += event.getMinTemp();
            count[monthIndex]++;
        }
    }
    
    std::ofstream outFile("MonthlyAvgMinMax.txt");
    outFile << std::fixed << std::setprecision(2);
    outFile << "Month,AvgMaxTemp,AvgMinTemp" << std::endl;
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Monthly Average Temperatures:" << std::endl;
    
    for (int i = 0; i < numMonths; ++i) {
        double avgMax = (count[i] > 0) ? sumMax[i] / count[i] : 0.0;
        double avgMin = (count[i] > 0) ? sumMin[i] / count[i] : 0.0;
        
        std::cout << i + 1 << ": " << avgMax << ", " << avgMin << std::endl;
        outFile << i + 1 << "," << avgMax << "," << avgMin << std::endl;
    }
    
    outFile.close();
}

void analyzeMonthlyAbsoluteMinMax(const std::vector<DailyMeteoEvent>& events) {
    const int numMonths = 12;
    std::vector<double> absMax(numMonths, -std::numeric_limits<double>::infinity());
    std::vector<double> absMin(numMonths, std::numeric_limits<double>::infinity());
    
    for (const auto& event : events) {
        int monthIndex = event.getMonth() - 1;
        if (monthIndex >= 0 && monthIndex < numMonths) {
            absMax[monthIndex] = std::max(absMax[monthIndex], event.getMaxTemp());
            absMin[monthIndex] = std::min(absMin[monthIndex], event.getMinTemp());
        }
    }
    
    std::ofstream outFile("MonthlyAbsoluteMinMax.txt");
    outFile << std::fixed << std::setprecision(2);
    outFile << "Month,MaxTemp,MinTemp" << std::endl;
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Monthly Absolute Max/Min Temperatures:" << std::endl;
    
    for (int i = 0; i < numMonths; ++i) {
        std::cout << i + 1 << ": " << absMax[i] << ", " << absMin[i] << std::endl;
        outFile << i + 1 << "," << absMax[i] << "," << absMin[i] << std::endl;
    }
    
    outFile.close();
}

int main() {
    const std::string inputFile = "input_for_ans4.txt";
    
    std::vector<DailyMeteoEvent> events = readMeteoData(inputFile);
    
    if (events.empty()) {
        std::cerr << "No data loaded. Check input file." << std::endl;
        return 1;
    }
    
    std::cout << "Loaded " << events.size() << " weather records." << std::endl << std::endl;
    
    DailyMeteoEvent event1 = findByDate(events, "10-1-1960");
    if (event1.getDay() > 0) {
        std::cout << "Mean temperature for 10-1-1960: " << event1.getMeanTemp() << std::endl;
    }
    
    DailyMeteoEvent event2 = findByDate(events, "1");
    if (event2.getDay() > 0) {
        std::cout << "Mean temperature for Julian day 1: " << event2.getMeanTemp() << std::endl;
    }
    
    std::cout << std::endl;
    analyzeYearlyMinMax(events);
    
    std::cout << std::endl;
    analyzeMonthlyAverages(events);
    
    std::cout << std::endl;
    analyzeMonthlyAbsoluteMinMax(events);
    
    return 0;
}
