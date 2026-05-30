#ifndef MATCH_H
#define MATCH_H

#include <string>
#include <vector>

// Структура, която пази резултата за един конкретен гейм
struct SetScore {
    int teamPoints;
    int opponentPoints;
};

class Match {
private:
    std::string opponent;
    std::string date;
    int teamSets;
    int opponentSets;
    std::vector<SetScore> setDetails; // Списък с резултатите от всеки изигран гейм

    // Вътрешен метод за пълна валидация на правилата на FIVB
    bool validateMatch() const;

public:
    Match(std::string opponent, std::string date, int teamSets, int opponentSets, 
          std::vector<SetScore> sets);
          
    void printMatchSummary() const;
};

#endif