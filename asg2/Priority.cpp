// Priority.h
//
//
#include <functional>
#include <queue>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template<typename T,
         typename Sequence = vector<T>,
         typename Compare = greater<typename Sequence::value_type> >
class MyQueue: public priority_queue<T, Sequence, Compare> {
public:
   void remove(const T& value){
      auto it = find(this->c.begin(), this->c.end(), value);
      if( it != this->c.end()){
         this->c.erase(it);
      }
   }
};


int main() {

   MyQueue<int, vector<int>, greater<int> > queue;
   vector<int> v {5,3,87,1,90,6,3};

   for( int i : v){
      queue.push(i);
   }

   queue.remove(90);

   while( !queue.empty() ){
      cout << queue.top() << " ";
      queue.pop();
   }
   cout << endl;

   return 0;
}
