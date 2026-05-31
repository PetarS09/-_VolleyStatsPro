#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"

class Player : public Person {
private:
    std::string position;
    int jerseyNumber;
    
    // Статистически показатели
    int totalAttacks;
    int attackErrors;
    int aces;
    int serviceErrors;
    int blocks;
    
    // Точкова система за посрещане и защита (3-метрова линия)
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
    
    void registerReception(int qualityCode);
    void registerDig(int qualityCode);

    // Нови методи за редакция на профила и контрол на статистическия прозорец
    void updatePhoneNumber(const std::string& newPhone);
    void updatePosition(const std::string& newPos);
    void clearMatchHistoryWindow();

    double getAttackEfficiency() const;
    int getReceptionScore() const;
    int getDigScore() const;
    double getOverallPerformanceScore() const; 

    void printInfo() const override;
};

#endif