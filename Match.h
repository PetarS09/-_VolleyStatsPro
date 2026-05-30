#ifndef MATCH_H
#define MATCH_H

#include <string>
#include <vector>

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
    std::vector<SetScore> setDetails;

    bool validateMatch() const;

public:
    Match(std::string opponent, std::string date, int teamSets, int opponentSets, std::vector<SetScore> sets);
    
    void printMatchSummary() const;
    std::string getFormattedSummary() const; // За нуждите на експорта на текстов файл
};

#endif