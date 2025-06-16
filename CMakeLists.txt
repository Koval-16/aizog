cmake_minimum_required(VERSION 3.26)
project(aizog)

set(CMAKE_CXX_STANDARD 17)

add_executable(aizog
        Main.cpp
        Main.h
        Graph.cpp
        Graph.h
        GraphAdjacency.cpp
        GraphAdjacency.h
        GraphIncidence.cpp
        GraphIncidence.h
        GraphList.cpp
        GraphList.h
        Edge.cpp
        Edge.h
        Main.cpp
        FileHandler.cpp
        FileHandler.h
        RandomHandler.cpp
        RandomHandler.h
        Timer.cpp
        Timer.h
        EdgeList.cpp
        EdgeList.h
        MST.cpp
        MST.h
        ShortestPath.cpp
        ShortestPath.h
        Disjoint.cpp
        Disjoint.h
        Heap.cpp
        Heap.h)
