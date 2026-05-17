#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ============================================================================
// БАЗОВ КЛАС: Person
// ============================================================================
class Person {
private:
    std::string name;
    std::string egn;
    std::string phone;
    std::string birthDate; // Формат: ГГГГ-ММ-ДД

protected:
    int getBirthYear() const {
        if (birthDate.length() >= 4) {
            return std::stoi(birthDate.substr(0, 4));
        }
        return 2000;
    }

public:
    Person(std::string name, std::string egn, std::string phone, std::string birthDate)
        : name(name), egn(egn), phone(phone), birthDate(birthDate) {}

    virtual ~Person() {}

    int getAge() const {
        int currentYear = 2026; 
        return currentYear - getBirthYear();
    }

    std::string getName() const { return name; }
    std::string getEgn() const { return egn; }

    virtual void printInfo() const {
        std::cout << "Име: " << name << " | Възраст: " << getAge() 
                  << " г. (Роден/а: " << birthDate << ") | Тел: " << phone;
    }
};

// ============================================================================
// НАСЛЕДНИК: Player
// ============================================================================
class Player : public Person {
private:
    std::string position; // Напр. "Разпределител", "Диагонал", "Либеро"
    int jerseyNumber;
    int totalAttacks;
    int attackErrors;

public:
    Player(std::string name, std::string egn, std::string phone, std::string birthDate, 
           std::string position, int jerseyNumber)
        : Person(name, egn, phone, birthDate), position(position), jerseyNumber(jerseyNumber),
          totalAttacks(0), attackErrors(0) {}

    std::string getPosition() const { return position; }

    std::string getAgeGroup() const {
        int age = getAge();
        if (age <= 16) return "U16";
        if (age <= 18) return "U18";
        if (age <= 21) return "U21";
        return "Мъже/Жени";
    }

    void addAttackStats(int attacks, int errors) {
        if (position == "Либеро") {
            std::cout << "⚠️ Грешка: Играчът " << getName() << " е Либеро и не може да има статистика за атака!\n";
            return;
        }

        if (attacks >= 0 && errors >= 0 && errors <= attacks) {
            totalAttacks += attacks;
            attackErrors += errors;
        }
    }

    double getAttackEfficiency() const {
        if (totalAttacks == 0) return 0.0;
        return static_cast<double>(totalAttacks - attackErrors) / totalAttacks;
    }

    void printInfo() const override {
        Person::printInfo();
        std::cout << " | №" << jerseyNumber << " | Позиция: " << position 
                  << " | Категория: " << getAgeGroup();
        
        if (position != "Либеро") {
            std::cout << " | Ефективност в атака: " << getAttackEfficiency() * 100 << "%";
        }
        std::cout << "\n";
    }
};

// ============================================================================
// НАСЛЕДНИК: Coach
// ============================================================================
class Coach : public Person {
private:
    std::string licenseID;
    int winsCount;         
    bool isHeadCoach;      // true = Главен, false = Помощник

public:
    Coach(std::string name, std::string egn, std::string phone, std::string birthDate, 
          std::string licenseID, int winsCount, bool isHeadCoach)
        : Person(name, egn, phone, birthDate), licenseID(licenseID), 
          winsCount(winsCount), isHeadCoach(isHeadCoach) {}

    bool getIsHeadCoach() const { return isHeadCoach; }

    void printInfo() const override {
        Person::printInfo();
        std::cout << " | [ТРЕНЬОР] " << (isHeadCoach ? "Главен треньор" : "Помощник треньор")
                  << " | Победи: " << winsCount 
                  << " | Лиценз: " << licenseID << "\n";
    }
};

// ============================================================================
// КЛАС: Team (С включени контроли за възраст и треньори)
// ============================================================================
class Team {
private:
    std::string teamName;
    std::string ageCategory; // "U16", "U18", "U21" или "Мъже/Жени"
    std::vector<std::unique_ptr<Player>> players; 
    std::unique_ptr<Coach> headCoach;             
    std::unique_ptr<Coach> assistantCoach;        

    // Помощен метод за превръщане на категорията в максимални години
    int getCategoryLimit(std::string cat) const {
        if (cat == "U16") return 16;
        if (cat == "U18") return 18;
        if (cat == "U21") return 21;
        return 99; // За "Мъже/Жени" няма горна граница
    }

public:
    Team(std::string name, std::string category) 
        : teamName(name), ageCategory(category), headCoach(nullptr), assistantCoach(nullptr) {}

    // Метод за добавяне на играч с проверка за брой и за възраст (волейболно правило)
    void addPlayer(std::unique_ptr<Player> player) {
        // 1. Валидация за максимален брой играчи (14)
        if (players.size() >= 14) {
            std::cout << "❌ Грешка: Отборът " << teamName << " вече има 14 играча! Блокиран: " << player->getName() << "\n";
            return;
        }

        // 2. Валидация за възрастова група
        int teamLimit = getCategoryLimit(ageCategory);
        int playerAge = player->getAge();

        if (playerAge > teamLimit) {
            std::cout << "❌ Грешка: Играчът " << player->getName() << " (на " << playerAge << " г.) "
                      << "е твърде голям за отбор " << ageCategory << "!\n";
            return;
        }

        // Ако всичко е наред, добавяме играча успешно
        std::cout << "✅ Успешно добавен играч: " << player->getName() << " (Възраст: " << playerAge << " г.)\n";
        players.push_back(std::move(player));
    }

    // Метод за задаване на треньори (макс 1 главен и 1 помощник)
    void setCoach(std::unique_ptr<Coach> coach) {
        if (coach->getIsHeadCoach()) {
            if (headCoach != nullptr) {
                std::cout << "❌ Грешка: " << teamName << " вече има Главен треньор (" << headCoach->getName() << ")! Блокиран: " << coach->getName() << "\n";
                return;
            }
            headCoach = std::move(coach);
            std::cout << "👑 Успешно назначен Главен треньор: " << headCoach->getName() << "\n";
        } else {
            if (assistantCoach != nullptr) {
                std::cout << "❌ Грешка: " << teamName << " вече има Помощник треньор (" << assistantCoach->getName() << ")! Блокиран: " << coach->getName() << "\n";
                return;
            }
            assistantCoach = std::move(coach);
            std::cout << "📋 Успешно назначен Помощник треньор: " << assistantCoach->getName() << "\n";
        }
    }

    Player* getPlayer(size_t index) {
        if (index < players.size()) {
            return players[index].get();
        }
        return nullptr;
    }

    void printTeamSquad() const {
        std::cout << "=======================================================================\n";
        std::cout << "ОТБОР: " << teamName << " [" << ageCategory << "] | Състав (Играчи: " << players.size() << "/14)\n";
        std::cout << "=======================================================================\n";
        
        if (headCoach) headCoach->printInfo();
        if (assistantCoach) assistantCoach->printInfo();
        
        std::cout << "------------------------------- Играчи -------------------------------\n";
        for (const auto& player : players) {
            player->printInfo();
        }
        std::cout << "=======================================================================\n\n";
    }
};

// ============================================================================
// КЛАС: Match
// ============================================================================
class Match {
private:
    std::string opponent;
    std::string date;
    int teamSets;
    int opponentSets;

public:
    Match(std::string opponent, std::string date, int teamSets, int opponentSets)
        : opponent(opponent), date(date), teamSets(teamSets), opponentSets(opponentSets) {}

    void printMatchSummary() const {
        std::cout << "[" << date << "] ВК Левски " << teamSets << " : " 
                  << opponentSets << " " << opponent 
                  << (teamSets > opponentSets ? " (Победа 🎉)" : " (Загуба ⁠❌)") << "\n";
    }
};

// ============================================================================
// ГЛАВНА ФУНКЦИЯ
// ============================================================================
int main() {
    // Създаваме отбор конкретно за категория U18
    Team myTeam("ВК Левски", "U18");

    std::cout << "--- 1. Тестване на ограниченията и волейболните правила ---\n";
    
    // ТЕСТ 1: Играч от U16 (Георги, на 16 г.) влиза в отбор U18 -> Допуснато!
    myTeam.addPlayer(std::make_unique<Player>("Георги Петров", "104215xxxx", "0888111222", "2010-02-15", "Разпределител", 10));
    
    // ТЕСТ 2: Играч точно за U18 (Мартин, на 18 г.) влиза в U18 -> Допуснато!
    myTeam.addPlayer(std::make_unique<Player>("Мартин Иванов", "084512xxxx", "0888333444", "2008-05-12", "Диагонал", 7));
    myTeam.addPlayer(std::make_unique<Player>("Николай Василев", "094111xxxx", "0888555666", "2009-11-11", "Либеро", 4));

    // ТЕСТ 3 (ГРЕШКА): Играч от категория Мъже (на 23 г.) се опитва да влезе в U18 -> БЛОКИРАН!
    myTeam.addPlayer(std::make_unique<Player>("Боян Йорданов", "034111xxxx", "0888777888", "2003-03-03", "Диагонал", 1));

    std::cout << "\n";

    // Добавяне на треньори
    myTeam.setCoach(std::make_unique<Coach>("Андрей Жеков", "800101xxxx", "0888999999", "1980-01-01", "A-0542", 42, true));
    myTeam.setCoach(std::make_unique<Coach>("Христо Цветанов", "780214xxxx", "0888123456", "1978-02-14", "B-0981", 15, false));

    // ТЕСТ 4 (ГРЕШКА): Втори главен треньор -> БЛОКИРАН!
    myTeam.setCoach(std::make_unique<Coach>("Пробен Треньор", "750505xxxx", "0888000000", "1975-05-05", "A-9999", 10, true));

    std::cout << "\n";
    myTeam.printTeamSquad();

    std::cout << "--- 2. Дневник на мачовете (Match Logging) ---\n";
    std::vector<Match> matchHistory;
    matchHistory.push_back(Match("ЦСКА", "2026-03-10", 3, 1));
    for (const auto& match : matchHistory) {
        match.printMatchSummary();
    }
    std::cout << "\n";

    std::cout << "--- 3. Симулация на статистика ---\n";
    Player* p1 = myTeam.getPlayer(0); // Георги
    if (p1) {
        p1->addAttackStats(25, 5); // 25 атаки, 5 грешки -> 80% ефективност
    }
    
    Player* p_libero = myTeam.getPlayer(2); // Николай (Либеро)
    if (p_libero) {
        p_libero->addAttackStats(5, 0); // Проверката за либеро ще го хване
    }
    std::cout << "\n";

    std::cout << "--- Финален изглед на отбора: ---\n";
    myTeam.printTeamSquad();

    return 0;
}