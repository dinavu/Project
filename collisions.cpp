// collisions.cpp

#include "collisions.h"
#include <iostream>
//#include <vector>
using namespace std;

Collisions::Collisions() {

	/*xPos.push_back(0);		//x0
	xPos.push_back(1103);
	xPos.push_back(1135);
	xPos.push_back(1375);
        xPos.push_back(1423);		//x4
        xPos.push_back(2447);
        xPos.push_back(2479);
	xPos.push_back(3391);
        xPos.push_back(256);
        xPos.push_back(272);		//x9
        xPos.push_back(320);
        xPos.push_back(400);
	xPos.push_back(352);
        xPos.push_back(368);
        xPos.push_back(1232);		//x14
        xPos.push_back(1280);
        xPos.push_back(1280);
	xPos.push_back(1408);
        xPos.push_back(1456);
        xPos.push_back(1520);		//x19
        xPos.push_back(1504);
        xPos.push_back(1520);
        xPos.push_back(1600);
        xPos.push_back(1632);
        xPos.push_back(1696);		//24
        xPos.push_back(1712);
        xPos.push_back(1744);
        xPos.push_back(1760);
        xPos.push_back(1792);
        xPos.push_back(1808);		//x29
        xPos.push_back(1744);
        xPos.push_back(1760);
	xPos.push_back(1888);
	xPos.push_back(1904);
        xPos.push_back(1936);		//x34
        xPos.push_back(1984);
        xPos.push_back(2048);
        xPos.push_back(2112);
        xPos.push_back(2064);
        xPos.push_back(2096);		//x39
        xPos.push_back(2688);
	xPos.push_back(2752);

        yPos.push_back(72);		
        yPos.push_back(88);
        yPos.push_back(152);
        yPos.push_back(136);
        yPos.push_back(224);
        yPos.push_back(200);*/

}//end Constructor

void Collisions::setPipes()
{
	//First pipe
	pipes[0].x = 100;
	pipes[0].y = 200;
	pipes[0].w = 20;
	pipes[0].h = 50;
}

int Collisions::checkCollision(int x, int y, int width, int height)
{

	//The sides of the rectangles
    	int leftA, leftB;
    	int rightA, rightB;
    	int topA, topB;
    	int bottomA, bottomB;

	//Set enemy or marios position as the above variables
	leftA = x;
	rightA = x + width;
	topA = y;
	bottomA = y + height;

	leftB = pipes[0].x;
	rightB = pipes[0].x + pipes[0].w;
	topB = pipes[0].y;
	bottomB = pipes[0].y + pipes[0].h;
	
    	//If any of the sides from A are outside of B
   	if( bottomA <= topB )
   	{
  	    	return 0;
  	}

 	if( rightA <= leftB )
  	{
  	     	return 0;
  	}

   	if( leftA >= rightB )
   	{
    	   	return 0;
	
   	}

   	//If none of the sides from A are outside B
   	return (1);
}

/*void Collisions::setFloor()
{

	floor1.x=xPos[0];
	floor1.y=yPos[5];
	floor1.w=1103;
	floor1.h=24;
	
	floor2.x=xPos[2];
	floor2.y=yPos[5];
	floor2.w=240;
	floor2.h=24;

	floor3.x=xPos[4];
	floor3.y=yPos[5];
	floor3.w=1024;
	floor3.h=24;

	floor4.x=xPos[6];
	floor4.y=yPos[5];
	floor4.w=912;
	floor4.h=24;

} //end SETFLOOR

void Collisions::setBoxes()
{
	box1.x=xPos[8];
	box1.y=yPos[5];
	box1.w=16;
	box1.h=16;
	
	box2.x=xPos[10];
	box2.y=yPos[5];
	box2.w=80;
	box2.h=16;

	box3.x=xPos[12];
	box3.y=yPos[3];
	box3.w=16;
	box3.h=16;

	box4.x=xPos[14];
	box4.y=yPos[3];
	box4.w=48;
	box4.h=16;

	box5.x=xPos[16];
	box5.y=yPos[3];
	box5.w=128;
	box5.h=16;
	
	box6.x=xPos[18];
	box6.y=yPos[3];
	box6.w=64;
	box6.h=16;

	box7.x=xPos[20];
	box7.y=yPos[3];
	box7.w=16;
	box7.h=16;

	box8.x=xPos[22];
	box8.y=yPos[3];
	box8.w=32;
	box8.h=16;

	box9.x=xPos[24];
	box9.y=yPos[3];
	box9.w=16;
	box9.h=16;

	box10.x=xPos[26];
	box10.y=yPos[3];
	box10.w=16;
	box10.h=16;

	box11.x=xPos[28];
	box11.y=yPos[3];
	box11.w=16;
	box11.h=16;

	box12.x=xPos[30];
	box12.y=yPos[3];
	box12.w=16;
	box12.h=16;

	box13.x=xPos[32];
	box13.y=yPos[3];
	box13.w=16;
	box13.h=16;
	
	box14.x=xPos[34];
	box14.y=yPos[3];
	box14.w=48;
	box14.h=16;

	box15.x=xPos[36];
	box15.y=yPos[3];
	box15.w=64;
	box15.h=16;

	box16.x=xPos[38];
	box16.y=yPos[3];
	box16.w=32;
	box16.h=16;

	box17.x=xPos[40];
	box17.y=yPos[3];
	box17.w=64;
	box17.h=16;

} //end SETBOXES 

void Collisions::setSpecialBoxes()
{

} //end SETSPECIAL BOXES */
