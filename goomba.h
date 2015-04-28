/* goomba.h */

#ifndef GOOMBA_H
#define GOOMBA_H

#include "enemy.h"
#include <vector>
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
	void virtual kill();		// kills goomba
	bool check_collision(SDL_Rect,SDL_Rect);//checks if Goomba has collided with an object
	void checkCollisionsVer();	// checks Goombas vertical collisions
	void createFloors();		// intializes vector of floors
	void createBoxes();		// intializes vector of boxes

	private:
	SDL_Rect clipsLeft[8];		//Goomba's left moving clips
	SDL_Rect clipsDeath[4];		//Goomba's death clips
	int floorcollision,boxcollision;//variables indicating floor and box collisions
	vector <SDL_Rect> floor;	// vector of the floor coordinates
	vector <SDL_Rect> boxes;	// vector of the boxes coordinates
};

#endif
