#include <iostream>
#include <vector>
#include <string>
// #include <cstring>
#include <fstream>

struct statement
{
    std::string full_name; 
    char date[10];
    int pay;
};

void list(std::string *pay_statements)
{
    std::ifstream file_pay_statements(*pay_statements, std::ios::binary);
    if (file_pay_statements.is_open())
    {
        int i, quantity(0);
        std::vector<statement> records;
        for (i = 0; !file_pay_statements.eof(); ++i)
        {
            statement temp_record;
            char trash;
            int len;
            file_pay_statements.read((char *)&len, sizeof(len));  
            file_pay_statements.read((char*)&trash, 1);          
            temp_record.full_name.resize(len);
            file_pay_statements.read((char*)temp_record.full_name.c_str(), len);
            if(file_pay_statements.eof())
            break;
            file_pay_statements.read((char*)&trash, 1);
            // char date[10];
            file_pay_statements.read((char*)&temp_record.date, 10);
            // std::cout<<date<<' '<<std::endl;
            // temp_record.date=date;
            // std::cout<<temp_record.date<<std::endl;
            file_pay_statements.read((char*)&trash, 1);
            file_pay_statements.read((char*)&temp_record.pay, sizeof(temp_record.pay));
            file_pay_statements.read((char*)&trash, 1);
            records.push_back(temp_record);
        }
        for (int j = 0; j < i; ++j)
        {
            std::cout << records[j].full_name << '\t' << records[j].date << '\t' << records[j].pay << std::endl;
        }
        file_pay_statements.close();
    }
    else
        std::cout << "ERROR: file missing";
}
void add(std::string *pay_statements)
{
    std::ofstream file_pay_statements(*pay_statements, std::ios::binary | std::ios::app);
    statement record;
    std::cout << "Enter full name: ";
    std::string first_name, last_name;
    std::cin >> first_name >> last_name;
    record.full_name = first_name + ' ' + last_name;
    std::cout << "Enter date: ";
    std::cin >> record.date;
    std::cout << "Enter pay: ";
    std::cin >> record.pay;
    int len = record.full_name.length();
    file_pay_statements.write((char *)&len, sizeof(len));
    file_pay_statements.write(" ", sizeof(char));
    file_pay_statements.write(record.full_name.c_str(), len);
    file_pay_statements.write(" ", sizeof(char));
    file_pay_statements.write(record.date, 10);
    file_pay_statements.write(" ", sizeof(char));
    file_pay_statements.write((char *)&record.pay, sizeof(record.pay));
    file_pay_statements.write("\n", sizeof(char));
    file_pay_statements.close();
}

int main()
{
    std::string pay_statements = "pay.bit";
    std::string command = "list";
    while (command != "-1")
    {
        std::cout << "Enter command: ";
        std::cin >> command;
        if (command == "list")
        {
            list(&pay_statements);
        }
        if (command == "add")
            add(&pay_statements);
    }
}