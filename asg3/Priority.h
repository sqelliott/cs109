// Priority.h
//
// MyQueue template. Inherits from priority_queue.
// Adds removal functionality to queuery the queue 
//  and remove values
//
// Sean Elliott
// cs109 asg2

#include <functional>
#include <queue>
#include <algorithm>
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
