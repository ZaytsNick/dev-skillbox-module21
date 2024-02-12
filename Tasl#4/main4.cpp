#include <iostream>
#include <string>
#include <random>
#include <stdlib.h>
struct person
{
    std::string name;
    int position[2] = {rand() % 20, rand() % 20};
    int life =  rand() % 151 + 50;
    int armor =  rand() % 51;
    int damage = rand() % 31 + 15;
};
void creation_evil(char battlefield[][20], std::vector<person> &persons)
{
    for (int i = 1; i <= 5; ++i)
    {
        std::cout << "Enter name evil #" << i << ": ";
        std::cin >> persons[i].name;
    }
}
void creation_player(char battlefield[][20], std::vector<person> &persons)
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

                if (persons[k].position[0] == i && persons[k].position[1] == j)
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
    if (person_2.armor - person_1.damage <= 0)
    {
        person_1.damage -= person_2.armor;
        person_2.armor = 0;
        if (person_2.life - person_1.damage <= 0)
        {
            system("cls");
            std::cout << "Evil in the person of "<<person_2.name <<" is defeated" << std::endl;
            return true;
        }
        else
            person_2.life -= person_1.damage;
    }
    else
    {
        person_2.armor -= person_1.damage;
    }
    return false;
}
void is_there_anyone_here(int x, int y, std::vector<person> &persons)
{
    for (int i = 1; i < 6; ++i)
    {
        if (persons[i].position[0] == x && persons[i].position[1] == y)
        {
            if (fight(persons[0], persons[i]))
            {
                persons.erase(persons.begin() + i);
                persons[0].position[0] = x;
                persons[0].position[1] = y;
                return;
            }
            else
                return;
            
        }
    }
    persons[0].position[0] = x;
    persons[0].position[1] = y;
}

void move(std::vector<person> &persons)
{
    char move;
    while (move != '0')
    {
        std::cout << "W/A/S/D? ";
        std::cin >> move;
        switch (move)
        {
        case 'W':
            is_there_anyone_here(((persons[0].position[0]) - 1), (persons[0].position[1]), persons);
            break;
        case 'A':
            is_there_anyone_here((persons[0].position[0]), ((persons[0].position[1]) - 1), persons);
            break;
        case 'S':
            is_there_anyone_here(((persons[0].position[0]) + 1), (persons[0].position[1]), persons);
            break;
        case 'D':
            is_there_anyone_here((persons[0].position[0]), ((persons[0].position[1]) + 1), persons);
            break;
        default:
            break;
        }
        viewer_battlefield(persons); 
    }
}
int main()
{
    char battlefield[20][20];
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
            battlefield[i][j] = -1;
        }
    }
    std::vector<person> persons(6);
    creation_evil(battlefield, persons);
    creation_player(battlefield, persons);
    viewer_battlefield(persons);
    move(persons);
}
