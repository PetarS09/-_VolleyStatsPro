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
    // Помощен метод за извличане на годината от birthDate (първите 4 символа)
    int getBirthYear() const {
        if (birthDate.length() >= 4) {
            return std::stoi(birthDate.substr(0, 4));
        }
        return 2000; // Стойност по подразбиране при грешка
    }

public:
    Person(std::string name, std::string egn, std::string phone, std::string birthDate)
        : name(name), egn(egn), phone(phone), birthDate(birthDate) {}

    virtual ~Person() {} // Виртуален деструктор - задължителен за наследяване

    // ПРОМЯНА В ДИЗАЙНА: Възрастта не е поле, а се изчислява спрямо текущата година (2026)
    int getAge() const {
        int currentYear = 2026; 
        return currentYear - getBirthYear();
    }

    std::string getName() const { return name; }
    std::string getEgn() const { return egn; }

    // Виртуален метод за извеждане на информация
    virtual void printInfo() const {
        std::cout << "Име: " << name << " | Възраст: " << getAge() 
                  << " г. (Роден/а: " << birthDate << ") | Тел: " << phone;
    }
};

// ============================================================================
// НАСЛЕДНИК: Player (Функционалност 1: Наследяване и Набори)
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

    // Гетър за позицията
    std::string getPosition() const { return position; }

    // Функционалност 3: Автоматично определяне на възрастова група (Набор)
    std::string getAgeGroup() const {
        int age = getAge();
        if (age <= 16) return "U16";
        if (age <= 18) return "U18";
        if (age <= 21) return "U21";
        return "Мъже/Жени";
    }

    // Функционалност 4: Въвеждане на сурови данни за статистика + проверка за Либеро
    void addAttackStats(int attacks, int errors) {
        // Волейболна проверка: Либерото не може да атакува!
        if (position == "Либеро") {
            std::cout << "⚠️ Грешка: Играчът " << getName() << " е Либеро и не може да има статистика за атака!\n";
            return;
        }

        if (attacks >= 0 && errors >= 0 && errors <= attacks) {
            totalAttacks += attacks;
            attackErrors += errors;
        }
    }

    // Функционалност 4: Изчисляване на коефициент на ефективност
    double getAttackEfficiency() const {
        if (totalAttacks == 0) return 0.0;
        return static_cast<double>(totalAttacks - attackErrors) / totalAttacks;
    }

    void printInfo() const override {
        Person::printInfo();
        std::cout << " | №" << jerseyNumber << " | Позиция: " << position 
                  << " | Категория: " << getAgeGroup();
        
        // Либерото не показва офанзивна статистика
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

public:
    Coach(std::string name, std::string egn, std::string phone, std::string birthDate, std::string licenseID)
        : Person(name, egn, phone, birthDate), licenseID(licenseID) {}

    void printInfo() const override {
        Person::printInfo();
        std::cout << " | [ТРЕНЬОР] Лиценз: " << licenseID << "\n";
    }
};

// ============================================================================
// КЛАС: Match (Функционалност 2: Записване на мачове)
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
// ГЛАВНА ФУНКЦИЯ (Тестване на функционалностите)
// ============================================================================
int main() {
    // Контейнер за управление на състава (Полиморфизъм с unique_ptr)
    std::vector<std::unique_ptr<Person>> teamSquad;

    std::cout << "--- 1. Добавяне на играчи и треньори (Squad Management) ---\n";
    // Добавяме състезатели с различни позиции и набори
    teamSquad.push_back(std::make_unique<Player>("Георги Петров", "104215xxxx", "0888111222", "2010-02-15", "Разпределител", 10)); // На 16 г. -> U16
    teamSquad.push_back(std::make_unique<Player>("Мартин Иванов", "084512xxxx", "0888333444", "2008-05-12", "Диагонал", 7));       // На 18 г. -> U18
    teamSquad.push_back(std::make_unique<Player>("Николай Василев", "094111xxxx", "0888555666", "2009-11-11", "Либеро", 4));      // Набор 2009 -> U18 Либеро
    teamSquad.push_back(std::make_unique<Coach>("Андрей Жеков", "800101xxxx", "0888999999", "1980-01-01", "A-0542"));

    // Извеждане на състава
    for (const auto& member : teamSquad) {
        member->printInfo();
    }
    std::cout << "\n";

    std::cout << "--- 2. Записване на мачове (Match Logging) ---\n";
    std::vector<Match> matchHistory;
    matchHistory.push_back(Match("ЦСКА", "2026-03-10", 3, 1));
    matchHistory.push_back(Match("Марек Дупница", "2026-03-17", 2, 3));

    for (const auto& match : matchHistory) {
        match.printMatchSummary();
    }
    std::cout << "\n";

    std::cout << "--- 3. Добавяне и анализ на статистика (Stats & Efficiency) ---\n";
    
    // 3.1. Опит за добавяне на статистика на атакуващ играч (Успешно)
    Player* player1 = dynamic_cast<Player*>(teamSquad[0].get());
    if (player1) {
        player1->addAttackStats(20, 4); // 20 атаки, 4 грешки -> 16 успешни. Ефективност: 16/20 = 80%
        std::cout << "Обновена статистика за " << player1->getName() << ":\n";
        player1->printInfo();
    }
    std::cout << "\n";

    // 3.2. Опит за добавяне на статистика за атака на Либерото (Ще хване проверката)
    Player* libero = dynamic_cast<Player*>(teamSquad[2].get()); // Индекс 2 е Николай (Либеро)
    if (libero) {
        std::cout << "Опит за добавяне на атаки на либерото " << libero->getName() << "...\n";
        libero->addAttackStats(10, 2); 
    }

    return 0;
}