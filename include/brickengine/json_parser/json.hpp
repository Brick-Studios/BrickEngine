#ifndef FILE_JSON_HPP
#define FILE_JSON_HPP

#include <iostream>
#include <string>
#include <memory>

#include <nlohmann/json.hpp> 

class Json {
public:
    Json(std::string raw_json);
    const std::string getString(std::string const name) const;
    const int getInt(std::string const name) const;
    const std::unique_ptr<Json> getArray(std::string const name) const;
private:
    nlohmann::json external_json;
};

#endif // FILE_JSON_HPP