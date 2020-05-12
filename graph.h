//Mahfal Naleemul Rahuman
//Csci 335
//Assignment 5


//Design and implement all the parts of the graph class
//creates the basic structure of the graph to find the distance between points

#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <iostream>
#include <list>      
#include <utility>       
#include <float.h>       
#include <climits>       
#include <queue>

template<typename Object>
class Graph;
template <typename Object>
class Vertex{
public:
   friend class Graph<Object>;
   Vertex() = default;
   Vertex(Object key){
       id_ = key;
       distance_ = DBL_MAX;
       known_ = false;
       path_prev_ = nullptr;
       starting_vertex_ = false;
   }
   int Get_distance() const {
       return distance_;
   }
private:
   Object id_;
   double distance_;
   bool known_;
   Vertex<Object> * path_prev_;
   bool starting_vertex_;
   std::list<std::pair< Vertex<Object>*, double>> adjacent_nodes_;
};

//Comparator class to orders vertices
template <typename Object>
class CompVertDist{
public:
    bool operator()(const Vertex<Object> *lhs, const Vertex<Object> * rhs) const{
        return lhs->Get_distance() > rhs->Get_distance();
    }
};

template <typename Object>
class Graph{
public:
   Graph() = default;   //constuctor
   ~Graph() = default;  //destructor

   Graph(const Graph & rhs) = delete;
   Graph(Graph && rhs) = delete;
   Graph & operator=(const Graph & rhs) = delete;
   Graph & operator=(Graph && rhs) = delete;
   //Adds a vertex to the graph with ID = a.
   //If a is already an ID then nothing will happen
   //returns true if vertex 'a' succesfully added
   bool Add_vertex(Object a){
    if(vertex_map_.find(a) == vertex_map_.end()){
       vertex_map_[a] = Vertex<Object>(a);
       return true;
   }
   return false;
   }
   void Add_connection(Object a, Object b, double weight){
    if(vertex_map_.find(a) == vertex_map_.end()){
       vertex_map_[a] = Vertex<Object>(a);
   }
   if(vertex_map_.find(b) == vertex_map_.end()){
       vertex_map_[b] = Vertex<Object>(b);
   }
   Vertex<Object>* temp = & vertex_map_[b];
   std::pair<Vertex<Object>*, double> new_connection = std::make_pair(temp, weight);
   vertex_map_[a].adjacent_nodes_.push_back(new_connection);
   }
   

   double Edge_weight(const Object &a, const Object &b) const{
    auto x = vertex_map_.find(a);
   if(x != vertex_map_.end()){
       //return x->second.Get_edge_weight(b);
       auto y = x->second.adjacent_nodes_.begin();
       auto x_end = x->second.adjacent_nodes_.end();
       while(y != x_end){
           if(y->first->id_ == b)
               return y->second;
           y++;
       }
       return DBL_MAX;
   }
   else
       return DBL_MAX;
   }
   bool Is_connected(const Object &v1, const Object &v2){
    if(vertex_map_.find(v1) == vertex_map_.end() || vertex_map_.find(v2) == vertex_map_.end())
       return false;
   for(auto it = vertex_map_[v1].adjacent_nodes_.begin(); it != vertex_map_[v1].adjacent_nodes_.end(); ++it){
       if(it->first->id_ == v2){
           return true;
       }
   }
   return false;
   }



   void Dijkstra(Object start){
    std::priority_queue<Vertex<Object> *, std::vector<Vertex<Object> *>, CompVertDist<Object>> distance_queue;
   for(auto it = vertex_map_.begin(); it != vertex_map_.end(); ++it ){
       Reset_vertex(it->second);
   }
   vertex_map_[start].distance_ = 0.0;
   Vertex<Object> *v = & vertex_map_[start];
   v->starting_vertex_ = true;
   distance_queue.push(v);
   while(true){
       bool success = false;
       while(!distance_queue.empty() && !success){
           v = distance_queue.top();
           distance_queue.pop();
           if(!v->known_)
               success = true;
       }
       if(!success)
           break;
       v->known_ = true;
       //THIS LOOP IS WHY I MADE GRAPH A FRIEND OF
       for(auto it = v->adjacent_nodes_.begin(); it != v->adjacent_nodes_.end(); ++it){
           if(v->distance_ + it->second < it->first->distance_){
               it->first->distance_ = v->distance_ + it->second;
               it->first->path_prev_ = v;
               distance_queue.push(it->first);
           }
       }
   }
}


   void Print_shortest_path(const Object & graph_node) const
   {
    auto x = vertex_map_.find(graph_node);
   if(x == vertex_map_.end()){
       std::cout << "Vertex " << graph_node << " does not exist!\n";
       return;
   }
   std::cout << graph_node << ": ";
   const Vertex<Object> * temp = & x->second;
   if(temp->starting_vertex_){
       std::cout << temp->id_<<" " << "cost: 0\n";
       return;
   }
   if(temp->path_prev_ == nullptr){
       std::cout << "not_possible\n";
   }
   else{
       Print_shortest_path_internal(temp);
       std::cout << "cost: " << temp->distance_ << std::endl;
   }
   }


   bool Contains(const Object & vertex_node) const{
    return vertex_map_.find(vertex_node) != vertex_map_.end();
}

   size_t Get_size() const
   {
      return vertex_map_.size();
   }

   void Print_stats() const{
    int smallest_out = INT_MAX;
   int largest_out = 0;
   int edge_total = 0;


   for(auto it = vertex_map_.begin(); it != vertex_map_.end(); ++it){
       int current = it->second.adjacent_nodes_.size();
       edge_total += current;
       if(current < smallest_out)
           smallest_out = current;
       if(largest_out < current)
           largest_out = current;
   }

   std::cout << "The Random graph of size " << vertex_map_.size() << " has " << edge_total << " directed edges\n";
   std::cout << "The smallest out degree is: " << smallest_out << std::endl;
   std::cout << "The largest out degree is: " << largest_out << std::endl;
   std::cout << "The average out degree is: " << edge_total / static_cast<double>(vertex_map_.size()) << std::endl;
   }
private:
   void Print_shortest_path_internal(const Vertex<Object> * graph_node) const{
    if(graph_node->path_prev_ == nullptr){
       std::cout << graph_node->id_ << " ";
   }
   else{
       Print_shortest_path_internal(graph_node->path_prev_);
       std::cout << graph_node->id_ << " ";
   }
   }
   void Reset_vertex(Vertex<Object> v){
    v.distance_ = DBL_MAX;
   v.known_ = false;
   v.path_prev_ = nullptr;
   v.starting_vertex_ = false;
   }
   std::unordered_map<Object, Vertex<Object>> vertex_map_;  
   size_t edge_count_;
};

#endif
