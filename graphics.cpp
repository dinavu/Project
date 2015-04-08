// graphics.cpp

#include "graphics.h"
#include <string>
using namespace std;

// class constructor
Graphics::Graphics() {
	// initialize variable
	screenWidth=640;
	screenHeight=224;
	screenBPP=32;
	levelWidth=3350;
	levelHeight=224;
	iconX=150;
	iconY=260;
	play=0;
	init();
	screen=SDL_SetVideoMode(screenWidth, screenHeight, screenBPP, SDL_SWSURFACE | SDL_RESIZABLE);
}

// global function to load an image, regardless of file format
SDL_Surface* Graphics::load_image(string filename) {
	SDL_Surface* loadedImage=NULL;		// image that's loaded
	SDL_Surface* optimizedImage=NULL;	// optimized image to be used

	loadedImage=IMG_Load(filename.c_str());	//Load the image

	// if the image loaded
	if(loadedImage != NULL) {
        	optimizedImage=SDL_DisplayFormat(loadedImage);	// create an optimized surface
        	SDL_FreeSurface(loadedImage);			// free old image

		//If the surface was optimized
        	if(optimizedImage!=NULL) {
            		//Color key surface for white background
            		SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0xFF, 0xFF, 0xFF));
		}
	}

	return optimizedImage;
}

// apply the optimized image
void Graphics::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
	SDL_Rect offset;	// holds offsets

	// get offsets
	offset.x=x;
	offset.y=y;

	// blit
	SDL_BlitSurface(source, clip, destination, &offset);
}

// reset the screen
SDL_Rect Graphics::clearScreen(SDL_Surface* screen) {
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
}

// initialize the SDL subsystems
bool Graphics::init() {
	// initialize all SDL subsystems
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
        	return false;
	}

	// set up the screen
	screen=SDL_SetVideoMode(screenWidth, screenHeight, screenBPP, SDL_SWSURFACE);

	// if there was an error in setting up the screen
	if(screen==NULL) {
	        return false;
	}

	// Set the window caption
	SDL_WM_SetCaption("Super Mario Bros", NULL);

	return true;	// everything initialized fine
}

// set the image clips for an object
void Graphics::set_clips() {}

// load the files for the program
bool Graphics::load_files() {
	background = load_image("images/level1-1.png");			// level background
	mario = load_image("images/bigMarioMotion1.png");		// mario clips
	startScreen = load_image("images/super-mario-bros-screen.jpg");	// start menu
	goombaIcon = load_image("images/goomba");			// goomba icon to select start menu choice
	fireball = load_image( "images/fireball_sprites.png" );		// fireball clips
	goomba = load_image("images/goomba.png");			// goomba enemy clips
	koopa = load_image("images/koopa2.png");			// koopa enemy clips
	plant = load_image("images/plant.png");				// plant enemy clips

	// if there was a problem in loading the dot
	if(mario==NULL) {
        	return false;
	}

	// if there was a problem in loading the background
	if(background==NULL) {
        	return false;
	}

	// if problem loading start screen
	if( startScreen == NULL ) {
        	return false;
	}

	// if problem loading goombaIcon
	if( goombaIcon == NULL ) {
		return false;
	}

	// if problem loading fireball
	if ( fireball == NULL) {
		return false;
	}

	// problem loading goomba enemy
	if(goomba == NULL) {
		return false;
	}

	// problem loading koopa enemy
	if(koopa == NULL) {
		return false;
	}
	
	// problem loading plant enemy
	if(plant == NULL) {
		return false;
	}

	return true; 	// everything loaded fine
}

// frees the surfaces
void Graphics::clean_up() {
	SDL_FreeSurface(mario);
	SDL_FreeSurface(background);
	SDL_FreeSurface(fireball);
	SDL_FreeSurface(goomba);
	SDL_FreeSurface(koopa);
	SDL_FreeSurface(plant);
	SDL_FreeSurface(startScreen);
	SDL_FreeSurface(goombaIcon);

	SDL_Quit();	// quit SDL
}

// return the width of the screen
int Graphics::getWidth() {
	return screenWidth;
}

// return the height of the screen
int Graphics::getHeight() {
	return screenHeight;
}

// return of the level width
int Graphics::getLevelW() {
	return levelWidth;
}

// return of the level height
int Graphics::getLevelH() {
	return levelHeight;
}

// return the screen
SDL_Surface *Graphics::getScreen() {
	return screen;
}

// determine whether or not to start the game
void Graphics::handleHome(SDL_Event event) {

	if (event.type == SDL_KEYDOWN ) {
		switch (event.key.keysym.sym) {
			case SDLK_UP: iconY=260; break;		// move icon to be 1 player game
			case SDLK_DOWN: iconY=295; break;	// move icon to be 2 player game
			case SDLK_RETURN: play=1; break;	// start the game
		}
	}
}

// initialize all SDL subsystems for the homescreen
bool Graphics::initHome() {
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

// updates the homescreen icon's position
int Graphics::showHome() {

	if (play==0) {
		apply_surface(0, 0, startScreen, screen, NULL);
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
int Graphics::runHomescreen(SDL_Event event) {

	bool quit = false;
	int enterPlay=0;
	SDL_Surface *startScreen = NULL;
	SDL_Surface *goombaIcon = NULL;

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
			handleHome(event);
			// if user has Xed out the window
			if( event.type == SDL_QUIT ) {
				quit = true;
			}
		}
		
		// apply the background
		enterPlay=showHome();

		// update the screen
		if( SDL_Flip( screen ) == -1 ) {
			return 1;
		}
		
		if (enterPlay == 1) {
			quit = true;
		}
	}
	
	SDL_FreeSurface(startScreen);
	SDL_FreeSurface(goombaIcon);
}
