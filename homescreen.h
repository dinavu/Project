/* homescreen.h
This class contains the necessary images for the
opening screen of the super mario bros game.
*/

#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "graphics.h"
//using namespace std;

class Homescreen : public Graphics {

public:
	Homescreen();			// class constructor
	void handle_input(SDL_Event);	// determine if player is ready to start
	bool initHome();		// initialize SDL subsystems for homescreen
	int show();			//
	bool load_files();		// load the images
	void clean_up();		// free surfaces and quit SDL window
	int runHomescreen(SDL_Event);	// displays the homescreen

private:
	int iconX, iconY;		// x and y coordinates of the goomba homescreen icon
	int play;
	SDL_Surface * goombaIcon;
	SDL_Surface * background;
};

#endif
