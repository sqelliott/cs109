#include <iostream>
#include "Graph.h"
#include "Node.h"
#include "Priority.h"
#include "ShortestPath.h"
#include <vector>

int main(){



   Graph g2(6);

   Graph g1("graph1.txt");

   cout << g2;
   cout << g1;

   ShortestPath sp;
   int s = 0, d = 4;
   //vector<int> path = sp.path(g1, s,d);
   
   //cout << "The shortest path from "<< s << " to " << d << " is: ";
   //for( int x : path ){
   //   cout << x << " ";
   //}
   cout << endl;
   cout << "the cost is: " << sp.path_cost(g1,s,d) << endl;
   
   return 0;
}
