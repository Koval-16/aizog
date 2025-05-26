//
// Created by kuba on 19.05.2025.
//

#include "FileHandler.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

void FileHandler::read_file(std::string &filename, Graph &graph, bool directed) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Failed to open the file.");
    std::string text;
    int index = 0;
    try{
        while(std::getline(file,text)){
            if(index==0){
                std::istringstream iss(text);
                int number_nodes, number_edges;
                if(!(iss >> number_nodes >> number_edges)){
                    throw std::runtime_error("Expected two values");
                }
                if(number_nodes<=0) throw std::runtime_error("Incorrect number of nodes");
                graph.set_nodes(number_nodes);
                graph.init();
            }
            else{
                std::istringstream iss(text);
                int node_beg, node_end, wage;
                if(!(iss >> node_beg >> node_end >> wage)){
                    throw std::runtime_error("Expected three values");
                }
                graph.add_edge(node_beg, node_end, wage, directed);
            }
            index++;
        }
    }
    catch (std::exception &e){
        throw std::runtime_error("Error occurred");
    }
}

void FileHandler::save_to_file(std::string &filename, Graph &graph) {

}