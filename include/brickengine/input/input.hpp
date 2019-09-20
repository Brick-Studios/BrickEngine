#include <iostream>
#include <unordered_map>

class BrickInput {

private:
    std::unordered_map<std::string, bool> inputs;
    // sdl mapped to game
    std::unordered_map<std::string, std::string> inputMapping;
public:
    BrickInput();
    void setInputMapping(std::unordered_map<std::string, std::string>& gameInput);
    void popInput(std::string const input);
    void checkInput(std::string const input);
    void processInput();
};