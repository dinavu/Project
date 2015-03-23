// mario.cpp

#include "mario.h"
using namespace std;

// mario class constructor
Mario::Mario() {
	// initialize variables
	x=0;
	y=168;
	frame=0;
	status=0;
	xVel=0;
	yVel=0;
}

// adjust mario's velocity based on key pressed
void Mario::handle_input() {
	// if a key was pressed
	if( event.type == SDL_KEYDOWN ) {
        	// adjust the velocity
        	switch( event.key.keysym.sym ) {
        		case SDLK_LEFT: xVel -= marioWidth / 4; break;	// move left
        		case SDLK_RIGHT: xVel += marioWidth / 4; break;// move right
			case SDLK_DOWN: xVel = 0; break;		// crouch
        	}
	}
	// if a key was released
	else if( event.type == SDL_KEYUP ) {
        	// adjust the velocity
        	switch( event.key.keysym.sym ) {
            		case SDLK_LEFT: xVel += marioWidth / 4; break;	// move left
           		case SDLK_RIGHT: xVel -= marioWidth / 4; break;// move right
	   		case SDLK_DOWN: xVel = 0; break;		// crouch
        	}
	}
}

// update mario's velocity to move
void Mario::move() {
	x += xVel;	// move the dot left or right

	// if mario went too far to the left or right
	if( ( x < 0 ) || ( x + marioWidth > levelWidth ) ) {
        	x -= xVel;	// move back
	}

	y += yVel;	// move the dot up or down

	// if mario went too far up or down
	if( ( y < 0 ) || ( y + marioHeight > levelHeight ) ) {
		y -= yVel;	// move back
	}
}

// display mario's update position
void Mario::show() {
	if (xVel<0) {			// choose proper leftward movement frame
		status=1;
		frame++;
	}
	else if (xVel>0) {		// choose proper rightward movement frame
		status=0;
		frame++;
	}
	else if (event.key.keysym.sym==SDLK_DOWN) {	// display crouching mario
		apply_surface(x-camera->x, screenHeight-marioHeight-24, mario, screen, &clipsStill[1]);
		status=0;
	}
	else {
		frame=0;
	}

	if(frame>=4) {		// reset frame count
		frame=0;
	}

	// display leftward or rightward movement if necessary
	if (event.key.keysym.sym!=SDLK_DOWN) {
		if(status==0) {
			apply_surface(x-camera->x, screenHeight-marioHeight-24, mario, screen, &clipsRight[frame]);
		}
		else if (status==1) {
			apply_surface(x-camera->x, screenHeight-marioHeight-24, mario, screen, &clipsLeft[frame]);
		}
	}
}

// update camera position relative to mario
void Mario::set_camera() {

	// center the camera over the dot
	camera->x=(x+marioWidth/2)-screenWidth/2;
	camera->y=(y+marioHeight/2)-screenHeight/2;

	// keep the camera in bounds.
	if (camera->x<0) {
        	camera->x=0;
	}
	if (camera->y<0) {
        	camera->y=0;
	}
	if (camera->x>levelWidth-camera->w) {
        	camera->x=levelWidth-camera->w;
	}
	if (camera->y>levelHeight-camera->h) {
        	camera->y=levelHeight-camera->h;
	}
}

// returns mario's x coordinate
int Mario::getX() {
	return x;
}

// returns mario's y coordinate
int Mario::getY() {
	return y;
}

// return mario's width
int Mario::getWidth() {
	return marioWidth;
}

// return mario's height
int Mario::getHeight() {
	return marioHeight;
}

// returns mario's frame
int Mario::getFrame() {
	return frame;
}

// returns mario's status
int Mario::getStatus() {
	return status;
}
