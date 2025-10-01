#include "json.h"
#include "parser.h"
#include "response.h"
#include <filesystem>
#include <string>
#include <iostream>

void ParseJson(const nlohmann::json& Json) {
    std::cout << "-----------------------------------------------------------------" << std::endl;
    std::cout << "Маршруты " << Json["search"]["from"]["title"] << " - " << Json["search"]["to"]["popular_title"] << std::endl;
    std::cout << "-----------------------------------------------------------------" << std::endl; 
    for (size_t i = 0; i != Json["pagination"]["total"]; ++i) {
        if (Json["segments"][i]["has_transfers"]) {
            std::cout << "Отправление " << Json["segments"][i]["departure_from"]["title"] << std::endl;
            std::cout << "Пересадка " << Json["segments"][i]["transfers"][0]["title"] << std::endl;
            std::cout << "Прибытие " << Json["segments"][i]["arrival_to"]["title"] << std::endl;
            std::cout << "Типы транспортов:";
            for (const std::string& transport : Json["segments"][i]["transport_types"]) {
                if (transport == "plane") {
                    std::cout << " Самолёт";
                } else if (transport == "train") {
                    std::cout << " Поезд";
                } else if (transport == "bus") {
                    std::cout << " Автобус";
                } else if (transport == "suburban") {
                    std::cout << " Электричка";
                }
            }
            std::cout << '\n';
            std::cout << "Время в формате: отъезд пересадка - пересадка прибытие" << std::endl;
            std::cout << std::string(Json["segments"][i]["details"][0]["departure"]).substr(0,10);
            std::cout << " " << std::string(Json["segments"][i]["details"][0]["departure"]).substr(11,8);
            std::cout << " - " << std::string(Json["segments"][i]["details"][0]["arrival"]).substr(0,10);
            std::cout << " " << std::string(Json["segments"][i]["details"][0]["arrival"]).substr(11,8);
            std::cout << '\n';
            std::cout << std::string(Json["segments"][i]["details"][2]["departure"]).substr(0,10);
            std::cout << " " << std::string(Json["segments"][i]["details"][2]["departure"]).substr(11,8);
            std::cout << " - " << std::string(Json["segments"][i]["details"][2]["arrival"]).substr(0,10);
            std::cout << " " << std::string(Json["segments"][i]["details"][2]["arrival"]).substr(11,8) << std::endl;
            std::cout << "-----------------------------------------------------------------" << std::endl;
        } else {
            std::cout << "Отправление " << Json["segments"][i]["from"]["title"] << std::endl;
            std::cout << "Прибытие " << Json["segments"][i]["to"]["title"] << std::endl;
            std::cout << "Тип транспорта ";
            if (Json["segments"][i]["thread"]["transport_type"] == "train") {
                std::cout << "Поезд" << std::endl;
            } else if (Json["segments"][i]["thread"]["transport_type"] == "bus") {
                std::cout << "Автобус" << std::endl;
            }
            std::cout << "Время отъезда " << std::string(Json["segments"][i]["departure"]).substr(0,10);
            std::cout << " " << std::string(Json["segments"][i]["departure"]).substr(11,8) << std::endl;
            std::cout << "Время прибытия " << std::string(Json["segments"][i]["arrival"]).substr(0,10);
            std::cout << " " << std::string(Json["segments"][i]["arrival"]).substr(11,8) << std::endl;
            std::cout << "-----------------------------------------------------------------" << std::endl; 
        }
    }
}

int JsonWork(const Arguments& args, bool IsDeparture) {

    const std::string filename = IsDeparture ? std::string(args.departure) : std::string(args.arrival);

    if (!std::filesystem::exists("../../cache/" + filename + ".json")) {
        cpr::Response response;
        MakeResponse(args,IsDeparture,response);
        if (response.status_code == 200) {
            nlohmann::json Json = nlohmann::json::parse(response.text);
            std::ofstream file("../../cache/" + filename + ".json");
            file << response.text;
            file.close();
            ParseJson(Json);            
        } else if (response.status_code == 400) {
            std::cout << "Bad request" << std::endl;
            return 1;
        } else if (response.status_code == 404) {
            std::cout << "Not found" << std::endl;
            return 1;
        }
    } else {
        std::fstream file("../../cache/" + filename + ".json");
        nlohmann::json Json = nlohmann::json::parse(file);
        file.close();
        ParseJson(Json);
    }
    return 0;
}