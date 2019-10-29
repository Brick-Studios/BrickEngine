#ifndef FILE_JSON_PARSER_HPP
#define FILE_JSON_PARSER_HPP

#include <iostream>
#include <memory> 
#include <string>

#include "brickengine/json_parser/json.hpp"

class JsonParser {
public:
    JsonParser() = default;
    Json readJson(std::string path);
}; 

#endif // FILE_JSON_PARSER_HPP