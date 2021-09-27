#ifndef ENGINE_H
#define ENGINE_H
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include "Potter.h"
#include "Moving.h"
#include "HighScore.h"

class Engine
{
	public:
		Engine(std::string filename, std::string player_name , std::string score_file);
		~Engine();
		void run();
		void print_scores();
	protected:
		std::string pname;
		bool map_loaded;
		std::string sfile;
		std::vector<std::string>maze;
		std::vector<Moving*>moving_vec;
		std::vector<HighScore*>score_vec;
		bool load_map_from_file(std::string filename);
		void set_entities();
		void set_collectables();
		void draw_map();
		int width , height;
		void get_random_pos(int &X,int &Y);
		int get_player_keystroke();
		int ch;
		void player_movement();
		int target_x , target_y;
		int c_checker;
		int check_collissions(int tx , int ty , int x , int y);
		void game_complete();
		void game_lost();
		void npc_movement();
		void set_colors();
		void init_score(std::string score_file);
		void search_update_score(std::string player_name , int player_score);
		
};

#endif
