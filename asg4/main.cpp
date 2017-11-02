// main.cpp
// sean elliott
// cs109 asg3

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
  Graph g3 ("sampleGraph.txt");
  Graph t3 = g3.MST();


  cout << "[graph from 'graph1.txt' with 10 nodes]" << endl;
  cout << g1;

  cout << "[MST from graph] "<< endl;
  cout << t1;
  cout << "MST cost is " << t1.get_MST_cost() << endl << endl;
   
  cout << "[MST for rand 100 node graph]" << endl;
  cout << t2;
  cout << "MST cost is " << t2.get_MST_cost() << endl << endl;

  cout <<  "[sample graph from coursera]" << endl;
  cout << g3;
  cout << "[tree of sample graph]" << endl;
  cout << t3;
  cout << "MST cost is " << t3.get_MST_cost() << endl;
  return 0;
}
