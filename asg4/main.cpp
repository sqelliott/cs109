// main.cpp
// sean elliott
// cs109 asg3

#include <iostream>
#include "Hex.h"
#include <vector>
#include <fstream>

int main(){

  Hex game(5);
  game.display_board();

  int r,y;
  while(!game.is_game_over()){
    Player curr = game.curr_player();
    if(curr == Player::red) cout << "RED";
    else cout << "BLUE";
    cout << "'s turn\n";
    int res;
    do{
      //cout << "Move: ";
      //cin >> r >> y;
      Spot move = game.rand_move();
      r = move.first; y = move.second;
      cout << "Move: " << r << " " << y << endl;
      res = game.make_move(r,y);
    }while(res != 1);
    game.display_board();
  }
  cout << "=========================GAME-OVER==============================="<<endl;
  cout << "Winner is ";
  if(Player::red == game.get_winner()) cout << "RED\n";
  else cout << "BLUE\n";

  return 0;
}
