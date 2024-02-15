#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include <stdlib.h>
struct person
{
    std::string name;
    int position[2] = {rand() % 20, rand() % 20};
    int life = rand() % 151 + 50;
    int armor = rand() % 51;
    int damage = rand() % 31 + 15;
};
void save(std::vector<person> &persons)
{
    system("cls");
    std::ofstream file("save.bin", std::ios::binary);
    if (file.is_open())
    {
        for (int i = 0; i < 6; ++i)
        {
            int len = persons[i].name.length();
            file.write((char *)&len, sizeof(len));
            file.write(persons[i].name.c_str(), len);
            file.write((char *)&persons[i].position[0], sizeof(persons[i].position[0]));
            file.write((char *)&persons[i].position[1], sizeof(persons[i].position[0]));
            file.write((char *)&persons[i].life, sizeof(int));
            file.write((char *)&persons[i].armor, sizeof(int));
            file.write((char *)&persons[i].damage, sizeof(int));
            file.write("\n", sizeof(char));
        }
    }
}
void load(std::vector<person> &persons)
{
    system("cls");
    std::ifstream file("save.bin", std::ios::binary);
    if (file.is_open())
    {
        for (int i = 0; i < 6; ++i)
        {
            int len;
            char trash;
            file.read((char *)&len, sizeof(len));
            persons[i].name.resize(len);
            file.read((char *)persons[i].name.c_str(), len);
            file.read((char *)&persons[i].position[0], sizeof(persons[i].position[0]));
            file.read((char *)&persons[i].position[1], sizeof(persons[i].position[1]));
            file.read((char *)&persons[i].life, sizeof(int));
            file.read((char *)&persons[i].armor, sizeof(int));
            file.read((char *)&persons[i].damage, sizeof(int));
            file.read((char *)&trash, 1);
        }
    }
    else
        std::cout << "ERROR: save file is missing";
}
void creation_evil(std::vector<person> &persons)
{
    for (int i = 1; i <= 5; ++i)
    {
        std::cout << "Enter name evil #" << i << ": ";
        std::cin >> persons[i].name;
    }
}
void creation_player(std::vector<person> &persons)
{

    std::cout << "Enter name Player: ";
    std::cin >> persons[0].name;
    std::cout << "Enter life, armor and damage:" << std::endl;
    std::cin >> persons[0].life >> persons[0].armor >> persons[0].damage;
}
void viewer_battlefield(std::vector<person> &persons)
{
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
            bool tmp(false);
            for (int k = 0; k < 6; ++k)
            {
                if (persons[k].position[0] == i && persons[k].position[1] == j && persons[k].life > 0)
                {
                    if (k)
                        std::cout << 'E';
                    else
                        std::cout << 'P';
                    tmp = true;
                    break;
                }
            }
            if (!tmp)
                std::cout << '*';
        }
        std::cout << std::endl;
    }
}
bool fight(person person_1, person &person_2)
{
    std::cout << person_1.name << " attacks " << person_2.name << "\n\t   LIFE\n\t"
              << person_1.life << "|" << person_2.life << "\n\t   ARMOR\n\t"
              << person_1.armor << "|" << person_2.armor << "\n\t   DAMAGE\n\t"
              << person_1.damage << "|" << person_2.damage << std::endl;
    system("pause");
    if (person_2.armor - person_1.damage <= 0)
    {
        person_1.damage -= person_2.armor;
        person_2.armor = 0;
        if (person_2.life - person_1.damage <= 0)
        {
            std::cout << person_2.name << " is defeated" << std::endl;
            person_2.life = 0;
            person_2.damage = 0;
            person_2.position[0] = -1;
            person_2.position[1] = -1;
            system("pause");
            return true;
        }
        else
        {
            person_2.life -= person_1.damage;
            std::cout << person_2.name << " was hurt, but it's still alive" << std::endl;
            system("pause");
        }
    }
    else
    {
        person_2.armor -= person_1.damage;
        std::cout << person_2.name << " armor was damaged" << std::endl;
        system("pause");
    }
    return false;
}
bool evil_life(std::vector<person> &persons)
{
    int evil_life;
    for (int i = 1; i < 6; ++i)
    {
        evil_life += persons[i].life;
    }
    if (evil_life <= 0)
        return true;
    else
        return false;
}
void is_there_anyone_here(int *id_attacking, int x, int y, std::vector<person> &persons)
{
    system("cls");
    for (int id_defending = 0; id_defending < 6; ++id_defending)
    {
        if (persons[id_defending].position[0] == x && persons[id_defending].position[1] == y)
        {
            if ((id_defending == 0 || *id_attacking == 0) && fight(persons[*id_attacking], persons[id_defending]))
            {
                persons[*id_attacking].position[0] = x;
                persons[*id_attacking].position[1] = y;
                return;
            }
            else
                return;
        }
    }
    persons[*id_attacking].position[0] = x;
    persons[*id_attacking].position[1] = y;
}
void move(std::vector<person> &persons)
{
    char move;
    while (move != '0')
    {
        system("cls");
        viewer_battlefield(persons);
        for (int i = 0; i < 6; ++i)
        {
            if (persons[i].life <= 0)
            {
                continue;
            }
            else
            {
                if (i == 0)
                {

                    std::cout << "Name:" << persons[i].name << "\nLife:" << persons[i].life << "/Armor:" << persons[i].armor << "/Damage:" << persons[i].damage << "\nW/A/S/D? ";
                    std::string tmp_move;
                    std::cin >> tmp_move;
                    if (tmp_move == "save")
                    {
                        save(persons);
                        break;
                    }
                    else if (tmp_move == "load")
                    {
                        load(persons);
                        break;
                    }
                    else
                        move = tmp_move[0];
                }
                else
                {
                    switch (rand() % 4)
                    {
                    case 0:
                        move = 'W';
                        break;
                    case 1:
                        move = 'A';
                        break;
                    case 2:
                        move = 'S';
                        break;
                    case 3:
                        move = 'D';
                        break;
                    };
                }
                switch (move)
                {
                case 'W':
                    if (((persons[i].position[0]) - 1) < 20 && ((persons[i].position[0]) - 1) >= 0)
                        is_there_anyone_here(&i, ((persons[i].position[0]) - 1), (persons[i].position[1]), persons);
                    break;
                case 'A':
                    if (((persons[i].position[1]) - 1) < 20 && ((persons[i].position[1]) - 1) >= 0)
                        is_there_anyone_here(&i, (persons[i].position[0]), ((persons[i].position[1]) - 1), persons);
                    break;
                case 'S':
                    if (((persons[i].position[0]) + 1) < 20 && ((persons[i].position[0]) + 1) >= 0)
                        is_there_anyone_here(&i, ((persons[i].position[0]) + 1), (persons[i].position[1]), persons);
                    break;
                case 'D':
                    if (((persons[i].position[1]) + 1) < 20 && ((persons[i].position[1]) + 1) >= 0)
                        is_there_anyone_here(&i, (persons[i].position[0]), ((persons[i].position[1]) + 1), persons);
                    break;
                }
            }
        }
        if (evil_life(persons))
        {
            system("cls");
            std::cout << "\t\tYOU WON\nsay EEhaaa and leave" << std::endl;
            system("pause");
            return;
        }
        if (persons[0].life <= 0)
        {
            system("cls");
            std::cout << "YOU LOSE\nPromise that you will return and defeat evil" << std::endl;
            system("pause");
            return;
        }
    }
}
int main()
{
    std::srand(std::time(nullptr));
    std::cout << "The game ends when either all opponents or the player die." << std::endl;
    std::cout << "In the first case, a message about victory is displayed on " << std::endl;
    std::cout << "the screen, in the second - about defeat.\n"
              << std::endl;
    system("pause");
    std::cout << "If at the beginning of a player's turn he enters a save or " << std::endl;
    std::cout << "load command instead of moving in a direction, the game" << std::endl;
    std::cout << "either saves its state to a file or loads that state from a file." << std::endl;
    system("pause");
    system("cls");
    std::vector<person> persons(6);
    creation_evil(persons);
    creation_player(persons);
    move(persons);
}
