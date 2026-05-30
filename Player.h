#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"

class Player : public Person {
private:
    std::string position;
    int jerseyNumber;
    
    // Разширени статистически показатели за реално време
    int totalAttacks;
    int attackErrors;
    int aces;
    int serviceErrors;
    int blocks;
    int positiveReceptions;
    int totalReceptions;

public:
    Player(std::string name, std::string egn, std::string phone, std::string birthDate, 
           std::string position, int jerseyNumber);

    std::string getPosition() const;
    int getJerseyNumber() const;
    std::string getAgeGroup() const;

    // Сетъри за въвеждане на сурови данни с логика за валидация
    void addAttackStats(int attacks, int errors);
    void addServiceStats(int newAces, int errors);
    void addBlockStats(int newBlocks);
    void addReceptionStats(int positive, int total);

    // Автоматичен анализ на ефективността (Динамично изчисляеми състояния)
    double getAttackEfficiency() const;
    double getReceptionPercentage() const;
    double getOverallPerformanceScore() const; // Общ индекс за Line-up генератора

    void printInfo() const override;
};

#endif