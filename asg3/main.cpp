// main.cpp
// sean elliott
// cs109 asg2
#include <iostream>
#include "Graph.h"
#include "Priority.h"
#include "ShortestPath.h"
#include <vector>
#include <fstream>

int main(){

   Graph g1 ("graph1.txt");
   Graph t1 = g1.MST();
   Graph g2 (100,.3,1,20);
   Graph t2 = g2.MST();

   cout << g1;
   cout << t1;
   cout << "MST cost is " << t1.get_MST_cost() << endl;
   
   cout << t2;
   cout << "MST cost is " << t2.get_MST_cost() << endl;
   return 0;
}
