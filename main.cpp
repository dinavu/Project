// main.cpp

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "graphics.h"
#include "mario.h"
#include "timer.h"
#include "fireball.h"
#include <iostream>
#include <string>
using namespace std;

int main( int argc, char* args[] ) {

	// instantiate objects
	Graphics myGraphics;					// create graphics object
	Mario myMario;						// create mario object
	Fireball myFireball(myMario.getX(), myMario.getY());	// create fireball object
	Timer fps;						// frame rate regulator

	// declare variables
	bool quit=false;		// quit flag
	SDL_Event event;

	// images
	SDL_Surface *background = NULL;
	SDL_Surface *mario = NULL;
	SDL_Surface *fireball = NULL;
	background = myGraphics.load_image("images/level1-1.png");
	fireball = myGraphics.load_image("images/fireball_sprites.png");
	mario = myGraphics.load_image("images/bigMarioMotion1.png");
		
	// set image clips
	myMario.set_clips();		// sets the mario images
	myFireball.set_clips();		// sets the fireball images

	// run the homescreen
	myGraphics.runHomescreen(event);

	// run the game
	myGraphics.init();				// resize the game window
	while(quit==false) {				// user has not quit
     		fps.start();				// start the frame timer
        	while(SDL_PollEvent(&event)) {		// there are events to handle
        		myMario.handle_input(event);	// handle events for mario
			myFireball.handleFire(event);	// handle events for fireball
        		if(event.type==SDL_QUIT) {	// user has Xed out the window
                		quit=true;		// quit the program
        		}
			else if(event.type == SDL_KEYDOWN) {
				if( event.key.keysym.sym == SDLK_SPACE){
					myFireball.setFireX(myMario.getX());
					myFireball.setFireY(myMario.getY()-myMario.getHeight()/2);
				}
			}
        	}

        	myMario.move();		// move mario
        	myMario.set_camera();	// set the camera centered on mario

		myFireball.moveFire();
		
		// reset the screen and display updated scene
		myGraphics.clearScreen(myGraphics.getScreen());
        	myGraphics.apply_surface(0, 0, background, myGraphics.getScreen(), myMario.getCamera());
		myMario.updateStatus();
		myFireball.updateFire();

		// mario moving right
		if(myMario.getStatus()==0) {
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getRclip());
			if (myFireball.getIsFire() == true) {
				if ( myFireball.getFireStatus() == 0) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY() , fireball, myGraphics.getScreen(), myFireball.getFireR());
				}
				else if ( myFireball.getFireStatus() ==1) {
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
				else if ( myFireball.getFireStatus() ==1) {
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
				else if ( myFireball.getFireStatus() ==1) {
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
				else if ( myFireball.getFireStatus() ==1) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY(), fireball, myGraphics.getScreen(), myFireball.getFireL());
				}
			}
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
	SDL_FreeSurface(fireball);

	return 0;
}
