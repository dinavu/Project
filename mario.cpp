// mario.cpp

#include "mario.h"
#include <iostream>
using namespace std;

// mario class constructor
Mario::Mario() {

	// initialize mario variables
	x=0;
	y=168;
	frame=0;
	status=0;
	xVel=0;
	yVel=0;
	yAcc=.1;
	dt=1.2;
	initialT=0;
	marioWidth=16;
	marioHeight=32;
	isCrouched=false;
	isJumped=false;

	//camera dimensions
	camera.x=0;
	camera.y=0;
	camera.w=640;
	camera.h=224;
}

// adjust mario's velocity based on key pressed
void Mario::handle_input(SDL_Event event, int time) {

	// if a key was pressed
	if( event.type == SDL_KEYDOWN ) {
        	// adjust the velocity
        	switch( event.key.keysym.sym ) {
        		case SDLK_LEFT:		// move left
				if (isJumped==false) {
					xVel -= getWidth() / 5;
				}
				break;
        		case SDLK_RIGHT:	// move right
				if (isJumped==false) {
					xVel += getWidth() / 5;
				}
				break;
			case SDLK_DOWN:		// crouch
				isCrouched = true;
				xVel = 0;
				if (isJumped==true) {
					isJumped=false;
					status=0;
				}
				break;
			case SDLK_x:		// jump
				if (isJumped==false) {
					initialT = time;
					jumpDir = getStatus();
					isJumped = true;
				}
				if (getStatus()==0) {
					xVel += getWidth() /5;
				}
				else if (getStatus()==1) {
					xVel -= getWidth() /5;
				}
				yVel += getHeight() /8;
				break;
        	}
	}

	// if a key was released
	else if( event.type == SDL_KEYUP ) {
        	// adjust the velocity
        	switch( event.key.keysym.sym ) {
            		case SDLK_LEFT:		// move left
				if (isJumped==false) {
					xVel += getWidth() / 5;
				}
				break;
           		case SDLK_RIGHT:	// move right
				if (isJumped==false) {
					xVel -= getWidth() / 5;
				}
				break;
	   		case SDLK_DOWN:		// crouch
				isCrouched = false;
				status = 0;	
				break;
        	}
	}

}

// set the clips for mario's motion
void Mario::set_clips() {
	clipsRight[0].x=0;
	clipsRight[0].y=0;
	clipsRight[0].w=16;
	clipsRight[0].h=32;

	clipsRight[1].x=16;
	clipsRight[1].y=0;
	clipsRight[1].w=16;
	clipsRight[1].h=32;

	clipsRight[2].x=16*2;
	clipsRight[2].y=0;
	clipsRight[2].w=16;
	clipsRight[2].h=32;

	clipsRight[3].x=16*3;
	clipsRight[3].y=0;
	clipsRight[3].w=16;
	clipsRight[3].h=32;

	clipsLeft[0].x=16*3;
	clipsLeft[0].y=32;
	clipsLeft[0].w=16;
	clipsLeft[0].h=32;

	clipsLeft[1].x=16*2;
	clipsLeft[1].y=32;
	clipsLeft[1].w=16;
	clipsLeft[1].h=32;

	clipsLeft[2].x=16;
	clipsLeft[2].y=32;
	clipsLeft[2].w=16;
	clipsLeft[2].h=32;

	clipsLeft[3].x=0;
	clipsLeft[3].y=32;
	clipsLeft[3].w=16;
	clipsLeft[3].h=32;

	clipsStill[1].x=0;
	clipsStill[1].y=32*2;
	clipsStill[1].w=16;
	clipsStill[1].h=32;

	clipsJump[0].x=16;
	clipsJump[0].y=32*2;
	clipsJump[0].w=16;
	clipsJump[0].h=32;

	clipsJump[1].x=16*2;
	clipsJump[1].y=32*2;
	clipsJump[1].w=16;
	clipsJump[1].h=32;
}

// update mario's velocity to move
void Mario::move() {
	x += xVel;			// move mario left or right

	// if mario went too far to the left or right
	if((x < 0) || (getX() + getWidth() > getLevelW())) {
        	x -= xVel;		// move back
	}

	y += getHeight() /8;	// move mario up or down

	// if mario went too far up or down
	if((y < 0 ) || (getY() + getHeight() > 224)) {
		y -= getHeight() /8;;		// move back
	}


	
}

// make Mario do a full jump
void Mario::jump(int time) {

	if (isCrouched==true) {
		isJumped=false;
	}	
	else if ((time-initialT)<600) {
		y -= (yVel*dt)+(yAcc*dt*dt);
		x += xVel;
	}
	else if ((time-initialT)<1200) {
		y += (yVel*dt)+(yAcc*dt*dt);
		x += xVel;
	}
	else if ((time-initialT)>=1200) {
		isJumped=false;
		initialT=0;
		xVel = 0;
		yVel = 0;
		status = 0;
	}
	cout << "time-initialT: " << time-initialT << endl;

}

// display mario's update position
void Mario::updateStatus() {
	if (isCrouched==true) {		// display crouching mario
		status=2;
	}
	else if (isJumped==true) {	// display jumping mario
		status=3;
		if (jumpDir==0) {
			frame=0;
		}
		else if (jumpDir==1) {
			frame=1;
		}

	}
	else if (xVel<0) {		// choose proper leftward movement frame
		status=1;
		frame++;
	}
	else if (xVel>0) {		// choose proper rightward movement frame
		status=0;
		frame++;
	}
	else {
		frame=0;
	}

	if(frame>=4) {		// reset frame count
		frame=0;
	}
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
}

// returns isJumped()
bool Mario::getisJumped(){
	return isJumped;
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

// get right motion clip
SDL_Rect *Mario::getRclip() {
	return &clipsRight[getFrame()];
}

// get left motion clip
SDL_Rect *Mario::getLclip() {
	return &clipsLeft[getFrame()];
}

// get crouch clip
SDL_Rect *Mario::getCclip() {
	return &clipsStill[1];
}

// get jumping clip
SDL_Rect *Mario::getJclip() {
	return &clipsJump[getFrame()];
}

// get camera's x coordinate
int Mario::getCamerax() {
	return camera.x;
}

// get camera's y coordinate
int Mario::getCameray() {
	return camera.y;
}
