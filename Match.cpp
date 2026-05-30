#include "Match.h"
#include <iostream>
#include <cmath>
#include <sstream>

Match::Match(std::string opponent, std::string date, int teamSets, int opponentSets, std::vector<SetScore> sets)
    : opponent(opponent), date(date), teamSets(teamSets), opponentSets(opponentSets), setDetails(sets) {}

bool Match::validateMatch() const {
    bool validScore = (teamSets == 3 && (opponentSets >= 0 && opponentSets <= 2)) ||
                      (opponentSets == 3 && (teamSets >= 0 && teamSets <= 2));
    if (!validScore) return false;
    if (setDetails.size() != static_cast<size_t>(teamSets + opponentSets)) return false;
    return true;
}

void Match::printMatchSummary() const {
    if (!validateMatch()) {
        std::cout << "[" << date << "] Среща с " << opponent << " - НЕВАЛИДЕН РЕЗУЛТАТ СПРЕД FIVB!\n";
        return;
    }
    std::cout << "[" << date << "] ВК Левски " << teamSets << " : " << opponentSets << " " << opponent;
    std::cout << (teamSets > opponentSets ? " (Победи 🎉)" : " (Загуба ⁠❌)") << "\n";
}

std::string Match::getFormattedSummary() const {
    std::stringstream ss;
    ss << "[" << date << "] Противник: " << opponent << " | Резултат: " << teamSets << ":" << opponentSets;
    return ss.str();
}