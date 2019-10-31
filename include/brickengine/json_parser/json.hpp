#ifndef FILE_JSON_HPP
#define FILE_JSON_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "brickengine/extern/nlohmann_json.hpp"

class Json {
public:
    Json(std::ifstream& source);
    Json(nlohmann::json json);
    const std::string getString(std::string const name) const;
    int getInt(std::string const name) const;
    double getDouble(std::string const name) const;
    bool getBool(std::string const name) const;
    const std::vector<Json> getVector(std::string const name) const;
private:
    nlohmann::json external_json;
};

#endif // FILE_JSON_HPP