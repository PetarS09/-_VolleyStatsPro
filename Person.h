#ifndef PERSON_H
#define PERSON_H
#include <string>

class Person {
private:
    std::string name;
    std::string egn;
    std::string phone;
    std::string birthDate;
protected:
    int getBirthYear() const;
public:
    Person(std::string name, std::string egn, std::string phone, std::string birthDate);
    virtual ~Person();
    int getAge() const;
    std::string getName() const;
    std::string getEgn() const;
    virtual void printInfo() const;
};
#endif