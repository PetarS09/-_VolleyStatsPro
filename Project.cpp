#include <iostream>
#include <limits>
#include <string>
#include "Team.h"

// Помощна функция за безопасно въвеждане на цяло число
int getSafeInt(std::string prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "❌ Невалиден вход! Моля, въведете число.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Помощна функция за избор на волейболен пост чрез меню
std::string getVolleyballPosition() {
    while (true) {
        std::cout << "\nИзберете пост на играча (1-5):\n";
        std::cout << "1. Разпределител\n";
        std::cout << "2. Диагонал\n";
        std::cout << "3. Център\n";
        std::cout << "4. Посрещач\n";
        std::cout << "5. Либеро\n";
        int choice = getSafeInt("Вашият избор: ");
        
        if (choice == 1) return "Разпределител";
        if (choice == 2) return "Диагонал";
        if (choice == 3) return "Център";
        if (choice == 4) return "Посрещач";
        if (choice == 5) return "Либеро";
        std::cout << "❌ Невалидна опция! Изберете число между 1 и 5.\n";
    }
}

// Функция за намиране на играч в отбора чрез име или номер на екип
Player* searchPlayerMenu(Team& team) {
    std::cout << "\nКак искате да намерите играча?\n";
    std::cout << "1. Чрез първо име\n";
    std::cout << "2. Чрез номер на екип\n";
    int mode = getSafeInt("Избор: ");

    if (mode == 1) {
        std::string firstName;
        std::cout << "Въведете първо име на играча: ";
        std::cin >> firstName;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        Player* p = team.findPlayerByName(firstName);
        if (!p) std::cout << "❌ Не е намерен играч с първо име '" << firstName << "'\n";
        return p;
    } 
    else if (mode == 2) {
        int jersey = getSafeInt("Въведете номер на екип: ");
        Player* p = team.findPlayerByJersey(jersey);
        if (!p) std::cout << "❌ Не е намерен играч с №" << jersey << "\n";
        return p;
    }
    std::cout << "❌ Невалиден избор на режим за търсене.\n";
    return nullptr;
}

int main() {
    // АВТОМАТИЧНА КОРЕКЦИЯ ЗА БЪЛГАРСКИ ЕЗИК В WINDOWS КОНЗОЛАТА
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif

    std::cout << "===================================================\n";
    std::cout << "      ДОБРЕ ДОШЛИ В VOLLEYSTATS PRO v2.0           \n";
    std::cout << "===================================================\n";

    // Инициализация на системата с един базов отбор (U21)
    Team myTeam("ВК Левски София", "U21");
    myTeam.setCoach(std::make_unique<Coach>("Андрей Жеков", "800101xxxx", "0888111222", "1980-01-01", "FIVB-III", 120, true));

    while (true) {
        std::cout << "\n--- ГЛАВНО МЕНЮ ---\n";
        std::cout << "1. Добавяне на нов играч в отбора\n";
        std::cout << "2. Въвеждане на игрова статистика (Посрещане/Защита/Атака/Блок)\n";
        std::cout << "3. Преглед на текущия състав и рейтинги\n";
        std::cout << "4. Автоматично генериране на стартови 7 (Line-up)\n";
        std::cout << "5. Регистриране на официален волейболен мач\n";
        std::cout << "6. Записване на проведена тренировка\n";
        std::cout << "7. Експорт на текстов отчет (report.txt) & Изход\n";
        
        int menuChoice = getSafeInt("Изберете опция (1-7): ");
        if (menuChoice == 7) {
            myTeam.exportReport();
            std::cout << "\n👋 Благодарим ви, че използвахте мениджъра! Довиждане.\n";
            break;
        }

        switch (menuChoice) {
            case 1: {
                std::cout << "\n--- ДОБАВЯНЕ НА ИГРАЧ ---\n";
                std::string name, egn, phone, birthDate;
                
                std::cout << "Въведете трите имена: ";
                std::getline(std::cin, name);
                std::cout << "Въведете ЕГН: ";
                std::cin >> egn;
                std::cout << "Въведете телефон: ";
                std::cin >> phone;
                std::cout << "Въведете дата на раждане (ГГГГ-ММ-ДД): ";
                std::cin >> birthDate;
                
                std::string position = getVolleyballPosition();
                int jersey = getSafeInt("Въведете номер на екип (1-99): ");

                myTeam.addPlayer(std::make_unique<Player>(name, egn, phone, birthDate, position, jersey));
                break;
            }
            case 2: {
                std::cout << "\n--- ДОБАВЯНЕ НА СТАТИСТИКА ---";
                Player* player = searchPlayerMenu(myTeam);
                if (!player) break;

                std::cout << "\nИзберете какъв елемент ще записвате за " << player->getName() << ":\n";
                std::cout << "1. Посрещане (3-метрова линия: 1, 0, -1, -2)\n";
                std::cout << "2. Защита/Диг (3-метрова линия: 1, 0, -1, -2)\n";
                std::cout << "3. Атака (Опити и Грешки)\n";
                std::cout << "4. Блокада (Успешни блокове)\n";
                int statType = getSafeInt("Избор: ");

                if (statType == 1) {
                    std::cout << "Въведете код на качеството (1=Перфектно, 0=Неутрално, -1=Лошо, -2=Ас): ";
                    int code = getSafeInt("");
                    player->registerReception(code);
                } 
                else if (statType == 2) {
                    std::cout << "Въведете код на качеството (1=Перфектно, 0=Неутрално, -1=Лошо, -2=Грешка): ";
                    int code = getSafeInt("");
                    player->registerDig(code);
                } 
                else if (statType == 3) {
                    int attacks = getSafeInt("Брой опити за атака: ");
                    int errors = getSafeInt("От тях директни грешки/антени: ");
                    player->addAttackStats(attacks, errors);
                } 
                else if (statType == 4) {
                    int blocks = getSafeInt("Брой успешни блокади (точки): ");
                    player->addBlockStats(blocks);
                }
                break;
            }
            case 3:
                myTeam.printTeamSquad();
                break;
            case 4:
                myTeam.generateLineUp();
                break;
            case 5: {
                std::cout << "\n--- РЕГИСТРИРАНЕ НА ОФИЦИАЛЕН МАЧ ---\n";
                std::string opponent, date;
                std::cout << "Име на противника: ";
                std::getline(std::cin, opponent);
                std::cout << "Дата на мача (ГГГГ-ММ-ДД): ";
                std::cin >> date;
                
                int teamSets = getSafeInt("Спечелени геймове от Левски (0-3): ");
                int oppSets = getSafeInt("Спечелени геймове от противника (0-3): ");

                std::vector<SetScore> sets;
                std::cout << "Въвеждане на точкови резултати за всеки гейм:\n";
                for (int i = 0; i < (teamSets + oppSets); i++) {
                    std::cout << "Гейм " << (i + 1) << " -> ";
                    int p1 = getSafeInt("Точки Левски: ");
                    int p2 = getSafeInt("Точки Противник: ");
                    sets.push_back({p1, p2});
                }

                Match newMatch(opponent, date, teamSets, oppSets, sets);
                myTeam.addMatch(newMatch); 
                break;
            }
            case 6: {
                std::cout << "\n--- ЗАПИС НА ТРЕНИРОВКА ---\n";
                std::string date;
                std::cout << "Дата: ";
                std::cin >> date;
                int duration = getSafeInt("Времетраене в минути: ");
                
                std::cout << "Тип на тренировката:\n1. Тактическа в зала\n2. Силова във фитнес\n";
                int tType = getSafeInt("Избор: ");
                
                if (tType == 1) {
                    std::string focus;
                    std::cout << "Фокус на тренировката (напр. Сервиз-Посрещане): ";
                    std::cin.ignore();
                    std::getline(std::cin, focus);
                    myTeam.addTrainingSession(std::make_unique<CourtPractice>(date, duration, focus));
                } else if (tType == 2) {
                    std::string ex;
                    std::cout << "Основно упражнение: ";
                    std::cin.ignore();
                    std::getline(std::cin, ex);
                    int s = getSafeInt("Серии: ");
                    int r = getSafeInt("Повторения: ");
                    myTeam.addTrainingSession(std::make_unique<StrengthWorkout>(date, duration, ex, s, r));
                }
                std::cout << "✅ Тренировката бе добавена в дневника.\n";
                break;
            }
            default:
                std::cout << "❌ Невалиден избор! Моля, опитайте отново.\n";
        }
    }
    return 0;
}