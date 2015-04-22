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
	bool virtual isDead();		//returns death
	void virtual checkDeath(int,int,int,int,int,int,bool);//checks if the enemy has been killed
	bool virtual mDead(int,int);	//returns true if mario is dead
	void virtual setX(int);		// sets the x coordinate of the plant
	void virtual setY(int);		// sets the y coordinate of the plant
	void virtual resetDeath();	// resets a plant to alive

	private:
	SDL_Rect clips[4];
};

#endif
