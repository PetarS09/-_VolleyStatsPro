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

// ============================================================================
// НАСЛЕДНИК: Player (С добавена логика за набори/възрастови групи)
// ============================================================================
class Player : public Person {
private:
    std::string position;
    int jerseyNumber;

public:
    Player(std::string name, std::string egn, std::string phone, std::string birthDate, 
           std::string position, int jerseyNumber)
        : Person(name, egn, phone, birthDate), position(position), jerseyNumber(jerseyNumber) {}

    std::string getPosition() const { return position; }

    // Функционалност: Автоматично определяне на възрастова група (Набор)
    std::string getAgeGroup() const {
        int age = getAge();
        if (age < 16) return "U16";
        if (age < 18) return "U18";
        if (age < 21) return "U21";
        return "Мъже/Жени";
    }

    void printInfo() const override {
        Person::printInfo();
        std::cout << " | №" << jerseyNumber << " | Позиция: " << position 
                  << " | Категория: " << getAgeGroup() << "\n";
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
// ГЛАВНА ФУНКЦИЯ
// ============================================================================
int main() {
    std::vector<std::unique_ptr<Person>> teamSquad;
    
    std::cout << "--- 1. Добавяне на състав и проверка на възрастовите групи ---\n";
    // Георги е роден 2010 г. -> през 2026 г. е на 16 г. -> категория U16
    teamSquad.push_back(std::make_unique<Player>("Георги Петров", "104215xxxx", "0888111222", "2010-02-15", "Разпределител", 10));
    // Добавяме играч, роден 2008 г. -> през 2026 г. е на 18 г. -> категория U18
    teamSquad.push_back(std::make_unique<Player>("Мартин Иванов", "084512xxxx", "0888333444", "2008-05-12", "Диагонал", 7));
    teamSquad.push_back(std::make_unique<Coach>("Андрей Жеков", "800101xxxx", "0888999999", "1980-01-01", "A-0542"));

    for (const auto& member : teamSquad) {
        member->printInfo();
    }
    
    return 0;
}