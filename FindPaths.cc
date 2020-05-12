//Mahfal Naleemul Rahuman
//Csci 335
//Assignment 5
//


#include <iostream>
#include "graph.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
template <typename Object>
void Make_Graph(std::string const & graph_file, Graph<Object> & graph){
    std::ifstream input;
    input.open(graph_file);
    if(input.fail()){
        std::cout << "Failed to open " << graph_file << std::endl;
        exit(1);
    }
    std::string line;
    Object this_vertex;
    Object a_new_vertex;
    double a_new_weight;
    //Kill first line in .txt that specifies the number of vertices
    std::getline(input, line);
    while(std::getline(input, line)){
        if(!line.empty()){
            std::stringstream ss(line);
            ss >> this_vertex;
            graph.Add_vertex(this_vertex);
            while(ss >> a_new_vertex && ss >> a_new_weight){
                graph.Add_connection(this_vertex, a_new_vertex, a_new_weight);
            }
        }
    }
    input.close();
}

//Path zfinder Driver
int pathfindDriver(int argc, char **argv){
    const std::string graph_filename(argv[1]);
    const int vertex = atoi(argv[2]);
    Graph<int> testgraph;
    Make_Graph<int>(graph_filename, testgraph);  
    testgraph.Dijkstra(vertex);
    int count = 1;
    while(testgraph.Contains(count)){
        testgraph.Print_shortest_path(count);
        ++count;
    }

    return 0;
}




int main(int argc, char **argv){
    if(argc != 3){
        std::cout << "Usage: " << argv[0] << " <graphInputFilename> <Vertex> " << std::endl;
        return 0;
    }
    pathfindDriver(argc, argv);
    return 0;
}
