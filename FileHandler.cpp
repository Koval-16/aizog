#include "FileHandler.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

// reads input data from file
void FileHandler::read_file(std::string &filename, Graph &graph, bool directed) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::exception();
    std::string text;
    int index = 0;
    try{
        while(std::getline(file,text)){
            if(index==0){
                std::istringstream iss(text);
                int number_nodes, number_edges;
                if(!(iss >> number_nodes >> number_edges)){
                    throw std::exception();
                }
                if(number_nodes<=0) throw std::exception();
                if(number_edges<=0) throw std::exception();
                graph.set_nodes(number_nodes);
                graph.init(number_edges);
            }
            else{
                std::istringstream iss(text);
                int node_beg, node_end, wage;
                if(!(iss >> node_beg >> node_end >> wage)){
                    throw std::exception();
                }
                graph.add_edge(node_beg, node_end, wage, directed);
            }
            index++;
        }
    }
    catch (std::exception &e){
        std::cout << "exception" << std::endl;
        throw std::exception();
    }
}

// saves results of single file test to the output file
void FileHandler::save_to_file(std::string &filename, Graph &graph, std::string text) {
    std::ofstream file(filename, std::ios::app);
    file << graph.toString() << std::endl;
    file << text << std::endl;
    file.close();
}

// saves results of benchmark mode to the output file
void FileHandler::save_test(std::string &filename,int i, int representation, int problem, int algorithm, int nodes, float density, int time) {
    std::ifstream file1(filename);
    int count = 0;
    std::string line;
    while(std::getline(file1,line)) count++;
    file1.close();

    std::ofstream file2(filename, std::ios::app);
    if(count>0) file2 << "\n";
    file2 << i << "\t";

    if(representation==0) file2 << "mADJ" << "\t";
    if(representation==1) file2 << "mINC" << "\t";
    if(representation==2) file2 << "LIST" << "\t";

    if(problem==0){
        file2 << "MST" << "\t";
        if(algorithm==0) file2 << "PRIM" << "\t";
        else if(algorithm==1) file2 << "KRUSK" << "\t";
    }
    else if(problem==1) {
        file2 << "PATH" << "\t";
        if(algorithm==0) file2 << "DIJK" << "\t";
        else if(algorithm==1) file2 << "BELL" << "\t";
    }
    file2 << nodes << "\t";
    file2 << density << "\t";
    file2 << time;
    file2.close();
}
