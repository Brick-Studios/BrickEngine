#include <string>
#include <vector>
#include <exception>

#include "brickengine/json_parser/json.hpp"
#include "brickengine/extern/nlohmann_json.hpp"
#include "brickengine/json_parser/exceptions/objectOrTypeException.hpp"

Json::Json(std::ifstream& source) {
    nlohmann::json json;
    source >> json;
    this->external_json = json;
}

Json::Json(nlohmann::json json) {
    this->external_json = json;
}

const std::string Json::getString(std::string const name) const {
    try {
        return std::string(external_json[name]);
    } catch(...) {
        throw ObjectOrTypeException("string");
    }
}

int Json::getInt(std::string const name) const {
    try {
        return int(external_json[name]);
    } catch(...) {
        throw ObjectOrTypeException("int");
    }
}

double Json::getDouble(std::string const name) const {
    try {
        return double(external_json[name]);
    } catch(...) {
        throw ObjectOrTypeException("double");
    }
}

bool Json::getBool(std::string const name) const {
    try {
        return bool(external_json[name]);
    } catch(...) {
        throw ObjectOrTypeException("bool");
    }
}

const std::vector<Json> Json::getVector(std::string const name) const {
    try {
        std::vector<Json> vector = std::vector<Json>();
        
        for(nlohmann::json part : external_json[name]) {
            vector.push_back(Json(part));
        }
        
        return vector;
    } catch(...) {
        throw ObjectOrTypeException("vector");
    }
}