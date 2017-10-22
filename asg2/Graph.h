// Graph.h
//
// Header file for GraphADT
#include <vector>
#include <iostream>
#include <string>
using namespace std;

#pragma once
class Graph {

public:

   // constructors
   Graph();
   Graph(int);
   Graph(int, double);
   Graph(int num_nodes, double density,  
          double min_cost, double max_cost);

   Graph(string);

   // deconstructor


   //////////////////////////////
   //  Public Member functions //
   //////////////////////////////

   // return number of vertices in graph
   int V() const;
   // number of edges in graph
   int E() const;
   // tests whether there is an edge from node x to node y
   bool adjacent( int, int) const;
   // lists all neightbors of node x
   vector<int> neighbors( int) const;
   void delete_edge( int, int);
   double get_edge_value( int, int) const;
   void set_edge_value( int, int, double);

   int get_id() const;
   string graph_path_id(int,int) const;

   friend int num_vertices( Graph);
   friend ostream &operator<<(ostream &stream, const Graph &);

private:

   vector<vector<double>> matrix;

   int num_nodes;
   int num_edges;   
   int graph_id;

protected:
   static int id;
};

