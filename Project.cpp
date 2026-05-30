#include <iostream>
#include <vector>
#include "Match.h"

int main() {
    std::cout << "--- Тестване на Волейболните Валидации за Мачове ---\n\n";

    // ТЕСТ 1: Напълно валиден мач (3:1 с продължение в единия гейм 26:24)
    std::vector<SetScore> validSets = { {25, 20}, {26, 24}, {18, 25}, {25, 13} };
    Match m1("ЦСКА", "2026-03-10", 3, 1, validSets);
    m1.printMatchSummary();

    // ТЕСТ 2 (ГРЕШКА В КРАЙНИЯ РЕЗУЛТАТ): Въвеждаме 2:0 в геймовете
    std::vector<SetScore> invalidResult = { {25, 20}, {25, 18} };
    Match m2("Марек", "2026-03-12", 2, 0, invalidResult);
    m2.printMatchSummary();

    // ТЕСТ 3 (ГРЕШКА В ГЕЙМ - БЕЗ РАЗЛИКА): Резултат 25:24 (Невъзможен във волейбола)
    std::vector<SetScore> noDiffSets = { {25, 24}, {25, 11}, {25, 15} };
    Match m3("Монтана", "2026-03-15", 3, 0, noDiffSets);
    m3.printMatchSummary();

    // ТЕСТ 4 (ГРЕШКА В ГЕЙМ - СЛЕД 25 ТОЧКИ): Резултат 28:24 (Разликата е 4 точки, трябвало е да свърши при 26:24)
    std::vector<SetScore> badExtension = { {25, 22}, {28, 24}, {25, 19} };
    Match m4("Нефтохимик", "2026-03-18", 3, 0, badExtension);
    m4.printMatchSummary();

    return 0;
}