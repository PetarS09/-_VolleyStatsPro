#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected:
    std::string name;
    std::string egn;
    std::string phone;
    std::string birthDate; // Формат: ГГГГ-ММ-ДД

protected:
    int getBirthYear() const;

public:
    Person(std::string name, std::string egn, std::string phone, std::string birthDate);
    virtual ~Person();

    int getAge() const;
    std::string getName() const;
    std::string getEgn() const;
    std::string getPhone() const;
    std::string getBirthDate() const;

    virtual void printInfo() const;
};

#endif