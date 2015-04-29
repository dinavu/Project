// enemy.cpp

#include "enemy.h"
#include <iostream>
using namespace std;

Enemy::Enemy()
{
	//Initialize animation variables
	frame = 0;
	status = 1; //staryt left
	death = false; //enemy starts off alive
}

void Enemy::move()
{
    	//Move left or right
   	 box.x += xVel;
}

void Enemy::update()
{
	if (xVel<0) { // choose proper leftward movement frame
		status = 1; //move left
		frame++;
	}
	else if (xVel>0) { // choose proper rightward movement frame
		status = 0; //move right
		frame++;
	}
	else {
		frame++;
	}
}

void Enemy::checkDeath(int marioy,int mariox,int firex,int firey,int firew,int fireh, bool isFire){
	//set collision equal to zero initially
	int collision = 0;
	//set variables
	int leftA = box.x;
    	int rightA = box.x + enemy_width;
    	int topA = box.y;
    	int bottomA = box.y + enemy_height;
	int leftB = firex;
    	int rightB = firex + firew -10;
    	int topB = firey;
    	int bottomB = firey + fireh -70;
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
	if (collision == 1 || firedeath == true){
		death = true;
	}
}

bool Enemy::mDead(int mariox,int marioy){
	//set collision equal to 0	
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
	if( death == false){
		if (rightA>=leftB && rightA<rightB && bottomA==bottomB && bottomA>=topB){
			collision = 1;
		} else if (leftA<=rightB && rightA>rightB && bottomA==bottomB && bottomA>=topB){
			collision = 1;
		}

		if ((collision == 1)&&(death==false)){
			return true;
		} else {
			return false;
		}
	}
}

bool Enemy::isDead(){
	return death;
}

void Enemy::set_clips(){}

SDL_Rect *Enemy::getLclip() {}// return enemy's left motion clip

SDL_Rect *Enemy::getRclip() {}// return enemy's right motion clip


int Enemy::getX() // returns enemies x coordinate
{
	return box.x;
}

int Enemy::getY() // returns enemies y coordinate
{
	return box.y;
}

int Enemy::getWidth()	// returns enemies width
{
	return enemy_width;
}

int Enemy::getHeight() // returns enemies height
{
	return enemy_height;
}

int Enemy::getStatus() //returns enemy status
{
	return status;
}

void Enemy::setX(int x) { //sets the x coordinate of enemy
	box.x = x;
}

void Enemy::setY(int y)	 { //sets y coordinate of enemy
	box.y = y;
}

void Enemy::resetDeath() { //reset enemy after death
	death = false;
}

void Enemy::kill() {
	firedeath = true;
}
