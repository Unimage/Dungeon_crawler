#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <string>

class HighScore
{
	public:
		HighScore(std::string _player_name , int _player_score );
		std::string print_info();
		void set_values(std::string _player_name , int _player_score);
		std::string get_name();
		int get_score();
			
	protected:
		int player_score;
		std::string player_name;
};

#endif
