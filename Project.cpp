#include <iostream>
#include "Team.h"
#include "Match.h"

int main() {
    Team myTeam("ВК Левски", "U18");

    myTeam.addPlayer(std::make_unique<Player>("Георги Петров", "104215xxxx", "0888111222", "2010-02-15", "Разпределител", 10));
    myTeam.addPlayer(std::make_unique<Player>("Мартин Иванов", "084512xxxx", "0888333444", "2008-05-12", "Диагонал", 7));
    myTeam.addPlayer(std::make_unique<Player>("Николай Василев", "094111xxxx", "0888555666", "2009-11-11", "Либеро", 4));

    myTeam.setCoach(std::make_unique<Coach>("Андрей Жеков", "800101xxxx", "0888999999", "1980-01-01", "A-0542", 42, true));
    myTeam.setCoach(std::make_unique<Coach>("Христо Цветанов", "780214xxxx", "0888123456", "1978-02-14", "B-0981", 15, false));

    myTeam.printTeamSquad();

    std::vector<Match> matchHistory;
    matchHistory.push_back(Match("ЦСКА", "2026-03-10", 3, 1));
    matchHistory.push_back(Match("Левски", "2026-03-17", 2, 2));
    matchHistory.push_back(Match("Славия", "2026-03-24", 1, 3));

    for (const auto& match : matchHistory) {
        match.printMatchSummary();
    }

    return 0;
}