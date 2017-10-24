// ShortestPath.cpp
//
// Sean Elliott
// cs109 asg2

#include "ShortestPath.h"
#include "Graph.h"
#include "Priority.h"
#include <vector>
#include <limits>
#include <algorithm>
#include "Node.h"
#include <string>

// Dijkstras algorithm to find the least cost path between
// nodes in a graph
vector<int> ShortestPath::path(const Graph& g, int src, int end){
   
   vector<double> dist( g.V() ); // cost to each node from src
   vector<int> prev( g.V(), -1); // parents of nodes in path. -1 for no parent
   MyQueue<Node> queue; // Queue of nodes
   vector<int> path;

   // Set to cost to each node (not src) to highest possible value
   // (within the constraints of ints.
   for( int i = 0; i < g.V(); i++){
      if( i != src){
         dist[i] = numeric_limits<double>::max();
      }
   }

   queue.push( Node( src, dist[src] ));

   while( !queue.empty() ){
      
      Node curr_node = queue.top();
      queue.pop();

      // Reached the end
      if( curr_node.v == end){
         set_path_cost(g,src,end,dist[end]); // store the cost
         path.push_back(end);
         int node = end;
         while( prev[node] != src){
            node = prev[node];
            path.push_back(node);
         }
         path.push_back( prev[node] );
         std::reverse(path.begin(), path.end() );
         return path;
      }

      // Get neighbors of current node. For each neighbor, calc cost to 
      // this neighbor give cost to curr_node + weight of edge between
      // them. On discovery of lower cost path, remove neighbor from queue 
      // (if there), update cost, parent, and push neighbor with new cost
      // on queue.
      vector<int> curr_node_neighbors = g.neighbors(curr_node.v);
      for( int j : curr_node_neighbors){
         double cost = dist[curr_node.v] + 
                         g.get_edge_value(curr_node.v, j);
         if( cost < dist[j]){
            queue.remove( Node(j, dist[j]));
            dist[j] = cost;
            prev[j] = curr_node.v;
            queue.push( Node(j, cost));
         }
      }
   }
   return path;
}

// Returns minimum cost between nodes of graph.
// Calls path() if value is not yet known.
double ShortestPath::path_cost(const Graph& g,int u,int w){
   string key = g.graph_path_id(u,w);
   if( cost_map.find(key) == cost_map.end() ){
      path(g,u,w);
   }
   return cost_map[key];
}

// Stores a path cost of a graph
void ShortestPath::set_path_cost(const Graph& g, int src, int end, double cost){
   string g_id = std::to_string( g.get_id() );
   string src_str = std::to_string( src);
   string end_str = std::to_string( end);

   string key = g_id + src_str + end_str;

   cost_map[key]= cost;
}
