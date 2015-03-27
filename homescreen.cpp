/* Jose Suarez
   March 21, 2015
   Home screen for SUPER MARIO BROS Project
Updated: 3/27/15 NW - adjusted to fit into class heirarchy
*/

//The headers
#include "homescreen.h"
#include <iostream>
//using namespace std;

// class constructor
Homescreen::Homescreen() {
	iconX=150;
	iconY=260;
	play=0;
	load_files();
	initHome();
	
}

// cycle goomba between options until the game starts
void Homescreen::handle_HomeInput(SDL_Event event) {

	if (event.type == SDL_KEYDOWN ) {
		switch (event.key.keysym.sym) {
			case SDLK_UP: iconY=260; break;
			case SDLK_DOWN: iconY=295; break;
			case SDLK_RETURN: play=1; break;
		}
	}
}

// initialize SDL subsystems for start screen
bool Homescreen::initHome() {
	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
       		return false;
	}

	//Set up the screen
	screen = SDL_SetVideoMode( 692, 484, 32, SDL_SWSURFACE | SDL_RESIZABLE );

	//If there was an error in setting up the screen
	if( screen == NULL ) {
        	return false;
	}

	// Set the window caption
	SDL_WM_SetCaption( "Super Mario Bros", NULL );

	return true;
}

bool Homescreen::load_files()
{
	//Load the background image
	background = load_image( "images/super-mario-bros-screen.jpg" );
	goombaIcon = load_image( "images/goomba" );

	//If there was a problem in loading the background
	if( background == NULL ) {
        	return false;
	}

	if( goombaIcon == NULL ) {
		return false;
	}

	return true;
}

// free the images and quit the SDL window
void Homescreen::clean_up() {
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( goombaIcon );

    //Quit SDL
    SDL_Quit();
}

// updates the icon's position
int Homescreen::showHome() {

	if (play==0) {
		apply_surface(0, 0, background, screen, NULL);
		apply_surface(iconX, iconY, goombaIcon, screen, NULL);
		return 0;
	}
	else if (play==1) {
		return 1;
	}
	else {
		return 0;
	}
}

// runs the homescreen sequence
int Homescreen::runHomescreen(SDL_Event event) {

	bool quit = false;
	int enterPlay=0;
	SDL_Surface *startScreen = NULL;
	SDL_Surface *goombaIcon = NULL;
	SDL_Surface *screen = NULL;

	// initialize homescreen
	if( initHome() == false ) {
        	return 1;
	}

	// load the files
	if( load_files() == false ) {
        	return 1;
	}

	// the user hasn't quit
	while( quit == false || enterPlay == 0) {
		// there's events to handle
		while( SDL_PollEvent( &event ) ) {
			handle_input(event);
			// if user has Xed out the window
			if( event.type == SDL_QUIT ) {
				quit = true;
			}
		}
		
		// apply the background
		enterPlay=show();

		// update the screen
		if( SDL_Flip( screen ) == -1 ) {
			return 1;
		}
		
		if (enterPlay == 1) {
			quit = true;
		}
	}
	clean_up();
}
