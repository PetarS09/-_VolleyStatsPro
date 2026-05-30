#include <iostream>
#include "Team.h"
#include "Match.h"

int main() {
    // 1. Управление на профили (Squad Management) и Автоматично категоризиране
    Team myTeam("ВК Левски", "U18");

    myTeam.addPlayer(std::make_unique<Player>("Георги Петров", "104215xxxx", "0888111222", "2010-02-15", "Разпределител", 10));
    myTeam.addPlayer(std::make_unique<Player>("Мартин Иванов", "084512xxxx", "0888333444", "2008-05-12", "Диагонал", 7));
    myTeam.addPlayer(std::make_unique<Player>("Николай Василев", "094111xxxx", "0888555666", "2009-11-11", "Либеро", 4));
    myTeam.addPlayer(std::make_unique<Player>("Александър Тодоров", "084214xxxx", "0888111333", "2008-02-14", "Посрещач", 5));
    myTeam.addPlayer(std::make_unique<Player>("Симеон Николов", "094618xxxx", "0888444555", "2009-06-18", "Разпределител", 1));
    myTeam.addPlayer(std::make_unique<Player>("Владимир Гърков", "084919xxxx", "0888777999", "2008-09-19", "Център", 12));

    myTeam.setCoach(std::make_unique<Coach>("Андрей Жеков", "800101xxxx", "0888999999", "1980-01-01", "A-0542", 42, true));

    // 2. Статистическо отчитане и автоматичен анализ
    Player* p = myTeam.getPlayer(0); // Георги
    if (p) {
        p->addAttackStats(20, 4); // 20 атаки, 4 грешки
        p->addServiceStats(3, 1);  // 3 аса, 1 грешка
        p->addReceptionStats(8, 10); // 80% позитивно посрещане
    }
    
    Player* p2 = myTeam.getPlayer(1); // Мартин
    if (p2) {
        p2->addAttackStats(30, 2);
        p2->addServiceStats(5, 2);
    }

    myTeam.printTeamSquad();

    // 3. Дневник на мачовете (Match Logging)
    std::vector<SetScore> scores1 = {{25,23}, {25,21}, {25,20}};
    myTeam.addMatch(Match("ЦСКА", "2026-03-10", 3, 0, scores1));
    
    std::cout << "--- Дневник на мачовете ---\n";
    scores1[0] = {25,23}; // Пример за извикване
    Match m("ЦСКА", "2026-03-10", 3, 0, scores1);
    m.printMatchSummary();
    std::cout << "\n";

    // 4. Генериране на стартов състав (Line-up Generator)
    myTeam.generateLineUp();

    // 5. Експорт на сезонен отчет
    myTeam.exportReport();

    return 0;
}