// Hex.cpp

#include "Hex.h"
#include <stdexcept>
#include <algorithm>
using namespace std;

Hex::Hex(int n = 11) : size(n){
  board.resize(get_size());
  for(auto it=board.begin(); it!=board.end();++it){
    *it.resize(get_size(),Player::none);
  }
}

int Hex::make_move(int row, int col){
  int valid = 1;
  if(game_over()){
    valid=-2;
  }
  else if(!valid_move(row,col)){
    valid = -1;
  }
  else if(!free_space(row,col)){
    valid =  0;
  }
  else{
    add_move(row,col);
  }
  return valid; 
}

bool Hex::winner(){
  if(!game_over()){
    did_player_won();
  }
  return game_over();;
}

int Hex::get_size() const{
  return this->size;
}

Player Hex::curr_player() const{
  return this->player;
}

/////////////////////
// private methods //
/////////////////////

bool Hex::game_over() const{
  return this->_game_over;
}

bool Hex::did_player_win(){
  if(on_both_walls()){
    auto spots = get_walls().first;;
    Spots visited;
    for(auto it = spots.cbegin(); it != spots.cend(); ++it){
      if(visited.find(*it) != visited.end()){
        visited.insert(*it);
        
      }
    }
  }
  return game_over();
}
