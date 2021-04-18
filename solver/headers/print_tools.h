#ifndef PRINT_TOOLS
#define PRINT_TOOLS

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

std::ostream& operator<< (std::ostream& os, std::vector<double>& v);
void PrintTable(std::vector<double>& X, std::vector<double>& Y);

template <class T>
void PrintNames(T names) {
    int i = 1;
    for (const auto& name : names) {
        std::cout << i << ". " << name << std::endl;
        ++i;
    }
}

#endif // PRINT_TOOLS

