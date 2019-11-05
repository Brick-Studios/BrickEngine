#include <iostream>
#include <gtest/gtest.h>

#include <string>
#include <vector>
#include "brickengine/json/json.hpp"
#include "brickengine/json/exceptions/noValidJsonOrPathException.hpp"
#include "brickengine/json/exceptions/noPathException.hpp"

TEST(JSON_Creation, Create_JSON_object_from_path){
    try {
        std::string test_file_path = "tests/assets/test.json";
        Json test_json = Json(test_file_path, true);
        EXPECT_EQ(typeid(test_json), typeid(Json));
    } catch(...) {
        FAIL() << "Json object was not created succesfully";
    }
}

TEST(JSON_CREATION, File_not_found) {
    try {
        std::string test_file_path = "tests/assets/idonotexist.json";
        Json test_json = Json(test_file_path, true);
        FAIL() << "Json object created from non-existing file";
    } catch(NoValidJsonOrPathException& err) {
        SUCCEED();
    } catch(...) {
        FAIL() << "Wrong exception thrown";
    }
}

TEST(JSON_CREATION, Wrong_constructor_usage) {
    try {
        std::string test_file_path = "tests/assets/test.json";
        Json test_json = Json(test_file_path, false);
        FAIL() << "Json object should not be created";
    } catch(NoPathException& err) {
        SUCCEED();
    } catch(...) {
        FAIL() << "Wrong exception thrown";
    }
}

TEST(JSON_CREATION, Create_from_object) {
    try {
        std::string test_file_path = "tests/assets/test.json";
        Json test_json1 = Json(test_file_path, true);
        Json test_json2 = Json(test_json1);
        EXPECT_EQ(typeid(test_json2), typeid(Json));
    } catch(...) {
        FAIL() << "Json object was not created succesfully";
    }
}

TEST(JSON_USAGE, Get_string) {
    std::string test_file_path = "tests/assets/test.json";
    Json test_json = Json(test_file_path, true);

    EXPECT_EQ(test_json.getString("string"), "This is a string");
}

TEST(JSON_USAGE, Get_int) {
    std::string test_file_path = "tests/assets/test.json";
    Json test_json = Json(test_file_path, true);

    EXPECT_EQ(test_json.getInt("integer"), 12);
}

TEST(JSON_USAGE, Get_double) {
    std::string test_file_path = "tests/assets/test.json";
    Json test_json = Json(test_file_path, true);

    EXPECT_EQ(test_json.getDouble("double"), 1.3);
}

TEST(JSON_USAGE, Get_boolean) {
    std::string test_file_path = "tests/assets/test.json";
    Json test_json = Json(test_file_path, true);

    EXPECT_EQ(test_json.getBool("boolean"), false);
}

TEST(JSON_USAGE, Get_vector) {
    std::string test_file_path = "tests/assets/test.json";
    Json test_json = Json(test_file_path, true);

    EXPECT_EQ(typeid(test_json.getVector("vector")), typeid(std::vector<Json>));
}

TEST(JSON_USAGE, Get_vector_element) {
    std::string test_file_path = "tests/assets/test.json";
    Json test_json = Json(test_file_path, true);

    EXPECT_EQ(test_json.getVector("vector")[0].getInt("object"), 1);
}

TEST(JSON_USAGE, Get_string_vector) {
    std::string test_file_path = "tests/assets/test.json";
    Json test_json = Json(test_file_path, true);

    EXPECT_EQ(typeid(test_json.getStringVector("string_vector")), typeid(std::vector<std::string>));
}

TEST(JSON_USAGE, Get_string_vector_element) {
    std::string test_file_path = "tests/assets/test.json";
    Json test_json = Json(test_file_path, true);

    EXPECT_EQ(test_json.getStringVector("string_vector")[0], "one");
}