// plant.cpp

#include "plant.h"
#include <iostream>
using namespace std;

Plant::Plant(int startx, int starty)
{
	//Initialize movement variables
	box.x = startx;
	box.y = starty;
	xVel = 0;
	yVel = 0;
	enemy_height = 26.5;
	enemy_width = 25.1;
	box.w = enemy_width;
	box.h = enemy_height;
}

void Plant::move()
{
	Enemy::move();
}

void Plant::update()
{
	Enemy::update();

	if(frame>=1) { // reset frame count
		frame=0;
	}

}

void Plant::checkDeath(int marioy,int mariox,int firex,int firey,int firew,int fireh,bool isFire)
{
	Enemy::checkDeath(marioy,mariox,firex,firey,firew,fireh,isFire);
}

bool Plant::mDead(int mariox,int marioy){
	Enemy::mDead(mariox,marioy);
	int collision = 0;
	//check mario jump
	//set variables
	int leftA = mariox;
    	int rightA = mariox + 16 ;
    	int topA = marioy;
    	int bottomA = marioy + 32;
	int leftB = box.x;
    	int rightB = box.x + enemy_width;
    	int topB = box.y;
    	int bottomB = box.y + enemy_height;
	//check collisions
if (death == false){

	if (bottomA>=topB && topA<topB && leftA>=leftB && leftA<=rightB){
		collision = 1;
	} 

	if (collision == 1 && death == false){
		return true;
	} else {
		return false;
	}
}
}

bool Plant::isDead()
{
	Enemy::isDead();
}

void Plant::set_clips()
{
	clips[0].x = 0;
	clips[0].y = enemy_height * 2;
	clips[0].w = enemy_width;
	clips[0].h = enemy_height;

	clips[1].x = enemy_width;
	clips[1].y = enemy_height * 2;
	clips[1].w = enemy_width;
	clips[1].h = enemy_height;

	clips[2].x = enemy_width * 2;
	clips[2].y = enemy_height * 2;
	clips[2].w = enemy_width;
	clips[2].h = enemy_height;

	clips[3].x = enemy_width * 3;
	clips[3].y = enemy_height * 2;
	clips[3].w = enemy_width;
	clips[3].h = enemy_height;
}

SDL_Rect *Plant::getLclip() // return enemy's left motion clip
{
	return &clips[frame];
}


int Plant::getX() // returns enemies x coordinate
{
	Enemy::getX();
}

int Plant::getY() // returns enemies y coordinate
{
	Enemy::getY();
}

int Plant::getWidth()	// returns enemies width
{
	Enemy::getWidth();
}

int Plant::getHeight() // returns enemies height
{
	Enemy::getHeight();
}

int Plant::getStatus() //return status of plant
{
	Enemy::getStatus();
}

void Plant::setX(int x) { //return plants x
	box.x = x;
}

void Plant::setY(int y) { //return plants y
	box.y = y;
}

void Plant::resetDeath() { //resets death
	Enemy::resetDeath();
}

void Plant::kill() {
	Enemy::kill();
}
