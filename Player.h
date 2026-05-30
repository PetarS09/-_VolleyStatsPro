#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"

class Player : public Person {
private:
    std::string position; // "Разпределител", "Диагонал", "Център", "Посрещач", "Либеро"
    int jerseyNumber;
    
    // Статистика
    int totalAttacks;
    int attackErrors;
    int aces;
    int serviceErrors;
    int blocks;
    int positiveReceptions;
    int totalReceptions;
    int successfulDigs; // Нова статистика за защита (главно за Разпределител/Либеро)

public:
    Player(std::string name, std::string egn, std::string phone, std::string birthDate, 
           std::string position, int jerseyNumber);

    std::string getPosition() const;
    int getJerseyNumber() const;
    std::string getAgeGroup() const;

    void addAttackStats(int attacks, int errors);
    void addServiceStats(int newAces, int errors);
    void addBlockStats(int newBlocks);
    void addReceptionStats(int positive, int total);
    void addDigStats(int digs); // Сетър за защита

    double getAttackEfficiency() const;
    double getReceptionPercentage() const;
    
    // Новата разширена формула за рейтинг
    double getOverallPerformanceScore() const; 

    void printInfo() const override;
};

#endif