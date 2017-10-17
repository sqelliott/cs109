// Priority.h
//
//
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
