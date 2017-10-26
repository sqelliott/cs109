// MST.cpp
#include "MST.h"
#include "Graph.h"

Graph MinimumSpanningTree::MST(const Graph& g) {
   Graph tree(g.V());
   // clear data structures
   nodes.clear();
   connections.clear();

   // 
   for(int i=0; i < g.V(); ++i){
      nodes.insert(i);
   }

   int v = rand_node(g.V());
   nodes.erase(v);
   fill_MST_connections(g,v);

   while( !nodes.empty() ){
      Edge e = next_prim_edge();
      double cost = e.first;
      int n1 = e.second.first;
      int n2 = e.second.second;
      tree.set_edge_value(n1,n2,cost);
   }
   

   return tree;
}

int MinimumSpanningTree::rand_node(int n) const{
   random_device rd;
   default_random_engine generator(rd());
   uniform_int_distribution<int> node(0,n-1);
   return node(generator);
}

Edge MinimumSpanningTree::next_prim_edge(){
   Edge e = connections.top();
   connections.pop();
   while(nodes.find(e.second.second) == nodes.end()){
      e = connections.top();
      connections.pop();
   }
   nodes.erase(e.second.second);
   return e;
}

void MinimumSpanningTree::fill_MST_connections(const Graph& g, int v){
   for( int i : g.neighbors(v)){
      if( nodes.find(i) != nodes.end()){
         double cost = g.get_edge_value(v,i);
         connections.push( make_pair(cost, make_pair(v,i)));
      }
   }  
}
