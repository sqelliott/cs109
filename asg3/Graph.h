// Graph.h
// Header file for GraphADT
//
// Sean Elliott
// cs109 asg2
#include <vector>
#include <iostream>
#include <string>
#include <unordered_set>
#include "Priority.h"
using namespace std;
typedef pair<double,pair<int,int>> Edge;

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

   // Default constructor.
   // 50 nodes. 10% density. [1.0,10.0] weight range
   Graph();
   // Create a graph with specified number of nodes
   // Node edges
   Graph(int);
   // Default graph options, with specified density
   Graph(double);
   // Default graph with specified num_nodes and density
   Graph(int, double);
   Graph(int num_nodes, double density,  
         double min_cost, double max_cost);

   // Create a graph from a file
   Graph(string);

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
   Graph MST();
   string graph_path_id(int,int) const;
   friend ostream &operator<<(ostream &stream, const Graph &);

private:

   vector<vector<double>> matrix;

   int num_nodes;
   int num_edges;   
   int graph_id;
   Edge next_prim_edge(unordered_set<int>&,MyQueue<Edge>&);
   void fill_MST_connections(unordered_set
   
   void set_num_nodes(int num_nodes);
   int rand_node() const;

protected:
   static int id;
};

