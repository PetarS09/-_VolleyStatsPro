#ifndef PLAYER_H
#define PLAYER_H
#include "Person.h"

class Player : public Person {
private:
    std::string position;
    int jerseyNumber;
    int totalAttacks;
    int attackErrors;
public:
    Player(std::string name, std::string egn, std::string phone, std::string birthDate, std::string position, int jerseyNumber);
    std::string getPosition() const;
    std::string getAgeGroup() const;
    void addAttackStats(int attacks, int errors);
    double getAttackEfficiency() const;
    void printInfo() const override;
};
#endif