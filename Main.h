//
// Created by kuba on 22.05.2025.
//

#ifndef AIZOGRAF_MAIN_H
#define AIZOGRAF_MAIN_H
#include <iostream>


class Main {
public:
    static void start(int arg_number, char* arg_values[]);
private:
    static void help_mode();
    static void file_mode(int problem, int algorithm, std::string input, std::string output);
    static void test_mode(int problem, int algorithm, int number, float denisty, int iterations, std::string output);
};


#endif //AIZOGRAF_MAIN_H
