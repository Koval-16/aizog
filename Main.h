//
// Created by kuba on 22.05.2025.
//

#ifndef AIZOGRAF_MAIN_H
#define AIZOGRAF_MAIN_H
#include <iostream>
#include "Timer.h"

class Main {
public:
    static void start(int arg_number, char* arg_values[]);
private:
    static void help_mode();
    static void file_mode(int problem, int algorithm, std::string input, std::string output, int start_node, int end_node);
    static void test_mode(int problem, int algorithm, int number, float denisty, int iterations, std::string output, int start_node, int end_node);
    static int testing(Graph& graph, int problem, int algorithm, int start_node, int end_node);
    static void singlefile(Graph& graph, int problem, int algorithm, std::string output, int start_node, int end_node);
};


#endif //AIZOGRAF_MAIN_H
