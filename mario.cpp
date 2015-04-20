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

	setPipes();		// initialize the pipe dimensions for the level

	createFloors();
	createBoxes();
	marioRect.x=getX();
	marioRect.y=getY();
	marioRect.w=getWidth();
	marioRect.h=getHeight();
	collision=0;
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

	checkPipeCollision();

	if (collision==0) {
		x += xVel;			// move mario left or right
	}
	
	//checkCollisionsHor();

	// if mario went too far to the left or right
	if((x < 0) || (getX() + getWidth() > getLevelW()) /*|| (pipecollision==1)*/) {
        	x -= 2 * xVel;		// move back
	}

	checkPipeCollision();
//	if (collision==0) {
//		y += getHeight() /8;	// move mario up or down
//	}

	checkCollisionsVer();

	if (collision==0 && floorcollision==0) {
		y += getHeight() /8;	// move mario up or down
	}

	// if mario went too far up or down
	if((y < 0 ) || (getY() + getHeight() > 224)) {
		y -= getHeight() /8;		// move back
	}

	collision = 0;
	floorcollision = 0;
	
	//Update Mario's Rectangle position
	marioRect.x=x;
	marioRect.y=y;
}

// make Mario do a full jump
void Mario::jump(int time) {

	if (isCrouched==true) {
		isJumped=false;
	}	
	else if ((time-initialT)<600  && (floorcollision==1)) {
		checkPipeCollision();
		if (collision==0) {
			y -= (yVel*dt)+(yAcc*dt*dt);
		}

		checkCollisionsVer();
		if (collision==0) {
			y -= (yVel*dt)+(yAcc*dt*dt);
		}

		checkPipeCollision();			
		if (collision==0) { 
			x += xVel;
		}

		//checkCollisionsHor();
		if (collision==0) {
			x += xVel;
		}
	}
	else if ((time-initialT)<1200) {
		checkPipeCollision();
		if (collision==0) {
			y += (yVel*dt)+(yAcc*dt*dt);
		}

		checkCollisionsVer();
		//if (collision==1) {
			y += (yVel*dt)+(yAcc*dt*dt);
		//}

		checkPipeCollision();			
		if (collision==0) { 
			x += xVel;
		}

		//checkCollisionsHor();
		if (collision==0) {
			x += xVel;
		}
	}
	else if ((time-initialT)>=1200 ) {
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


void Mario::setPipes()
{
	//First pipe
	pipes[0].x = 451;
	pipes[0].y = 170;//142;
	pipes[0].w = 20;
	pipes[0].h = 50;
}

void Mario::checkPipeCollision()
{

	//The sides of the rectangles
    	int leftA, leftB;
    	int rightA, rightB;
    	int topA, topB;
    	int bottomA, bottomB;

	//Set enemy or marios position as the above variables
	leftA = x;
	rightA = x + marioWidth;
	topA = y;
	bottomA = y + marioHeight;

	leftB = pipes[0].x;
	rightB = pipes[0].x + pipes[0].w;
	topB = pipes[0].y;
	bottomB = pipes[0].y + pipes[0].h;
	
    	//If any of the sides from A are outside of B
	if ((rightA>=leftB)&&(leftA<leftB)){
		pipecollision = 1;
	} else if ((leftA<=rightB)&&(leftA>leftB)){
		pipecollision = 1;
	} else if ((rightA<=rightB)&&(leftA>=leftB)){
		pipecollision = 1;
	} else {
		pipecollision = 0;
	}
 
}


//Create the collisions for the floors
void Mario::createFloors() {

	SDL_Rect floor1,floor2,floor3,floor4;

	floor1.x=0;
	floor1.y=200;
	floor1.w=1103;
	floor1.h=24;
	floor.push_back(floor1);
	
	floor2.x=1135;
	floor2.y=200;
	floor2.w=240;
	floor2.h=24;
	floor.push_back(floor2);

	floor3.x=1423;
	floor3.y=200;
	floor3.w=1024;
	floor3.h=24;
	floor.push_back(floor3);

	floor4.x=2479;
	floor4.y=200;
	floor4.w=912;
	floor4.h=24;
	floor.push_back(floor4);
}

//Create the collisions for boxes
void Mario::createBoxes() {
	SDL_Rect box1,box2,box3,box4,box5,box6,box7,box8,box9;
	SDL_Rect box10,box11,box12,box13,box14,box15,box16,box17;

	box1.x=256;
	box1.y=136;
	box1.w=16;
	box1.h=16;
	boxes.push_back(box1);
	
	box2.x=320;
	box2.y=136;
	box2.w=80;
	box2.h=16;
	boxes.push_back(box2);

	box3.x=352;
	box3.y=72;
	box3.w=16;
	box3.h=16;
	boxes.push_back(box3);

	box4.x=1232;
	box4.y=136;
	box4.w=48;
	box4.h=16;
	boxes.push_back(box4);

	box5.x=1280;
	box5.y=72;
	box5.w=128;
	box5.h=16;
	boxes.push_back(box5);

	box6.x=1456;
	box6.y=72;
	box6.w=64;
	box6.h=16;
	boxes.push_back(box6);

	box7.x=1504;
	box7.y=136;
	box7.w=16;
	box7.h=16;
	boxes.push_back(box7);

	box8.x=1600;
	box8.y=136;
	box8.w=32;
	box8.h=16;
	boxes.push_back(box8);

	box9.x=1696;
	box9.y=136;
	box9.w=16;
	box9.h=16;
	boxes.push_back(box9);

	box10.x=1744;
	box10.y=136;
	box10.w=16;
	box10.h=16;
	boxes.push_back(box10);

	box11.x=1792;
	box11.y=136;
	box11.w=16;
	box11.h=16;
	boxes.push_back(box11);

	box12.x=1744;
	box12.y=72;
	box12.w=16;
	box12.h=16;
	boxes.push_back(box12);

	box13.x=1888;
	box13.y=136;
	box13.w=16;
	box13.h=16;
	boxes.push_back(box13);
	
	box14.x=1936;
	box14.y=72;
	box14.w=48;
	box14.h=16;
	boxes.push_back(box14);

	box15.x=2048;
	box15.y=72;
	box15.w=64;
	box15.h=16;
	boxes.push_back(box15);

	box16.x=2064;
	box16.y=136;
	box16.w=32;
	box16.h=16;
	boxes.push_back(box16);

	box17.x=2688;
	box17.y=136;
	box17.w=64;
	box17.h=16;
	boxes.push_back(box17);
}

bool Mario::check_collision( SDL_Rect A, SDL_Rect B )
{

	//MARIO = A

    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = x;
    rightA = x + marioWidth;
    topA = y;
    bottomA = y + marioHeight;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
	//check horizontal
	cout << "bottomA:" << bottomA << " topB:" << topB << " topA:" << topA << " bottomB:" << bottomB << endl;
	cout << "leftA:" << leftA << " leftB:" << leftB << " rightB:" << rightB << endl;
	if (bottomA>=topB && topA<topB && leftA>=leftB && leftA<=rightB){
		cout << "1";
		return true;
	} else if (topA<=bottomB && topA>topB && leftA>=leftB && leftA<=rightB){
		cout << "2";
		return true;
	} else if (rightA>=leftB && rightA<rightB && topA>=topB && topA<=bottomB){
		cout << "4";	
		return true;
	} else if (leftA<=rightB && rightA>rightB && topA>=topB && topA<=bottomB){
		cout << "5";	
		return true;
	} else {
		cout << "3";
		return false;
	}
}


void Mario::checkCollisionsHor() {

	// if mario went too far to the left or right
	if((x < 0) || (getX() + getWidth() > getLevelW())) {
        	x -= xVel;	// move back
	}

	//Floor (RIGHT / LEFT)
	for (int i = 0 ; i < floor.size() ; i++ ) {
		if(check_collision(marioRect,floor[i]) ) {
			if ((marioRect.x <= (floor[i].x+floor[i].w)) && (marioRect.x >=floor[i].x) && ((marioRect.y+marioRect.h)!=floor[i].y)) 
				{ cout <<"Case 1" <<endl;
				 collision=1; }
			//if ( ((marioRect.x+marioRect.w) > floor[i].x)  && (marioRect.y+marioRect.h) != floor[i].y ) 
		//		{ cout << "Case 2" <<endl;
		//			collision=1; }
		}
	}

	//Boxes (RIGHT / LEFT)
	for ( int m=0 ; m<boxes.size() ; m++ ) {
		if ( check_collision(marioRect,boxes[m]) ) {
			if ((marioRect.x < (boxes[m].x+boxes[m].w)) && (marioRect.x >= boxes[m].x) && (marioRect.y == boxes[m].y+boxes[m].h )) 
				{ cout << "Case 3" <<endl;
				collision=1; }
			if ( ((marioRect.x+marioRect.w) > boxes[m].x)  && ((marioRect.x+marioRect.w) <= (boxes[m].x + boxes[m].w)) && (marioRect.y+marioRect.h)==boxes[m].y ) 
				{ cout << "Case 4" <<endl;
				 collision=1; }
		}
	}

}

void Mario::checkCollisionsVer() {

	//Floor (UP / DOWN)
	for ( int z = 0 ; z < floor.size() ; z++ ) {
		if ((y < 0) || ( ((y+marioHeight)>=floor[z].y ) /*&& check_collision(marioRect,floor[z])*/)) {
			y = getLevelH() - getHeight() - 24;
	   		//y -= yVel;	// move back
			floorcollision = 1;
		}
	}

	//Boxes (UP / DOWN)
	for (int j = 0 ; j < boxes.size() ; j++ ) {
		if ( check_collision(marioRect,boxes[j]) ) {
			cout << "hi";
			collision = 1;
		}
	}
}

