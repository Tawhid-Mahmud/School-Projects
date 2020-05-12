//Mahfal Naleemul Rahuman
//Csci 335
//Assignment 5
//


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std;
//input the file
ifstream openFile(const string filename){
    ifstream input;
    input.open(filename);
    if(input.fail()){
        cout << "Cannot open " << filename;
        exit(1);
    }
    return input;
}

Graph CreateGraph(const string graph_filename) {
// Open graph input file
    ifstream graphInput = openFile(graph_filename);
  
    int size(0), originVertex(0), targetVertex(0);
    float edgeWeight(0.0);
  
    string line;
    stringstream sLine;
  
// Read in size and initialize Graph
    getline(graphInput, line);
    sLine.str(line);
    sLine >> size;
    Graph newGraph(size);
  
// Read in directed edges and construct Graph
    while(getline(graphInput, line)) {
        sLine.clear();
        sLine.str(line);
  
        sLine >> originVertex;
  
        while(sLine >> targetVertex) {
            sLine >> edgeWeight;
  
            newGraph.addEdge(originVertex, targetVertex, edgeWeight);
        }
}
    //Close file
    graphInput.close();
    
    return newGraph;
}


void queryGraph(const string query_filename, Graph & testGraph) {
// Open query file
    ifstream queryInput = openFile(query_filename);
  
    int originVertex(0), targetVertex(0);
    float edgeWeight (0.0);
    string line;
    stringstream sLine;
  
// For each edge query, check if edge exists between the origin and "target"
// vertices.
    while(getline(queryInput, line)) {
        sLine.clear();
        sLine.str(line);
  
        sLine >> originVertex >> targetVertex;
  
        edgeWeight = testGraph.isConnected(originVertex, targetVertex);
  
        if(originVertex == targetVertex) {
            cout << originVertex << " " << targetVertex
            << ": not_connected";
        }
        else if(edgeWeight != -1.0) {
            cout << originVertex << " " << targetVertex
            << ": connected " << edgeWeight;
        }
        else {
            cout << originVertex << " " << targetVertex
            << ": not_connected";
        }
  
        cout << endl;
    }
//Close file
    queryInput.close();
}



int graphTestDriver(int argc, char **argv) {
    const string graph_filename(argv[1]);
    const string query_filename(argv[2]);
    
    Graph test = CreateGraph(graph_filename);
    queryGraph(query_filename, test);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    graphTestDriver(argc, argv);

    return 0;
}
