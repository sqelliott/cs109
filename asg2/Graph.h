// Graph.h
//
// Header file for GraphADT
#include <vector>
#include <iostream>
#include <string>
using namespace std;

#pragma once
// ADT representation for vertices and edges in a graph
// Uses vector of vectors to maintain edge connections
// between vertices, such that the edge weight between
// node x and y is indexed by matrix[x][y].
//
// When matrix[x][y] is 0, there is no edge between 
// these nodes
class Graph {

public:

   // constructors
   Graph();
   Graph(int);
   Graph(double);
   Graph(int, double);
   Graph(int num_nodes, double density,  
         double min_cost, double max_cost);
   Graph(string);

   // deconstructor


   //////////////////////////////
   //  Public Member functions //
   //////////////////////////////

   inline int V() const{
      return num_nodes;
   }
   inline int E() const{
      return num_edges;
   }
   inline bool adjacent(int x, int y) const{
      return (get_edge_value(x,y) != 0);
   }
   vector<int> neighbors( int) const;
   void delete_edge( int, int);
   inline double get_edge_value(int x, int y) const{
      return matrix[x][y];
   }
   void set_edge_value( int, int, double);
   inline int get_id() const{
      return graph_id;
   }
   string graph_path_id(int,int) const;
   friend ostream &operator<<(ostream &stream, const Graph &);

private:

   vector<vector<double>> matrix;

   int num_nodes;
   int num_edges;   
   int graph_id;

protected:
   static int id;
};

