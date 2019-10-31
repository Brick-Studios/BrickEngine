#include <fstream>

#include "brickengine/json_parser/json_parser.hpp"
#include "brickengine/json_parser/json.hpp"

Json JsonParser::readJson(std::string path) {
    std::ifstream source(path);
    return Json(source&);
    //Json j = Json::parse("{\"json\": true}");
}