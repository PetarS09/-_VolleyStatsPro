#include "TrainingSession.h"
#include <iostream>

// Имплементация на базовия клас TrainingSession
TrainingSession::TrainingSession(std::string date, int durationMinutes)
    : date(date), durationMinutes(durationMinutes) {}

TrainingSession::~TrainingSession() {}

std::string TrainingSession::getDate() const { return date; }
int TrainingSession::getDuration() const { return durationMinutes; }


// Имплементация на CourtPractice
CourtPractice::CourtPractice(std::string date, int duration, std::string focus)
    : TrainingSession(date, duration), tacticalFocus(focus) {}

void CourtPractice::logSessionDetails() const {
    std::cout << "[ЗАЛА] Дата: " << getDate() << " | Времетраене: " << getDuration() 
              << " мин | Фокус: " << tacticalFocus << "\n";
}


// Имплементация на StrengthWorkout
StrengthWorkout::StrengthWorkout(std::string date, int duration, std::string exercise, int s, int r)
    : TrainingSession(date, duration), exerciseType(exercise), sets(s), reps(r) {}

void StrengthWorkout::logSessionDetails() const {
    std::cout << "[СИЛОВА] Дата: " << getDate() << " | Времетраене: " << getDuration() 
              << " мин | Упражнение: " << exerciseType << " (" << sets << "x" << reps << ")\n";
}