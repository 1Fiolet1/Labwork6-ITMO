#include "response.h"
#include <string>
#include <iostream>
const char* CodeSPb = "c2";
const char* CodeKush = "c22921";
const char* API = "MyAPIKey";
const char* YandexUrl = "https://api.rasp.yandex.net/v3.0/search";

void MakeResponse(const Arguments& args, bool IsDeparture, cpr::Response& response) {
    response = cpr::Get(cpr::Url{YandexUrl},
                    cpr::Parameters{{"apikey",API},{"transfers","true"},
                                    {"from",IsDeparture ? CodeSPb : CodeKush},{"to",IsDeparture ? CodeKush : CodeSPb},
                                    {"format","json"},{"date",IsDeparture ? args.departure : args.arrival},
                                    {"transfers","true"}});
}