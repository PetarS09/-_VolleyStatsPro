#include "Player.h"
#include <iostream>

Player::Player(std::string name, std::string egn, std::string phone, std::string birthDate, 
               std::string position, int jerseyNumber)
    : Person(name, egn, phone, birthDate), position(position), jerseyNumber(jerseyNumber),
      totalAttacks(0), attackErrors(0), aces(0), serviceErrors(0), blocks(0), 
      receptionScore(0), digScore(0) {}

std::string Player::getPosition() const { return position; }
int Player::getJerseyNumber() const { return jerseyNumber; }

std::string Player::getAgeGroup() const {
    int age = getAge();
    if (age < 16) return "U16";
    if (age < 18) return "U18";
    if (age < 21) return "U21";
    return "Мъже/Жени";
}

void Player::addAttackStats(int attacks, int errors) {
    if (position == "Либеро") {
        std::cout << "⚠️ Грешка: Либерото не може да атакува!\n";
        return;
    }
    if (attacks >= 0 && errors >= 0 && errors <= attacks) {
        totalAttacks += attacks;
        attackErrors += errors;
    }
}

void Player::addServiceStats(int newAces, int errors) {
    if (position == "Либеро") {
        std::cout << "⚠️ Грешка: Либерото не изпълнява сервис!\n";
        return;
    }
    if (newAces >= 0 && errors >= 0) {
        aces += newAces;
        serviceErrors += errors;
    }
}

void Player::addBlockStats(int newBlocks) {
    if (position == "Либеро") {
        std::cout << "⚠️ Грешка: Либерото не играе на блок!\n";
        return;
    }
    if (newBlocks >= 0) {
        blocks += newBlocks;
    }
}

void Player::registerReception(int qualityCode) {
    if (position == "Център" || position == "Диагонал") {
        std::cout << "⚠️ Тактическо предупреждение: Играч на позиция " << position << " не трябва да посреща!\n";
        return;
    }
    if (qualityCode == 1 || qualityCode == 0 || qualityCode == -1 || qualityCode == -2) { {
        receptionScore += qualityCode;
    }
}
}

void Player::registerDig(int qualityCode) {
    if (qualityCode == 1 || qualityCode == 0 || qualityCode == -1 || qualityCode == -2) {
        digScore += qualityCode;
    }
}

// РЕДАКЦИЯ НА ДАННИ (Покрива изискването от заданието)
void Player::updatePhoneNumber(const std::string& newPhone) {
    if (!newPhone.empty() && newPhone.length() >= 6) {
        this->phone = newPhone;
        std::cout << "✅ Телефонният номер бе обновен успешно.\n";
    } else {
        std::cout << "❌ Невалиден телефонен номер!\n";
    }
}

void Player::updatePosition(const std::string& newPos) {
    this->position = newPos;
    std::cout << "✅ Позицията на играча бе променена на: " << newPos << "\n";
}

// ПЛАВАЩ ПРОЗОРЕЦ НА СТАТИСТИКАТА (Покрива изискването за "последните мачове")
void Player::clearMatchHistoryWindow() {
    this->totalAttacks = 0;
    this->attackErrors = 0;
    this->aces = 0;
    this->blocks = 0;
    this->receptionScore = 0;
    this->digScore = 0;
}

double Player::getAttackEfficiency() const {
    if (totalAttacks == 0) return 0.0;
    return static_cast<double>(totalAttacks - attackErrors) / totalAttacks;
}

int Player::getReceptionScore() const { return receptionScore; }
int Player::getDigScore() const { return digScore; }

double Player::getOverallPerformanceScore() const {
    double baseScore = 0.0;
    double experienceFactor = 1.0;
    
    if (position == "Център") {
        if (totalAttacks < 10) experienceFactor = 0.5;
        baseScore = (getAttackEfficiency() * 50.0) + (blocks * 8.0);
    } 
    else if (position == "Диагонал") {
        if (totalAttacks < 15) experienceFactor = 0.4; 
        baseScore = (getAttackEfficiency() * 70.0) + (aces * 4.0) + (blocks * 3.0);
    } 
    else if (position == "Разпределител") {
        baseScore = (digScore * 5.0) + (aces * 4.0) + (getAttackEfficiency() * 20.0);
    } 
    else { // Посрещач и Либеро
        if (totalAttacks < 10 && position == "Посрещач") experienceFactor = 0.5;
        baseScore = (receptionScore * 6.0) + (digScore * 4.0) + (getAttackEfficiency() * 20.0);
    }

    return baseScore * experienceFactor;
}

void Player::printInfo() const {
    Person::printInfo();
    std::cout << " | №" << jerseyNumber << " | " << position;
    if (position != "Разпределител" && position != "Либеро") {
        std::cout << " | Атака опити: " << totalAttacks << " (Еф: " << getAttackEfficiency() * 100 << "%)";
    }
    std::cout << " | Точки посрещане: " << receptionScore 
              << " | Точки защита: " << digScore 
              << " -> Комплексен Рейтинг: " << getOverallPerformanceScore() << "\n";
}