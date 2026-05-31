#include "TrainingSession.h"

// Имплементация на базовия клас
TrainingSession::TrainingSession(std::string date, int duration) 
    : date(date), duration(duration) {}

// Имплементация на CourtPractice
CourtPractice::CourtPractice(std::string date, int duration, std::string focus)
    : TrainingSession(date, duration), tacticalFocus(focus) {}

void CourtPractice::logSessionDetails() const {
    std::cout << "[ЗАЛА] Дата: " << date << " | Времетраене: " << duration 
              << " мин | Фокус: " << tacticalFocus << "\n";
}

// Имплементация на StrengthWorkout
#include "TrainingSession.h"

StrengthWorkout::StrengthWorkout(std::string date, int duration, std::string ex, int s, int r)
    : TrainingSession(date, duration), exercise(ex), sets(s), reps(r) {}

void StrengthWorkout::logSessionDetails() const {
    std::cout << "[СИЛОВА] Дата: " << date << " | Времетраене: " << duration 
              << " мин | Упражнение: " << exercise << " (" << sets << "x" << reps << ")\n";
}

// Имплементация на PhysicalTest
PhysicalTest::PhysicalTest(std::string date, int duration, int jump, double speed)
    : TrainingSession(date, duration), verticalJump(jump), sprintSpeed(speed) {}

void PhysicalTest::logSessionDetails() const {
    std::cout << "[ФИЗ. ТЕСТ] Дата: " << date << " | Времетраене: " << duration 
              << " мин | Вертикален отскок: " << verticalJump << " см | Скорост: " << sprintSpeed << " сек\n";
}