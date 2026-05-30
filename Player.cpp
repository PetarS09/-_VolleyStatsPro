#include "Player.h"
#include <iostream>

Player::Player(std::string name, std::string egn, std::string phone, std::string birthDate, std::string position, int jerseyNumber)
    : Person(name, egn, phone, birthDate), position(position), jerseyNumber(jerseyNumber), totalAttacks(0), attackErrors(0) {}

std::string Player::getPosition() const { return position; }

std::string Player::getAgeGroup() const {
    int age = getAge();
    if (age <= 16) return "U16";
    if (age <= 18) return "U18";
    if (age <= 21) return "U21";
    return "Мъже/Жени";
}

void Player::addAttackStats(int attacks, int errors) {
    if (position == "Либеро") {
        std::cout << "⚠️ Грешка: Играчът " << getName() << " е Либеро и не може да има статистика за атака!\n";
        return;
    }
    if (attacks >= 0 && errors >= 0 && errors <= attacks) {
        totalAttacks += attacks;
        attackErrors += errors;
    }
}

double Player::getAttackEfficiency() const {
    if (totalAttacks == 0) return 0.0;
    return static_cast<double>(totalAttacks - attackErrors) / totalAttacks;
}

void Player::printInfo() const override {
    Person::printInfo();
    std::cout << " | №" << jerseyNumber << " | Позиция: " << position << " | Категория: " << getAgeGroup();
    if (position != "Либеро") {
        std::cout << " | Ефективност в атака: " << getAttackEfficiency() * 100 << "%";
    }
    std::cout << "\n";
}