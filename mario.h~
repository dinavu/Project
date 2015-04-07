/* mario.h */

#ifndef MARIO_H
#define MARIO_H

#include "graphics.h"
#include <cmath>
using namespace std;

class Mario : public Graphics {

public:
	Mario();			// class constructor
	void handle_input(SDL_Event);	// take key presses and adjusts marios's velocity
	void set_clips();		// sets the images for mario's motion
	void move();			// move mario
	void updateStatus();		// update mario's position on the screen
	void set_camera();		// set the camera over mario's position
	int getX();			// returns mario's x coordinate
	int getY();			// returns mario's y coordinate
	int getWidth();			// returns mario's width
	int getHeight();		// returns mario's height
	int getFrame();			// returns mario's current frame
	int getStatus();		// returns mario's status
	SDL_Rect* getCamera();		// returns camera
	SDL_Event* getEvent();		// return the event from the event queue
	SDL_Rect *getRclip();		// return mario's right motion clip
	SDL_Rect *getLclip();		// return mario's left motion clip
	SDL_Rect *getCclip();		// return mario's crouch clip
	SDL_Rect *getJclip();		// return mario's jumping clip
	int getCamerax();		// return camera's x coordinate
	int getCameray();		// return camera's y coordinate

protected:
	int x, y;			// the X and Y offsets of the dot
	int xVel, yVel;			// velocity of the mario
	int frame;			// frame of image
	int status;			// direction to face
	int marioHeight;		// mario's height
	int marioWidth;			// mario's width
	bool isCrouched;		// true/false that mario is crouched
	bool isJumped;			// true/false that mario is jumping
	SDL_Rect camera;		// camera object to view specific portion of background
};

#endif
