#include <iostream>
#include <vector>
#include <string>
#include <utility>

enum type_room
{
    bedroom = 1,
    kitchen = 2,
    bathroom = 4,
    children_s = 8,
    living_room = 16
};
enum type_construction
{
    house = 1,
    garage = 2,
    barn = 4,
    bathhouse = 8
};
struct room
{
    char type_room;
    int square;
};

struct floor
{
    int height;
    std::vector<room> rooms;
};
struct construction
{
    char type_construction;
    int square;
    std::vector<floor> floor;
    bool stove_with_pipe;
};
struct plot
{
    int id;
    std::vector<construction> construction;
};
int main()
{
    int quantity_plot;
    std::cout << "Enter quantity plot: ";
    std::cin >> quantity_plot;
    std::vector<plot> plots(quantity_plot);
    for (int i = 0; i < quantity_plot; ++i)
    {
        plots[i].id = i + 1;
        std::cout << "Plot #" << plots[i].id << std::endl;
        std::cout << "Enter quantity construction: ";
        int quantity_construction;
        std::cin >> quantity_construction;
        plots[i].construction.resize(quantity_construction);
        for (int j = 0; j < quantity_construction; ++j)
        {
            std::cout << "Enter type construction(0 - house,1 - garage,2 - barn,3 - bathhouse): ";
            char tmp_type_construction;
            std::cin >> tmp_type_construction;
            switch (tmp_type_construction)
            {
            case '0':
                plots[i].construction[j].type_construction = type_construction::house;
                break;
            case '1':
                plots[i].construction[j].type_construction = type_construction::garage;
                break;
            case '2':
                plots[i].construction[j].type_construction = type_construction::barn;
                break;
            case '3':
                plots[i].construction[j].type_construction = type_construction::bathhouse;
                break;
            }

            std::cout << "Enter square construction: " << std::endl;
            std::cin >> plots[i].construction[j].square;
            if (plots[i].construction[j].type_construction == type_construction::house)
            {
                int quantity_floor;
                std::cout << "Enter quantity floor: " << std::endl;
                std::cin >> quantity_floor;
                plots[i].construction[j].floor.resize(quantity_floor);
                for (int k = 0; k < quantity_floor; ++k)
                {
                    std::cout << "Enter height floor #" << k + 1 << ": ";
                    std::cin >> plots[i].construction[j].floor[k].height;
                    std::cout << "Enter quantity rooms: ";

                    int quantity_rooms;
                    std::cin >> quantity_rooms;
                    plots[i].construction[j].floor[k].rooms.resize(quantity_rooms);
                    for (int l = 0; l < quantity_rooms; ++l)
                    {
                        std::cout << "Enter type and square room #" << l + 1 << "\n type:\n0 - bedroom,\n1 - kitchen,\n2 - bathroom,\n3 - children_s,\n4 - living_room" << std::endl;
                        char tmp_type_room('o');
                        std::cin >> tmp_type_room >> plots[i].construction[j].floor[k].rooms[l].square;
                        switch (tmp_type_room)
                        {
                        case '0':
                            plots[i].construction[j].floor[k].rooms[l].type_room = type_room::bedroom;
                            break;
                        case '1':
                            plots[i].construction[j].floor[k].rooms[l].type_room = type_room::kitchen;
                            break;
                        case '2':
                            plots[i].construction[j].floor[k].rooms[l].type_room = type_room::bathroom;
                            break;
                        case '3':
                            plots[i].construction[j].floor[k].rooms[l].type_room = type_room::children_s;
                            break;
                        case '4':
                            plots[i].construction[j].floor[k].rooms[l].type_room = type_room::living_room;
                            break;
                        }
                    }
                }
            }
            else
            {
                plots[i].construction[j].floor.resize(0);
            }
            if (plots[i].construction[j].type_construction == type_construction::house || plots[i].construction[j].type_construction == type_construction::bathhouse) // если дом или баня
            {
                std::cout << "Enter yes or no stove with pipe: ";
                std::cin >> plots[i].construction[j].stove_with_pipe;
            }
        }
    }

    for (int i = 0; i < quantity_plot; ++i)
    {
        std::cout << "Plot#" << plots[i].id << std::endl;
        std::cout << "There are " << size(plots[i].construction) << " buildings on the site" << std::endl;
        for (int j = 0; j < size(plots[i].construction); ++j)
        {
            std::string s_type_construction;
            switch (plots[i].construction[j].type_construction)
            {
            case type_construction::house:
                s_type_construction = "house";
                break;

            case type_construction::garage:
                s_type_construction = "garage";
                break;

            case type_construction::barn:
                s_type_construction = "barn";
                break;

            case type_construction::bathhouse:
                s_type_construction = "bathhouse";
                break;
            }
            std::cout << "\tСonstracion #" << j + 1 << " " << s_type_construction << std::endl;
            std::cout << "\tThis building has area: " << plots[i].construction[j].square << std::endl;
            if (plots[i].construction[j].type_construction == type_construction::house)
            {
                std::cout << "\tThe house has " << size(plots[i].construction[j].floor) << " floor" << std::endl;
                for (int k = 0; k < size(plots[i].construction[j].floor); ++k)
                {
                    std::cout << "\t\tFloor#" << k + 1 << "\n\t\theight: " << plots[i].construction[j].floor[k].height << "\n\t\t" << size(plots[i].construction[j].floor[k].rooms) << " rooms" << std::endl;
                    for (int l = 0; l < size(plots[i].construction[j].floor[k].rooms); ++l)
                    {
                        std::string s_type_room;
                        switch (plots[i].construction[j].floor[k].rooms[l].type_room)
                        {
                        case type_room::bedroom:
                            s_type_room = "bedroom";
                            break;
                        case type_room::kitchen:
                            s_type_room = "kitchen";
                            break;
                        case type_room::bathroom:
                            s_type_room = "bathroom";
                            break;
                        case type_room::children_s:
                            s_type_room = "children's";
                            break;
                        case type_room::living_room:
                            s_type_room = "living room";
                            break;

                        default:
                            break;
                        }
                        std::cout << "\t\t\tRoom #" << l + 1 << " " << s_type_room << "\n\t\t\tSquare room: " << plots[i].construction[j].floor[k].rooms[l].square << std::endl;
                    }
                }
            }
            if (plots[i].construction[j].stove_with_pipe & (plots[i].construction[j].type_construction == type_construction::house || plots[i].construction[j].type_construction == type_construction::bathhouse))
            {
                std::cout << "\tThere is a stove in the " << plots[i].construction[j].type_construction << std::endl;
            }
        }
    }
}
