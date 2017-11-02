// Hex.cpp

#include "Hex.h"
#include <stdexcept>
using namespace std;

Hex::Hex(int n = 11){
  set_size(n);
  board.resize(get_size());
  for(auto it=board.begin(); it!=board.end();++it){
    *it.resize(get_size(),Player::none);
  }
}

int Hex::move(int row, int col){
  int valid = 1;
  if(!valid_move(row,col)){
    valid = -1;
  }
  else if(!free_space(row,col)){
    valid = 0;
  }
  else{
    board[row][col]= curr_player();
  }
  return valid; 
}

bool Hex::winner(){
  if(!game_over()){
    if(curr_player() == Player::red){
      did_red_win();
    }
    else{
      did_blue_win();
    }
  }

  return game_over();;
}

int Hex::get_size() const{
  return this->size;
}

void Hex::set_size(int size){
  this->size = size;
}

Player Hex::current_player() const{
  return this->player;
}

/////////////////////
// private methods //
/////////////////////

bool Hex::game_over() const{
  return this->winner;
}

bool Hex::did_red_win(){
  
}
