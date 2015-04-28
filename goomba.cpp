// goomba.cpp

#include "goomba.h"
#include <iostream>
#include <vector>
using namespace std;


Goomba::Goomba(int startx, int starty)
{
	//Initialize movement variables	
	box.x = startx;
	box.y = starty;
	xVel = -1;
	yVel = 0;
	enemy_height = 25.5;
	enemy_width = 25;
	//set box dimensions
	box.w = enemy_width;
	box.h = enemy_height;
	createFloors();
	createBoxes();
}

void Goomba::move()
{
	checkCollisionsVer();
	if (floorcollision==0 && boxcollision==0) {
		box.y += getHeight() /16;	// move goomba up or down
	} else {
		Enemy::move(); //move horizontally
	}
	//reset collisions
	boxcollision = 0;
	floorcollision = 0;
}

void Goomba::checkDeath(int marioy,int mariox,int firex,int firey,int firew,int fireh,bool isFire)
{
	//check fireball
	Enemy::checkDeath(marioy,mariox,firex,firey,firew,fireh,isFire);
	int collision = 0;
	//check mario jump
	//set variables
	int leftA = mariox;
    	int rightA = mariox + 16;
    	int topA = marioy;
    	int bottomA = marioy + 32 -5;
	int leftB = box.x;
    	int rightB = box.x + enemy_width;
    	int topB = box.y;
    	int bottomB = box.y + enemy_height;
	//check collisions
	if (bottomA>=topB && topA<topB && leftA>=leftB && rightA<=rightB){
		collision = 1;
		//cout << "death by mario" << endl;
	} 
	if (collision == 1){
		death = true;
	}
}

// checks for a vertical collision
void Goomba::checkCollisionsVer() {

	//Floor (UP / DOWN)
	for ( int z = 0 ; z < floor.size() ; z++ ) {
		if (((box.y+enemy_height)>=floor[z].y ) && check_collision(box,floor[z])) {
			box.y = 224 - enemy_height -24;
			floorcollision = 1;
		}
	}

	//Boxes (UP / DOWN)
	for (int j = 0 ; j < boxes.size() ; j++ ) {
		if ( ((box.y+enemy_height)>=boxes[j].y) && (box.y<boxes[j].y) && (box.x+box.w>=boxes[j].x) && (box.x<=(boxes[j].x+boxes[j].w))){
			box.y = boxes[j].y - enemy_height;
			boxcollision = 1;
		}
	}

	//Check for marios death
	if ((box.y+enemy_height) >= 224 ) {
		death = true;
	}
}

//Create the collisions for the floors
void Goomba::createFloors() {

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
void Goomba::createBoxes() {
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

// determines if there is a collision
bool Goomba::check_collision( SDL_Rect A, SDL_Rect B ) {
	//MARIO = A
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = box.x;
    rightA = box.x + enemy_width;
    topA = box.y;
    bottomA = box.y + enemy_height;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
	//check horizontal
	if (bottomA>=topB && topA<topB && leftA>leftB && leftA<rightB){
		return true;
	} else if (topA<=bottomB && topA>topB && leftA>leftB && leftA<rightB){
		return true;
	//check vertical
	} else if (rightA>=leftB && rightA<rightB && topA>=topB && topA<=bottomB){
		return true;
	} else if (leftA<=rightB && rightA>rightB && topA>=topB && topA<=bottomB){	
		return true;
	//if no collision return false
	} else {
		return false;
	}
}

bool Goomba::mDead(int mariox,int marioy){
	Enemy::mDead(mariox,marioy);
}

void Goomba::update()
{
	Enemy::update();
	
	if(frame>=8) { // reset frame count
		frame=0;
	}
}

bool Goomba::isDead()
{
	Enemy::isDead();
}

void Goomba::set_clips()
{
    	//Clip the sprites
    	clipsLeft[ 0 ].x = 0;
    	clipsLeft[ 0 ].y = enemy_height;
    	clipsLeft[ 0 ].w = enemy_width;
    	clipsLeft[ 0 ].h = enemy_height;

    	clipsLeft[ 1 ].x = enemy_width;
    	clipsLeft[ 1 ].y = enemy_height;
    	clipsLeft[ 1 ].w = enemy_width;
    	clipsLeft[ 1 ].h = enemy_height;

   	clipsLeft[ 2 ].x = enemy_width * 2;
   	clipsLeft[ 2 ].y = enemy_height;
   	clipsLeft[ 2 ].w = enemy_width;
    	clipsLeft[ 2 ].h = enemy_height;

   	clipsLeft[ 3 ].x = enemy_width * 3;
   	clipsLeft[ 3 ].y = enemy_height;
   	clipsLeft[ 3 ].w = enemy_width;
   	clipsLeft[ 3 ].h = enemy_height;

   	clipsLeft[ 4 ].x = enemy_width * 4;
   	clipsLeft[ 4 ].y = enemy_height;
    	clipsLeft[ 4 ].w = enemy_width;
    	clipsLeft[ 4 ].h = enemy_height;

   	clipsLeft[ 5 ].x = enemy_width * 5;
   	clipsLeft[ 5 ].y = enemy_height;
   	clipsLeft[ 5 ].w = enemy_width;
   	clipsLeft[ 5 ].h = enemy_height;

   	clipsLeft[ 6 ].x = enemy_width * 6;
    	clipsLeft[ 6 ].y = enemy_height;
   	clipsLeft[ 6 ].w = enemy_width;
    	clipsLeft[ 6 ].h = enemy_height;

    	clipsLeft[ 7 ].x = enemy_width * 7;
    	clipsLeft[ 7 ].y = enemy_height;
    	clipsLeft[ 7 ].w = enemy_width;
    	clipsLeft[ 7 ].h = enemy_height;

	clipsDeath[0].x = 0;
	clipsDeath[0].y = 0;
	clipsDeath[0].w = enemy_width;
	clipsDeath[0].h = enemy_height;

	clipsDeath[1].x = enemy_width;
	clipsDeath[1].y = 0;
	clipsDeath[1].w = enemy_width;
	clipsDeath[1].h = enemy_height;

	clipsDeath[2].x = enemy_width * 2;
	clipsDeath[2].y = 0;
	clipsDeath[2].w = enemy_width;
	clipsDeath[2].h = enemy_height;

	clipsDeath[2].x = enemy_width * 3;
	clipsDeath[2].y = 0;
	clipsDeath[2].w = enemy_width;
	clipsDeath[2].h = enemy_height;
}

SDL_Rect *Goomba::getLclip() // return enemy's left motion clip
{
	return &clipsLeft[frame];
}


int Goomba::getX() // returns enemies x coordinate
{
	Enemy::getX();
}

int Goomba::getY() // returns enemies y coordinate
{
	Enemy::getY();
}

int Goomba::getWidth()	// returns enemies width
{
	Enemy::getWidth();
}

int Goomba::getHeight() // returns enemies height
{
	Enemy::getHeight();
}

int Goomba::getStatus() //returns the status
{
	Enemy::getStatus();
}

void Goomba::setX(int x) { //sets goombas x
	box.x = x;
}

void Goomba::setY(int y) { //sets goomba y
	box.y = y;
}

void Goomba::resetDeath() { //resets goomba after dying
	Enemy::resetDeath();
}

void Goomba::kill() {
	Enemy::kill();
}
