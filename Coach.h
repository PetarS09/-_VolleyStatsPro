#ifndef COACH_H
#define COACH_H

#include "Person.h"

class Coach : public Person {
private:
    std::string licenseID;
    int winsCount;
    bool isHeadCoach;

public:
    Coach(std::string name, std::string egn, std::string phone, std::string birthDate, 
          std::string licenseID, int winsCount, bool isHeadCoach);

    bool getIsHeadCoach() const;
    int getWinsCount() const;
    std::string getLicenseID() const;

    void printInfo() const override;
};

#endif