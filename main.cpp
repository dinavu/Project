// main.cpp

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "graphics.h"
#include "mario.h"
#include "timer.h"
#include "fireball.h"
#include "enemy.h"
#include "goomba.h"
#include "koopa.h"
#include "plant.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main( int argc, char* args[] ) {

	// instantiate objects
	Graphics myGraphics;					// create graphics object
	Mario myMario;						// create mario object
	Fireball myFireball(myMario.getX(), myMario.getY());	// create fireball object
	Timer fps;						// frame rate regulator

	// instantiate enemies
	vector < Enemy* > myenemies(4);		//Create a vector of enemies
	
	Goomba Goomba1(500, 168);	
	Goomba Goomba2(550, 168);
	Koopa Koopa1(350, 100, 300, 375);
	Plant Plant1(451, 142);
	
	// assign enemies
	myenemies[0] = &Goomba1;
	myenemies[1] = &Goomba2;
	myenemies[2] = &Koopa1;
	myenemies[3] = &Plant1;

	//Number of enemies
	int e_num = 4;

	// declare variablesi
	int marioDir;			// direction mario faces when initially using fireball
	bool quit=false;		// quit flag
	int time;
	bool isJumped;
	SDL_Event event;

	// images
	SDL_Surface *background = NULL;
	SDL_Surface *startScreen = NULL;
	SDL_Surface *goombaIcon = NULL;
	SDL_Surface *mario = NULL;
	SDL_Surface *fireball = NULL;
	SDL_Surface *goomba = NULL;
	SDL_Surface *koopa = NULL;
	SDL_Surface *plant = NULL;
	background = myGraphics.load_image("images/level1-1.png");
	startScreen = myGraphics.load_image("images/super-mario-bros-screen.jpg");
	goombaIcon = myGraphics.load_image("images/goomba");
	fireball = myGraphics.load_image("images/fireball_sprites.png");
	mario = myGraphics.load_image("images/bigMarioMotion1.png");
	goomba = myGraphics.load_image("images/goomba.png");
	koopa = myGraphics.load_image("images/koopa2.png");
	plant = myGraphics.load_image("images/plant.png");
		
	// set image clips
	myMario.set_clips();		// sets the mario images
	myFireball.set_clips();		// sets the fireball images
	
	//set enemy clips
	for (int i=0; i<e_num; i++ ) {		
		myenemies[i]->set_clips();
	}

	// run the homescreen
	myGraphics.runHomescreen(event);

	// run the game
	myGraphics.init();					// resize the game window
	while(quit==false) {					// user has not quit
     		fps.start();					// start the frame timer
		time = SDL_GetTicks();				// microseconds that have passed
       		while(SDL_PollEvent(&event)) {			// there are events to handle
        		myMario.handle_input(event,time);	// handle events for mario
			myFireball.handleFire(event);		// handle events for fireball
        		if(event.type==SDL_QUIT) {		// user has Xed out the window
                		quit=true;			// quit the program
        		}
			else if(event.type == SDL_KEYDOWN) {
				if(event.key.keysym.sym == SDLK_SPACE){
					if (myMario.getX()>312) {
						myFireball.setFireX(myMario.getX()-myMario.getCamerax());
					}
					else {
						myFireball.setFireX(myMario.getX());
					}
					myFireball.setFireY(myMario.getY()-myMario.getHeight()/2);
					marioDir=myMario.getStatus();
				}
			}
        	}

		// determine how to update mario's position
		isJumped = myMario.getisJumped(); 
		if (isJumped == true) {
			myMario.jump(time);
		}	
		else {
			//Check if mario has collided
			//int mariocollision = 0;
			//mariocollision = myCol.checkCollision(myMario.getX(), myMario.getY(), myMario.getWidth(),myMario.getHeight());
			//Put into mario class status of marios collision
			//myMario.m_collision(mariocollision);
	        	myMario.move();
		}

		// DEBUGGGGGGGGGG
		/*cout << "MARIO STATS" << endl;
		cout << "isJumped: " << isJumped << endl;
		cout << "x: " << myMario.getX() << endl;
		cout << "y: " << myMario.getY() << endl;
		cout << "status: " << myMario.getStatus() << endl;*/

	
        	myMario.set_camera();	// set the camera centered on mario
		
		//move enemies
		for (int i=0; i<e_num; i++ ) {		
			myenemies[i]->move();
		}
		
		myFireball.moveFire(marioDir);
		
		// reset the screen and display updated scene
		myGraphics.clearScreen(myGraphics.getScreen());
        	myGraphics.apply_surface(0, 0, background, myGraphics.getScreen(), myMario.getCamera());
		myMario.updateStatus();
		myFireball.updateFire();
		//update the enemies
		for (int i=0; i<e_num; i++ ) {		
			myenemies[i]->update();
		}

		// mario moving right
		if(myMario.getStatus()==0) {
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getRclip());
			if (myFireball.getIsFire() == true) {
				if ( myFireball.getFireStatus() == 0) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY() , fireball, myGraphics.getScreen(), myFireball.getFireR());
				}
				else if ( myFireball.getFireStatus() == 1) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY(), fireball, myGraphics.getScreen(), myFireball.getFireL());
				}
			}
		}

		// mario moving left
		else if(myMario.getStatus()==1) {
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getLclip());
			if (myFireball.getIsFire() == true) {
				if ( myFireball.getFireStatus() == 0) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY() , fireball, myGraphics.getScreen(), myFireball.getFireR());
				}
				else if ( myFireball.getFireStatus() == 1) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY(), fireball, myGraphics.getScreen(), myFireball.getFireL());
				}
			}
		}

		// mario crouching
		else if(myMario.getStatus()==2) {
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getCclip());
			if (myFireball.getIsFire() == true) {
				if ( myFireball.getFireStatus() == 0) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY() , fireball, myGraphics.getScreen(), myFireball.getFireR());
				}
				else if ( myFireball.getFireStatus() == 1) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY(), fireball, myGraphics.getScreen(), myFireball.getFireL());
				}
			}
		}

		// mario jumping
		else if(myMario.getStatus()==3) {
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getJclip());
			if (myFireball.getIsFire() == true) {
				if ( myFireball.getFireStatus() == 0) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY() , fireball, myGraphics.getScreen(), myFireball.getFireR());
				}
				else if ( myFireball.getFireStatus() == 1) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY(), fireball, myGraphics.getScreen(), myFireball.getFireL());
				}
			}
		}

		//Move goomba left
		myGraphics.apply_surface(myenemies[0]->getX()-myMario.getCamerax(),myGraphics.getHeight()-myenemies[0]->getHeight()-24, goomba, myGraphics.getScreen(), myenemies[0]->getLclip());
		myGraphics.apply_surface(myenemies[1]->getX()-myMario.getCamerax(),myGraphics.getHeight()-myenemies[1]->getHeight()-24, goomba, myGraphics.getScreen(), myenemies[1]->getLclip());

		//Move plant
		myGraphics.apply_surface(myenemies[3]->getX()-myMario.getCamerax(),myenemies[3]->getY(), plant, myGraphics.getScreen(), myenemies[3]->getLclip());

		//Move Koopa left or right
		if(myenemies[2]->getStatus()==0) { //move right
			myGraphics.apply_surface(myenemies[2]->getX()-myMario.getCamerax(),myenemies[2]->getY(), koopa, myGraphics.getScreen(), myenemies[2]->getRclip());
		}
		if (myenemies[2]->getStatus()==1) { //move left
			myGraphics.apply_surface(myenemies[2]->getX()-myMario.getCamerax(),myenemies[2]->getY(), koopa, myGraphics.getScreen(), myenemies[2]->getLclip());
		}

		// update the screen
        	if(SDL_Flip(myGraphics.getScreen())==-1) {
        		return 1;
        	}

		// cap the frame rate
		if(fps.get_ticks()<1000/20) {
        		SDL_Delay((1000/20)-fps.get_ticks());
    		}
	}

	SDL_FreeSurface(mario);
	SDL_FreeSurface(background);
	SDL_FreeSurface(startScreen);
	SDL_FreeSurface(goombaIcon);
	SDL_FreeSurface(fireball);
	SDL_FreeSurface(goomba);
	SDL_FreeSurface(koopa);
	SDL_FreeSurface(plant);

	return 0;
}
