#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "response.h"
#include "json.h"
#include <iostream>
#include "parser.h"


int main(int argc, char** argv) {
    Arguments args;
    
    if (ParserArgs(args, argc, argv) == 1)
        return 1; 
    
    bool Departure = true;
    
    if (JsonWork(args,Departure) == 1)
        return 1;
    
    Departure = false;

    if (JsonWork(args,Departure) == 1)
        return 1;

    return 0;
}