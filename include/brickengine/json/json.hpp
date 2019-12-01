#ifndef FILE_JSON_HPP
#define FILE_JSON_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "brickengine/extern/nlohmann_json.hpp"

class Json {
public:
    Json(std::string source, bool isString); // You cannot make a difference between a string and an external json object so we need a bool
    Json();
    const std::string getString(std::string const name) const;
    int getInt(std::string const name) const;
    double getDouble(std::string const name) const;
    bool getBool(std::string const name) const;
    const std::vector<Json> getVector(std::string const name) const;
    const std::vector<std::string> getStringVector(std::string const name) const;
    void setString(std::string key, std::string value);
    void setInt(std::string key, int value);
    int getIntFromObject(std::string object, std::string key);
    void addStringToObject(std::string object, std::string key, std::string value);
    void addIntToObject(std::string object, std::string key, int value);
    friend std::ostream& operator<< (std::ostream& ostream, const Json& json);
private:
    Json(nlohmann::json source);
    nlohmann::json external_json;
};

#endif // FILE_JSON_HPP