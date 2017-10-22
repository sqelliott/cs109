// Graph.cpp

#include "Graph.h"
#include <random>
#include <iostream>
#include <fstream>
#include <queue>
#include <ctime>
#include <stdlib.h>
#include <math.h>
using namespace std;

Graph::Graph() : Graph::Graph(50,.1,1,10){}
Graph::Graph(int num_nodes) : Graph::Graph(num_nodes,.1,1,10) {}
Graph::Graph(int num_nodes, double density):
       Graph::Graph(num_nodes,density,1, 10){}


// Graph() constructor
Graph::Graph( int num_nodes = 50,
              double density = .1,
              double min_cost = 1.0,
              double max_cost = 10.0): graph_id(Graph::id++){

   // Validate input
   if( num_nodes < 1){
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
   this->num_nodes = num_nodes;
   
   // set matrix to correct size
   matrix.resize( V() );
   for( int i = 0; i < V(); i++){
      matrix[i].resize( V() );
   }

   // random
   random_device rd;
   default_random_engine generator(rd());
   uniform_real_distribution<double> density_distr( 0.0, 1.0);
   uniform_real_distribution<double> weight_distr( min_cost, max_cost);

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
            else{
               set_edge_value( i, j, 0.0);
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
      this->num_nodes = num_nodes;
   }
   else{
      cerr << "Incorrect input format";
      exit(1);
   }

   matrix.resize(V());
   for( int i = 0; i < V(); i++){
      matrix[i].resize(V());
   }

   // use for error checking
   //int num_input_weights = V() * ( V() +1) /2; 
   int w;

   for(int i = 0; i < V(); i++){
      for( int j = 0; j < V(); j++){
         input >> w;

         set_edge_value(i,j,w);
      }
   }
   
}


// Member Functions
inline int Graph::V() const{
   return num_nodes;
}


inline int Graph::E() const{
   return num_edges;
}


inline bool Graph::adjacent( int x, int y) const{
   return (get_edge_value(x,y) != 0);   
}


vector<int> Graph::neighbors( int x) const{
   vector<int> neighbors;
   for( int i = 0; i < V(); i++){
      if( get_edge_value(x,i) != 0){
         neighbors.push_back(i);
      }
   }
   return neighbors;
}



void Graph::delete_edge( int x, int y){
   // if edge exists, decrement num_edges
   if( get_edge_value(x,y) > 0 ){
      num_edges--;
   }

   set_edge_value(x,y,0);
   set_edge_value(y,x,0);

}

inline double Graph::get_edge_value( int x, int y) const{
   return matrix[x][y];
}

void Graph::set_edge_value( int x, int y, double v){
   // increment num_edges if new edge is added
   if( get_edge_value(x,y) == 0){
      num_edges++;
   }

   matrix[x][y] = v;
   matrix[y][x] = v;
}

int Graph::get_id() const{
   return graph_id;
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
   int pad_space = ceil( log10( graph.V()) );
   for( int i = 0; i < graph.V(); i++){
      vector<int> neighbors = graph.neighbors(i);
      int pad;
      if( i == 0){  pad = 1;}
      else{  pad = ceil( log10( i + 1));}
      for( ; pad < pad_space; pad++){
         stream << " ";
      }
      stream << i << ": ";
      for( int j : neighbors){
         stream << fixed << "(" << j << "," 
                << graph.get_edge_value(i,j) << ") ";
      }
      stream << endl;
   }
   return stream;
}

int Graph::id;
