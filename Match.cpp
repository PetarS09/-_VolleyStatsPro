#include "Match.h"
#include <iostream>

Match::Match(std::string opponent, std::string date, int teamSets, int opponentSets)
    : opponent(opponent), date(date), teamSets(teamSets), opponentSets(opponentSets) {}

void Match::printMatchSummary() const {
    std::cout << "[" << date << "] ВК Левски " << teamSets << " : " 
              << opponentSets << " " << opponent 
              << (teamSets > opponentSets ? " (Победа 🎉)" : " (Загуба ⁠❌)") << "\n";
}