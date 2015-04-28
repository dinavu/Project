// fireball.cpp
#include <iostream>
#include "fireball.h"
using namespace std;

// class constructor
Fireball::Fireball(int x, int y) {
	fireH=100;
	fireW=24;
	fireX=x;
	fireY=y;
	fireXvel=0;
	fireYvel=0;
	fireFrame=0;
	fireStatus=0;
	isFire = false;
	fireballcount = 0;
	collision = false;
}

// sets the clip images for the fireball
void Fireball::set_clips() {

	clipsfireR[ 0 ].x = 0;
	clipsfireR[ 0 ].y = fireH;
	clipsfireR[ 0 ].w = fireW;
	clipsfireR[ 0 ].h = fireH;

	clipsfireR[ 1 ].x = fireW;
	clipsfireR[ 1 ].y = fireH;
	clipsfireR[ 1 ].w = fireW;
	clipsfireR[ 1 ].h = fireH;

	clipsfireR[ 2 ].x = fireW * 2;
	clipsfireR[ 2 ].y = fireH;
	clipsfireR[ 2 ].w = fireW;
	clipsfireR[ 2 ].h = fireH;

	clipsfireR[ 3 ].x = fireW * 3;
	clipsfireR[ 3 ].y = fireH;
	clipsfireR[ 3 ].w = fireW;
	clipsfireR[ 3 ].h = fireH;

	clipsfireL[ 0 ].x = 0;
	clipsfireL[ 0 ].y = fireH;
	clipsfireL[ 0 ].w = fireW;
	clipsfireL[ 0 ].h = fireH;

	clipsfireL[ 1 ].x = fireW;
	clipsfireL[ 1 ].y = fireH;
	clipsfireL[ 1 ].w = fireW;
	clipsfireL[ 1 ].h = fireH;

	clipsfireL[ 2 ].x = fireW * 2;
	clipsfireL[ 2 ].y = fireH;
	clipsfireL[ 2 ].w = fireW;
	clipsfireL[ 2 ].h = fireH;

	clipsfireL[ 3 ].x = fireW * 3;
	clipsfireL[ 3 ].y = fireH;
	clipsfireL[ 3 ].w = fireW;
	clipsfireL[ 3 ].h = fireH;
}

// use key presses to adjust fireball's position
void Fireball::handleFire(SDL_Event event) {
	if( event.type == SDL_KEYDOWN ) {
		if (event.key.keysym.sym == SDLK_SPACE) { 
				fireXvel = fireW / 4;
				fireYvel = sqrt(fireW/4);
				isFire = true;
				//fireballcount++;
		}
	}

}

// move fireball
void Fireball::moveFire(int marioDirection) {
	if (isFire==true){
		if (marioDirection==1) {
			fireX -= fireXvel;
		}
		else {
			fireX += fireXvel;
		}
		fireY += fireYvel;		

		if((fireX < 0) || (fireX + fireW > screenWidth)) {		
			isFire = false;
		}

		if (fireY > (screenHeight-fireH/2)) {
			fireYvel = -sqrt(fireW/4);
		}
		else if (fireY < (screenHeight - fireH)) {
			fireYvel = sqrt(fireW/4);
		}
	}
}

int Fireball::checkDeath(int enemyX, int enemyY, int enemyW, int enemyH, bool enemydead){
	//set collision equal to zero initially
	int collision = 0;

	int leftA = enemyX;
    	int rightA = enemyX + enemyH;
    	int topA = enemyY;
    	int bottomA = enemyY + enemyH;
	int leftB = fireX;
    	int rightB = fireX + fireW -10;
    	int topB = fireY;
    	int bottomB = fireY + fireH -70;
	//check collisions
	if(isFire==true){
		if (bottomA>=topB && topA<topB && leftA>leftB && leftA<rightB){
			collision = 1;
		} else if (topA<=bottomB && topA>topB && leftA>leftB && leftA<rightB){
			collision = 1;
		} else if (rightA>=leftB && rightA<rightB && topA>=topB && topA<=bottomB){
			collision = 1;
		} else if (leftA<=rightB && rightA>rightB && topA>=topB && topA<=bottomB){	
			collision = 1;
		}
	}
	//set death to true if enemy is hit by fireball
	if (collision == 1){
		isFire = false;
		return 1;
	}
}

// display the updated fireball on the screen
void Fireball::updateFire() {
	if( fireXvel < 0 ) {
		fireStatus = 1;
		fireFrame++;
	}
	else if (fireXvel > 0) {
		fireStatus = 0;
		fireFrame++;
	}

	fireFrame = fireFrame % 3;
}

// sets the value of fireball's x coordinate
void Fireball::setFireX(int x) {
	fireX=x;
}

// sets the value of fireball's y coordinate
void Fireball::setFireY(int y) {
	fireY=y;
}

// returns the value of fireball's x coordinate
int Fireball::getFireX() {
	return fireX;
}

// returns the value of fireball's y coordinate
int Fireball::getFireY() {
	return fireY;
}

// returns the frame of the fireball's motion
int Fireball::getFireFrame() {
	return fireFrame;
}

// returns the status (direction) of the fireball
int Fireball::getFireStatus() {
	return fireStatus;
}

// returns the fireball's right motion clip
SDL_Rect* Fireball::getFireR() {
	return &clipsfireR[getFireFrame()];
}

// returns the fireball's left motion clip
SDL_Rect* Fireball::getFireL() {
	return &clipsfireL[getFireFrame()];
}

// return the truth value of isFire
bool Fireball::getIsFire() {
	return isFire;
}

// returns the width of fireball sprite
int Fireball::getFireW() {
	return fireW;
}

// returns the height of fireball sprite
int Fireball::getFireH() {
	return fireH;
}

// returns the number of fireballs fired
int Fireball::getCount() {
	return fireballcount;
}

// increments the fireball count
void Fireball::countup() {
	fireballcount++;
}

// resets isFire to false
void Fireball::resetIsFire() {
	isFire = false;
}
