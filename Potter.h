#ifndef POTTER_H
#define POTTER_H

#include "Moving.h"

class Potter : public Moving
{
	public:
		Potter(char _emblem):Moving(_emblem){
			score = 0;	
		};
		void update_score(int _pts);
		int get_score();
	protected:
		int score;
};

#endif
