#include "Engine.h"
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include "Potter.h"
#include "Moving.h"
#include <curses.h>
#include <time.h>
#include "Gnome.h"
#include "Traal.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cstring>

using namespace std;

Engine::Engine(string filename, string player_name, string score_file){
 	map_loaded = load_map_from_file(filename);
 	if(map_loaded == true){
 		srand(time(NULL));
 		initscr();
    	start_color();
    	cbreak();
    	noecho();
    	nonl();
    	intrflush (stdscr,FALSE);
    	keypad(stdscr,TRUE);
    	curs_set(0);
    	set_colors();
    	pname = player_name;
    	sfile = score_file;
    	moving_vec.push_back(new Potter('P'));
    	moving_vec.push_back(new Gnome('G'));
    	moving_vec.push_back(new Traal('T'));
		init_score(score_file);		
	 }
}

bool Engine::load_map_from_file(string filename ){
	ifstream mapFile(filename);
	if (!mapFile){
    	return false;
}
	string mapLine;

	while (getline (mapFile, mapLine)) {
  		maze.push_back(mapLine);
	}
	return true;
}

void Engine::draw_map(){
	 width = maze.at(0).size();
	 height = maze.size();
	for(int i = 0; i<height; i++){
		for(int j = 0; j<width; j++){
			if(maze.at(i)[j]=='@'){
			attron(COLOR_PAIR(1));
			mvprintw(i, j, &maze.at(i)[j]);
			attroff(COLOR_PAIR(1));
				
			}else if (maze.at(i)[j]=='T'||maze.at(i)[j]=='G')
			{
				attron(COLOR_PAIR(3));
				mvprintw(i, j, &maze.at(i)[j]);
				attroff(COLOR_PAIR(3));
			}else if (maze.at(i)[j]=='$')
			{
				attron(COLOR_PAIR(4));
				mvprintw(i, j, &maze.at(i)[j]);
				attroff(COLOR_PAIR(4));
			}else if (maze.at(i)[j]=='P')
			{
				attron(COLOR_PAIR(2));
				mvprintw(i, j, &maze.at(i)[j]);
				attroff(COLOR_PAIR(2));
				
			}else
			mvprintw(i, j, &maze.at(i)[j]);
		}
	}
}

void Engine::set_collectables(){
	int Y, X ;
	for(int i = 0 ; i < 10 ; i++)
	{
		get_random_pos(X,Y);
		maze.at(Y)[X] = '@';	
	}
	get_random_pos(X,Y);
	maze.at(Y)[X] = '$';
	
}

void Engine::get_random_pos(int &X,int &Y){
    do {
        X = rand() % width;
        Y = rand() % height;
    } while(maze.at(Y)[X]!=' ');
}

void Engine::set_entities(){
	int Y, X ;
	for(int i =0 ; i<moving_vec.size();i++)
	{
		get_random_pos(X,Y);
		maze.at(Y)[X] = moving_vec.at(i)->get_emblem();
		moving_vec.at(i)->set_x_y(X , Y);		
	}
	
}

int Engine::get_player_keystroke(){
	return getch();
}

void Engine::player_movement(){
	target_x = moving_vec.at(0)->getx();
	target_y = moving_vec.at(0)->gety();
	while(1)
	{
		ch=get_player_keystroke();
		if(ch == 27) {
			attron(COLOR_PAIR(2));
            mvprintw(11,(width+2)/2-(strlen("PRESS ANY KEY TO EXIT")/2),"PRESS ANY KEY TO EXIT");
            search_update_score(pname , 0);
            attroff(COLOR_PAIR(2));
			endwin();
            break;
        }
    	switch(ch){
            case KEY_LEFT:
                target_x--;
            break;
            case KEY_UP:
                target_y--;
            break;
            case KEY_RIGHT:
                target_x++;
            break;
            case KEY_DOWN:
                target_y++;
            break;
        }
        c_checker = check_collissions(target_x , target_y ,moving_vec.at(0)->getx() ,moving_vec.at(0)->gety() );
        if(c_checker == 1)
		{			//its a wall
					draw_map();
					refresh();
					target_x  = moving_vec.at(0)->getx();
					target_y = moving_vec.at(0)->gety();
		 }
		 else if (c_checker == 2)
		 {
		 	//its a gemstone
		 	int pts = 10;
		 	maze.at(target_y)[target_x] = 'P';
		 	maze.at(moving_vec.at(0)->gety())[moving_vec.at(0)->getx()] = ' ';
		 	moving_vec.at(0)->set_x_y(target_x , target_y);
		 	Potter *t = (Potter*)moving_vec.at(0);
		 	t->update_score(pts);
		 	draw_map();
			refresh();
		 	
		  }
		  else if (c_checker == 3)
		 {
		 	//its a scroll
		 	int pts = 100;
		 	maze.at(target_y)[target_x] = 'P';
		 	maze.at(moving_vec.at(0)->gety())[moving_vec.at(0)->getx()] =' ';
		 	moving_vec.at(0)->set_x_y(target_x , target_y);
		 	Potter *t = (Potter*)moving_vec.at(0);
		 	t->update_score(pts);
		 	game_complete();
			 break;	
		  }
		  else if (c_checker ==4){
		  	//its either of the mobs
		  	game_lost();
		  	break;
		  	}
		  	else{
		  		
		  		maze.at(target_y)[target_x] = 'P';
		 		maze.at(moving_vec.at(0)->gety())[moving_vec.at(0)->getx()] = ' ';
		 		moving_vec.at(0)->set_x_y(target_x , target_y);
		  		mvaddch(moving_vec.at(0)->gety(),moving_vec.at(0)->getx(),' ');		
			  }
		npc_movement();
		draw_map();
		refresh();	
	}
}

int Engine::check_collissions(int tx , int ty , int x , int y){
	if(maze.at(ty)[tx] == '*'){return 1;
	}else if (maze.at(ty)[tx] == '@')
	{return 2;}
	else if (maze.at(ty)[tx] == '$')
	{return 3;}
	else if (maze.at(ty)[tx] == 'G' ||maze.at(ty)[tx]=='T' || maze.at(ty)[tx]=='P' )
	{return 4;}
	else{return 0;}
	
}

void Engine::game_complete(){
	Potter *t = (Potter*)moving_vec.at(0);
	int res = t->get_score();
	clear();
	attron(COLOR_PAIR(1));
	mvprintw(11,(width+2)/2-(strlen("You won!")),"You Won!");
    mvprintw(12,(width+2)/2-(strlen("Points got:")),"Points got %d",res);
    attroff(COLOR_PAIR(1));
    search_update_score(pname , res);
	endwin();
	
}

void Engine::game_lost(){
	Potter *t = (Potter*)moving_vec.at(0);
	int res = t->get_score();
	clear();
	attron(COLOR_PAIR(3));
	mvprintw(11,(width+2)/2-(strlen("You lost!")),"You lost!");
    mvprintw(12,(width+2)/2-(strlen("Points got:")),"Points got %d",res);
    attroff(COLOR_PAIR(3));
    search_update_score(pname , res);
    endwin();
	
}

void Engine::npc_movement(){
	for(int i=1; i<moving_vec.size();i++)
	{	
		int colls;
		int direction;
        int cur_x =moving_vec.at(i)->getx();
        int cur_y = moving_vec.at(i)->gety();
        bool done = false; 
		do{
			direction = rand() % 4;	
			switch(direction){
			 
			case 0://move up check colls
                cur_y --;
                if(cur_x < width-1 && cur_y < height-1 && cur_x > 1 && cur_y > 1){
				
				if(maze.at(cur_y)[cur_x] == ' ')
                {
                    maze.at(cur_y)[cur_x] = moving_vec.at(i)->get_emblem();
                    maze.at(moving_vec.at(i)->gety())[moving_vec.at(i)->getx()] = ' ';
                    moving_vec.at(i)->set_x_y(cur_x , cur_y);
                    done = true;

                }
            }
                break;
			case 1://move down check colls
                cur_y ++;
                if(cur_x < width-1 && cur_y < height-1 && cur_x > 1 && cur_y > 1){
				if(maze.at(cur_y)[cur_x] == ' ')
                {
                    maze.at(cur_y)[cur_x] = moving_vec.at(i)->get_emblem();
                    maze.at(moving_vec.at(i)->gety())[moving_vec.at(i)->getx()] = ' ';
                    moving_vec.at(i)->set_x_y(cur_x , cur_y);
                    done = true;

                }}
                break;
			case 2://move right check colls
                cur_x ++;
                if(cur_x < width-1 && cur_y < height-1 && cur_x > 1 && cur_y > 1){
				if(maze.at(cur_y)[cur_x] == ' ')
                {
                    maze.at(cur_y)[cur_x] = moving_vec.at(i)->get_emblem();
                    maze.at(moving_vec.at(i)->gety())[moving_vec.at(i)->getx()] = ' ';
                    moving_vec.at(i)->set_x_y(cur_x , cur_y);
                    done = true;

                }}
                break;
			case 3://move left check colls
				cur_x --;
				if(cur_x < width-1 && cur_y < height-1 && cur_x > 1 && cur_y > 1){
                if(maze.at(cur_y)[cur_x] == ' ')
                {
                    maze.at(cur_y)[cur_x] = moving_vec.at(i)->get_emblem();
                    maze.at(moving_vec.at(i)->gety())[moving_vec.at(i)->getx()] = ' ';
                    moving_vec.at(i)->set_x_y(cur_x , cur_y);
                    done = true;

                }}
                break;
	 	}
		}while(done==false);			
	}
}

void Engine::set_colors(){
	if(has_colors()){
		start_color();
		init_pair(1, COLOR_GREEN, COLOR_BLACK);	
		init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(3, COLOR_RED, COLOR_BLACK);
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	}
	
}

void Engine::init_score(string score_file)
{
	fstream fin;
	int counter = 5;
	string name;
	int score;
	string line;
	string delimiter = ",";
	fin.open(score_file,std::ios::in);
	if(!fin.is_open()){
    	std::cout<<"Exiting game.";
		return;
	}
	while (std::getline(fin, line) && counter){
	 	name = line.substr(0, line.find(delimiter));
		score =  stoi(line.substr(line.find(delimiter)+1, *(line.end()-1))); 
		
		score_vec.push_back(new HighScore(name,score));
		counter--;
	}
	fin.close();

}

void Engine::search_update_score(string player_name , int player_score){
	bool done = false;
	for(int i=0; i<score_vec.size();i++)
	{
		if(score_vec.at(i)->get_name() == player_name)
		{
			if(score_vec.at(i)->get_score() < player_score)
			{
				score_vec.at(i)->set_values(player_name , player_score);
				done = true;
			}
		}		
	}
	if(done == false)
	{
		score_vec.push_back(new HighScore(player_name,player_score));
	}
}

//also saves to csv.
void Engine:: print_scores(){
		cout<<"\n\t\tHigh Scores"<<endl;
	for(int i =0 ; i<score_vec.size();i++)
	{
		cout<<"\t\t"<<score_vec.at(i)->print_info()<<endl;
	}
	fstream fout;
	fout.open(sfile);
	for(int i =0 ; i<score_vec.size();i++)
	{
		string fname = score_vec.at(i)->get_name();
		int fscore = score_vec.at(i)->get_score();
		fout<<fname + "," + to_string(fscore) + "\n";
	}
}

void Engine::run(){
	draw_map();
	set_collectables();
	set_entities();
	draw_map();
    refresh();
    player_movement();
}


