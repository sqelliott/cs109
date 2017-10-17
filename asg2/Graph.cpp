// Graph.cpp

#include "Graph.h"
#include <random>
#include <iostream>
#include <fstream>
#include <queue>
#include <ctime>
using namespace std;

// Graph() constructor
Graph::Graph( double density = .1,
              int num_nodes = 50, 
              double min_cost = 1.0,
              double max_cost = 10.0){
   // initialize the number of nodes in the graph
   this->num_nodes = num_nodes;
   
   // set matrix to correct size
   matrix.resize( V() );
   for( int i = 0; i < V(); i++){
      matrix[i].resize( V() );
   }

   // random
   std::random_device rd;
   std::default_random_engine generator(rd());
   std::uniform_real_distribution<double> density_distr( 0.0, 1.0);
   std::uniform_real_distribution<double> weight_distr( min_cost, max_cost);

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

Graph::Graph( string file){
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

   int num_input_weights = V() * ( V() +1) /2; 
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


vector<int> Graph::neighbors( int x) {
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

ostream &operator<<(ostream& stream, const Graph &graph){
   stream.precision(1);


   for( int i = 0; i < graph.V(); i++){
      for( int j = 0; j < graph.V(); j++){
         stream << fixed << graph.get_edge_value(i,j) << " ";
      }
      stream << endl;
   }
   return stream;
}

