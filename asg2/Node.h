// Node.h
//

class Node {
public:
   Node(int v, int w) : v(v), w(w) {}

   friend bool operator>(const Node &x, const Node &y){
      return (x.w > y.w);
   }
   friend bool operator==(const Node &x, const Node &y){
      return (x.v == y.v);
   }

   friend ostream &operator<<(ostream &stream, Node &node){
      stream << "(" << node.v << "," << node.w << ") ";
   }
   int v;
   int w;
};
