/* plant.h */

#ifndef PLANT_H
#define PLANT_H

#include "enemy.h"
using namespace std;

class Plant: public Enemy
{
	public:
	Plant(int, int);		//Plant constructor
	void virtual move();		//Make Plant move
	void virtual update();		//Update plant frame
	void virtual set_clips();	//Set plant clips
	SDL_Rect virtual *getLclip(); 	//return plants clip
	int virtual getX(); 		//returns enemies x coordinate
	int virtual getY(); 		//returns enemies y coordinate
	int virtual getWidth();		//returns enemies width
	int virtual getHeight();	//returns enemies height
	int virtual getStatus(); 	//returns enemies status


	private:
	SDL_Rect clips[4];
};

#endif
