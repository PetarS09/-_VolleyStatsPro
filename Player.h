#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"

class Player : public Person {
private:
    std::string position;
    int jerseyNumber;
    
    // Статистика
    int totalAttacks;
    int attackErrors;
    int aces;
    int serviceErrors;
    int blocks;
    
    // Нова точкова система за посрещане и защита
    int receptionScore; 
    int digScore;       

public:
    Player(std::string name, std::string egn, std::string phone, std::string birthDate, 
           std::string position, int jerseyNumber);

    std::string getPosition() const;
    int getJerseyNumber() const;
    std::string getAgeGroup() const;

    void addAttackStats(int attacks, int errors);
    void addServiceStats(int newAces, int errors);
    void addBlockStats(int newBlocks);
    
    // Нови методи за регистрация на отиграванията
    void registerReception(int qualityCode);
    void registerDig(int qualityCode);

    double getAttackEfficiency() const;
    int getReceptionScore() const;
    int getDigScore() const;
    double getOverallPerformanceScore() const; 

    void printInfo() const override;
};

#endif