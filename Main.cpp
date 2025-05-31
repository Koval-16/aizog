#include <iostream>
#include <sstream>
#include "Graph.h"
#include "FileHandler.h"
#include "Main.h"
#include "Timer.h"
#include "RandomHandler.h"
#include "MST.h"
#include "ShortestPath.h"

#include "GraphAdjacency.h"
#include "GraphIncidence.h"
#include "GraphList.h"

int main(int arg_number, char* arg_values[]) {
    srand(time(0));
    Main::start(arg_number,arg_values);
    return 0;
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

    singlefile(graph_inc,problem,algorithm,output);
    singlefile(graph_list,problem,algorithm,output);
    singlefile(graph_adj,problem,algorithm,output);
}

void Main::test_mode(int problem, int algorithm, int number, float density, int iterations, std::string output) {
    int id=0;
    for(int i=0; i<iterations; i++){
        GraphAdjacency graph_adj;
        GraphIncidence graph_inc;
        GraphList graph_list;
        if(problem==0){
            RandomHandler::generate_graph(number,density,graph_adj,graph_inc,graph_list,false);
        }
        else{
            RandomHandler::generate_graph(number,density,graph_adj,graph_inc,graph_list,true);
        }
        int t1 = testing(graph_adj,problem,algorithm);
        int t2 = testing(graph_inc,problem,algorithm);
        int t3 = testing(graph_list,problem,algorithm);
        FileHandler::save_test(output,id,0,problem,algorithm,number,density,t1);
        FileHandler::save_test(output,id+1,1,problem,algorithm,number,density,t2);
        FileHandler::save_test(output,id+2,2,problem,algorithm,number,density,t3);
        id+=3;
    }
}

int Main::testing(Graph& graph, int problem, int algorithm) {
    Timer timer;
    timer.reset();
    timer.start();
    if(problem==0){
        if(algorithm==0) MST::prim(graph);
        else if (algorithm==1) MST::kruskal(graph);
    }
    else{
        if(algorithm==0) ShortestPath::dijkstra(graph);
        else if(algorithm==1) ShortestPath::bellman(graph);
    }
    timer.stop();
    return timer.result();
}

void Main::singlefile(Graph& graph, int problem, int algorithm, std::string output){
    std::ostringstream result;
    int ret;
    if(problem==0){
        if(algorithm==0) ret = MST::prim(graph,&result);
        else if (algorithm==1) ret = MST::kruskal(graph,&result);
    }
    else{
        if(algorithm==0) ret = ShortestPath::dijkstra(graph,&result);
        else if(algorithm==1) ret = ShortestPath::bellman(graph,&result);
    }
    result << ret << std::endl;
    std::cout << graph.toString() << std::endl << result.str() << std::endl;
    FileHandler::save_to_file(output,graph,result.str());
}