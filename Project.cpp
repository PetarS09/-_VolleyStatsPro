#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Person {
private:
    std::string name;
    std::string egn;
    std::string phone;
    std::string birthDate;

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

    virtual void printInfo() const {
        std::cout << "Име: " << name << " | Възраст: " << getAge() 
                  << " г. (Роден: " << birthDate << ") | Тел: " << phone;
    }
};

class Player : public Person {
private:
    std::string position;
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
        if (age < 16) return "U16";
        if (age < 18) return "U18";
        if (age < 21) return "U21";
        return "Мъже/Жени";
    }

    void addAttackStats(int attacks, int errors) {
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
                  << " | Категория: " << getAgeGroup() 
                  << " | Ефективност в атака: " << getAttackEfficiency() * 100 << "%\n";
    }
};

class Coach : public Person {
private:
    std::string licenseID;

public:
    Coach(std::string name, std::string egn, std::string phone, std::string birthDate, std::string licenseID)
        : Person(name, egn, phone, birthDate), licenseID(licenseID) {}

    void printInfo() const override {
        Person::printInfo();
        std::cout << " | [ТРЕНЬОР] Лиценз: " << licenseID << "\n";
    }
};

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

int main() {
    std::vector<std::unique_ptr<Person>> teamSquad;
    
    std::cout << "--- 1. Базово добавяне на състав (Squad Management) ---\n";
    teamSquad.push_back(std::make_unique<Player>("Георги Петров", "104215xxxx", "0888111222", "2010-02-15", "Разпределител", 10));
    teamSquad.push_back(std::make_unique<Coach>("Андрей Жеков", "800101xxxx", "0888999999", "1980-01-01", "A-0542"));

    for (const auto& member : teamSquad) {
        member->printInfo();
    }
    std::cout << "\n";

    std::cout << "--- 2. Записване на мачове (Match Logging) ---\n";
    std::vector<Match> matchHistory;
    matchHistory.push_back(Match("ЦСКА", "2026-03-10", 3, 1));
    for (const auto& match : matchHistory) {
        match.printMatchSummary();
    }
    std::cout << "\n";

    std::cout << "--- 3. Добавяне и анализ на статистика (Stats & Efficiency) ---\n";
    Player* player1 = dynamic_cast<Player*>(teamSquad[0].get());
    if (player1) {
        player1->addAttackStats(20, 4); // Тестване на статистиката
        std::cout << "Обновена статистика за " << player1->getName() << ":\n";
        player1->printInfo();
    }

    return 0;
}