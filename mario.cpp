// mario.cpp

#include "mario.h"
#include <iostream>
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
	marioWidth=16;
	marioHeight=32;
	//camera dimensions
	camera.x=0;
	camera.y=0;
	camera.w=640;
	camera.h=224;
	mario=load_image("images/bigMarioMotion.png");
}

// adjust mario's velocity based on key pressed
void Mario::handle_input(SDL_Event event) {
	// if a key was pressed
	if( event.type == SDL_KEYDOWN ) {
        	// adjust the velocity
        	switch( event.key.keysym.sym ) {
        		case SDLK_LEFT: xVel -= getWidth() / 4; break;	// move left
        		case SDLK_RIGHT: xVel += getWidth() / 4; break;// move right
			case SDLK_DOWN: xVel = 0; break;		// crouch
        	}
	}
	// if a key was released
	else if( event.type == SDL_KEYUP ) {
        	// adjust the velocity
        	switch( event.key.keysym.sym ) {
            		case SDLK_LEFT: xVel += getWidth() / 4; break;	// move left
           		case SDLK_RIGHT: xVel -= getWidth() / 4; break;// move right
	   		case SDLK_DOWN: xVel = 0; break;		// crouch
        	}
	}

	cout << "MARIO HANDLE INPUT" << endl;
	cout << "xVel: " << xVel << endl;
	cout << "yVel: " << yVel << endl;
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;
	cout << "mariowidth " << getWidth() << endl;
}

// update mario's velocity to move
void Mario::move() {
	x += xVel;	// move the dot left or right

	// if mario went too far to the left or right
	if( ( x < 0 ) || ( getX() + getWidth() > getLevelW() ) ) {
        	x -= xVel;	// move back
	}

	y += yVel;	// move the dot up or down

	// if mario went too far up or down
	if( ( y < 0 ) || ( getY() + getHeight() > getLevelH() ) ) {
		y -= yVel;	// move back
	}

	cout << "MARIO MOVE" << endl;
	cout << "xVel: " << xVel << endl;
	cout << "yVel: " << yVel << endl;
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;

}

// display mario's update position
void Mario::updatePos() {
	if (xVel<0) {			// choose proper leftward movement frame
		status=1;
		frame++;
	}
	else if (xVel>0) {		// choose proper rightward movement frame
		status=0;
		frame++;
	}
	else if (event.key.keysym.sym==SDLK_DOWN) {	// display crouching mario
		//apply_surface(x-camera.x, screenHeight-marioHeight-24, mario, screen, &clipsStill[1]);
		status=2;
	}
	else {
		frame=0;
	}

	if(frame>=4) {		// reset frame count
		frame=0;
	}
/*
	// display leftward or rightward movement if necessary
	if (event.key.keysym.sym!=SDLK_DOWN) {
		if(status==0) {
			apply_surface(x-camera.x, screenHeight-marioHeight-24, mario, screen, &clipsRight[frame]);
			cout << "Mario moved right" << endl;
		}
		else if (status==1) {
			apply_surface(x-camera.x, screenHeight-marioHeight-24, mario, screen, &clipsLeft[frame]);
			cout << "Mario moved left" << endl;
		}
	}
*/

}

// update camera position relative to mario
void Mario::set_camera() {

	// center the camera over mario
	camera.x=(getX()+getWidth()/2)-screenWidth/2;
	camera.y=(getY()+getHeight()/2)-screenHeight/2;

	// keep the camera in bounds.
	if (camera.x<0) {
        	camera.x=0;
	}
	if (camera.y<0) {
        	camera.y=0;
	}
	if (camera.x>levelWidth-camera.w) {
        	camera.x=getLevelW()-camera.w;
	}
	if (camera.y>levelHeight-camera.h) {
        	camera.y=getLevelH()-camera.h;
	}

	cout << "x camera: " << camera.x << endl;
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

// return the camera's view
SDL_Rect *Mario::getCamera() {
	return &camera;
}

// return the event
SDL_Event *Mario::getEvent() {
	return &event;
}

SDL_Rect *Mario::getRclip() {
	return &clipsRight[getFrame()];
}

SDL_Rect *Mario::getLclip() {
	return &clipsLeft[getFrame()];
}
