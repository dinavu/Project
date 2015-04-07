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

	protected:
	int xVel,yVel; 			//Its rate of movement
	int frame; 			//Its current frame
	int status; 			//Its animation status
	int enemy_height, enemy_width;	//enemy width and height
	SDL_Rect box;			//dimensions of enemy
};

#endif
