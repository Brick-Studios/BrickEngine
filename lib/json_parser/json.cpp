#include "brickengine/json_parser/json.hpp"
#include "brickengine/extern/nlohmann_json.hpp"

#include <string>
#include <vector>

Json::Json(std::ifstream& source) {
    nlohmann::json json;
    source >> json;
    this->external_json = json;
}

Json::Json(nlohmann::json json) {
    this->external_json = json;
}

const std::string Json::getString(std::string const name) const {
    return std::string(external_json[name]);
}

int Json::getInt(std::string const name) const {
    return int(external_json[name]);
}

double Json::getDouble(std::string const name) const {
    return double(external_json[name]);
}

bool Json::getBool(std::string const name) const {
    return bool(external_json[name]);
}

const std::vector<Json> Json::getVector(std::string const name) const {
    std::vector<Json> vector = std::vector<Json>();
    
    for(nlohmann::json part : external_json[name]) {
        vector.push_back(Json(part));
    }
    
    return vector;
}