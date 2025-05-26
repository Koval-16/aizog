//
// Created by kuba on 19.05.2025.
//

#ifndef AIZOGRAF_FILEHANDLER_H
#define AIZOGRAF_FILEHANDLER_H

#include <iostream>
#include "Graph.h"

class FileHandler {
public:
    static void read_file(std::string& filename, Graph& graph, bool directed);
    static void save_to_file(std::string& filename, Graph& graph);
};


#endif //AIZOGRAF_FILEHANDLER_H
