#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(std::string name, std::string egn, std::string phone, std::string birthDate, 
               std::string position, int jerseyNumber)
    : Person(name, egn, phone, birthDate), position(position), jerseyNumber(jerseyNumber),
      totalAttacks(0), attackErrors(0), aces(0), serviceErrors(0), blocks(0), 
      positiveReceptions(0), totalReceptions(0), successfulDigs(0) {}

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

void Player::addReceptionStats(int positive, int total) {
    // Волейболно правило: Централните блокировачи и Диагоналите НЕ посрещат в съвременните тактики
    if (position == "Център" || position == "Диагонал") {
        std::cout << "⚠️ Тактическо предупреждение: Играч на позиция " << position << " не трябва да посреща!\n";
        return;
    }
    if (positive >= 0 && total >= 0 && positive <= total) {
        positiveReceptions += positive;
        totalReceptions += total;
    }
}

void Player::addDigStats(int digs) {
    if (digs >= 0) {
        successfulDigs += digs;
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

// ИНТЕЛЕГЕНТНА ОЦЕНКА СПРЕД ПОЗИЦИЯТА И ОБЕМА НА ОПИТИТЕ
double Player::getOverallPerformanceScore() const {
    double baseScore = 0.0;

    // Фактор за обем (опити). Ако играчът има под 10 атаки/посрещания, 
    // рейтингът му изкуствено се намалява, за да се даде предимство на игралия повече.
    double experienceFactor = 1.0;
    
    if (position == "Център") {
        if (totalAttacks < 10) experienceFactor = 0.5;
        // За центъра търсим мощна атака (50% тежест) и много блокове (50% тежест)
        baseScore = (getAttackEfficiency() * 50.0) + (blocks * 8.0);
    } 
    else if (position == "Диагонал") {
        if (totalAttacks < 15) experienceFactor = 0.4; // Диагоналът ТРЯБВА да има много атаки
        // Диагоналът е основен реализатор: огромна тежест на атаката (70%) + асове/блок
        baseScore = (getAttackEfficiency() * 70.0) + (aces * 4.0) + (blocks * 3.0);
    } 
    else if (position == "Разпределител") {
        // Разпределителят не прави точки често. Оценяваме го по защити, асове и хитрост (пускания)
        baseScore = (successfulDigs * 5.0) + (aces * 4.0) + (getAttackEfficiency() * 20.0);
    } 
    else { // Посрещач и Либеро
        if (totalReceptions < 10) experienceFactor = 0.5;
        baseScore = (getReceptionPercentage() * 40.0) + (getAttackEfficiency() * 30.0) + (successfulDigs * 3.0);
    }

    return baseScore * experienceFactor;
}

void Player::printInfo() const override {
    Person::printInfo();
    std::cout << " | №" << jerseyNumber << " | " << position;
    if (position != "Разпределител" && position != "Либеро") {
        std::cout << " | Атака опити: " << totalAttacks << " (Еф: " << getAttackEfficiency() * 100 << "%)";
    }
    if (position == "Посрещач" || position == "Либеро") {
        std::cout << " | Посрещане: " << getReceptionPercentage() * 100 << "%";
    }
    std::cout << " | Защита(диг): " << successfulDigs << " | Блокове: " << blocks << " -> Рейтинг: " << getOverallPerformanceScore() << "\n";
}