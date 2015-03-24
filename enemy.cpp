/* This program is going to be added to nick's marioMove.cpp
The enemy Goomba is going to be walking left throught the course.
Victoria Johnston */

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

// Goomba dimensions
const int GOOMBA_WIDTH=25;
const int GOOMBA_HEIGHT=25.5;

// direction of Goomba
const int GOOMBA_LEFT=1;

//The dimensions of the level
const int LEVEL_WIDTH = 3350;
const int LEVEL_HEIGHT = 224;
const int BLOCK_HEIGHT=24;

//The surfaces
SDL_Surface *goomba = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The camera
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

// image clips
SDL_Rect clipsLeft[8];

class Goomba
{
	public:
	Goomba(); //Initializes the variables
	void move(); //Moves Goomba left
	void show(); //Shows goomba
	void set_camera();

	private:
	int x,y;
	int velocity; //Its rate of movement
	int frame; //Its current frame
	int status; //Its animation status
};

// timer class for regulating frame rate
class Timer {
	public:
	Timer(); // class constructor
	void start(); // start timer
	void stop(); // stop timer
	void pause(); // pause timer
	void unpause(); // unpause timer
	int get_ticks(); // get the timer's time
	bool is_started(); // true/false the timer is started
	bool is_paused(); // true/false the timer is paused

	private:
	int startTicks; //The clock time when the timer started
	int pausedTicks; //The ticks stored when the timer was paused
	bool paused, started; //The timer status
};

SDL_Surface *load_image( std::string filename );
void apply_surface( int, int, SDL_Surface*, SDL_Surface*, SDL_Rect*);
bool init();
bool load_files();
void clean_up();
void set_clips();

int main( int argc, char* args[] ) 
{
	//quit flag
	bool quit = false;
	//Create Goomba class
	Goomba myGoomba;
	// sets the necessary images
	set_clips(); 
	// frame rate regulator
	Timer fps; 

	// initialize SDL subsystems
	if( init() == false ) 
	{
		return 1;
	}
	// load the files
	if( load_files() == false ) 
	{
	return 1;
	}

	while( quit == false ) 
	{ 
		fps.start(); // start the frame timer
		while(SDL_PollEvent(&event)) {

			// user has Xed out the window
			if( event.type == SDL_QUIT ) 
			{
				quit = true;
			}
		}

		//Move Goomba
		myGoomba.move();
		// Set camera to Goomba
		myGoomba.set_camera();
		// reset the screen and display updated scene
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
		apply_surface( 0, 0, background, screen, &camera );
		myGoomba.show();

		// update the screen
		if( SDL_Flip( screen ) == -1 ) 
		{
			return 1;
		}

		// cap the frame rate
		if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) 
		{
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}
	
	clean_up();
	return 0;
}

Goomba::Goomba()
{
	//Initialize movement variables
	x = 500;
	y = 168;
	velocity = -1;

	//Initialize animation variables
	frame = 0;
	status = GOOMBA_LEFT;
}

void Goomba::move()
{
    	//Move
   	 x += velocity;

    	//Keep goomba in bounds
    	if( ( x < 0 ) || ( x + GOOMBA_WIDTH > SCREEN_WIDTH ) )
    	{
    	    x -= velocity;
    	}
}

void Goomba::show()
{
   	status = GOOMBA_LEFT;

    	//Move to the next frame in the animation
    	frame++;

    	//Loop the animation
   	 if( frame >= 8 )
    	{
       	 frame = 0;
    	}

    	//Show Goomba
    	apply_surface( x, SCREEN_HEIGHT - GOOMBA_HEIGHT -BLOCK_HEIGHT, goomba, screen, &clipsLeft[ frame ] );
}

void Goomba::set_camera()
{
	// center the camera over the dot
	camera.x = ( x + GOOMBA_WIDTH / 2 ) - GOOMBA_WIDTH / 2;
	camera.y = ( y + GOOMBA_HEIGHT / 2 ) - GOOMBA_HEIGHT / 2;
	// keep the camera in bounds.
	if( camera.x < 0 ) 
	{
		camera.x = 0;
	}
	if( camera.y < 0 ) 
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w ) 
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h ) 
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}


void set_clips()
{
    	//Clip the sprites
    	clipsLeft[ 0 ].x = 0;
    	clipsLeft[ 0 ].y = GOOMBA_HEIGHT;
    	clipsLeft[ 0 ].w = GOOMBA_WIDTH;
    	clipsLeft[ 0 ].h = GOOMBA_HEIGHT;

    	clipsLeft[ 1 ].x = GOOMBA_WIDTH;
    	clipsLeft[ 1 ].y = GOOMBA_HEIGHT;
    	clipsLeft[ 1 ].w = GOOMBA_WIDTH;
    	clipsLeft[ 1 ].h = GOOMBA_HEIGHT;

   	clipsLeft[ 2 ].x = GOOMBA_WIDTH * 2;
   	clipsLeft[ 2 ].y = GOOMBA_HEIGHT;
   	clipsLeft[ 2 ].w = GOOMBA_WIDTH;
    	clipsLeft[ 2 ].h = GOOMBA_HEIGHT;

   	clipsLeft[ 3 ].x = GOOMBA_WIDTH * 3;
   	clipsLeft[ 3 ].y = GOOMBA_HEIGHT;
   	clipsLeft[ 3 ].w = GOOMBA_WIDTH;
   	clipsLeft[ 3 ].h = GOOMBA_HEIGHT;

   	clipsLeft[ 4 ].x = GOOMBA_WIDTH * 4;
   	clipsLeft[ 4 ].y = GOOMBA_HEIGHT;
    	clipsLeft[ 4 ].w = GOOMBA_WIDTH;
    	clipsLeft[ 4 ].h = GOOMBA_HEIGHT;

   	clipsLeft[ 5 ].x = GOOMBA_WIDTH * 5;
   	clipsLeft[ 5 ].y = GOOMBA_HEIGHT;
   	clipsLeft[ 5 ].w = GOOMBA_WIDTH;
   	clipsLeft[ 5 ].h = GOOMBA_HEIGHT;

   	clipsLeft[ 6 ].x = GOOMBA_WIDTH * 6;
    	clipsLeft[ 6 ].y = GOOMBA_HEIGHT;
   	clipsLeft[ 6 ].w = GOOMBA_WIDTH;
    	clipsLeft[ 6 ].h = GOOMBA_HEIGHT;

    	clipsLeft[ 7 ].x = GOOMBA_WIDTH * 7;
    	clipsLeft[ 7 ].y = GOOMBA_HEIGHT;
    	clipsLeft[ 7 ].w = GOOMBA_WIDTH;
    	clipsLeft[ 7 ].h = GOOMBA_HEIGHT;
}

Timer::Timer()
{
	//Initialize the varibales
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::start()
{
	//Start the timer
	started = true;
	//Unpause the timer
	paused = false;
	//Get the current clock time
	startTicks = SDL_GetTicks();
}

void Timer::stop()
{
	//Stop the timer
	started = false;
	
	//Unpause the timer
	paused = false;
}

int Timer::get_ticks()
{
	//If the timer is running
	if( started == true )
	{
		//If the timer is paused
		if( paused == true )
		{
			//Return the number of ticks when the timer was paused
			return pausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			return SDL_GetTicks() - startTicks;
		}
	}
	//If the timer isn't running
	return 0;
}

void Timer::pause()
{
	//If the timer is running and isn't already paused
	if( (started == true ) && (paused == false) )
	{
		//pause the timer
		paused = true;

		//Get the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause()
{
	//If the timer is paused
	if(paused == true )
	{
		//unpause the timer
		paused = false;

		//Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset the paused ticks
		pausedTicks = 0;
	}
}

bool Timer::is_started()
{
	return started;
}

bool Timer::is_paused()
{
	return paused;
}

SDL_Surface *load_image( std::string filename )
{
    	//The image that's loaded
    	SDL_Surface* loadedImage = NULL;

    	//The optimized surface that will be used
    	SDL_Surface* optimizedImage = NULL;

    	//Load the image
    	loadedImage = IMG_Load( filename.c_str() );

    	//If the image loaded
    	if( loadedImage != NULL )
    	{
        	//Create an optimized surface
        	optimizedImage = SDL_DisplayFormat( loadedImage );

        	//Free the old surface
        	SDL_FreeSurface( loadedImage );

        	//If the surface was optimized
        	if( optimizedImage != NULL )
        	{
            		//Color key surface
            		SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        	}
    	}

    	//Return the optimized surface
    	return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    	//Holds offsets
    	SDL_Rect offset;

    	//Get offsets
    	offset.x = x;
    	offset.y = y;

    	//Blit
    	SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    	//Initialize all SDL subsystems
    	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    	{
        	return false;
    	}

    	//Set up the screen
    	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//If there was an error in setting up the screen
	if( screen == NULL )
	{
		return false;
    	}

	//Set the window caption
	SDL_WM_SetCaption( "Goomba level 1-1", NULL );

    	//If everything initialized fine
    	return true;
}

bool load_files()
{
	//Load the background and goomba image
	goomba = load_image( "goomba.png" );
	background = load_image( "level1-1.png" );

	//If there was an error in loading the background or Goomba
	if( background == NULL )
	{
		return false;
	}

	if( goomba == NULL )
	{
		return false;
	}

    	//If everything loaded fine
    	return true;
}

void clean_up()
{
	//Free the surface
	SDL_FreeSurface( goomba );
	SDL_FreeSurface( background );

    	//Quit SDL
    	SDL_Quit();
}


