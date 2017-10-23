#include <iostream>
#include "Graph.h"
#include "Node.h"
#include "Priority.h"
#include "ShortestPath.h"
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
   cout << total_cost << " " << num_paths << endl;
   stream << "The average path cost is: " << total_cost / num_paths << endl;
}


int main(){

   std::ofstream ofs;
   ofs.open("RandomGraphs.txt", std::ofstream::out);
   Graph g1(10);
   Graph g2(10);
   ofs << "Two random graphs with 10 nodes" << endl;
   ofs << g1;
   ofs << g2;
   avg_cost(g2,ofs);
   ofs.close();

   ofs.open("Graph_20\%", std::ofstream::out);
   Graph g3(.2);
   ofs << g3;
   avg_cost(g3,ofs);
   ofs.close();

   ofs.open("Graph_40\%", std::ofstream::out);
   Graph g4(.4);
   ofs << g4;
   avg_cost(g4,ofs);
   ofs.close();
   
   return 0;
}
