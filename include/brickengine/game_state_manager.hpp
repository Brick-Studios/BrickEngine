#ifndef FILE_GAME_STATE_MANAGER_HPP
#define FILE_GAME_STATE_MANAGER_HPP

#include <vector>
#include <unordered_map>
#include <memory>

#include "brickengine/systems/system.hpp"

template<typename State>
class GameStateManager {
public:
    GameStateManager(std::unordered_map<State, std::unique_ptr<std::vector<System>>> state_systems,
                     std::unordered_map<State, bool> reset_on_set_state, State begin_state)
        : state_systems(state_systems), reset_on_set_state(reset_on_set_state), current_state(begin_state) {}

    void setState(State state) {
        if (reset_on_set_state.at(state)) {
            for (auto& system : *state_systems.at(state)) {
                system.reset();
            }
        }
        current_state = state;
    }
    std::vector<System>& getSystems() {
        return *state_systems.at(current_state);
    }
private:
    std::unordered_map<State, std::unique_ptr<std::vector<System>>> state_systems;
    std::unordered_map<State, bool> reset_on_set_state;
    State current_state;
};

#endif // FILE_GAME_STATE_MANAGER_HPP