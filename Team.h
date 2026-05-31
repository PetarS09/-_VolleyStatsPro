#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <memory>
#include "Player.h"
#include "Coach.h"
#include "Match.h"
#include "TrainingSession.h"

class Team {
private:
    std::string teamName;
    std::string ageCategory;
    std::vector<std::unique_ptr<Player>> players; 
    std::unique_ptr<Coach> headCoach;             
    std::unique_ptr<Coach> assistantCoach;
    std::vector<Match> matchHistory;
    std::vector<std::unique_ptr<TrainingSession>> trainingLog;

    int getCategoryLimit(std::string cat) const;

public:
    Team(std::string name, std::string category);

    void addPlayer(std::unique_ptr<Player> player);
    Player* findPlayerByName(const std::string& firstName);
    Player* findPlayerByJersey(int jerseyNum);
    void setCoach(std::unique_ptr<Coach> coach);
    void addMatch(const Match& match);
    void addTrainingSession(std::unique_ptr<TrainingSession> session);

    Player* getPlayer(size_t index);
    
    // Нови функционалности от ТЗ
    void generateLineUp() const;  // Генератор на стартови 6-има въз основа на статистика
    void exportReport() const;    // Сезонен отчет в .txt файл

    void printTeamSquad() const;
    void printTrainingLog() const;
};

#endif