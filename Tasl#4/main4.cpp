#include <iostream>
#include <string>
#include <random>

struct person
{
    std::string name;
    int life = rand() % 151 + 50;
    int armor = rand() % 51;
    int damage = rand() % 31 + 15;
};
void creation_evil(char battlefield[][20], std::vector<person> &persons)
{
    for (int i = 1; i <= 5; ++i)
    {
        battlefield[rand() % 20][rand() % 20] = i;
        std::cout << "Enter name evil #" << i << ": ";
        std::cin >> persons[i].name;
    }
}
void creation_player(char battlefield[][20], std::vector<person> &persons)
{
    battlefield[rand() % 20][rand() % 20] = 0;
    std::cout << "Enter name Player: ";
    std::cin >> persons[0].name;
    std::cout << "Enter life, armor and damage:" << std::endl;
    std::cin >> persons[0].life >> persons[0].armor >> persons[0].damage;
}
void viewer_battlefield(char battlefield[][20])
{
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
            if (battlefield[i][j] == 0)
                std::cout << 'P';

            else if (battlefield[i][j] == -1)
                std::cout << '*';
            else
                std::cout << 'E';
        }
        std::cout << std::endl;
    }
}
// enum spot
// {
//     player = 1,
//     evil = 2,
//     emptiness = 4
// };
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
    viewer_battlefield(battlefield);
}
