#include "Team.h"
#include <iostream>

Team::Team(std::string name, std::string category) 
    : teamName(name), ageCategory(category), headCoach(nullptr), assistantCoach(nullptr) {}

int Team::getCategoryLimit(std::string cat) const {
    if (cat == "U16") return 16;
    if (cat == "U18") return 18;
    if (cat == "U21") return 21;
    return 99;
}

void Team::addPlayer(std::unique_ptr<Player> player) {
    if (players.size() >= 14) {
        std::cout << "❌ Грешка: Отборът " << teamName << " вече има 14 играча!\n";
        return;
    }
    int teamLimit = getCategoryLimit(ageCategory);
    if (player->getAge() > teamLimit) {
        std::cout << "❌ Грешка: Играчът " << player->getName() << " е твърде голям за " << ageCategory << "!\n";
        return;
    }
    std::cout << "✅ Успешно добавен играч: " << player->getName() << "\n";
    players.push_back(std::move(player));
}

void Team::setCoach(std::unique_ptr<Coach> coach) {
    if (coach->getIsHeadCoach()) {
        if (headCoach != nullptr) {
            std::cout << "❌ Грешка: Вече има Главен треньор!\n";
            return;
        }
        headCoach = std::move(coach);
    } else {
        if (assistantCoach != nullptr) {
            std::cout << "❌ Грешка: Вече има Помощник треньор!\n";
            return;
        }
        assistantCoach = std::move(coach);
    }
}

Player* Team::getPlayer(size_t index) {
    if (index < players.size()) return players[index].get();
    return nullptr;
}

void Team::printTeamSquad() const {
    std::cout << "=======================================================================\n";
    std::cout << "ОТБОР: " << teamName << " [" << ageCategory << "]\n";
    std::cout << "=======================================================================\n";
    if (headCoach) headCoach->printInfo();
    if (assistantCoach) assistantCoach->printInfo();
    for (const auto& player : players) player->printInfo();
    std::cout << "=======================================================================\n\n";
}