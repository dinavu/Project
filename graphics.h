/* graphics.h */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
using namespace std;
class Graphics {

public:
	Graphics();				// class constructor
	SDL_Surface *load_image(string);	// loads an image
	void apply_surface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect* clip); // apply optimized image to destination
	SDL_Rect clearScreen(SDL_Surface*);	// reset the screen to black
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
	void handleHome(SDL_Event event);	// determine to start the game or not
	bool initHome();			// intialize all SDL subsystems for the homescreen
	int showHome();				// updates the homescreen
	int runHomescreen(SDL_Event event);	// runs the homescreen
	SDL_Rect clearScreenB(SDL_Surface*);

protected:
	int screenWidth;			// width of the screen
	int screenHeight;			// height of the screen
	int screenBPP;				// bits per pixel
	int levelWidth;				// width of the level
	int levelHeight;			// height of the level
	int iconX, iconY;			// goomba icon start screen's x and y coordinates
	int play;				// determine whether to start the game
	SDL_Surface* screen;			// display window
	SDL_Surface* background;		// background of the display window
	SDL_Surface* goombaIcon;		// icon of goomba for start screen selection
	SDL_Surface* startScreen;		// background of start screen
	SDL_Surface* mario;			// mario background
	SDL_Surface* fireball;			// mario's fireball
	SDL_Surface* goomba;			// Goomba- enemy
	SDL_Surface* koopa;			// Koopa- enemy
	SDL_Surface* plant;			// Plant- enemy
	SDL_Rect clipsRight[4];			// images for mario moving right
	SDL_Rect clipsLeft[4];			// images for mario moving left
	SDL_Rect clipsStill[1];			// image for mario crouching
	SDL_Rect clipsJump[1];			// image for mario jumping
	SDL_Rect clipsfireR[4];			// images for fireball moving right
	SDL_Rect clipsfireL[4];			// images for fireball moving left
	SDL_Event event;
	TTF_Font *font;				// game text font
	SDL_Surface *prelevel;			// states level and life count
	SDL_Color textColor;
};

#endif
