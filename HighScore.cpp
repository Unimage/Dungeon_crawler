#include "HighScore.h"
#include <string>
#include <iostream>
using namespace std;



HighScore::HighScore(string _player_name , int _player_score)
{
	player_score = _player_score;
	player_name = _player_name;
}

string HighScore::print_info(){
	string s = "Player: " + player_name + " Score: " + to_string(player_score);
	return s;
}

void HighScore :: set_values(string _player_name , int _player_score)
{
	if(player_name == _player_name)
	{
		player_score = _player_score;
	}
}
string HighScore::get_name(){return player_name;
}
int HighScore::get_score(){return player_score;
}
