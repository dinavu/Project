/* enemy.h */

#ifndef ENEMY_H
#define ENEMY_H

#include "graphics.h"
#include <cmath>
using namespace std;

class Enemy : public Graphics
{
	public:	
	Enemy(); 			//Initializes the variables
	void virtual move(); 		//Moves enemies
	void virtual update();		//updates enemies frams
	void virtual set_clips(); 	//Set clips for each enemy
	SDL_Rect virtual *getLclip(); 	//return enemy's left motion clip
	SDL_Rect virtual *getRclip(); 	//return enemy's right motion clip
	int virtual getX(); 		//returns enemies x coordinate
	int virtual getY(); 		//returns enemies y coordinate
	int virtual getWidth();		//returns enemies width
	int virtual getHeight(); 	//returns enemies height
	int virtual getStatus(); 	//returns enemies status
	bool virtual isDead();		//returns death
	void virtual checkDeath(int,int,int,int,int,int,bool);//checks if the enemy has been killed
	bool virtual mDead(int,int);	//returns true if mario is dead
	void virtual setX(int);		// sets enemy x coordinate
	void virtual setY(int);		// sets enemy y coordinate
	void virtual resetDeath();	// resets all the enemies to alive
	void virtual kill();		//kills the enemy

	protected:
	int xVel,yVel; 			//Its rate of movement
	int frame; 			//Its current frame
	int status; 			//Its animation status
	int enemy_height, enemy_width;	//enemy width and height
	SDL_Rect box;			//dimensions of enemy
	bool death;			//true if the enemy is dead
	bool firedeath;			//true when killed by fireball
};

#endif
