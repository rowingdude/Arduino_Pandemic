#ifndef PANDEMIC_H
#define PANDEMIC_H

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class GameState {
public:
    std::vector<std::string> infections;
    std::vector<std::string> cures;
    std::unordered_map<std::string, std::string> player_positions;
    // other game state variables...
};

class PlayerCard {
public:
    std::string name;
    std::function<void(GameState&, const std::string&)> action;

    PlayerCard(const std::string& name, std::function<void(GameState&, const std::string&)> action);
};

class Player {
public:
    std::string name;
    PlayerCard card;

    Player(const std::string& name, const PlayerCard& card);

    void play_card(GameState& game_state);
};

// Define actions for each player role card
void dispatcher_action(GameState& game_state, const std::string& player_name);
void scientist_action(GameState& game_state, const std::string& player_name);
void medic_action(GameState& game_state, const std::string& player_name);
void researcher_action(GameState& game_state, const std::string& player_name);
void quarantine_specialist_action(GameState& game_state, const std::string& player_name);
void operations_expert_action(GameState& game_state, const std::string& player_name);
void contingency_planner_action(GameState& game_state, const std::string& player_name);

#endif // PANDEMIC_H