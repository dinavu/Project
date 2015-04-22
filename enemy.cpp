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

    	//Keep enemy in bounds
    	if( ( box.x < 0 ) || ( box.x + enemy_width > screenWidth) )
    	{
    		box.x -= xVel;
    	}

	//move up or down
	box.y += yVel;

	//Keep enemy in bounds
	if( (box.y < 0) || ( box.y + enemy_height > screenHeight ) ) {
		box.y -= yVel;
	}
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

void Enemy::checkDeath(int marioy,int mariox,int firex,int firey,int firew,int fireh){
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
	if (bottomA>=topB && topA<topB && leftA>leftB && leftA<rightB){
		collision = 1;
	} else if (topA<=bottomB && topA>topB && leftA>leftB && leftA<rightB){
		collision = 1;
	} else if (rightA>=leftB && rightA<rightB && topA>=topB && topA<=bottomB){
		collision = 1;
	} else if (leftA<=rightB && rightA>rightB && topA>=topB && topA<=bottomB){	
		collision = 1;
	}
	//set death to true if enemy is hit by fireball
	if (collision == 1){
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
	if (rightA>=leftB && rightA<rightB && topA>=topB && topA<=bottomB){
		collision = 1;
	} else if (leftA<=rightB && rightA>rightB && topA>=topB && topA<=bottomB){	
		collision = 1;
	}

	if ((collision == 1)&&(death==false)){
		return true;
	} else {
		return false;
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

int Enemy::getStatus()
{
	return status;
}
