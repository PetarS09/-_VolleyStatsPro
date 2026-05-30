#include "Coach.h"
#include <iostream>

Coach::Coach(std::string name, std::string egn, std::string phone, std::string birthDate, std::string licenseID, int winsCount, bool isHeadCoach)
    : Person(name, egn, phone, birthDate), licenseID(licenseID), winsCount(winsCount), isHeadCoach(isHeadCoach) {}

bool Coach::getIsHeadCoach() const { return isHeadCoach; }

void Coach::printInfo() const override {
    Person::printInfo();
    std::cout << " | [ТРЕНЬОР] " << (isHeadCoach ? "Главен треньор" : "Помощник треньор")
              << " | Победи: " << winsCount << " | Лиценз: " << licenseID << "\n";
}