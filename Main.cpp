#include <iostream>
#include "Graph.h"
#include "FileHandler.h"
#include "Main.h"
#include "Timer.h"
#include "RandomHandler.h"
#include "MST.h"

#include "GraphAdjacency.h"
#include "GraphIncidence.h"
#include "GraphList.h"

int main(int arg_number, char* arg_values[]) {
    srand(time(0));
    Main::start(arg_number,arg_values);
    return 0;
    // FILE MODE:
    // - problem: MST, Shortest Path
    // - algorithm: Prim/Kruskal, Dijkstr/Bellman
    // - input
    // - output

    // TEST MODE:
    // - problem: MST, SHortest Path
    // - algorithm: Prim/Kruskal, Dijkstr/Bellman
    // - number of nodes
    // - density
    // - iterations
    // - output for results
    // - start node and end node
}

void Main::start(int arg_number, char* arg_values[]){
    if(arg_number<2){
        help_mode();
        return;
    }
    Timer timer;
    std::string mode = arg_values[1];
    if(mode=="--file"){
        int problem = std::stoi(arg_values[2]);
        int algorithm = std::stoi(arg_values[3]);
        std::string input = arg_values[4];
        std::string output = arg_values[5];
        file_mode(problem,algorithm,input,output);
    }
    else if(mode=="--test"){
        int problem = std::stoi(arg_values[2]);
        int algorithm = std::stoi(arg_values[3]);
        int number_of_nodes = std::stoi(arg_values[4]);
        float density = std::stof(arg_values[5]);
        int iterations = std::stoi(arg_values[6]);
        std::string output = arg_values[7];
        test_mode(problem,algorithm,number_of_nodes,density,iterations,output);
    }
    else help_mode();
}

void Main::help_mode(){
    std::cout << "" << std::endl;
}

void Main::file_mode(int problem, int algorithm, std::string input, std::string output) {
    GraphAdjacency graph_adj;
    GraphIncidence graph_inc;
    GraphList graph_list;
    if(problem==0){
        FileHandler::read_file(input, graph_adj, false);
        FileHandler::read_file(input, graph_inc, false);
        FileHandler::read_file(input, graph_list, false);
    }
    else{
        FileHandler::read_file(input,graph_adj,true);
        FileHandler::read_file(input,graph_inc,true);
        FileHandler::read_file(input,graph_list,true);
    }
    graph_adj.print();
    std::cout << "\n";
    graph_inc.print();
    std::cout << "\n";
    graph_list.print();
    std::cout << "\n";
    if(problem==0){
        if(algorithm==0){
            std::cout << MST::prim(graph_adj,0) << std::endl;
            std::cout << MST::prim(graph_inc,0) << std::endl;
            std::cout << MST::prim(graph_list,0) << std::endl;
        }
        else if(algorithm==1){
            std::cout << MST::kruskal(graph_adj,0) << std::endl;
            std::cout << MST::kruskal(graph_inc,0) << std::endl;
            std::cout << MST::kruskal(graph_list,0) << std::endl;
        }
    }
    else if(problem==1){
        if(algorithm==0){
            //ShortestPath::dijkstra(graph);
        }
        else if(algorithm==1){
            //ShortestPath::bellman(graph);
        }
    }
}

void Main::test_mode(int problem, int algorithm, int number, float density, int iterations, std::string output) {
    for(int i=0; i<iterations; i++){
        GraphAdjacency graph_adj;
        GraphIncidence graph_inc;
        GraphList graph_list;
        if(problem==0) RandomHandler::generate_graph(number,density,graph_adj,graph_inc,graph_list,false);
        else RandomHandler::generate_graph(number,density,graph_adj,graph_inc,graph_list,true);
        graph_adj.print();
        std::cout << "\n";
        graph_inc.print();
        std::cout << "\n";
        graph_list.print();
        std::cout << "\n";
    }
}