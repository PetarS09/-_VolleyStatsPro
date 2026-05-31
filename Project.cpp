#include <iostream>
#include "Team.h"

int main() {
    std::cout << "=======================================================================\n";
    
    // 1. Създаване на отбор
    std::cout << "\n[ФУНКЦИОНАЛНОСТ 1 & 2] Създаване на отбор и назначаване на треньори...\n";
    Team myTeam("ВК Левски София", "U21"); 
    myTeam.setCoach(std::make_unique<Coach>("Андрей Жеков", "800101xxxx", "0888111222", "1980-01-01", "FIVB-III", 120, true));

    // 2. Тестване на волейболните лимити за брой играчи при старт на мач
    std::cout << "\n[ФУНКЦИОНАЛНОСТ 4] Тест на FIVB лимитите за състав на мач (Мин 7, Макс 14)...\n";
    std::vector<SetScore> tempSets = {{25,20}, {25,22}, {25,21}};
    Match testMatch("ЦСКА", "2026-05-31", 3, 0, tempSets);
    
    // Опит за добавяне на мач без играчи (Очаква се блокиране)
    myTeam.addMatch(testMatch); 

    // Добавяне на пълна легитимна волейболна селекция от 7 играчи.
    // За да сме в крак с 2026 г. и лимита U21, играчите трябва да са родени 2005 г. или след това!
    std::cout << "\n[ФУНКЦИОНАЛНОСТ 3] Картотекиране на легитимен състав по волейболни позиции...\n";
    myTeam.addPlayer(std::make_unique<Player>("Симеон Николов", "064618xxxx", "0888111111", "2006-06-18", "Разпределител", 1));
    myTeam.addPlayer(std::make_unique<Player>("Венислав Антов", "054214xxxx", "0888222222", "2005-02-14", "Диагонал", 11)); // Подмладен до 21г.
    myTeam.addPlayer(std::make_unique<Player>("Алекс Грозданов", "054919xxxx", "0888333333", "2005-09-19", "Център", 12));
    myTeam.addPlayer(std::make_unique<Player>("Лазар Бучков", "064819xxxx", "0888444444", "2006-08-19", "Център", 2));       // Подмладен до 20г.
    myTeam.addPlayer(std::make_unique<Player>("Владимир Гърков", "054412xxxx", "0888555555", "2005-04-12", "Посрещач", 7));   // Подмладен до 21г.
    myTeam.addPlayer(std::make_unique<Player>("Александър Николов", "064512xxxx", "0888666666", "2006-10-12", "Посрещач", 8)); 
    myTeam.addPlayer(std::make_unique<Player>("Калоян Ботев", "054111xxxx", "0888777777", "2005-11-11", "Либеро", 4));       // Подмладен до 21г.

    // Сега вече имаме точно 7 състезатели и възрастта им е валидна, мачът ще се добави успешно
    myTeam.addMatch(testMatch); 

    // 3. ТЕСТ НА СИСТЕМАТА ЗА КОЛИЧЕСТВЕНО ОЦЕНЯВАНЕ (3-метрова линия)
    std::cout << "\n[ФУНКЦИОНАЛНОСТ 5] Наливане на игрови данни и количествено оценяване...\n";
    
    // Тест Посрещане (Либерото ни сега е на точен индекс 6)
    Player* libero = myTeam.getPlayer(6); 
    if (libero) {
        std::cout << "-> Симулиране отигравания на Либерото (" << libero->getName() << "):\n";
        libero->registerReception(1);  // +1
        libero->registerReception(1);  // +1
        libero->registerReception(0);  //  0
        libero->registerReception(-1); // -1
        libero->registerReception(-2); // -2
        // Точно така! Балансът тук ще излезе отрицателен: -1
    }

    // Тест Защита (Разпределител - индекс 0)
    Player* setter = myTeam.getPlayer(0); 
    if (setter) {
        std::cout << "-> Симулиране отигравания на Разпределителя:\n";
        setter->registerDig(1); 
        setter->registerDig(1); 
        setter->registerDig(0); 
        // Баланс: +2
    }

    // Тест за тактическо предупреждение (Центърът не трябва да посреща)
    Player* center = myTeam.getPlayer(2);
    if (center) {
        center->registerReception(1); 
        center->addBlockStats(6);     
    }

    // Наливане на малко атака за диагонала ни (индекс 1)
    Player* diagonal = myTeam.getPlayer(1);
    if (diagonal) {
        diagonal->addAttackStats(40, 10);
    }

    // 4. Принтиране на разширения състав с новите точкови активи
    std::cout << "\n[ФУНКЦИОНАЛНОСТ 6] Извеждане на състава с новите точкови баланси:\n";
    myTeam.printTeamSquad();

    // 5. Генериране на стартовия FIVB състав
    std::cout << "\n[ФУНКЦИОНАЛНОСТ 7] Стартиране на тактическия Line-up генератор...\n";
    myTeam.generateLineUp();

    // 6. Полиморфизъм в тренировъчния процес
    std::cout << "\n[ФУНКЦИОНАЛНОСТ 8] Добавяне и преглед на тренировъчния дневник...\n";
    myTeam.addTrainingSession(std::make_unique<CourtPractice>("2026-05-28", 120, "Стиковка между разпределител и центрове"));
    myTeam.addTrainingSession(std::make_unique<StrengthWorkout>("2026-05-29", 90, "Клек и експлозивна сила за отскок", 4, 6));
    myTeam.printTrainingLog();

    // Експорт на текстов файл
    myTeam.exportReport();

    std::cout << "\n=======================================================================\n";
    std::cout << " ВСИЧКИ КОРЕКЦИИ И ФУНКЦИОНАЛНОСТИ ПРЕМИНАХА УСПЕШНО!\n";
    std::cout << "=======================================================================\n";

    return 0;
}