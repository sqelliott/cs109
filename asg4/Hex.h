// Hex.h

#include <vector>
enum class Player{red,blue,none};

class Hex{
public:  
  // constructor
  Hex(int n=11);

  // public methods
  int make_move(Player,int,int);
  bool winner() const;

  int get_size() const;
  void set_size(int);
  Player current_player() const;
  
private:
  vector<vector<Player>> board;
  Player player = Player::red;
  bool winner = false;
  int size;

  bool game_over() const;
  bool did_red_win();
  bool did_blue_win();
};
