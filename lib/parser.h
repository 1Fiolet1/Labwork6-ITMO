#pragma once

struct Arguments{
    const char* departure = nullptr;
    const char* arrival = nullptr;
};

int ParserArgs(Arguments& args, int argc, char** argv);

bool IsValidDate(const char* date);