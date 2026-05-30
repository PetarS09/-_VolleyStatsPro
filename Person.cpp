#include "Person.h"
#include <iostream>

Person::Person(std::string name, std::string egn, std::string phone, std::string birthDate)
    : name(name), egn(egn), phone(phone), birthDate(birthDate) {}

Person::~Person() {}

int Person::getBirthYear() const {
    if (birthDate.length() >= 4) {
        return std::stoi(birthDate.substr(0, 4));
    }
    return 2000;
}

int Person::getAge() const {
    return 2026 - getBirthYear(); // Текуща календарна година по задание: 2026
}

std::string Person::getName() const { return name; }
std::string Person::getEgn() const { return egn; }
std::string Person::getPhone() const { return phone; }
std::string Person::getBirthDate() const { return birthDate; }

void Person::printInfo() const {
    std::cout << "Име: " << name << " | Възраст: " << getAge() 
              << " г. (Роден/а: " << birthDate << ") | Тел: " << phone;
}