// 
// Sean Elliott (sqelliot)
// CS109 Fall 2017
// Assignment 1
// code.cpp

// Conver this program to C++
// change to C++ io
// change to one line comments
// change defines of constants to const
// change array to vector<>
// inline an short function

#include <iostream>
#include <vector>

using namespace std;

const int NUM_DATA=40;

// Calculates the sum of data stored in a vector
inline void sum(int& accum, int NUM_DATA, const vector<int>& d ){
   int i;
   accum = 0;
   for( i = 0; i < NUM_DATA; ++i){
      accum = accum + d[i];
   }
}

int main(){
   
   int i;
   int accum = 0;
   vector<int> data (NUM_DATA);

   for( i = 0; i < NUM_DATA; ++i){
      data[i] = i;
   } 

   sum( accum, NUM_DATA, data );

   cout << "sum is " << accum << "\n";
   
   return 0;
}
