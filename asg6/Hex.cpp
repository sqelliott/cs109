// Hex.cpp

#include "Hex.h"
#include <iostream>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <stdlib.h>
#include <ctime>
#include <math.h>
using namespace std;

Hex::Hex(int n,int num_players) : size(n),num_players(num_players){
  board.resize(get_size());
  for(int i=0; i < get_size();++i){
    board[i].resize(get_size(),Player::none);
  }
}

// adds move to board
int Hex::make_move(int row, int col){
  row -= 1;
  col -= 1;
  int valid = 1;
  if(is_game_over()){
    valid=-2;
  }
  else if(!valid_spot(row,col)){
    valid = -1;
  }
  else if(!free_spot(row,col)){
    valid =  0;
  }
  else{
    add_move(row,col);
    check_for_winner();
    if( !is_game_over() &&
        get_num_players() == 1 && 
        curr_player() == Player::blue
      ){
      cout << "Calculating move...  "<<flush;
      computers_move();
    }
  }
  return valid; 
}


// resets board and game state
bool Hex::new_game(){
  if(is_game_over()){
    for(int i=0;i<get_size();++i){
      for(int j=0; j<get_size();++j){
        this->board[i][j] = Player::none;
      }
    }
    this->player = Player::red;
    this->winner = Player::none;
    this->_game_over = false;
    this->red_walls.first.clear();
    this->red_walls.second.clear();
    this->blue_walls.first.clear();
    this->blue_walls.second.clear();
    return true;
  }
  return false;
}

inline int Hex::get_size() const{
  return this->size;
}

bool Hex::check_for_winner(){
  if(!is_game_over()){
    did_player_win();
    end_turn();
  }
  return is_game_over();;
}


Player Hex::curr_player() const{
  return this->player;
}

void Hex::display_board() const{
  int i = 0;
  for( int row = 0; row < get_size(); ++row, i+=2){
    for(int pad=0; pad < i; ++pad){cout << " ";}
    for(int col = 0; col < get_size(); ++col){
      Player p = player_on_spot(row,col,this->board);
      switch(p){
        case Player::red  : cout << "R";
             break;
        case Player::blue : cout << "B";
             break;
        default :
                  cout << ".";
                  break;
      }
      if(col < get_size()-1)cout << " - ";
    }
    cout << endl;
    if(row < get_size()-1){
      for(int pad=0; pad<=i;++pad){cout << " ";}
      for(int col = 0; col < 2*get_size()-1; ++col){
        if(col%2==0) cout << "\\";
        else cout << "/";
        cout << " ";
      }
    }
    cout << endl;
  } 
}

int Hex::get_num_players() const{
  return this->num_players;
}

Spots Hex::get_empty_spots(Board& b) const{
  Spots empty;
  for(int i = 0; i < get_size(); ++i){
    for(int j = 0; j < get_size(); ++j){
      if( b[i][j] == Player::none){
        empty.push_back( make_pair(i,j));
      }
    }
  }
  return empty;
}

Player Hex::get_winner() const{
  return this->winner;
}

Spot Hex::rand_move() const{
  random_device rd;
  default_random_engine gen(rd());
  uniform_int_distribution<int> node(1,get_size());
  return make_pair(node(gen),node(gen)); 
}

/////////////////////
// private methods //
/////////////////////

// valid_spot()
bool Hex::valid_spot(int r, int c) const{
  if( r < 0 || r >= get_size() || c < 0 || c >= get_size()){
    return false;
  }
  return true;
}

// free_spot()
bool Hex::free_spot(int r,int c) const{
  if( player_on_spot(r,c,this->board) != Player::none){
    return false;
  }
  return true;
}

//player_on_spot()
Player Hex::player_on_spot(int r, int c,Board b) const{
  return b[r][c];
}


// adds move to board
// keeps track of moves added to players
// walls
void Hex::add_move(int row, int col){
   board[row][col] = curr_player();
   if(Player::red == curr_player()){
     if(row ==0){
       this->red_walls.first.push_back(make_pair(row,col));
     }
     if(row == get_size()-1){
       this->red_walls.second.push_back(make_pair(row,col));
     } 
   }
   if(Player::blue == curr_player()){
     if(col == 0){
       this->blue_walls.first.push_back(make_pair(row,col));
     }
     if(col == get_size()-1){
       this->blue_walls.second.push_back(make_pair(row,col));
     }
   }
   this->history.push_back(make_pair(row,col));
}

void Hex::end_turn(){
  if(Player::red == curr_player())
    this->player = Player::blue;
  else
    this->player = Player::red;
}

// checks if current players walls
// are connected
bool Hex::did_player_win(){
  if(on_both_walls()){
    auto spots = get_wall();;
    vector<Spot> visited;
    vector<Spot> edge_queue;

    // add all occupied spots by player 
    for(auto it = spots.cbegin(); it != spots.cend(); ++it){
      edge_queue.push_back(*it);
    }
    while(!edge_queue.empty()){
      Spot curr_spot = edge_queue.front();
      edge_queue.erase(edge_queue.begin());
      auto it = find(visited.begin(), visited.end(), curr_spot);
      if(it == visited.end()){
        
        if(spot_connects_walls(curr_spot)){
          game_is_over();
          return is_game_over();
        }

        visited.push_back(curr_spot);

        vector<Spot> neigh = get_spots_neigh(curr_spot,this->board,curr_player());
        for(auto s : neigh){
          auto v_it = find(visited.begin(), visited.end(), s);
          auto e_it = find(edge_queue.begin(), edge_queue.end(),s);
          if(v_it == visited.end() && e_it == edge_queue.end()){
            edge_queue.push_back(s);
          }
        }
      }
    }
  }
  return is_game_over();
}

// sets game state to over
void Hex::game_is_over(){
  this->_game_over = true;
  this->winner = curr_player();
}

bool Hex::is_game_over() const{
  return this->_game_over;
}

// returns board spots adjacent to Spot s,
// which match current player
vector<Spot> Hex::get_spots_neigh(Spot s, Board b,Player p){
  int row = s.first;
  int col = s.second;
  int n_row, n_col;
  vector<Spot> neigh;
  for(int drow = -1; drow <2; ++drow){
    for(int dcol = -1; dcol <2; ++dcol){
      if( drow != dcol){
        n_row = row+drow;
        n_col = col+dcol;
        if( valid_spot(n_row,n_col) && 
            p == player_on_spot(n_row,n_col,b)){
          neigh.push_back( make_pair(n_row,n_col));
        }
      }
    }
  }
  return neigh;
}

// check if player occupies both of their walls
// if not, they have not won
bool Hex::on_both_walls(){
  if(Player::red == curr_player()){
    if(!(this->red_walls.first.empty() || 
         this->red_walls.second.empty())){
      return true;
    }
  }
  else{
    if(!(this->blue_walls.first.empty() ||
         this->blue_walls.second.empty())){
      return true;
    }
  }
  return false;
}

bool Hex::spot_connects_walls(Spot s){
  if(Player::red == curr_player()){
    auto it = find(red_walls.second.begin(), red_walls.second.end(), s);
    return (it != this->red_walls.second.end());
  }
  else{
    auto it1 = find(blue_walls.second.begin(), blue_walls.second.end(), s);
    return (it1 != this->blue_walls.second.end());
  }
}


// get_walls()
Spots Hex::get_wall(){
  if(Player::red == curr_player()){
    return this->red_walls.first;
  }
  else{
    return this->blue_walls.first;
  }
}

// Implement Monte Carlo
// Plays a random game on each available empty spot on board
// Selects the one with the most wins
void Hex::computers_move() {
  const clock_t begin_time = clock();
  Spots       empty  = get_empty_spots(this->board);
  Board b = this->board;
  vector<int> values;
  for( Spot s : empty){
    Board b_instance = b;
    b_instance[s.first][s.second] = curr_player();
    int wins = 0;
    for(int i = 0; i < 1000; ++i){
      if(simulate_random_game(b_instance)) ++wins;
    }
    values.push_back(wins);
  }
  int index = distance(values.begin(), 
                                 max_element(values.begin(),values.end()));   
  int x = empty[index].first+1;
  int y = empty[index].second+1;
  make_move(x,y);
  cout << float(clock()-begin_time)/CLOCKS_PER_SEC << " secs\n";
}

// Simluates a random game based
// returns amount of wins for AI
bool Hex::simulate_random_game(Board b){
  Spots empty = get_empty_spots(this->board);
  Player curr = Player::blue;
  
  random_device rd;
  default_random_engine gen(rd());
  uniform_int_distribution<int> node(0,empty.size()-1);

  int move;
  Spot s;
  while(!empty.empty()){
    move = node(gen);
    s = empty[move];
    empty.erase(empty.begin()+move);
    
    b[s.first][s.second] = curr;
    if(curr == Player::blue){
      curr = Player::red;
    }
    else{
      curr = Player::blue; 
    }

    if(winning_move(b)) return true;
    if(losing_move(b))  return false;
    
  }
  
}


int Hex::alpha_beta(Board& b,Spot& s, int depth, int alpha, int beta, bool AI){
  if( depth == 0 || winning_move(b) || losing_move(b)){
    return move_evaluation(b,s);
  }
  if(AI){
    int v = numeric_limits<int>::min();
    Spots empty = get_empty_spots(b);
    for( Spot spot : empty){
      Board b_instance = b;
      b_instance[spot.first][spot.second] = curr_player();
      v     = max(v, alpha_beta(b_instance,spot,depth-1,alpha,beta,false));
      alpha = max(alpha,v);
      if( beta <= alpha){
        break;
      }
    }
    return v;
  }
  else{
    int v = numeric_limits<int>::max();
    Spots empty = get_empty_spots(b);
    for( Spot spot : empty){
      Board b_instance = b;
      b_instance[spot.first][spot.second] = curr_player();
      v    = min(v, alpha_beta(b_instance,spot,depth-1,alpha,beta,true));
      beta = min(beta,v);
      if(beta <= alpha){
        break;
      }
    }
    return v;
  }
  return 0;
}

int Hex::move_evaluation(Board& b,Spot& s){
  int value = 0;

  if(winning_move(b)){
    value += 100;
  }
  if(losing_move(b)){
    value -= 10;
  }

  // average move towards middle
  auto bw = blue_spots(b);
  int mid = b.size()/2;
  int tmp = 0;
  for(Spot s : bw){
    tmp -= abs(s.first - mid);
  }
  value -= tmp/10;

  // longest blue chain from left wall
  value += longest_blue_path(b);
  value -= longest_red_path(b);
  //cout << value << endl;
  return value;
}

// get blues left wall
Spots Hex::blue_wall(Board& b){
  Spots bw;
  for(int i = 0; i < b.size(); ++i){
    if(b[i][0] == Player::blue){
      bw.push_back(make_pair(i,0));
    }
  }
  return bw;
}

int Hex::longest_blue_path(Board& b){
  Spots v, e;
  vector<vector<int>> values;//higher values for connectivity
  values.resize(b.size());
  for(int i=0; i < b.size(); ++i){
    values[i].resize(b.size());
  }
  vector<vector<Spot>> p;//parents
  p.resize(b.size());
  for(int i = 0; i < b.size(); ++i){
    p[i].resize(b.size(),make_pair(-1,-1));
  }

  auto bw = blue_spots(b);//get blue left walls
  while(!bw.empty()){
    Spot curr_spot = bw.front();
    bw.erase(bw.begin());

    Spots neighbors = get_spots_neigh(curr_spot,b,Player::blue);
    for(auto n : neighbors){
      int value = values[curr_spot.first][curr_spot.second] +
                  (n.second - curr_spot.second) + 1;
      values[n.first][n.second] = value;
    }
  }
  int max = 0;
  for(int i = 0; i < values.size();++i){
    for(int j = 0; j < values.size();++j){
      if( values[i][j] > max){
        max = values[i][j];
      }
    }
  }
  return max;
}


int Hex::longest_red_path(Board& b){
  Spots v, e;
  vector<vector<int>> values;//higher values for connectivity
  values.resize(b.size());
  for(int i=0; i < b.size(); ++i){
    values[i].resize(b.size());
  }
  vector<vector<Spot>> p;//parents
  p.resize(b.size());
  for(int i = 0; i < b.size(); ++i){
    p[i].resize(b.size(),make_pair(-1,-1));
  }

  auto bw = red_spots(b);//get blue left walls
  while(!bw.empty()){
    Spot curr_spot = bw.front();
    bw.erase(bw.begin());

    Spots neighbors = get_spots_neigh(curr_spot,b,Player::red);
    for(auto n : neighbors){
      int value = values[curr_spot.first][curr_spot.second] +
                  1;
      values[n.first][n.second] = value;
    }
  }
  int max = 0;
  for(int i = 0; i < values.size();++i){
    for(int j = 0; j < values.size();++j){
      if( values[i][j] > max){
        max = values[i][j];
      }
    }
  }
  return max;
}


Spots Hex::blue_spots(Board& b){
  Spots blue;
  for(int i = 0; i < b.size(); ++i){
    for(int j = 0; j < b.size(); ++j){
      if(b[i][j] == Player::blue){
        blue.push_back(make_pair(i,j));
      }
    }
  }
  return blue;
}

Spots Hex::red_spots(Board& b){
  Spots red;
  for(int i = 0; i < b.size(); ++i){
    for(int j = 0; j < b.size(); ++j){
      if(b[i][j] == Player::red){
        red.push_back(make_pair(i,j));
      }
    }
  }
  return red;
}

Spots Hex::free_spots(Board& b){
  Spots free;
  for(int i = 0; i < b.size(); ++i){
    for(int j = 0; j < b.size(); ++j){
      if(b[i][j] == Player::none){
        free.push_back(make_pair(i,j));
      }
    }
  }
  return free;  
}

int Hex::dist_to_wall(Board& b, Spot& s){
  vector<Spot> visited;
  vector<Spot> edge_queue;
  vector<vector<int>> costs;
  costs.resize(b.size());
  for(int i=0; i < b.size();i++){
    costs[i].resize(b.size());
  }

  for(int i = 0; i < get_size(); ++i){
    if(b[i][0] == Player::blue){
      edge_queue.push_back(make_pair(i,0));
    }
  }
  while(!edge_queue.empty()){
    Spot curr_spot = edge_queue.front();
    edge_queue.erase(edge_queue.begin());
    auto it = find(visited.begin(), visited.end(), curr_spot);
    if(it == visited.end()){
      
      if(curr_spot.second == get_size() -1){
        return true;
      }

      visited.push_back(curr_spot);

      vector<Spot> neigh = get_spots_neigh(curr_spot,b,Player::blue);
      for(auto s : neigh){
        auto v_it = find(visited.begin(), visited.end(), s);
        auto e_it = find(edge_queue.begin(), edge_queue.end(),s);
        if(v_it == visited.end() && e_it == edge_queue.end()){
          edge_queue.push_back(s);
        }
      }
    }
  }

  return false;
}

bool Hex::winning_move(Board& b){
  vector<Spot> visited;
  vector<Spot> edge_queue;

  for(int i = 0; i < get_size(); ++i){
    if(b[i][0] == Player::blue){
      edge_queue.push_back(make_pair(i,0));
    }
  }
  while(!edge_queue.empty()){
    Spot curr_spot = edge_queue.front();
    edge_queue.erase(edge_queue.begin());
    auto it = find(visited.begin(), visited.end(), curr_spot);
    if(it == visited.end()){
      if(curr_spot.second == get_size()-1){
        return true;
      }

      visited.push_back(curr_spot);

      vector<Spot> neigh = get_spots_neigh(curr_spot,b,Player::blue);
      for(auto s : neigh){
        auto v_it = find(visited.begin(), visited.end(), s);
        auto e_it = find(edge_queue.begin(), edge_queue.end(),s);
        if(v_it == visited.end() && e_it == edge_queue.end()){
          edge_queue.push_back(s);
        }
      }
    }
  }

  return false;
}

bool Hex::losing_move(Board& b){
  vector<Spot> visited;
  vector<Spot> edge_queue;

  for(int i = 0; i < get_size(); ++i){
    if(b[0][i] == Player::red){
      edge_queue.push_back(make_pair(0,i));
    }
  }
  while(!edge_queue.empty()){
    Spot curr_spot = edge_queue.front();
    edge_queue.erase(edge_queue.begin());
    auto it = find(visited.begin(), visited.end(), curr_spot);
    if(it == visited.end()){
      
      if(curr_spot.first == get_size() -1){
        return true;
      }

      visited.push_back(curr_spot);

      vector<Spot> neigh = get_spots_neigh(curr_spot,b,Player::blue);
      for(auto s : neigh){
        auto v_it = find(visited.begin(), visited.end(), s);
        auto e_it = find(edge_queue.begin(), edge_queue.end(),s);
        if(v_it == visited.end() && e_it == edge_queue.end()){
          edge_queue.push_back(s);
        }
      }
    }
  }

  return false;
}
