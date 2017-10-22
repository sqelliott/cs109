// ShortestPath.h
//
#include <string>
#include <unordered_map>
#include "Graph.h"

class ShortestPath{
public:

   // constructor

   // public member functions
   vector<int> path(const Graph&, int, int);
   double path_cost(const Graph&, int, int);

private:
   void set_path_cost(const Graph&, int, int, double);
   std::unordered_map<std::string,double> cost_map;
};