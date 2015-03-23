/* mario.h */

#ifndef MARIO_H
#define MARIO_H

#include "graphics.h"
using namespace std;

class Mario : public Graphics {

public:
	Mario();		// class constructor
	void handle_input();	// take key presses and adjusts marios's velocity
	void move();		// move mario
	void show();		// display the updated mario on the screen
	void set_camera();	// set the camera over mario's position
	int getX();		// returns mario's x coordinate
	int getY();		// returns mario's y coordinate
	int getWidth();		// returns mario's width
	int getHeight();	// returns mario's height
	int getFrame();		// returns mario's current frame
	int getStatus();	// returns mario's status

protected:
	int x, y;		// the X and Y offsets of the dot
	int xVel, yVel;		// velocity of the mario
	int frame;		// frame of image
	int status;		// direction to face
	int marioHeight;	// mario's height
	int marioWidth;		// mario's width
};

#endif
