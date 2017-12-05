// main.cpp
// sean elliott
// cs109 asg5

#include <iostream>
#include "Hex.h"
#include <vector>
#include <fstream>

int main(){
  // Change the below value to play the game on a different board size
  Hex game(6);
  cout << "Playing Hex on a " << game.get_size() << " x "
       << game.get_size() << " board\n";
  game.display_board();

  int r,y;
  while(!game.is_game_over()){
    Player curr = game.curr_player();
    if(curr == Player::red) cout << "RED";
    else cout << "BLUE";
    cout << "'s turn\n";
    int res;
    do{
      cout << "Enter your Move: ";
      cin >> r >> y;
      res = game.make_move(r,y);
      if(res == -1){
        cout << "Hex: illegal move ("<<r<<","<<y<<endl;
      }
      else if(res == 0){
        cout << "Hex: spot is occupied\n";
      }
    }while(res != 1);
    game.display_board();
  }
  cout << "=========================GAME-OVER==============================="<<endl;
  cout << "Winner is ";
  if(Player::red == game.get_winner()){ cout << "RED\n";}
  else{cout << "BLUE\n";}
  return 0;
}
