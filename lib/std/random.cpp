#include "brickengine/std/random.hpp"

Random& Random::getInstance(){
    static Random INSTANCE;
    return INSTANCE;
}

Random::Random() {
    std::random_device device;
    std::default_random_engine dre(device());
}

int Random::getRandomInt(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(device);
}