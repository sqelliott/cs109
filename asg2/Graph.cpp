// Graph.cpp

#include "Graph.h"
#include <random>
#include <iostream>
using namespace std;


Graph::Graph( double density = .1, unsigned _num_nodes = 50){
   // initialize the number of nodes in the graph
   num_nodes = _num_nodes;
   
   // set matrix to correct size
   matrix.resize(_num_nodes);
   for( unsigned i = 0; i < _num_nodes; i++){
      matrix[i].resize(_num_nodes);
   }

   // random
   std::default_random_engine generator;
   std::uniform_real_distribution<double> density_distr( 0.0, 1.0);
   std::uniform_real_distribution<double> weight_distr( 1.0, 10.0);

   for( unsigned i = 0; i < V(); i++){    
      // randomly produced value 
      double value = density_distr(generator);
      if( value < density){
         for( unsigned j = 0; j < V(); j++){
            double weight = weight_distr(generator);
            set_edge_value( i, j, weight);
         }
      }
   }
}


inline unsigned Graph::V() const{
   return num_nodes;
}


inline unsigned Graph::E() const{
   return num_edges;
}


inline bool Graph::adjacent( unsigned x, unsigned y) const{
   return (get_edge_value(x,y) != 0);   
}


vector<unsigned> Graph::neighbors( unsigned x) const{
   vector<unsigned> neighbors;
   for( unsigned i = 0; i < V(); i++){
      if( get_edge_value(x,i) != 0){
         neighbors.push_back(i);
      }
   }
   return neighbors;
}



void Graph::delete_edge( unsigned x, unsigned y){
   // if edge exists, decrement num_edges
   if( get_edge_value(x,y) > 0 ){
      num_edges--;
   }

   set_edge_value(x,y,0);
   set_edge_value(y,x,0);

}

unsigned Graph::get_edge_value( unsigned x, unsigned y) const{
   return matrix[x][y];
}

void Graph::set_edge_value( unsigned x, unsigned y, double v){
   // increment num_edges if new edge is added
   if( get_edge_value(x,y) == 0){
      num_edges++;
   }

   matrix[x][y] = v;
   matrix[y][x] = v;
}

ostream &operator<<(ostream& stream, const Graph &graph){
   for( unsigned i = 0; i < graph.V(); i++){
      for( unsigned j = 0; j < graph.V(); j++){
         stream << graph.get_edge_value(i,j) << " ";
      }
      stream << endl;
   }
   return stream;
}



int main(){
   Graph g = Graph();
   cout << "This is my graph" << endl;
   cout << g;
   return 0;
}
