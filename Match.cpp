#include "Match.h"
#include <iostream>
#include <cmath>

Match::Match(std::string opponent, std::string date, int teamSets, int opponentSets, 
             std::vector<SetScore> sets)
    : opponent(opponent), date(date), teamSets(teamSets), opponentSets(opponentSets), setDetails(sets) {}

bool Match::validateMatch() const {
    // 1. Проверка за валиден краен резултат в мача
    bool validScore = (teamSets == 3 && (opponentSets == 0 || opponentSets == 1 || opponentSets == 2)) ||
                      (opponentSets == 3 && (teamSets == 0 || teamSets == 1 || teamSets == 2));
                      
    if (!validScore) {
        std::cout << "❌ Волейболна грешка: Невалиден краен резултат (" << teamSets << ":" << opponentSets 
                  << "). Мачът трябва да завърши при 3:0, 3:1, 3:2, 0:3, 1:3 или 2:3!\n";
        return false;
    }

    // 2. Проверка дали броят на подадените геймове съвпада с крайния резултат
    int totalSets = teamSets + opponentSets;
    if (setDetails.size() != static_cast<size_t>(totalSets)) {
        std::cout << "❌ Волейболна грешка: Броят на геймовете в историята (" << setDetails.size() 
                  << ") не съвпада с общия брой изиграни геймове (" << totalSets << ")!\n";
        return false;
    }

    // 3. Проверка на всеки гейм поотделно
    for (size_t i = 0; i < setDetails.size(); ++i) {
        int tPoints = setDetails[i].teamPoints;
        int oPoints = setDetails[i].opponentPoints;
        int maxPoints = std::max(tPoints, oPoints);
        int minPoints = std::min(tPoints, oPoints);
        int pointDiff = maxPoints - minPoints;
        
        bool isTiebreak = (i == 4); // Петият гейм е тайбрек
        int requiredMinToWin = isTiebreak ? 15 : 25;

        // Проверка 3.1: Спечелилият трябва да има поне необходимия минимум точки
        if (maxPoints < requiredMinToWin) {
            std::cout << "❌ Волейболна грешка в Гейм " << (i + 1) << ": Резултатът " << tPoints << ":" << oPoints 
                      << " е невалиден. Геймът се играе до минимум " << requiredMinToWin << " точки!\n";
            return false;
        }

        // Проверка 3.2: Проверка за разликата от 2 точки
        if (maxPoints == requiredMinToWin) {
            // Ако победителят има точно 25 (или 15 за тайбрек), победеният трябва да има максимум 23 (или 13)
            if (minPoints > (requiredMinToWin - 2)) {
                std::cout << "❌ Волейболна грешка in Гейм " << (i + 1) << ": Резултатът " << tPoints << ":" << oPoints 
                          << " е невалиден. Трябва да има 2 точки разлика (напр. " << requiredMinToWin << ":" << (requiredMinToWin - 2) << ")!\n";
                return false;
            }
        } else {
            // Ако са преминали лимита (напр. играят над 25), разликата трябва да е ТОЧНО 2 точки (напр. 26:24, 27:25)
            if (pointDiff != 2) {
                std::cout << "❌ Волейболна грешка в Гейм " << (i + 1) << ": Резултатът " << tPoints << ":" << oPoints 
                          << " е невалиден. При игра след " << requiredMinToWin << " точки, разликата трябва да е точно 2!\n";
                return false;
            }
        }
    }

    return true;
}

void Match::printMatchSummary() const {
    std::cout << "[" << date << "] ВК Левски vs " << opponent << " -> ";
    
    if (!validateMatch()) {
        std::cout << "[НЕВАЛИДЕН МАЧ - Нарушени правила на FIVB]\n\n";
        return;
    }

    std::cout << "Краен резултат: " << teamSets << ":" << opponentSets 
              << (teamSets > opponentSets ? " (Победа 🎉)" : " (Загуба ⁠❌)") << "\n  Детайли по геймове: ";
              
    for (size_t i = 0; i < setDetails.size(); ++i) {
        std::cout << setDetails[i].teamPoints << ":" << setDetails[i].opponentPoints;
        if (i < setDetails.size() - 1) std::cout << ", ";
    }
    std::cout << "\n\n";
}