#include <iostream>
#include "Graph.h"
#include "Node.h"
#include "Priority.h"
#include "ShortestPath.h"
#include <vector>

int main(){


   //Graph g(.7, 8, 1, 10);

   //cout << g;

   Graph g("graph1.txt");
   cout << g;

   ShortestPath sp;
   int s = 0, d = 4;
   vector<int> path = sp.path(g, s,d);
   
   cout << "The shortest path from "<< s << " to " << d << " is: ";
   for( int x : path ){
      cout << x << " ";
   }
   cout << endl;
   
   return 0;
}
