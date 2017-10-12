// Graph.h
//
// Header file for GraphADT
#include <vector>
#include <iostream>
using namespace std;

class Graph {

public:

   // constructors
   Graph( double density, unsigned num_nodes, unsigned min_cost, unsigned max_cost);

   // deconstructor


   ///////////////////////
   //  Member functions //
   ///////////////////////

   // return number of vertices in graph
   unsigned V() const;

   // number of edges in graph
   unsigned E() const;

   // tests whether there is an edge from node x to node y
   bool adjacent( unsigned, unsigned) const;

   // lists all neightbors of node x
   vector<unsigned> neighbors( unsigned) const;

   void delete_edge( unsigned, unsigned);

   double get_edge_value( unsigned, unsigned) const;

   void set_edge_value( unsigned, unsigned, double);

   friend ostream &operator<<(ostream &stream, const Graph &);

private:

   vector<vector<double>> matrix;

   unsigned num_nodes;
   unsigned num_edges;   

};

