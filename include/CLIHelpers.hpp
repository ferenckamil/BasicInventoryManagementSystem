#pragma once

#include <string>
#include <chrono>

class CLIHelpers {
public:

    static void pause(const std::string& msg = "Press Enter to continue...\n");

    static bool confirm(const std::string& question);

    static std::string askString(const std::string& prompt, bool allowEmpty = false);

    static int askInt(const std::string& prompt, int minValue = 0);

    static double askDouble(const std::string& prompt, double minValue = 0.0);

    static std::chrono::year_month_day askDate(const std::string& prompt);
};