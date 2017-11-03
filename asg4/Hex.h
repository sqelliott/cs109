// Hex.h

#include <vector>
#include <unordered_set>
using namespace std;
enum class Player{red,blue,none};
typedef pair<int,int> Spot;
typedef pair<unordered_set<Spot>,unordered_set<Spot>> Walls;

class Hex{
public:  
  // constructor
  Hex(int n=11);

  // public methods
  int make_move(Player,int,int);
  bool winner() const;

  int get_size() const;
  Player curr_player() const;
  
private:
  vector<vector<Player>> board;
  Player player = Player::red;
  bool _game_over = false;
  const int size;
  Walls red_walls;
  Walls blue_walls;
  

  void add_move();
  bool game_over() const;
  bool did_player_won();
  bool on_both_walls();
  const Walls& get_walls();
};
