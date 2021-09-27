#include "Engine.h"
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include "Potter.h"
#include "Moving.h"
#include <curses.h>
using namespace std;


int main (int argc , char *argv[]){
	if(argc < 4)
	{
		string player_name = "Uknown Player";
		string filename = "maze.txt";
		string scorefile = "score.csv";
		Engine *eng = new Engine(filename , player_name,scorefile);
		eng->run();
		getch();
		eng->print_scores();
		system("PAUSE");
	}
	if(argc == 4){
		string filename = argv[1];
		string player_name = argv[2];
		string scorefile = argv[3];
		Engine *eng = new Engine(filename , player_name, scorefile);
		eng->run();
		getch();
		eng->print_scores();
		system("PAUSE");
		
	}
}
	

