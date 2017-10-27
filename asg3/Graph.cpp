// Graph.cpp
//
// Sean Elliott
// cs109 asg2

#include "Graph.h"
#include "ShortestPath.h"
#include "Priority.h"

#include <random>
#include <limits>
#include <iostream>
#include <fstream>
#include <queue>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include <unordered_set>
using namespace std;
typedef pair<double,pair<int,int>> Edge;

Graph::Graph():Graph::Graph(50,.1,1,10){}
Graph::Graph(int num_nodes):graph_id(Graph::id++){
   if( num_nodes < 1){
      cerr << "Graph error: Must be at least one node." << endl;
      exit (EXIT_FAILURE);
   }
   set_num_nodes(num_nodes);
}
Graph::Graph(double density):Graph::Graph(50,density,1,10){}
Graph::Graph(int num_nodes, double density):
       Graph::Graph(num_nodes,density,1, 10){}


// Graph() constructor
Graph::Graph( int num_nodes, double density, double min_cost,
              double max_cost): graph_id(Graph::id++){

   // Validate input
   if( num_nodes < 1) {
      cerr << "Graph error: Must be at least one node." << endl;
      exit (EXIT_FAILURE);
   }
   if( density > 1 || density < 0){
      cerr << "Graph error: Invalid edge density" << endl;
      exit (EXIT_FAILURE);
   }
   if( min_cost > max_cost || min_cost <= 0){
      cerr << "Graph error: Invalid edge weight range" << endl;
      exit (EXIT_FAILURE);
   }
   set_num_nodes(num_nodes);
   

   // random
   random_device rd;
   default_random_engine generator(rd());
   uniform_real_distribution<double> density_distr( 0.0, 1.0);
   uniform_real_distribution<double> weight_distr( min_cost, max_cost);
   // Use random engine to determine if an edge exists
   // and to determine its weight
   for( int i = 0; i < V(); i++){    
      for( int j = 0; j < V(); j++){
         // no self-loops
         if( i != j){
            // randomly produced value 
            double value = density_distr( generator);
            if( value < density){
               double weight = weight_distr( generator);
               set_edge_value( i, j, weight);
            }
         }
      }
   }
}

Graph::Graph(string file):graph_id(Graph::id++){
   ifstream input;
   input.open(file, ifstream::in);

   if(!input){
      cerr << "Unable to open file " << file;
      exit(1);
   }

   if(input >> num_nodes){
      set_num_nodes(num_nodes);
   }
   else{
      cerr << "Incorrect input format\n";
      exit(1);
   }
   
   int n1,n2,c;
   while( input >> n1 >> n2 >> c){
      set_edge_value(n1,n2,c);
   }
}



//////////////////////
// Member Functions //
//////////////////////

// Returns the neighbors of a node.
// This is all nodes in nodes vector with a positive
// edge weight value.
vector<int> Graph::neighbors( int x) const{
   vector<int> neighbors;
   for( int i = 0; i < V(); i++){
      if( get_edge_value(x,i) != DISJOINT){
         neighbors.push_back(i);
      }
   }
   return neighbors;
}


// Set the weight between nodes to zero.
// Decrement number of edges if edge exists
void Graph::delete_edge( int x, int y){
   // if edge exists, decrement num_edges
   if( get_edge_value(x,y) >= 0 ){
      num_edges--;
   }

   set_edge_value(x,y,DISJOINT);
   set_edge_value(y,x,DISJOINT);

}

//
void Graph::set_edge_value( int x, int y, double v){
   // increment num_edges if new edge is added
   if( get_edge_value(x,y) == DISJOINT && v !=DISJOINT){
      num_edges++;
   }

   matrix[x][y] = v;
   matrix[y][x] = v;
}


string Graph::graph_path_id(int src, int end) const{
   string g_str = to_string(get_id());
   string src_str = to_string(src);
   string end_str = to_string(end);

   string graph_key = g_str + src_str + end_str;
   return graph_key;
}


ostream &operator<<(ostream& stream, const Graph &graph){
   stream.precision(1);

   stream << "Graph " << graph.get_id() << endl;
   int pad_space = ceil( log10( graph.V()));
   for(int i = 0; i < graph.V(); ++i){
      vector<int> neighbors = graph.neighbors(i);
      int pad;
      if( i ==0) pad =1;
      else{
         pad = ceil( log10(i+1));
      }
      for( ; pad < pad_space; ++pad){
         stream << " ";
      }
      stream << i << ": ";
      for( int j: neighbors){
         stream << fixed << "(" << j << ","
                << graph.get_edge_value(i,j) << ") ";
      }
      stream << endl;
   }
   return stream;
}



// Minimum Spanning Tree
Graph Graph::MST(){
   Graph tree(V());
   nodes.clear();
   connections.clear();
   mst_cost = 0;

   for(int i = 0; i < V(); ++i){
      nodes.insert(i);
   }

   int v = rand_node(V());
   nodes.erase(v);
   fill_MST_connections(v);

   while( !nodes.empty()){
      Edge e = next_prim_edge();
      fill_MST_connections(e.second.second);
      double cost = e.first;
      int n1 = e.second.first;
      int n2 = e.second.second;
      tree.set_edge_value(n1,n2,cost);
      mst_cost += cost;
   }
   return tree;
}

int Graph::get_MST_cost(){
   if( mst_cost == -1){
      MST();
   }
   return mst_cost;  
}

int Graph::rand_node(int n) const{
   random_device rd;
   default_random_engine generator(rd());
   uniform_int_distribution<int> node(0,n-1);
   return node(generator);
}

Edge Graph::next_prim_edge(){
   Edge e = connections.top();
   connections.pop();
   while(nodes.find(e.second.second) == nodes.end()){
      e = connections.top();
      connections.pop();
   }
   nodes.erase(e.second.second);
   return e;
}

void Graph::fill_MST_connections(int v){
   for( int i : neighbors(v)){
      if( nodes.find(i) != nodes.end()){
         double cost = get_edge_value(v,i);
         connections.push( make_pair(cost, make_pair(v,i)));
      }
   }  
}

// Private Members
int Graph::id;

void Graph::set_num_nodes(int num_nodes){
   this->num_nodes = num_nodes;
   matrix.resize(V());
   for(int i = 0; i < V(); ++i)
      matrix[i].resize(V(),DISJOINT);
   this->num_edges = 0;
}

 
