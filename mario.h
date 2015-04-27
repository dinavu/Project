/* mario.h */

#ifndef MARIO_H
#define MARIO_H

#include "graphics.h"
#include <cmath>
#include <vector>
using namespace std;

class Mario : public Graphics {

public:
	Mario();				// class constructor
	void handle_input(SDL_Event, int);	// take key presses and adjusts marios's velocity
	void set_clips();			// sets the images for mario's motion
	void move();				// move mario
	void jump(int);				// jump mario
	void updateStatus();			// update mario's position on the screen
	void set_camera();			// set the camera over mario's position
	int getX();				// returns mario's x coordinate
	int getY();				// returns mario's y coordinate
	int getWidth();				// returns mario's width
	int getHeight();			// returns mario's height
	int getFrame();				// returns mario's current frame
	int getStatus();			// returns mario's status
	SDL_Rect* getCamera();			// returns camera
	SDL_Event* getEvent();			// return the event from the event queue
	SDL_Rect *getRclip();			// return mario's right motion clip
	SDL_Rect *getLclip();			// return mario's left motion clip
	SDL_Rect *getCclip();			// return mario's crouch clip
	SDL_Rect *getJclip();			// return mario's jumping clip
	SDL_Rect *getOclip();			// returns a clip of mario for prelevel screen
	SDL_Rect *getFPclip();			// return mario's sliding on the flagpole clip
	SDL_Rect *getDclip();			// returns mario's death clip
	int getCamerax();			// return camera's x coordinate
	int getCameray();			// return camera's y coordinate
	bool getisJumped();			// return whether mario is jumping or not
	void setPipes();			// set pipe coordinates
	void checkPipeCollision();		// checks if mario has collided with a pipe
	void createFloors();			// create floor boundaries
	void createBoxes();			// create box/brick boundaries
	bool check_collision(SDL_Rect, SDL_Rect);// sets the true/false value for collision
	void checkCollisionsHor();		// checks for a horizontal collision
	void checkCollisionsVer();		// checks for a vertical collision
	bool isDead();				// checks if mario was killed
	void resetDeath();			// sets the value of mario's death to false
	void makeDead();			// sets the value of mario's death to true
	void setX();				// resets mario's x coordinate
	void setY();				// resets mario's y coordinate

protected:
	float x, y;				// the X and Y offsets of the dot
	float xVel, yVel;			// velocity of the mario
	float yAcc;				// mario's y acceleration
	int frame;				// frame of image
	int status;				// direction to face
	float dt;				// change in time to be used for jump()
	int marioHeight;			// mario's height
	int marioWidth;				// mario's width
	int initialT;				// get the initial time of button press
	int jumpDir;				// initial direction of mario's jump
	bool isCrouched;			// true/false that mario is crouched
	bool isJumped;				// true/false that mario is jumping
	SDL_Rect camera;			// camera object to view specific portion of background
	int collision;				// true when mario has collided with something
	int pipecollision;			// true/false of whether mario collided with a pipe
	SDL_Rect pipes[31];			// An array of all the pipes coordinates
	vector <SDL_Rect> floor;		// vector of the floor coordinates
	vector <SDL_Rect> boxes;		// vector of the boxes coordinates
	SDL_Rect marioRect;			// collisions SDL_Rect for mario		
	int floorcollision;			// detects a floor collision
	int boxcollision;			// detects a box collision
	bool death;				// true/false for alive/dead
};

#endif
