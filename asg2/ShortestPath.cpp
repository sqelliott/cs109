// ShortestPath.cpp
//

#include "ShortestPath.h"
#include "Graph.h"
#include "Priority.h"
#include <vector>
#include <limits>
#include <algorithm>
#include "Node.h"



vector<int> ShortestPath::path(Graph g, int src, int end){
   
   vector<int> dist( g.V() );   
   vector<int> prev( g.V(), -1);
   MyQueue<Node> queue;
   vector<int> path;

   for( int i = 0; i < g.V(); i++){
      if( i != src){
         dist[i] = numeric_limits<int>::max();
      }
   }

   queue.push( Node( src, dist[src] ));

   while( !queue.empty() ){
      
      Node curr_node = queue.top();
      queue.pop();

      if( curr_node.v == end){
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

      vector<int> curr_node_neighbors = g.neighbors(curr_node.v);
      for( int j = 0; j < curr_node_neighbors.size(); j++){
         int cost = dist[curr_node.v] + 
                         g.get_edge_value(curr_node.v, j);
         if( cost < dist[j]){
            //queue.remove( Node(j, dist[j]));
            dist[j] = cost;
            prev[j] = curr_node.v;
            queue.push( Node(j, cost));
         }
      }
   }
   return path;
}

/*
double ShortestPath::path_size( int u, int w){

}*/
