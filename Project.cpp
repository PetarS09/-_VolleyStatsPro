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

public:
    Player(std::string name, std::string egn, std::string phone, std::string birthDate, 
           std::string position, int jerseyNumber)
        : Person(name, egn, phone, birthDate), position(position), jerseyNumber(jerseyNumber) {}

    std::string getPosition() const { return position; }

    void printInfo() const override {
        Person::printInfo();
        std::cout << " | №" << jerseyNumber << " | Позиция: " << position << "\n";
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

int main() {
    std::vector<std::unique_ptr<Person>> teamSquad;
    
    std::cout << "--- 1. Базово добавяне на състав ---\n";
    teamSquad.push_back(std::make_unique<Player>("Георги Петров", "104215xxxx", "0888111222", "2010-02-15", "Разпределител", 10));
    teamSquad.push_back(std::make_unique<Coach>("Андрей Жеков", "800101xxxx", "0888999999", "1980-01-01", "A-0542"));

    for (const auto& member : teamSquad) {
        member->printInfo();
    }
    return 0;
}