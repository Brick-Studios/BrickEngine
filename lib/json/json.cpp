#include <string>
#include <vector>
#include <exception>
#include <iomanip>

#include "brickengine/json/json.hpp"
#include "brickengine/extern/nlohmann_json.hpp"
#include "brickengine/json/exceptions/object_or_type_exception.hpp"
#include "brickengine/json/exceptions/no_path_exception.hpp"
#include "brickengine/json/exceptions/no_valid_json_or_path_exception.hpp"

Json::Json(std::string source, bool isString) {
    if(isString) {
        try {
            nlohmann::json json;
            std::ifstream(source) >> json;
            this->external_json = json;
        } catch(...) {
            throw NoValidJsonOrPathException();
        }
    } else {
        throw NoPathException();
    }
}

Json::Json(nlohmann::json source) {
    this->external_json = source;
}

Json::Json() {
    nlohmann::json json;
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

const std::vector<std::string> Json::getStringVector(std::string const name) const {
    try {
        std::vector<std::string> vector = std::vector<std::string>();
        
        for(std::string part : external_json[name]) {
            vector.push_back(part);
        }
        
        return vector;
    } catch(...) {
        throw ObjectOrTypeException("string vector");
    }
}

void Json::setString(std::string key, std::string value) {
    external_json[key] = value; 
}

void Json::setInt(std::string key, int value) {
    external_json[key] = value;
}

int Json::getIntFromObject(std::string object, std::string key) { 
    return external_json[object][key];
}

void Json::addIntToObject(std::string object, std::string key, int value) {
    external_json[object][key] = value;
}

std::ostream& operator<< (std::ostream& ostream, const Json& json) {
    // Write it pretty to output
    return ostream << std::setw(4) << json.external_json;
}