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
        try{
            int problem = std::stoi(arg_values[2]);
            int algorithm = std::stoi(arg_values[3]);
            std::string input = arg_values[4];
            std::string output = arg_values[5];
            int start_node = (arg_number>=7) ? std::stoi(arg_values[6]) : 0;
            int end_node = (arg_number>=8) ? std::stoi(arg_values[7]) : 1;
            if(problem<0 || problem>1) throw std::exception();
            if(algorithm<0 || algorithm>1) throw std::exception();
            file_mode(problem,algorithm,input,output,start_node,end_node);
        } catch (...){
            help_mode();
        }

    }
    else if(mode=="--test"){
        try{
            int problem = std::stoi(arg_values[2]);
            int algorithm = std::stoi(arg_values[3]);
            int number_of_nodes = std::stoi(arg_values[4]);
            float density = std::stof(arg_values[5]);
            int iterations = std::stoi(arg_values[6]);
            std::string output = arg_values[7];
            int start_node = (arg_number>=9) ? std::stoi(arg_values[8]) : 0;
            int end_node = (arg_number>=10) ? std::stoi(arg_values[9]) : number_of_nodes-1;
            if(problem<0 || problem>1) throw std::exception();
            if(algorithm<0 || algorithm>1) throw std::exception();
            if(density<0 || density>1) throw std::exception();
            if(iterations<=0) throw std::exception();
            test_mode(problem,algorithm,number_of_nodes,density,iterations,output,start_node,end_node);
        } catch (...){
            help_mode();
        }
    }
    else help_mode();
}

void Main::help_mode(){
    std::cout << "Help Mode\n"
                 "FILE TEST MODE\n"
                 "\tUsage:\n"
                 "\t./aizog --file <problem> <algorithm> <inputFile> <outputFile>\n"
                 "\t<problem>\tProblem to be solved:\n"
                 "\t\t0 - Minimum Spanning Tree\n"
                 "\t\t1 - Shortest Path in Graph\n"
                 "\t<algorithm>\tChosen algorithm: 0-Prim/Dijkstra, 1-Kruskal/Bellman\n"
                 "\t\t0 - Prim(MST), Dijsktra(SP)\n"
                 "\t\t1 - Kruskal(MST), Bellman(SP)\n"
                 "\t<inputFile>\tName of input file storing a graph, with extension\n"
                 "\t<outputFile>\tName of output file, where results will be saved.\n"
                 "BENCHMARK MODE\n"
                 "\tUsage:\n"
                 "\t./aizog --test <problem> <algorithm> <number_of_nodes> <density> <iterations> <outputFile>\n"
                 "\t<problem>\tProblem to be solved:\n"
                 "\t\t0 - Minimum Spanning Tree\n"
                 "\t\t1 - Shortest Path in Graph\n"
                 "\t<algorithm>\tChosen algorithm: 0-Prim/Dijkstra, 1-Kruskal/Bellman\n"
                 "\t\t0 - Prim(MST), Dijsktra(SP)\n"
                 "\t\t1 - Kruskal(MST), Bellman(SP)\n"
                 "\t<number_of_nodes>\tNumber of nodes in graph\n"
                 "\t<density>\tDensity of edges in graph - float value in range [0;1]\n"
                 "\t<iterations>\tNumber of times algorithm will be done.\n"
                 "\t<outputFile>\tName of output file, where results will be saved.\n"
                 "HELP MODE\n"
                 "\tUsage:\n"
                 "\t./aizo --help\n" << std::endl;
}

void Main::file_mode(int problem, int algorithm, std::string input, std::string output, int start_node, int end_node) {
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
    singlefile(graph_inc,problem,algorithm,output,start_node,end_node);
    singlefile(graph_list,problem,algorithm,output,start_node,end_node);
    singlefile(graph_adj,problem,algorithm,output,start_node,end_node);
}

void Main::test_mode(int problem, int algorithm, int number, float density, int iterations, std::string output, int start_node, int end_node) {
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
        int t1 = testing(graph_adj,problem,algorithm,start_node,end_node);
        int t2 = testing(graph_inc,problem,algorithm,start_node,end_node);
        int t3 = testing(graph_list,problem,algorithm,start_node,end_node);
        FileHandler::save_test(output,id,0,problem,algorithm,number,density,t1);
        FileHandler::save_test(output,id+1,1,problem,algorithm,number,density,t2);
        FileHandler::save_test(output,id+2,2,problem,algorithm,number,density,t3);
        id+=3;
    }
}

int Main::testing(Graph& graph, int problem, int algorithm, int start_node, int end_node) {
    Timer timer;
    timer.reset();
    timer.start();
    if(problem==0){
        if(algorithm==0) MST::prim(graph);
        else if (algorithm==1) MST::kruskal(graph);
    }
    else{
        if(algorithm==0) ShortestPath::dijkstra(graph,start_node,end_node);
        else if(algorithm==1) ShortestPath::bellman(graph,start_node,end_node);
    }
    timer.stop();
    return timer.result();
}

void Main::singlefile(Graph& graph, int problem, int algorithm, std::string output, int start_node, int end_node){
    std::ostringstream result;
    int ret;
    if(problem==0){
        if(algorithm==0) ret = MST::prim(graph,&result);
        else if (algorithm==1) ret = MST::kruskal(graph,&result);
    }
    else{
        if(algorithm==0) ret = ShortestPath::dijkstra(graph,start_node,end_node,&result);
        else if(algorithm==1) ret = ShortestPath::bellman(graph,start_node,end_node,&result);
    }
    result << ret << std::endl;
    std::cout << graph.toString() << std::endl << result.str() << std::endl;
    FileHandler::save_to_file(output,graph,result.str());
}