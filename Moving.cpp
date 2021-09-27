#include "Moving.h"

Moving::Moving(char _emblem){
	emblem = _emblem;
	
}
char Moving::get_emblem(){
	return emblem;
}
int Moving::getx(){return cord_x;
}
int Moving::gety(){return cord_y;
}
void Moving::set_x_y(int x , int y){
	cord_x = x;
	cord_y = y;
}
