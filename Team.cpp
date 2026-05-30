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
        std::cout << "❌ Отборът вече е запълнен (макс 14 играча за мач съгласно FIVB)!\n";
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

// =======================================================================
// НОВА ПРОМЯНА: Валидация за брой играчи при добавяне на мач (FIVB съвместимост)
// =======================================================================
void Team::addMatch(const Match& match) {
    if (players.size() < 7) {
        std::cout << "❌ Административна грешка: Отборът " << teamName 
                  << " има само " << players.size() << " играчи. Минималният брой за мач е 7!\n";
        return;
    }
    if (players.size() > 14) {
        std::cout << "❌ Административна грешка: Отборът " << teamName 
                  << " има " << players.size() << " играчи. Максималният брой записани за мач е 14!\n";
        return;
    }
    matchHistory.push_back(match);
    std::cout << "✅ Мачът бе успешно записан в дневника на отбора.\n";
}

void Team::addTrainingSession(std::unique_ptr<TrainingSession> session) {
    trainingLog.push_back(std::move(session));
}

Player* Team::getPlayer(size_t index) {
    if (index < players.size()) return players[index].get();
    return nullptr;
}

// =======================================================================
// НОВА ПРОМЯНА: generateLineUp с двойна проверка за бройка и точни роли
// =======================================================================
void Team::generateLineUp() const {
    std::cout << "=== ГЕНЕРИРАН СТАРТОВ СЪСТАВ (Оптимални 7 състезатели по волейболни позиции) ===\n";
    
    // 1. Проверка на лимитите за общ брой играчи в тимовия лист за срещата
    if (players.size() < 7) {
        std::cout << "⚠️ Тактическа грешка: Нямате минималния брой играчи (минимум 7) за започване на мач!\n\n";
        return;
    }
    if (players.size() > 14) {
        std::cout << "⚠️ Тактическа грешка: Надвишаване на допустимия състав за мач (максимум 14 играчи)!\n\n";
        return;
    }

    // Локални контейнери за разпределяне по позиции
    std::vector<Player*> setters;
    std::vector<Player*> diagonals;
    std::vector<Player*> centers;
    std::vector<Player*> receivers; 
    std::vector<Player*> liberos;

    // 2. Разпределяне на текущия състав по роли
    for (const auto& p : players) {
        std::string pos = p->getPosition();
        if (pos == "Разпределител") setters.push_back(p.get());
        else if (pos == "Диагонал") diagonals.push_back(p.get());
        else if (pos == "Център") centers.push_back(p.get());
        else if (pos == "Посрещач") receivers.push_back(p.get());
        else if (pos == "Либеро") liberos.push_back(p.get());
    }

    // Сортиране по новия комплексен коефициент на полезно действие
    auto sortByScore = [](Player* a, Player* b) {
        return a->getOverallPerformanceScore() > b->getOverallPerformanceScore();
    };

    std::sort(setters.begin(), setters.end(), sortByScore);
    std::sort(diagonals.begin(), diagonals.end(), sortByScore);
    std::sort(centers.begin(), centers.end(), sortByScore);
    std::sort(receivers.begin(), receivers.end(), sortByScore);
    std::sort(liberos.begin(), liberos.end(), sortByScore);

    // 3. Проверка дали имаме нужните хора за тактическата постройка на полето
    bool hasValidSquad = true;
    if (setters.empty()) { std::cout << "❌ Липсва Разпределител!\n"; hasValidSquad = false; }
    if (diagonals.empty()) { std::cout << "❌ Липсва Диагонал!\n"; hasValidSquad = false; }
    if (liberos.empty()) { std::cout << "❌ Липсва Либеро!\n"; hasValidSquad = false; }
    if (centers.size() < 2) { std::cout << "❌ Трябват поне 2 Центъра (Имате " << centers.size() << ")!\n"; hasValidSquad = false; }
    if (receivers.size() < 2) { std::cout << "❌ Трябват поне 2 Посрещача /Четворки/ (Имате " << receivers.size() << ")!\n"; hasValidSquad = false; }

    if (!hasValidSquad) {
        std::cout << "⚠️ Стартовият състав не може да бъде генериран поради непълнота по тактически позиции.\n\n";
        return;
    }

    // 4. Извеждане на оптималната стартова седморка (6 на полето + 1 Либеро)
    std::cout << "Успешно сглобен състав (FIVB съвместим):\n\n";
    std::cout << "[РАЗПРЕДЕЛИТЕЛ]  №" << setters[0]->getJerseyNumber() << " - " << setters[0]->getName() << " (Рейтинг: " << setters[0]->getOverallPerformanceScore() << ")\n";
    std::cout << "[ДИАГОНАЛ]       №" << diagonals[0]->getJerseyNumber() << " - " << diagonals[0]->getName() << " (Рейтинг: " << diagonals[0]->getOverallPerformanceScore() << ")\n";
    std::cout << "[ЦЕНТЪР 1]       №" << centers[0]->getJerseyNumber() << " - " << centers[0]->getName() << " (Рейтинг: " << centers[0]->getOverallPerformanceScore() << ")\n";
    std::cout << "[ЦЕНТЪР 2]       №" << centers[1]->getJerseyNumber() << " - " << centers[1]->getName() << " (Рейтинг: " << centers[1]->getOverallPerformanceScore() << ")\n";
    std::cout << "[ПОСРЕЩАЧ 1]     №" << receivers[0]->getJerseyNumber() << " - " << receivers[0]->getName() << " (Рейтинг: " << receivers[0]->getOverallPerformanceScore() << ")\n";
    std::cout << "[ПОСРЕЩАЧ 2]     №" << receivers[1]->getJerseyNumber() << " - " << receivers[1]->getName() << " (Рейтинг: " << receivers[1]->getOverallPerformanceScore() << ")\n";
    std::cout << "[ЛИБЕРО]         №" << liberos[0]->getJerseyNumber() << " - " << liberos[0]->getName() << " (Рейтинг: " << liberos[0]->getOverallPerformanceScore() << ")\n";
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

    outFile << "--- СПИСЪК НА ИГРАЧИТЕ ---\n";
    for (const auto& p : players) {
        outFile << "№" << p->getJerseyNumber() << " " << p->getName() << " | Позиция: " << p->getPosition() << "\n";
    }
    outFile.close();
    std::cout << "💾 Отчетът бе успешно генериран в 'report.txt'\n";
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