//Mahfal Naleemul Rahuman
//Csci 335
//Assignment 5


// implement and design the graph class to find the shortest
// path for two points





#ifndef GRAPH
#define GRAPH

#include "binary_heap.h"
#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <iomanip>
#include "binary_heap.h"
using namespace std;

class Graph {
public:
    Graph(const int size = 10) : graph_vertices_(size),
    number_of_vertices_{size} {

        // Set all proper/intuitive identities
        for(int i = 0; i < size; i++) {
            graph_vertices_[i] = Vertex(i+1);
        }
    }
    //add all the edges
void addEdge(const int from, const int to, float edgeWeight) {
    if(!isValidVertex(from) || !isValidVertex(to) || edgeWeight < 0.0) {
        cout << "Invalid input! Please provide vertex selections between "
        << "1 and " << number_of_vertices_ << " and positive edge "
        << "edge weight." << endl << endl;
        return;
    }
  
    // Check if an edge already exists
    if(isConnected(from, to) != -1.0 || from == to) {
        return;
}
    graph_vertices_[from - 1].adjacent_vertices_.push_back(&(graph_vertices_[to-1]));
    graph_vertices_[from - 1].edge_weights_.push_back(edgeWeight);
  
}
  

float isConnected(const int from, const int to) {
    float weight = -1.0;
  
    // Check valid input
    if(!isValidVertex(from) || !isValidVertex(to)) {
        cout << "Invalid vertex selections! Please provide selections "
        << "between 1 and " << number_of_vertices_ << endl << endl;
        return weight;
    }
  
    auto it = graph_vertices_[from - 1].adjacent_vertices_.begin();
    auto it2 = graph_vertices_[from - 1].edge_weights_.begin();
  
    while(it != graph_vertices_[from - 1].adjacent_vertices_.end()) {
        if((*it)->identity_ == to) {
            weight = *it2;
            break;
        }
  
        it++;
        it2++;
    }
  
  
    return weight;
}
  
void dijkstra(const int from) {
  
// Check valid input
    if(!isValidVertex(from)){
        cout << "Invalid vertex selection! Please provide a selection "
        << "between 1 and " << number_of_vertices_ << endl << endl;
        return;
    }
  
    // Execute Dijkstra's algorithm.
    dijkstraAlgorithm(from);
  
// Output results
for(int i = 0; i < number_of_vertices_; i++) {
    cout << graph_vertices_[i].identity_ << ": ";
    printPath(graph_vertices_[i]);
    cout << ", Cost: " << fixed << setprecision(1)
    << graph_vertices_[i].distance_;
    cout << endl;
    }
}
  
void outputDegreeInformation() {
  
// Check if Graph is empty
if(number_of_vertices_ == 0) {
cout << "Graph is empty." << endl;
return;
}
  
int totalDegrees(0), largestDegree(0),
smallestDegree(number_of_vertices_ - 1);
  
// For each Vertex in the Graph...
for(int i = 0; i < number_of_vertices_; i++) {
int currentDegree =
static_cast<int>(graph_vertices_[i].adjacent_vertices_.size());
  
// Update total degree of Graph
totalDegrees += currentDegree;
  
// Update largest degree, if applicable
if(currentDegree > largestDegree) {
largestDegree = currentDegree;
}
  
// Update smallest degree, if applicable
if(currentDegree < smallestDegree) {
smallestDegree = currentDegree;
}
}
  
// Calculate number of edges and average degree
int numberOfEdges = (totalDegrees / 2);
float avgDegree = (totalDegrees / number_of_vertices_);
  
cout << "Number of Edges: " << numberOfEdges << endl;
cout << "Smallest Degree: " << smallestDegree << endl;
cout << "Largest Degree: " << largestDegree << endl;
cout << "Average Degree: " << setprecision(1) << avgDegree
<< endl << endl;
  
}

private:

// PRIVATE STRUCT - VERTEX
    struct Vertex {
  
        // Data members
        list<Vertex*> adjacent_vertices_;
        list<float> edge_weights_;
        int identity_;
        bool known_;
        float distance_;
        Vertex* previous_vertex_;
  
        // Default Constructor
        Vertex() : identity_{0}, known_{false}, distance_{0.0},
        previous_vertex_{nullptr} { }
  
        // Parameterized Constructor
        Vertex(int identity) : identity_{identity}, known_{false}, distance_{0.0},
        previous_vertex_{nullptr} { }
  
        bool operator<(const Vertex & rhs) const {
            return distance_ < rhs.distance_;
        }
~Vertex() {
    previous_vertex_ = nullptr;
}
  
};
  
    vector<Vertex> graph_vertices_;
    int number_of_vertices_;
  

  
    void dijkstraAlgorithm(const int from) {
      
    // Create Queue and initialize all vertices to unknown and "infinity"
    // distance.
    BinaryHeap<Vertex> queue;
      
    for(int i = 0; i < number_of_vertices_; i++) {
    graph_vertices_[i].distance_ = INT_MAX;
    graph_vertices_[i].known_ = false;
    }
      
    // Zero distance of origin Vertex and insert into queue
    graph_vertices_[from-1].distance_ = 0.0;
    queue.insert(graph_vertices_[from-1]);
      
    // While there are vertices to process...
    while(true) {
    bool success = false;
    int identity = 0; // Selected vertex identity.
      
    // While the queue is not empty and still dequeueing known vertex
    // duplicate representatives, continue to dequeue.
    while(!queue.isEmpty() && !success) {
    identity = (queue.findMin()).identity_;
    queue.deleteMin();
      
    if(!graph_vertices_[identity - 1].known_) {
    success = true;
    }
    }
      
    // If no unknown vertices remain; terminate algorithm.
    if(!success) {
    break;
    }
      
    // Else operate on selected vertex.
    Vertex &opV = graph_vertices_[identity-1];
      
    opV.known_ = true;
      
    auto it = opV.adjacent_vertices_.begin();
    auto it2 = opV.edge_weights_.begin();
    while(it != opV.adjacent_vertices_.end()) {
    if(!(*it)->known_) {
    float costVW = *it2;
      
    if((opV.distance_ + costVW) < (*it)->distance_) {
        (*it)->distance_ = opV.distance_ + costVW;
        (*it)->previous_vertex_ = &opV;
        queue.insert(*(*it));
        }
    }
      
        it++;
        it2++;
        }
    }
    }
    void printPath(Vertex &v) {
    if(v.previous_vertex_ != nullptr) {
    printPath(*(v.previous_vertex_));
    cout << ", ";
    }
    cout << v.identity_;
    }
      
    // Check for valid vertex selection.
    // @identity An identity (integer) of a vertex.
    // @return True if identity is within range of ids; false otherwise.
    bool isValidVertex(const int identity) {
    if(identity < 1 || identity > number_of_vertices_) {
        return false;
                        }
      
        return true;
    }
      

    };

#endif
