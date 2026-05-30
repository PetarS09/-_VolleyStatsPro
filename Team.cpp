#include "Team.h"
#include <iostream>
#include <fstream>
#include <algorithm>

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
        std::cout << "❌ Отборът вече е запълнен (макс 14 играча)!\n";
        return;
    }
    if (player->getAge() > getCategoryLimit(ageCategory)) {
        std::cout << "❌ Играчът " << player->getName() << " превишава възрастта за " << ageCategory << "!\n";
        return;
    }
    players.push_back(std::move(player));
}

void Team::setCoach(std::unique_ptr<Coach> coach) {
    if (coach->getIsHeadCoach()) {
        if (headCoach != nullptr) return;
        headCoach = std::move(coach);
    } else {
        if (assistantCoach != nullptr) return;
        assistantCoach = std::move(coach);
    }
}

void Team::addMatch(const Match& match) {
    matchHistory.push_back(match);
}

void Team::addTrainingSession(std::unique_ptr<TrainingSession> session) {
    trainingLog.push_back(std::move(session));
}

Player* Team::getPlayer(size_t index) {
    if (index < players.size()) return players[index].get();
    return nullptr;
}

void Team::generateLineUp() const {
    std::cout << "=== ГЕНЕРИРАН СТАРТОВ СЪСТАВ (Оптимални 6-има на база статистика) ===\n";
    if (players.size() < 6) {
        std::cout << "⚠️ Няма достатъчно играчи за генериране на състав (минимум 6).\n\n";
        return;
    }

    // Сортиране на локални копия на указателите по производителност
    std::vector<Player*> sortedPlayers;
    for (const auto& p : players) sortedPlayers.push_back(p.get());

    std::sort(sortedPlayers.begin(), sortedPlayers.end(), [](Player* a, Player* b) {
        return a->getOverallPerformanceScore() > b->getOverallPerformanceScore();
    });

    for (size_t i = 0; i < 6; ++i) {
        std::cout << (i + 1) << ". №" << sortedPlayers[i]->getJerseyNumber() << " - " 
                  << sortedPlayers[i]->getName() << " (Рейтинг: " 
                  << sortedPlayers[i]->getOverallPerformanceScore() << ")\n";
    }
    std::cout << "====================================================================\n\n";
}

void Team::exportReport() const {
    std::ofstream outFile("report.txt");
    if (!outFile) {
        std::cout << "❌ Грешка при създаване на файл за отчет!\n";
        return;
    }

    outFile << "СЕЗОНЕН ОТЧЕТ НА ОТБОР: " << teamName << " [" << ageCategory << "]\n";
    outFile << "====================================================\n";
    if (headCoach) outFile << "Главен треньор: " << headCoach->getName() << "\n";
    outFile << "Брой състезатели: " << players.size() << "\n\n";

    outFile << "--- ИЗПЛЪЛНЕНИЕ НА ИГРАЧИТЕ ---\n";
    for (const auto& p : players) {
        outFile << "№" << p->getJerseyNumber() << " " << p->getName() 
                << " | Ефективност атака: " << p->getAttackEfficiency() * 100 << "%\n";
    }

    outFile << "\n--- ИСТОРИЯ НА МАЧОВЕТЕ ---\n";
    for (const auto& m : matchHistory) {
        outFile << m.getFormattedSummary() << "\n";
    }

    outFile.close();
    std::cout << "💾 Сезонният отчет бе успешно генериран във файл: 'report.txt'\n\n";
}

void Team::printTeamSquad() const {
    std::cout << "=======================================================================\n";
    std::cout << "СЪСТАВ НА ОТБОР: " << teamName << " [" << ageCategory << "]\n";
    std::cout << "=======================================================================\n";
    if (headCoach) headCoach->printInfo();
    if (assistantCoach) assistantCoach->printInfo();
    std::cout << "-----------------------------------------------------------------------\n";
    for (const auto& p : players) p->printInfo();
    std::cout << "=======================================================================\n\n";
}

void Team::printTrainingLog() const {
    std::cout << "=== ДНЕВНИК НА ТРЕНИРОВЪЧНИЯ ПРОЦЕС (Training Log) ===\n";
    for (const auto& s : trainingLog) {
        s->logSessionDetails();
    }
    std::cout << "======================================================\n\n";
}