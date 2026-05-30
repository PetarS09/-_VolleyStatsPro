#include "Player.h"
#include <iostream>

Player::Player(std::string name, std::string egn, std::string phone, std::string birthDate, 
               std::string position, int jerseyNumber)
    : Person(name, egn, phone, birthDate), position(position), jerseyNumber(jerseyNumber),
      totalAttacks(0), attackErrors(0), aces(0), serviceErrors(0), blocks(0), 
      positiveReceptions(0), totalReceptions(0) {}

std::string Player::getPosition() const { return position; }
int Player::getJerseyNumber() const { return jerseyNumber; }

std::string Player::getAgeGroup() const {
    int age = getAge();
    if (age <= 16) return "U16";
    if (age <= 18) return "U18";
    if (age <= 21) return "U21";
    return "Мъже/Жени";
}

void Player::addAttackStats(int attacks, int errors) {
    if (position == "Либеро") {
        std::cout << "⚠️ Грешка: Играчът " << getName() << " е Либеро и не може да атакува!\n";
        return;
    }
    if (attacks >= 0 && errors >= 0 && errors <= attacks) {
        totalAttacks += attacks;
        attackErrors += errors;
    }
}

void Player::addServiceStats(int newAces, int errors) {
    if (newAces >= 0 && errors >= 0) {
        aces += newAces;
        serviceErrors += errors;
    }
}

void Player::addBlockStats(int newBlocks) {
    if (newBlocks >= 0) {
        blocks += newBlocks;
    }
}

void Player::addReceptionStats(int positive, int total) {
    if (positive >= 0 && total >= 0 && positive <= total) {
        positiveReceptions += positive;
        totalReceptions += total;
    }
}

double Player::getAttackEfficiency() const {
    if (totalAttacks == 0) return 0.0;
    return static_cast<double>(totalAttacks - attackErrors) / totalAttacks;
}

double Player::getReceptionPercentage() const {
    if (totalReceptions == 0) return 0.0;
    return static_cast<double>(positiveReceptions) / totalReceptions;
}

double Player::getOverallPerformanceScore() const {
    // Формула за комплексна оценка на играча (използва се за генериране на Line-up)
    return (getAttackEfficiency() * 40.0) + (getReceptionPercentage() * 30.0) + (aces * 5.0) + (blocks * 5.0);
}

void Player::printInfo() const override {
    Person::printInfo();
    std::cout << " | №" << jerseyNumber << " | " << position << " [" << getAgeGroup() << "]";
    if (position != "Либеро") {
        std::cout << " | Ефективност атака: " << getAttackEfficiency() * 100 << "%";
    }
    std::cout << " | Позитивно посрещане: " << getReceptionPercentage() * 100 << "%"
              << " | Асове: " << aces << " | Блокади: " << blocks << "\n";
}