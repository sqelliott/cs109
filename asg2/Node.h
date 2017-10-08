// Node.h
//

class Node {
  
public:

   //constructor
   Node(unsigned v, unsigned w);
      
   // get methods
   unsigned getVertice() const;
   unsigned getWeight() const;

private:
   unsigned vertice;
   unsigned weight;

};
