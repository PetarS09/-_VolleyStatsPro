#ifndef TRAININGSESSION_H
#define TRAININGSESSION_H

#include <string>
#include <iostream>

// Базов абстрактен клас
class TrainingSession {
protected:
    std::string date;
    int duration;
public:
    TrainingSession(std::string date, int duration);
    virtual ~TrainingSession() = default;
    virtual void logSessionDetails() const = 0;
};

// Наследник 1: Техническа тренировка
class CourtPractice : public TrainingSession {
private:
    std::string tacticalFocus;
public:
    CourtPractice(std::string date, int duration, std::string focus);
    void logSessionDetails() const override;
};

// Наследник 2: Силова тренировка
class StrengthWorkout : public TrainingSession {
private:
    std::string exercise;
    int sets;
    int reps;
public:
    StrengthWorkout(std::string date, int duration, std::string ex, int s, int r);
    void logSessionDetails() const override;
};

// Наследник 3: Физически тестове (Покрива изискването от заданието)
class PhysicalTest : public TrainingSession {
private:
    int verticalJump;    // Вертикален отскок в см
    double sprintSpeed;  // Скорост в секунди
public:
    PhysicalTest(std::string date, int duration, int jump, double speed);
    void logSessionDetails() const override;
};

#endif