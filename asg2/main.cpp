#include <iostream>
#include "Graph.h"
#include "Node.h"
#include "Priority.h"
#include "ShortestPath.h"
#include <vector>


void printPath(const Graph& g, const vector<int>& path, int src, int end){
   cout << "The shortest path from " << src << " to " << end 
        << " in graph " << g.get_id() << " is: ";
   for(int x : path){
      cout << x << " ";
   }   
   cout << endl;
}



double avg_cost(const Graph& g){ 
   int num_paths;
   double total_cost;
   double cost;
   vector<int> path;
   ShortestPath sp; 
   int src = 0;

   for(int j=1; j < g.V(); ++j){
      path = sp.path(g,src,j);
      printPath(g,path,src,j);
      if((cost = sp.path_cost(g,src,j)) != 0){ 
         total_cost += cost;
         num_paths++;
      }   
   }   
   return total_cost / num_paths;
}


int main(){



   Graph g1(.2); // Graph with density 20%
   Graph g2(.4); // Graph with density 40%


   ShortestPath sp;
   double g1_avg = avg_cost(g1);
   double g2_avg = avg_cost(g2);

   cout << g1_avg << endl;
   
   return 0;
}
