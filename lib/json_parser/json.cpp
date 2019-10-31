#include "brickengine/json_parser/json.hpp"

Json::Json(std::string raw_json) {
    this->external_json = nlohmann::json::parse(raw_json);
}

const std::string Json::getString(std::string const name) const {
    
}