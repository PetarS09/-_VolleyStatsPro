#ifndef TRAINING_SESSION_H
#define TRAINING_SESSION_H

#include <string>

// Абстрактен базов клас за тренировъчния процес
class TrainingSession {
private:
    std::string date;
    int durationMinutes;

public:
    TrainingSession(std::string date, int durationMinutes);
    virtual ~TrainingSession();

    std::string getDate() const;
    int getDuration() const;

    // Чисто виртуален метод (Превръща класа в абстрактен)
    virtual void logSessionDetails() const = 0;
};

// Наследник 1: Техническа тренировка в зала
class CourtPractice : public TrainingSession {
private:
    std::string tacticalFocus; // напр. "Атака/Защита"

public:
    CourtPractice(std::string date, int duration, std::string focus);
    void logSessionDetails() const override;
};

// Наследник 2: Силова тренировка във фитнес
class StrengthWorkout : public TrainingSession {
private:
    std::string exerciseType;
    int sets;
    int reps;

public:
    StrengthWorkout(std::string date, int duration, std::string exercise, int s, int r);
    void logSessionDetails() const override;
};

#endif