// main.cpp
// sean elliott
// cs109 asg3

#include <iostream>
#include "Hex.h"
#include <vector>
#include <fstream>

int main(){

  Hex game(8);
  game.display_board();

  int r,y;
  int blue = 0;
  int red = 0;
  int t = 0;
  const int num_games = 1;
  for(int i = 0;i<num_games;++i){
    ++t;
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
    if(Player::red == game.get_winner()){ cout << "RED\n";++red;}
    else{ cout << "BLUE\n";++blue;}
    game.new_game();
  }
  return 0;
}
