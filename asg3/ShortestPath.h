// ShortestPath.h
//
// Implements Dijkstras algorithm to find least cost
// paths between nodes in graphs.
// Maintains the costs of searched paths using unordered_map
//
// Sean Elliott
// cs109 asg2

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
