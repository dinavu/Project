/* fireball.h
This class controls the movement of a fireball from mario
*/

#ifndef FIREBALL_H
#define FIREBALL_H

#include "graphics.h"
#include <cmath>

class Fireball : public Graphics {

public:
	Fireball(int, int);		// class constructpr
	void handleFire(SDL_Event);	// use key presses to adjust fireball's position
	void moveFire();		// move fireball
	void set_clips();		// sets the image clips for fireball
	void updateFire();		// display the updated fireball on the screen
	void setFireX(int);		// sets the x coordinate of fireball
	void setFireY(int);		// sets the y coordinate of fireball
	int getFireX();			// returns the x coordinate of fireball
	int getFireY();			// returns the y coordinate of the fireball
	int getFireFrame();		// return the frame of the fireball's motion
	int getFireStatus();		// return the status (direction of the fireball
	SDL_Rect *getFireR();		// return fireball's right motion clip
	SDL_Rect *getFireL();		// return fireball's left motion clip
	bool getIsFire();		// return truth value of isFire

private:
	int fireX, fireY;		// x and y offsets of the fireball
	int fireXvel, fireYvel;		// x and y velocities of the fireball
	int fireFrame;			// frame of fireball image
	int fireStatus;			// direction of fireball
	int fireH;			// fireball height
	int fireW;			// fireball width
	bool isFire;			// true/false that there is a fireball to display
};

#endif
