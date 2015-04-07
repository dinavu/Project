// enemy.cpp

#include "enemy.h"
#include <iostream>
using namespace std;

Enemy::Enemy()
{
	//Initialize animation variables
	frame = 0;
	status = 1; //staryt left
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
