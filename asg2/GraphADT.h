// GraphADT.h
//
// Header file for GraphADT
#include <iostream>
#include <vector>
#include "EdgeList.h"


class Graph {

public:

   // constructors
   Graph( unsigned rows, unsigned cols);

private:
   std::vector<EdgeList> graph;
   
   unsigned num_cols;

};
