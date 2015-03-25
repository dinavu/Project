// main.cpp

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "graphics.h"
#include "mario.h"
#include "timer.h"
#include <iostream>
#include <string>
using namespace std;

int main( int argc, char* args[] ) {
	bool quit=false;		// quit flag
	Graphics myGraphics;		// create graphics object
	Mario myMario;			// create mario object
	myMario.set_clips();		// sets the necessary images
	Timer fps;			// frame rate regulator
	SDL_Event event;

	// images
	SDL_Surface *background=NULL;
	SDL_Surface *mario=NULL;
	background=myGraphics.load_image("images/level1-1.png");
	mario=myGraphics.load_image("images/bigMarioMotion.png");

	while(quit==false) {				// user has not quit
     		fps.start();				// start the frame timer
        	while(SDL_PollEvent(&event)) {		// there are events to handle
			//cout << "Event: " << &event << endl;
        		myMario.handle_input(event);		// handle events for mario
        		if(event.type==SDL_QUIT) {	// user has Xed out the window
                		quit=true;		// quit the program
        		}
        	}

        	myMario.move();		// move mario
        	myMario.set_camera();	// set the camera centered on mario

		// reset the screen and display updated scene
		myGraphics.clearScreen(myGraphics.getScreen());
        	myGraphics.apply_surface( 0, 0, background, myGraphics.getScreen(), myMario.getCamera() );
       		//myMario.show();
		myMario.updatePos();

		if(myMario.getStatus()==0) {
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getRclip());
		}
		else if(myMario.getStatus()==1) {
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getLclip());
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

	return 0;
}
