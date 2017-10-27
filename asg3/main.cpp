// main.cpp
// sean elliott
// cs109 asg2
#include <iostream>
#include "Graph.h"
#include "Priority.h"
#include "ShortestPath.h"
#include "MST.h"
#include <vector>
#include <fstream>

void printPath(ostream& stream, const Graph& g, const vector<int>& path, int src, int end){
   stream << "The shortest path from " << src << " to " << end 
        << " in graph " << g.get_id() << " is: [ ";
   for(int x : path){
      stream << x << " ";
   }   
   stream << "] " << endl;
}



void avg_cost(const Graph& g,ostream& stream){ 
   stream.precision(1);
   int num_paths=0;
   double total_cost;
   double cost;
   vector<int> path;
   ShortestPath sp; 
   int src = 0;

   for(int j=1; j < g.V(); ++j){
      path = sp.path(g,src,j);
      printPath(stream, g,path,src,j);
      cost = sp.path_cost(g,src,j);
      stream << fixed << "with cost: " << cost << endl;
      if(cost != 0){ 
         total_cost += cost;
         num_paths++;
      }   
   }   
   stream << "The average path cost is: " << total_cost / num_paths << endl;
}


int main(){

   Graph* g = new Graph("graph2.txt");
   cout << *g;
   
   Graph tree = g->MST();
   cout << tree;
   cout << tree.V() << " vertices and " << tree.E() << " edges\n";
   cout << "Tree cost is: " << tree.get_MST_cost() << endl;

   
   return 0;
}
