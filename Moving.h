#ifndef MOVING_H
#define MOVING_H
#include <string>

class Moving
{
	public:
		Moving(char _emblem);
    	~Moving(){};
    	char get_emblem();
    	int getx();
    	int gety();
    	void set_x_y(int x , int y);
		
	protected:
		char emblem;
    	int cord_x;
    	int cord_y;
};

#endif
