// Node.h
//

class Node {
public:
   Node(unsigned v, unsigned w) : v(v), w(w) {}

   friend bool operator>(const Node &x, const Node &y){
      return (x.v > y.v);
   }
   unsigned v;
   unsigned w;
};
