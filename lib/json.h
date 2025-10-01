#pragma once
#include "parser.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <fstream>

int JsonWork(const Arguments& args, bool IsDeparture);

void ParseJson(const nlohmann::json& Json);