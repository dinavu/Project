/* graphics.h */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
using namespace std;

class Graphics {

public:
	Graphics();				// class constructor
	SDL_Surface *load_image(string);	// loads an image
	void apply_surface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect* clip); // apply optimized image to destination
	SDL_Rect clearScreen(SDL_Surface*);		// reset the screen to black
	bool init();				// initializes all SDL subsystems
	bool load_files();			// loads all the necessary files for the game
	void set_clips();			// sets all the image clips
	void clean_up();			// free images from memory and quit the game
	int getWidth();				// returns the width	
	int getHeight();			// returns the height
	int getLevelH();			// returns the level height
	int getLevelW();			// returns the level width
	SDL_Surface *getScreen();		// returns the screen
	SDL_Rect *getCamera();			// returns the camera view

protected:
	int screenWidth;			// width of the screen
	int screenHeight;			// height of the screen
	int screenBPP;				// bits per pixel
	int levelWidth;				// width of the level
	int levelHeight;			// height of the level
	SDL_Surface* screen;			// display window
	SDL_Surface* background;		// background of the display window
	SDL_Surface* mario;			// mario background
	SDL_Rect clipsRight[4];			// images for mario moving right
	SDL_Rect clipsLeft[4];			// images for mario moving left
	SDL_Rect clipsStill[1];			// image for mario crouching
	SDL_Event event;
};

#endif
