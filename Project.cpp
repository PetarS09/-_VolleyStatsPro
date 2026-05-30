#include <iostream>
#include "Team.h"

int main() {
    Team myTeam("ВК Левски", "Мъже/Жени");

    // ТЕСТ НА ОПИТА (100 забити срещу 2 забити):
    // Играч 1: Истински нападател - 100 атаки, 50 грешки (50% ефективност)
    auto playerVolume = std::make_unique<Player>("Мартин Нападателя", "054512xxxx", "0888333444", "2005-05-12", "Диагонал", 7);
    playerVolume->addAttackStats(100, 50); // 100 общо, 50 грешни -> 50% еф.
    myTeam.addPlayer(std::move(playerVolume));

    // Играч 2: Късметлия - 2 атаки, 0 грешки (100% ефективност, но твърде малко опити)
    auto playerLucky = std::make_unique<Player>("Иван Късметлията", "064214xxxx", "0888111333", "2006-02-14", "Диагонал", 11);
    playerLucky->addAttackStats(2, 0); // 2 общо, 0 грешни -> 100% еф.
    myTeam.addPlayer(std::move(playerLucky));

    // Добавяме и един Разпределител, за да тестваме неговата статистика за защита (digs)
    auto setter = std::make_unique<Player>("Симеон Разпределителя", "044618xxxx", "0888444555", "2004-06-18", "Разпределител", 1);
    setter->addDigStats(25); // 25 успешни спасявания в защита
    setter->addServiceStats(4, 1);
    myTeam.addPlayer(std::move(setter));

    // Проверка за забрана за посрещане на Диагонал (Ще изпише предупреждение в конзолата)
    Player* pMartin = myTeam.getPlayer(0);
    if (pMartin) {
        pMartin->addReceptionStats(5, 5); 
    }

    std::cout << "\n--- СЪСТАВ И РЕЙТИНГИ ---\n";
    myTeam.printTeamSquad();

    // Генериране на състава. Благодарение на "experienceFactor", 
    // Мартин ще има много по-висок рейтинг от Иван и ще бъде избран първи!
    myTeam.generateLineUp();

    return 0;
}