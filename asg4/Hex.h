// Hex.h

#include <vector>
#include <unordered_set>
using namespace std;
enum class Player{red,blue,none};
typedef pair<int,int> Spot;
typedef vector<Spot> Spots;
typedef pair<Spots,Spots> Walls;

class Hex{
public:  
  // constructor
  Hex(int n=11);

  // public methods
  int make_move(int,int);
  bool check_for_winner();

  int get_size() const;
  Player curr_player() const;
  bool is_game_over() const;
  Player get_winner() const;

  void display_board() const;
  Spot rand_move() const;
  
private:
  // state member variables
  vector<vector<Player>> board;
  Player player = Player::red;
  Player winner = Player::none;
  bool _game_over = false;
  const int size;

  // Container to maintain spots occupied by a player
  // on their respective walls to win the game.
  Walls red_walls;
  Walls blue_walls;
  
  // methods to check board 'Spots' logic
  bool valid_spot(int,int) const;
  bool free_spot(int,int) const;
  Player player_on_spot(int,int) const;

  void add_move(int,int );
  void end_turn();
  bool did_player_win();

  void game_is_over();

  vector<Spot> get_spots_neigh(Spot s);
  bool on_both_walls();
  bool spot_connects_walls(Spot);
  Spots get_wall();
};


