/* collisions.h */

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "graphics.h"
#include <vector>
using namespace std;

class Collisions : public Graphics
{

public:
	Collisions();				//initializes variables

	void setFloor();
	void setBoxes();
	void setSpecialBoxes();

protected:
	vector <int> xPos;
	vector <int> yPos;

	SDL_Rect floor1;
	SDL_Rect floor2;
	SDL_Rect floor3;
	SDL_Rect floor4;

	SDL_Rect box1;
	SDL_Rect box2;
	SDL_Rect box3;
	SDL_Rect box4;
	SDL_Rect box5;
	SDL_Rect box6;
	SDL_Rect box7;
	SDL_Rect box8;
	SDL_Rect box9;
	SDL_Rect box10;
	SDL_Rect box11;
	SDL_Rect box12;
	SDL_Rect box13;
	SDL_Rect box14;
	SDL_Rect box15;
	SDL_Rect box16;
	SDL_Rect box17;
};

#endif
