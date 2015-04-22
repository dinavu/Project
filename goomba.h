/* goomba.h */

#ifndef GOOMBA_H
#define GOOMBA_H

#include "enemy.h"
using namespace std;

class Goomba: public Enemy
{
	public:
	Goomba(int, int);		//Goomba constructor
	void virtual move();		//Make Goomba move
	void virtual update();		//Update Goomba's position
	void virtual set_clips();	//Sets Goomba's clips
	SDL_Rect virtual *getLclip(); 	//return Goomba's left motion clip
	int virtual getX(); 		//returns enemies x coordinate
	int virtual getY(); 		//returns enemies y coordinate
	int virtual getWidth();		//returns enemies width
	int virtual getHeight();	//returns enemies height
	int virtual getStatus(); 	//returns enemies status
	bool virtual isDead();		//returns death
	void virtual checkDeath(int,int,int,int,int,int,bool);//checks if the enemy has been killed
	bool virtual mDead(int,int);	//returns true if mario is dead
	void virtual setX(int);		// sets the x coordinate of the goomba
	void virtual setY(int);		// sets the y coordinate of the goomba
	void virtual resetDeath();	// resets the enemy to alive

	private:
	SDL_Rect clipsLeft[8];		//Goomba's left moving clips
	SDL_Rect clipsDeath[4];		//Goomba's death clips
};

#endif
