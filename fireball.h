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
	void moveFire(int);		// move fireball
	void set_clips();		// sets the image clips for fireball
	void updateFire();		// display the updated fireball on the screen
	void setFireX(int);		// sets the x coordinate of fireball
	void setFireY(int);		// sets the y coordinate of fireball
	int getFireX();			// returns the x coordinate of fireball
	int getFireY();			// returns the y coordinate of the fireball
	int getFireH();			// return the fireballs width
	int getFireW();			// return the fireballs height
	int getFireFrame();		// return the frame of the fireball's motion
	int getFireStatus();		// return the status (direction of the fireball
	SDL_Rect *getFireR();		// return fireball's right motion clip
	SDL_Rect *getFireL();		// return fireball's left motion clip
	bool getIsFire();		// return truth value of isFire
	int checkDeath(int, int, int, int, bool);// Checks if fireball collides with anything. return 1 when enemy enemy should die
	void countup();			// increase fireballcount
	int getCount();			// returns number of fireballs fired
	void resetIsFire();		// resets isFire to false

private:
	int fireX, fireY;		// x and y offsets of the fireball
	int fireXvel, fireYvel;		// x and y velocities of the fireball
	int fireFrame;			// frame of fireball image
	int fireStatus;			// direction of fireball
	int fireH;			// fireball height
	int fireW;			// fireball width
	bool isFire;			// true/false that there is a fireball to display
	int fireballcount;		// Keeps track of how many fireballs can be used
	bool collision;			// Enemy or obstacle collision
};

#endif
