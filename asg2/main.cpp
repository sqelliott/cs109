#include <iostream>
#include "Graph.h"
#include "Node.h"
#include "Priority.h"
#include "ShortestPath.h"
#include <vector>

int main(){


   Graph g(.3, 100, 1, 10);



   ShortestPath sp;
   unsigned s = 0, d = 34;
   vector<unsigned> path = sp.path(g, s,d);
   
   cout << "The shortest path from 0 to 2 is: ";
   for( unsigned x : path ){
      cout << x << " ";
   }
   cout << endl;
   
   return 0;
}
