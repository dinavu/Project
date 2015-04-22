// koopa.cpp

#include "koopa.h"
#include <iostream>
using namespace std;

Koopa::Koopa(int startx, int starty, int startmin, int startmax)
{
	//Initialize movement variables
	box.x = startx;
	box.y = starty;
	xVel = 1;
	yVel = 0;
	enemy_height = 37.5;
	enemy_width = 39;
	//kstatus = 1; //start left
	xmin = startmin;
	xmax = startmax;

	box.w = enemy_width;
	box.h = enemy_height;
}

void Koopa::move()
{
	if (box.x<=xmin)
	{
		status = 0; //go right
		frame = 0;
		xVel = 1;
	}
	if (box.x>xmax)
	{	
		status = 1; //go left
		frame = 0;
		xVel = -1;
	}
	Enemy::move();
}

void Koopa::update()
{
	Enemy::update();

	if(frame>=4) { // reset frame count
		frame=0;
	}
}

bool Koopa::isDead()
{
	Enemy::isDead();
}

void Koopa::checkDeath(int marioy,int mariox,int firex,int firey,int firew,int fireh,bool isFire)
{
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

	if (bottomA>=topB && topA<topB && leftA>=leftB && leftA<=rightB){
		collision = 1;
	} 
	if (collision == 1){
		death = true;
	}
}

bool Koopa::mDead(int mariox,int marioy){
	Enemy::mDead(mariox,marioy);
}

void Koopa::set_clips()
{
    	//Clip the sprites
    	clipsRight[ 0 ].x = enemy_width * 5;
    	clipsRight[ 0 ].y = enemy_height * 2;
    	clipsRight[ 0 ].w = enemy_width;
    	clipsRight[ 0 ].h = enemy_height;

    	clipsRight[ 1 ].x = enemy_width * 6;
    	clipsRight[ 1 ].y = enemy_height * 2;
    	clipsRight[ 1 ].w = enemy_width;
    	clipsRight[ 1 ].h = enemy_height;

   	clipsRight[ 2 ].x = enemy_width * 7;
   	clipsRight[ 2 ].y = enemy_height * 2;
   	clipsRight[ 2 ].w = enemy_width;
    	clipsRight[ 2 ].h = enemy_height;

   	clipsRight[ 3 ].x = enemy_width * 8;
   	clipsRight[ 3 ].y = enemy_height * 2;
   	clipsRight[ 3 ].w = enemy_width;
   	clipsRight[ 3 ].h = enemy_height;

   	clipsLeft[ 0 ].x = enemy_width * 4;
    	clipsLeft[ 0 ].y = enemy_height * 2;
   	clipsLeft[ 0 ].w = enemy_width;
    	clipsLeft[ 0 ].h = enemy_height;

    	clipsLeft[ 1 ].x = enemy_width * 3;
    	clipsLeft[ 1 ].y = enemy_height * 2;
   	clipsLeft[ 1 ].w = enemy_width;
    	clipsLeft[ 1 ].h = enemy_height;
	
	clipsLeft[ 2 ].x = enemy_width * 2;
    	clipsLeft[ 2 ].y = enemy_height * 2;
   	clipsLeft[ 2 ].w = enemy_width;
    	clipsLeft[ 2 ].h = enemy_height;

	clipsLeft[ 3 ].x = enemy_width;
    	clipsLeft[ 3 ].y = enemy_height * 2;
   	clipsLeft[ 3 ].w = enemy_width;
    	clipsLeft[ 3 ].h = enemy_height;

}

SDL_Rect *Koopa::getLclip() // return enemy's left motion clip
{
	return &clipsLeft[frame];
}

SDL_Rect *Koopa::getRclip() // return enemy's right motion clip
{
	return &clipsRight[frame];
}

int Koopa::getX() // returns enemies x coordinate
{
	Enemy::getX();
}

int Koopa::getY() // returns enemies y coordinate
{
	Enemy::getY();
}

int Koopa::getWidth()	// returns enemies width
{
	Enemy::getWidth();
}

int Koopa::getHeight() // returns enemies height
{
	Enemy::getHeight();
}

int Koopa::getStatus() 
{
	Enemy::getStatus();
}

void Koopa::setXmax(int max) {
	xmax = max;
}

void Koopa::setXmin(int min) {
	xmin = min;
}

void Koopa::setX(int x) {
	box.x = x;
}

void Koopa::setY(int y) {
	box.y = y;
}

void Koopa::resetDeath() {
	Enemy::resetDeath();
}
