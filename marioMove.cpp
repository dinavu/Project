/* marioMove.cpp
	Author: Nick Ward
	last updated: 3/13/15
This program is just to test my knowledge of SDL
after having done the first 22 tutorials from Lazy
Foo, incorporating much of the tutorials' code as
as basis. My goal was also to experiment and see
where any potential difficulties might arise.
*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 224;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 20;

// mario dimensions
const int MARIO_WIDTH=16;
const int MARIO_HEIGHT=32;

// direction of mario
const int MARIO_RIGHT=0;
const int MARIO_LEFT=1;

//The dimensions of the level
const int LEVEL_WIDTH = 3350;
const int LEVEL_HEIGHT = 224;
const int BLOCK_HEIGHT=24;

//The surfaces
SDL_Surface *mario = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The camera
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

// image clips
SDL_Rect clipsRight[4];		// images for mario moving right
SDL_Rect clipsLeft[4];		// images for mario moving left
SDL_Rect clipsStill[1];		// image for mario crouching

// mario class
class Mario {
	private:
	int x, y;		// the X and Y offsets of the dot
	int xVel, yVel;		// velocity of the mario
	int frame;		// frame of image
	int status;		// direction to face

	public:
	Mario();		// class constructor
	void handle_input();	// take key presses and adjusts marios's velocity
	void move();		// move mario
	void show();		// display the updated mario on the screen
	void set_camera();	// set the camera over mario's position
};

// timer class for regulating frame rate
class Timer {
	private:
	int startTicks;		//The clock time when the timer started
 	int pausedTicks;	//The ticks stored when the timer was paused
	bool paused, started;	//The timer status

	public:
	Timer();		// class constructor
	void start();		// start timer
	void stop();		// stop timer
	void pause();		// pause timer
	void unpause();		// unpause timer
	int get_ticks();	// get the timer's time
	bool is_started();	// true/false the timer is started
	bool is_paused();	// true/false the timer is paused
};

// global function to load an image, regardless of file format
SDL_Surface *load_image( std::string filename ) {
	SDL_Surface* loadedImage = NULL;	// image that's loaded
	SDL_Surface* optimizedImage = NULL;	// optimized image to be used

	loadedImage=IMG_Load(filename.c_str());	//Load the image

	// if the image loaded
	if( loadedImage != NULL ) {
        	optimizedImage = SDL_DisplayFormat( loadedImage );	// create an optimized surface
        	SDL_FreeSurface( loadedImage );				// free old image

		//If the surface was optimized
        	if( optimizedImage != NULL ) {
            	//Color key surface
            	SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xFF, 0xFF, 0xFF ) );
		}
	}

	return optimizedImage;
}

// apply the optimized image
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ) {
	SDL_Rect offset;	// holds offsets

	// get offsets
	offset.x = x;
	offset.y = y;

	// blit
	SDL_BlitSurface( source, clip, destination, &offset );
}

// initialize the SDL subsystems
bool init() {
	// initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
        	return false;
	}

	// set up the screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	// if there was an error in setting up the screen
	if( screen == NULL ) {
	        return false;
	}

	// Set the window caption
	SDL_WM_SetCaption( "Super Mario -- World 1-1", NULL );

	return true;	// everything initialized fine
}

// load the files for the program
bool load_files() {
	mario = load_image( "big mario motion.png" );	// loads all the mario images
	background = load_image( "1-1.png" );		// loads the level background

	// if there was a problem in loading the dot
	if( mario == NULL ) {
        	return false;
	}

	// if there was a problem in loading the background
	if( background == NULL ) {
        	return false;
	}

	return true; 	// everything loaded fine
}

// sets all the image clips for mario's motion
void set_clips() {
	clipsRight[0].x=0;
	clipsRight[0].y=0;
	clipsRight[0].w=MARIO_WIDTH;
	clipsRight[0].h=MARIO_HEIGHT;

	clipsRight[1].x=MARIO_WIDTH;
	clipsRight[1].y=0;
	clipsRight[1].w=MARIO_WIDTH;
	clipsRight[1].h=MARIO_HEIGHT;

	clipsRight[2].x=MARIO_WIDTH*2;
	clipsRight[2].y=0;
	clipsRight[2].w=MARIO_WIDTH;
	clipsRight[2].h=MARIO_HEIGHT;

	clipsRight[3].x=MARIO_WIDTH*3;
	clipsRight[3].y=0;
	clipsRight[3].w=MARIO_WIDTH;
	clipsRight[3].h=MARIO_HEIGHT;

	clipsLeft[0].x=MARIO_WIDTH*3;
	clipsLeft[0].y=MARIO_HEIGHT;
	clipsLeft[0].w=MARIO_WIDTH;
	clipsLeft[0].h=MARIO_HEIGHT;

	clipsLeft[1].x=MARIO_WIDTH*2;
	clipsLeft[1].y=MARIO_HEIGHT;
	clipsLeft[1].w=MARIO_WIDTH;
	clipsLeft[1].h=MARIO_HEIGHT;

	clipsLeft[2].x=MARIO_WIDTH;
	clipsLeft[2].y=MARIO_HEIGHT;
	clipsLeft[2].w=MARIO_WIDTH;
	clipsLeft[2].h=MARIO_HEIGHT;

	clipsLeft[3].x=0;
	clipsLeft[3].y=MARIO_HEIGHT;
	clipsLeft[3].w=MARIO_WIDTH;
	clipsLeft[3].h=MARIO_HEIGHT;

	clipsStill[1].x=0;
	clipsStill[1].y=MARIO_HEIGHT*2;
	clipsStill[1].w=MARIO_WIDTH;
	clipsStill[1].h=MARIO_HEIGHT;
}

// frees the surfaces
void clean_up() {
	SDL_FreeSurface(mario);
	SDL_FreeSurface( background );

	SDL_Quit();	// quit SDL
}

// mario class constructor
Mario::Mario() {
	// initialize variables
	x=0;
	y=168;
	frame=0;
	status=MARIO_RIGHT;
	xVel=0;
	yVel=0;
}

// adjust mario's velocity based on key pressed
void Mario::handle_input() {
	// if a key was pressed
	if( event.type == SDL_KEYDOWN ) {
        	// adjust the velocity
        	switch( event.key.keysym.sym ) {
        		case SDLK_LEFT: xVel -= MARIO_WIDTH / 4; break;	// move left
        		case SDLK_RIGHT: xVel += MARIO_WIDTH / 4; break;// move right
			case SDLK_DOWN: xVel = 0; break;		// crouch
        	}
	}
	// if a key was released
	else if( event.type == SDL_KEYUP ) {
        	// adjust the velocity
        	switch( event.key.keysym.sym ) {
            		case SDLK_LEFT: xVel += MARIO_WIDTH / 4; break;	// move left
           		case SDLK_RIGHT: xVel -= MARIO_WIDTH / 4; break;// move right
	   		case SDLK_DOWN: xVel = 0; break;		// crouch
        	}
	}
}

// update mario's velocity to move
void Mario::move() {
	x += xVel;	// move the dot left or right

	// if mario went too far to the left or right
	if( ( x < 0 ) || ( x + MARIO_WIDTH > LEVEL_WIDTH ) ) {
        	x -= xVel;	// move back
	}

	y += yVel;	// move the dot up or down

	// if mario went too far up or down
	if( ( y < 0 ) || ( y + MARIO_HEIGHT > LEVEL_HEIGHT ) ) {
		y -= yVel;	// move back
	}
}

// display mario's update position
void Mario::show() {
	if (xVel<0) {			// choose proper leftward movement frame
		status=MARIO_LEFT;
		frame++;
	}
	else if (xVel>0) {		// choose proper rightward movement frame
		status=MARIO_RIGHT;
		frame++;
	}
	else if (event.key.keysym.sym==SDLK_DOWN) {	// display crouching mario
		apply_surface(x-camera.x, SCREEN_HEIGHT-MARIO_HEIGHT-BLOCK_HEIGHT, mario, screen, &clipsStill[1]);
		status=MARIO_RIGHT;
	}
	else {
		frame=0;
	}

	if(frame>=4) {		// reset frame count
		frame=0;
	}

	// display leftward or rightward movement if necessary
	if (event.key.keysym.sym!=SDLK_DOWN) {
		if(status==MARIO_RIGHT) {
			apply_surface(x-camera.x, SCREEN_HEIGHT-MARIO_HEIGHT-BLOCK_HEIGHT, mario, screen, &clipsRight[frame]);
		}
		else if (status==MARIO_LEFT) {
			apply_surface(x-camera.x, SCREEN_HEIGHT-MARIO_HEIGHT-BLOCK_HEIGHT, mario, screen, &clipsLeft[frame]);
		}
	}
}

// update camera position relative to mario
void Mario::set_camera() {
	// center the camera over the dot
	camera.x = ( x + MARIO_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( y + MARIO_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

	// keep the camera in bounds.
	if( camera.x < 0 ) {
        	camera.x = 0;
	}
	if( camera.y < 0 ) {
        	camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w ) {
        	camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h ) {
        	camera.y = LEVEL_HEIGHT - camera.h;
	}
}

// Timer class constructor
Timer::Timer() {
	// initialize the variables
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

// starts the timer
void Timer::start() {
	started=true;			// start the timer
	paused=false;			// unpause the timer
	startTicks = SDL_GetTicks();	// get the current clock time
}

// stops the timer
void Timer::stop() {
	started = false;	// stop the timer
	paused = false;		// unpause the timer
}

// pause the timer
void Timer::pause() {
	// if the timer is running and isn't already paused
	if( ( started == true ) && ( paused == false )) {
		paused = true;					// pause the timer
		pausedTicks = SDL_GetTicks() - startTicks;	// calculate the paused ticks
	}
}

// unpause the timer
void Timer::unpause() {
	// if the timer is paused
	if( paused == true ) {
        	paused = false;					// unpause the timer
        	startTicks = SDL_GetTicks() - pausedTicks;	// reset the starting ticks
        	pausedTicks = 0;				// reset the paused ticks
        }
}

// get the timer's time
int Timer::get_ticks() {
	//If the timer is running
	if( started == true ) {
        	//If the timer is paused
        	if( paused == true ) {
        		return pausedTicks;		// return the number of ticks when the timer was paused
        	}
	}
        else {
        	return SDL_GetTicks() - startTicks;	// return the current time minus the start time
        }

	return 0;	// timer isn't running
}

// true/false timer is started
bool Timer::is_started() {
	return started;
}

// true/false timer is paused
bool Timer::is_paused() {
	return paused;
}

int main( int argc, char* args[] ) {
	bool quit = false;	// quit flag
	Mario myMario;		// create mario object
	set_clips();		// sets the necessary images
	Timer fps;		// frame rate regulator
    
	// initialize SDL subsystems
	if( init() == false ) {
        	return 1;
	}

	// load the files
	if( load_files() == false ) {
        	return 1;
	}

	while( quit == false ) {			// user has not quit
     		fps.start();				// start the frame timer
        	while(SDL_PollEvent(&event)) {		// there are events to handle
        		myMario.handle_input();		// handle events for mario
        		if( event.type == SDL_QUIT ) {	// user has Xed out the window
                		quit = true;		// quit the program
        		}
        	}

        	myMario.move();		// move mario
        	myMario.set_camera();	// set the camera centered on mario

		// reset the screen and display updated scene
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
        	apply_surface( 0, 0, background, screen, &camera );
       		myMario.show();

		// update the screen
        	if( SDL_Flip( screen ) == -1 ) {
        		return 1;
        	}

		// cap the frame rate
		if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) {
        		SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
    		}
	}

	clean_up();	// free surfaces

	return 0;
}
