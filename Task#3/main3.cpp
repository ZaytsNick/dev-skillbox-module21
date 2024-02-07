#include <iostream>
#include <string>
#include <vector>
#include <math.h>
struct tdmv // two dimensional mathematical vector
{
    double x_y[2];
};
tdmv write_vec()
{
    tdmv vec;
    std::cout << "Enter X and Y: ";
    std::cin >> vec.x_y[0] >> vec.x_y[1];
    return vec;
}
void add()
{
    tdmv vec[2] = {write_vec(), write_vec()};
    std::cout << "When adding the vector [" << vec[0].x_y[0] << "," << vec[0].x_y[1] << "] and the vector [" << vec[1].x_y[0] << "," << vec[1].x_y[1] << "] we get  [" << vec[0].x_y[0] + vec[1].x_y[0] << "," << vec[0].x_y[1] + vec[1].x_y[1] << "]" << std::endl;
}
void subtract()
{
    tdmv vec[2] = {write_vec(), write_vec()};
    std::cout << "By subtracting the vector [" << vec[0].x_y[0] << "," << vec[0].x_y[1] << "] and the vector [" << vec[1].x_y[0] << "," << vec[1].x_y[1] << "] we get  [" << vec[0].x_y[0] - vec[1].x_y[0] << "," << vec[0].x_y[1] - vec[1].x_y[1] << "]" << std::endl;
}
void scale()
{
    tdmv vec = {write_vec()};
    std::cout << "Enter to scalar: ";
    int scale;
    std::cin >> scale;
    std::cout << "When multiplying a vector [" << vec.x_y[0] << "," << vec.x_y[1] << "] by a scalar " << scale
              << " we get [" << vec.x_y[0] * scale << "," << vec.x_y[1] * scale << "]" << std::endl;
}
void length()
{
    tdmv vec = {write_vec()};
    std::cout << "The length of the vector [" << vec.x_y[0] << "," << vec.x_y[1] << "] is equal to: " << sqrt(pow(vec.x_y[0], 2) + pow(vec.x_y[1], 2)) << std::endl;
}
void normalize()
{
    tdmv vec = {write_vec()};
    auto length = sqrt(pow(vec.x_y[0], 2) + pow(vec.x_y[1], 2));
    std::cout << "Vector [" << vec.x_y[0] << "," << vec.x_y[1] << "]\nNormalized vector: [" << vec.x_y[0] / length << "," << vec.x_y[1] / length << "]" << std::endl;
    // sqrt(pow(vec.x_y[0],2)+pow(vec.x_y[1],2))
}
int main()
{
    std::string operation("0");
    while (operation != "exit")
    {
        std::cout << "Enter operation: ";
        std::cin >> operation;
        if (operation == "add")
        {
            add();
            continue;
        }
        if (operation == "subtract")
        {
            subtract();
            continue;
        }
        if (operation == "scale")
        {
            scale();
            continue;
        }
        if (operation == "length")
        {
            length();
            continue;
        }
        if (operation == "normalize")
        {
            normalize();
            continue;
        }
    }
}