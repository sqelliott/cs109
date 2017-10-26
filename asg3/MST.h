// MST.h
// Header file for minimum spanning tree of a graph

#include "Graph.h"
#include "Priority.h"

#include <unordered_set>
using namespace std;
typedef pair<double,pair<int,int>> Edge;


class MinimumSpanningTree{
public:
	Graph MST(const Graph&);

private:
	int rand_node(int) const;
	Edge next_prim_edge();
        void fill_MST_connections(const Graph&,int);

	unordered_set<int> nodes;
	MyQueue<Edge> connections;

};

