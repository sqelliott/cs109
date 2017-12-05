// Hex.h

#include <vector>
#include <unordered_set>
using namespace std;



enum class Player{red,blue,none};
// Defines Player types.
typedef pair<int,int> Spot;
// Defines a spot on Hex board
typedef vector<Spot> Spots;
// vector of Spots
typedef pair<Spots,Spots> Walls;
// pair of vectors of spots
// used to keep track of each 
// players walls needed to win
typedef vector<vector<Player>> Board;


class Hex{
public:  
  // Constructor:
  Hex(int n=11, int num_players=1);

  // Modifiers
  int make_move(int,int);
  bool new_game();

  // Selectors
  inline int get_size() const;
  // return board dimensions

  Spot rand_move() const;
  // generate a random move

  Player get_winner() const;
  // return game winner

  Player curr_player() const;
  // return current turn's
  // player

  bool is_game_over() const;
  void display_board() const;

  int get_num_players() const;
  Spots get_empty_spots(Board& b) const;
  
private:
  // state member variables
  Board board;
  Player player = Player::red;
  Player winner = Player::none;
  bool _game_over = false;
  const int size;
  const int num_players;
  Spots history;

  // Container to maintain spots occupied by a player
  // on their respective walls to win the game.
  Walls red_walls;
  Walls blue_walls;
  
  bool   check_for_winner();
  bool   valid_spot(int,int) const;
  bool   free_spot(int,int) const;
  Player player_on_spot(int,int,Board) const;

  void add_move(int,int );
  void end_turn();
  bool did_player_win();

  void game_is_over();

  vector<Spot> get_spots_neigh(Spot s, Board,Player p);
  bool  on_both_walls();
  bool  spot_connects_walls(Spot);
  Spots get_wall();
  bool  on_wall(Spot);

  // alpha beta
  void computers_move();
  bool simulate_random_game(Board);
  int  alpha_beta(Board&,Spot&,int,int,int,bool);
  bool winning_move(Board&);
  bool losing_move(Board&);
  int  move_evaluation(Board&, Spot& s);
  int  dist_to_wall(Board&,Spot& s);
  Spots blue_spots(Board&);
  Spots red_spots(Board&);
  Spots free_spots(Board&);

  Spots blue_wall(Board&);
  int longest_blue_path(Board&);
  int longest_red_path(Board&);

};


