#include "CLIHelpers.hpp"

#include <iostream>

void CLIHelpers::pause(const std::string& msg) {
    std::cout << msg;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

bool CLIHelpers::confirm(const std::string& question) {
    char c;
    std::cout << question << " (y/n): ";
    std::cin >> c;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::tolower(c) == 'y';
}

std::string CLIHelpers::askString(const std::string& prompt, bool allowEmpty) {
    std::string input;
    std::cout << prompt;
    if (std::cin.peek() == '\n') 
    {
        std::cin.ignore();
    }

    std::getline(std::cin, input);

    if (!allowEmpty && input.empty()) {
        throw std::invalid_argument("Value cannot be empty");
    }
    return input;
}

int CLIHelpers::askInt(const std::string& prompt, int minValue) {
    int value;
    std::cout << prompt;
    if (!(std::cin >> value) || value < minValue) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid integer input");
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

double CLIHelpers::askDouble(const std::string& prompt, double minValue) {
    double value;
    std::cout << prompt;
    if (!(std::cin >> value) || value <= minValue) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid double input");
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

std::chrono::year_month_day CLIHelpers::askDate(const std::string& prompt) {
    std::string dateStr;
    std::cout << prompt;
    std::cin >> dateStr;
    std::istringstream ss(dateStr);

    std::chrono::year_month_day date;
    ss >> std::chrono::parse("%F", date);

    if (ss.fail() || !date.ok()) 
    {
        throw std::invalid_argument("Invalid date format (expected YYYY-MM-DD)");
    }
    return date;
}