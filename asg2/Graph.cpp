// Graph.cpp

#include "Graph.h"
#include <random>
#include <iostream>
#include <ctime>
using namespace std;


Graph::Graph( double density = .1,
              unsigned _num_nodes = 50, 
              unsigned min_cost = 1.0,
              unsigned max_cost = 10.0){
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
   std::uniform_real_distribution<double> weight_distr( min_cost, max_cost);

   for( unsigned i = 0; i < V(); i++){    
      for( unsigned j = 0; j < V(); j++){
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

double Graph::get_edge_value( unsigned x, unsigned y) const{
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
   stream.precision(2);


   for( unsigned i = 0; i < graph.V(); i++){
      for( unsigned j = 0; j < graph.V(); j++){
         if( graph.get_edge_value(i,j) == 0){
            stream << "0.0 ";
         }
         else{
            stream << graph.get_edge_value(i,j) << " ";
         }
      }
      stream << endl;
   }
   return stream;
}



int main(){
   Graph g = Graph(.5,10);
   cout << "This is my graph" << endl;
   cout << g;

   cout << "5's neighbors are: ";
   vector<unsigned> n = g.neighbors(5);
   for( unsigned x : n){
      cout << x << " ";
   }
   cout << endl;

   cout << "num edges: " << g.E() << endl;

   return 0;
}
