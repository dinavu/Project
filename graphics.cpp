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
	init();
	//load_files();
	screen=SDL_SetVideoMode(screenWidth, screenHeight, screenBPP, SDL_SWSURFACE);
}

// global function to load an image, regardless of file format
SDL_Surface* Graphics::load_image(string filename) {
	SDL_Surface* loadedImage=NULL;		// image that's loaded
	SDL_Surface* optimizedImage=NULL;	// optimized image to be used

	loadedImage=IMG_Load(filename.c_str());	//Load the image

	// if the image loaded
	if(loadedImage != NULL) {
        	optimizedImage=SDL_DisplayFormat(loadedImage);	// create an optimized surface
        	SDL_FreeSurface(loadedImage);				// free old image

		//If the surface was optimized
        	if(optimizedImage!=NULL) {
            		//Color key surface
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
	SDL_WM_SetCaption("Super Mario", NULL);

	return true;	// everything initialized fine
}

// load the files for the program
bool Graphics::load_files() {
	background=load_image("level1-1.png");	// loads the level background
	mario=load_image("bigMarioMotion.png");	// loads all the mario images

	// if there was a problem in loading the dot
	if(mario==NULL) {
        	return false;
	}

	// if there was a problem in loading the background
	if(background==NULL) {
        	return false;
	}

	return true; 	// everything loaded fine
}

// sets all the image clips
void Graphics::set_clips() {
	clipsRight[0].x=0;
	clipsRight[0].y=0;
	clipsRight[0].w=16;
	clipsRight[0].h=32;

	clipsRight[1].x=16;
	clipsRight[1].y=0;
	clipsRight[1].w=16;
	clipsRight[1].h=32;

	clipsRight[2].x=16*2;
	clipsRight[2].y=0;
	clipsRight[2].w=16;
	clipsRight[2].h=32;

	clipsRight[3].x=16*3;
	clipsRight[3].y=0;
	clipsRight[3].w=16;
	clipsRight[3].h=32;

	clipsLeft[0].x=16*3;
	clipsLeft[0].y=32;
	clipsLeft[0].w=16;
	clipsLeft[0].h=32;

	clipsLeft[1].x=16*2;
	clipsLeft[1].y=32;
	clipsLeft[1].w=16;
	clipsLeft[1].h=32;

	clipsLeft[2].x=16;
	clipsLeft[2].y=32;
	clipsLeft[2].w=16;
	clipsLeft[2].h=32;

	clipsLeft[3].x=0;
	clipsLeft[3].y=32;
	clipsLeft[3].w=16;
	clipsLeft[3].h=32;

	clipsStill[1].x=0;
	clipsStill[1].y=32*2;
	clipsStill[1].w=16;
	clipsStill[1].h=32;
}

// frees the surfaces
void Graphics::clean_up() {
	SDL_FreeSurface(mario);
	SDL_FreeSurface(background);

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
