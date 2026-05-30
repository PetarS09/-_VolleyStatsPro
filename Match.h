#ifndef MATCH_H
#define MATCH_H
#include <string>

class Match {
private:
    std::string opponent;
    std::string date;
    int teamSets;
    int opponentSets;
public:
    Match(std::string opponent, std::string date, int teamSets, int opponentSets);
    void printMatchSummary() const;
};
#endif