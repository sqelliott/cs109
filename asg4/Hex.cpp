// Hex.cpp

#include "Hex.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

Hex::Hex(int n) : size(n){
  board.resize(get_size());
  for(int i=0; i < get_size();++i){
    board[i].resize(get_size(),Player::none);
  }
}

int Hex::make_move(int row, int col){
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
  }
  return valid; 
}

bool Hex::check_for_winner(){
  if(!is_game_over()){
    did_player_win();
    end_turn();
  }
  return is_game_over();;
}

int Hex::get_size() const{
  return this->size;
}

Player Hex::curr_player() const{
  return this->player;
}

void Hex::display_board() const{
  int i = 0;
  for( int row = 0; row < get_size(); ++row, ++i){
    for(int pad=0; pad < i; ++pad){cout << " ";}
    for(int col = 0; col < get_size(); ++col){
      Player p = player_on_spot(row,col);
      switch(p){
        case Player::red  : cout << "R";
             break;
        case Player::blue : cout << "B";
             break;
        default :
                  cout << "U";
                  break;
      }
      cout << " ";
    }
    cout << endl;
  } 
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
  if( player_on_spot(r,c) != Player::none){
    return false;
  }
  return true;
}

//player_on_spot()
Player Hex::player_on_spot(int r, int c) const{
  return this->board[r][c];
}



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
}

void Hex::end_turn(){
  if(Player::red == curr_player())
    this->player = Player::blue;
  else
    this->player = Player::red;
}


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
      auto it = find(visited.begin(), visited.end(), curr_spot);
      if(it != visited.end()){
        
        if(spot_connects_walls(curr_spot)){
          game_is_over();
          return is_game_over();
        }

        edge_queue.erase(edge_queue.begin());
        visited.push_back(curr_spot);

        vector<Spot> neigh = get_spots_neigh(curr_spot);
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

void Hex::game_is_over(){
  this->_game_over = true;
  this->winner = curr_player();
}

bool Hex::is_game_over() const{
  return this->_game_over;
}

vector<Spot> Hex::get_spots_neigh(Spot s){
  int row = s.first;
  int col = s.second;
  int n_row, n_col;
  vector<Spot> neigh;
  for(int drow = -1; drow <2; ++drow){
    for(int dcol = -1; dcol <2; ++dcol){
      n_row = row+drow;
      n_col = col+dcol;
      if( valid_spot(n_row,n_col) && 
          curr_player() == player_on_spot(n_row,n_col)){
        neigh.push_back( make_pair(n_row,n_col));
      }
    }
  }
  return neigh;
}


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
  else
    return this->blue_walls.first;
}


