// goomba.cpp

#include "goomba.h"
#include <iostream>
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
}

void Goomba::move()
{
	Enemy::move();
}

void Goomba::update()
{
	Enemy::update();
	
	if(frame>=8) { // reset frame count
		frame=0;
	}
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

int Goomba::getStatus() 
{
	Enemy::getStatus();
}
