#ifndef TEAM_H
#define TEAM_H
#include <vector>
#include <memory>
#include "Player.h"
#include "Coach.h"

class Team {
private:
    std::string teamName;
    std::string ageCategory;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<Coach> headCoach;
    std::unique_ptr<Coach> assistantCoach;
    int getCategoryLimit(std::string cat) const;
public:
    Team(std::string name, std::string category);
    void addPlayer(std::unique_ptr<Player> player);
    void setCoach(std::unique_ptr<Coach> coach);
    Player* getPlayer(size_t index);
    void printTeamSquad() const;
};
#endif