/* koopa.h */

#ifndef KOOPA_H
#define KOOPA_H

#include "enemy.h"
using namespace std;

class Koopa: public Enemy
{
	public:
	Koopa(int, int, int, int);	//Koopa constructor	
	void virtual move();		//Move Koopa
	void virtual update();		//Update Koopa's position
	void virtual set_clips();	//Set Koopa's clips
	SDL_Rect virtual *getLclip(); 	//return enemy's left motion clip
	SDL_Rect virtual *getRclip(); 	//return enemy's left motion clip
	int virtual getX(); 		//returns enemies x coordinate
	int virtual getY(); 		//returns enemies y coordinate
	int virtual getWidth();		//returns enemies width
	int virtual getHeight(); 	//returns enemies height
	int virtual getStatus(); 	//returns enemies status
	bool virtual isDead();		//returns death
	void virtual checkDeath(int,int,int,int,int,int,bool);//checks if the enemy has been killed
	bool virtual mDead(int,int);	//returns true if mario is dead
	void setXmax(int);		// sets the koopa's max x coordinate
	void setXmin(int);		// sets the koopa's min x coordinate
	void virtual setX(int);		// sets the x coordinate of the koopa
	void virtual setY(int);		// sets the y coordinate of the koopa
	void virtual resetDeath();	// resets a koopa to alive
	void virtual kill();		// kills koopa

	private:
	SDL_Rect clipsLeft[4];		//Koopas left moving clips
	SDL_Rect clipsRight[4];		//Koopas right moving clips
	int xmin,xmax;			//Maximum and minimum positions of koopa
};	

#endif
