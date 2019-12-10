#ifndef FILE_GAME_STATE_MANAGER_HPP
#define FILE_GAME_STATE_MANAGER_HPP

#include <vector>
#include <unordered_map>
#include <memory>
#include <optional>

#include "brickengine/systems/system.hpp"
#include "brickengine/exceptions/reset_on_set_state_not_set.hpp"
#include "brickengine/exceptions/state_systems_not_set.hpp"
#include "brickengine/scenes/scene_reset_state.hpp"

template<typename State>
class GameStateManager {
public:
    using Systems = std::vector<std::unique_ptr<System>>;
    using StateSystems = std::unordered_map<State, std::unique_ptr<Systems>>;

    GameStateManager(std::unique_ptr<StateSystems> state_systems, std::unordered_map<State, SceneResetState> reset_on_set_state, State begin_state)
        : state_systems(std::move(state_systems)), reset_on_set_state(reset_on_set_state), current_state(begin_state), next_state(std::nullopt) {}

    // The actual state switch will happen in the next frame, when getSystems is called.
    void setState(State state) {
        // Check whether the state exists in the reset on set state.
        if (!reset_on_set_state.count(state))
            throw ResetOnSetStateNotSetException<State>(state);
        // Checks whether the state has systems affiliated with it.
        if (!state_systems->count(state))
            throw StateSystemsNotSet<State>(state);

        next_state = state;
    }

    std::vector<std::unique_ptr<System>>& getSystems() {
        if (next_state) {
            bool reset_systems = true;

            // The game is initialized and has a current_state.
            if((int)current_state != 0){
                // Check whether the current scene should be resetted on start.
                if(!reset_on_set_state.at(current_state).reset_on_end)
                    reset_systems = false;
            }

            if(!reset_systems)
                reset_systems = reset_on_set_state.at(*next_state).reset_on_start;

            // Reset systems
            if (reset_systems) {
                for (auto& system : *state_systems->at(*next_state)) {
                    system->reset();
                }
            }

            current_state = *next_state;
            next_state.reset();
        }
        return *state_systems->at(current_state);
    }
private:
    std::unique_ptr<StateSystems> state_systems;
    std::unordered_map<State, SceneResetState> reset_on_set_state;
    State current_state;
    std::optional<State> next_state;
};

#endif // FILE_GAME_STATE_MANAGER_HPP