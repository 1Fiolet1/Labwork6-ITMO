#include "parser.h"
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>

bool IsValidDate(const char* date) {
    if (strlen(date) != 10) {
        return false;
    }

    if (date[4] != '-' || date[7] != '-') {
        return false;
    }
    char year[5], month[3], day[3];
    year[4] = '\0'; month[2] = '\0'; day[2] = '\0';
    strncpy(year,date,4); strncpy(month,date + 5,2); strncpy(day,date + 8,2);

    int int_year = std::stoi(year);
    int int_month = std::stoi(month);
    int int_day = std::stoi(day);

    bool IsLeapYear;
    if ((int_year % 4 == 0 && int_year % 100 != 0) || (int_year % 400 == 0)) {
        IsLeapYear = true;
    } else {
        IsLeapYear = false;
    }

    int DayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (IsLeapYear) {
        DayInMonth[1] = 29;
    }

    if (int_year < 0 || int_month < 1 || int_month > 12 || int_day < 1 || int_day > 31) {
        return false;
    }

    if (int_day > DayInMonth[int_month-1]) {
        return false;
    }

    return true;
}


int ParserArgs(Arguments& args, int argc, char** argv) {
    if (argc != 5) {
        std::cout << "Not valid number of arguments" << std::endl;
        return 1;
    }

    for (size_t i = 1; i < argc - 1; ++i) {
        if (strcmp(argv[i], "-departure") == 0 || strcmp(argv[i], "-dep") == 0) {
            if (IsValidDate(argv[i + 1])) {
                args.departure = argv[i + 1];
                ++i;
            } else {
                std::cout << "Not valid departure date" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-arrival") == 0 || strcmp(argv[i], "-arr") == 0) {
            if (IsValidDate(argv[i + 1])) {
                args.arrival = argv[i + 1];
                ++i;
            } else {
                std::cout << "Not valid arrival date" << std::endl;
                return 1;
            }
        } else {
            std::cout << "Unknown argument: " << argv[i] << std::endl;
            std::cout << "Use -dep -departure -arr -arrival" << std::endl;
            return 1;
        }
    }

    return 0;
}