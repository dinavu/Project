/* This program is going to be added to nick's marioMove.cpp
The enemy Goomba is going to be walking left throught the course.
Victoria Johnston */

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 224;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 20;

// direction of Goomba
const int ENEMY_LEFT=1;
const int ENEMY_RIGHT=1;

//The dimensions of the level
const int LEVEL_WIDTH = 3350;
const int LEVEL_HEIGHT = 224;
const int BLOCK_HEIGHT=24;

//The surfaces
SDL_Surface *goomba = NULL;
SDL_Surface *koopa = NULL;
SDL_Surface *plant = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The camera
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

class Enemy
{
	public:
	Enemy(); //Initializes the variables
	void virtual move(); //Moves Goomba left
	void virtual show(); //Shows goomba
	void set_camera();

	protected:
	int x,y;
	int xVel,yVel; //Its rate of movement
	int frame; //Its current frame
	int status; //Its animation status
	int enemy_height, enemy_width;
};

class Goomba: public Enemy
{
	public:
	Goomba(int, int);
	void virtual move();
	void virtual show();
	void set_clips();
	private:
	SDL_Rect clipsLeft[8];
	int GOOMBA_HEIGHT, GOOMBA_WIDTH;
};

class Koopa: public Enemy
{
	public:
	Koopa(int, int);
	void virtual move();
	void virtual show();
	void set_clips();
	private:
	SDL_Rect clipsLeft[4];
	SDL_Rect clipsRight[4];
	int KOOPA_HEIGHT, KOOPA_WIDTH;
};	

class Plant: public Enemy
{
	public:
	Plant(int, int);
	void virtual move();
	void virtual show();
	void set_clips();
	private:
	SDL_Rect clips[4];
	int PLANT_HEIGHT, PLANT_WIDTH;
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

int main( int argc, char* args[] ) 
{
	//quit flag
	bool quit = false;

	//Number of enemies
	int e_num = 4;

	//Declare vector of enemies
	vector < Enemy* > myenemies(4);

	//Create Goomba class
	Goomba Goomba1(500, 168);
	Goomba Goomba2(550, 168);
	Koopa Koopa1(350, 100);
	Plant Plant1(455, 142);

	//assign vector of enemies
	myenemies[0] = &Goomba1;
	myenemies[1] = &Goomba2;
	myenemies[2] = &Koopa1;
	myenemies[3] = &Plant1;

	// sets the necessary images
	Goomba1.set_clips(); 
	Goomba2.set_clips(); 
	Koopa1.set_clips();
	Plant1.set_clips();

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
		for (int i=0; i<e_num; i++ )
		{		
			myenemies[i]->move();
		}
		// Set camera to Goomba
		Goomba1.set_camera();
		// reset the screen and display updated scene
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
		apply_surface( 0, 0, background, screen, &camera );
		for (int i=0; i<e_num; i++ )
		{		
			myenemies[i]->show();
		}

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

Goomba::Goomba(int startx, int starty)
{
	//Initialize movement variables
	x = startx;
	y = starty;
	xVel = -1;
	yVel = 0;
	GOOMBA_HEIGHT = 25.5;
	GOOMBA_WIDTH = 25;
	enemy_height = GOOMBA_HEIGHT;
	enemy_width = GOOMBA_WIDTH;
}

void Goomba::move()
{
	Enemy::move();
}

void Goomba::show()
{
	Enemy::show();
	
	if(frame>=8) { // reset frame count
		frame=0;
	}
	apply_surface(x, SCREEN_HEIGHT-enemy_height-BLOCK_HEIGHT, goomba, screen, &clipsLeft[frame]);
}

Koopa::Koopa(int startx, int starty)
{
	//Initialize movement variables
	x = startx;
	y = starty;
	xVel = 1;
	yVel = 0;
	KOOPA_WIDTH=39;
	KOOPA_HEIGHT=37.5;
	enemy_height = KOOPA_HEIGHT;
	enemy_width = KOOPA_WIDTH;
}

void Koopa::move()
{
	if (x<=300)
	{
		status = ENEMY_RIGHT;
		frame = 0;
		xVel = 1;
	}
	if (x>375)
	{	
		status = ENEMY_LEFT;
		frame = 0;
		xVel = -1;
	}
	Enemy::move();
}

void Koopa::show()
{
	Enemy::show();
	
	if(frame>=4) { // reset frame count
		frame=0;
	}
	// display leftward or rightward movement if necessary
	if(status==ENEMY_RIGHT) {
		apply_surface(x,y+50, koopa, screen, &clipsRight[frame]);
	}
	if (status==ENEMY_LEFT) {
		apply_surface(x,y, koopa, screen, &clipsLeft[frame]);
	}
}

Plant::Plant(int startx, int starty)
{
	//Initialize movement variables
	x = startx;
	y = starty;
	xVel = 0;
	yVel = 0;
	PLANT_WIDTH= 25.1;
	PLANT_HEIGHT= 26.5;
	enemy_height = PLANT_HEIGHT;
	enemy_width = PLANT_WIDTH;
}

void Plant::move()
{
	Enemy::move();
}

void Plant::show()
{
	Enemy::show();

	//if(frame>=2) { // reset frame count
		frame=0;
	//}

	apply_surface(x,y, plant, screen, &clips[frame]);
}

Enemy::Enemy()
{
	//Initialize animation variables
	frame = 0;
	status = ENEMY_LEFT;
}

void Enemy::move()
{
    	//Move left or right
   	 x += xVel;

    	//Keep enemy in bounds
    	if( ( x < 0 ) || ( x + enemy_width > SCREEN_WIDTH ) )
    	{
    	    x -= xVel;
    	}

	//move up or down
	y += yVel;

	//Keep enemy in bounds
	if( (y < 0) || ( y + enemy_height > LEVEL_HEIGHT ) ) {
		y -= yVel;
	}
}

void Enemy::show()
{
	if (xVel<0) { // choose proper leftward movement frame
		status = ENEMY_LEFT;
		frame++;
	}
	else if (xVel>0) { // choose proper rightward movement frame
		status=ENEMY_RIGHT;
		frame++;
	}
	else {
		frame++;
	}
}

void Enemy::set_camera()
{
/*	// center the camera over the dot
	camera.x = ( x + enemy_width / 2 ) - enemy_width / 2;
	camera.y = ( y + enemy_height / 2 ) - enemy_height / 2;
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
	}*/
}

void Plant::set_clips()
{
	clips[0].x = 0;
	clips[0].y = PLANT_HEIGHT * 2;
	clips[0].w = PLANT_WIDTH;
	clips[0].h = PLANT_HEIGHT;

	clips[1].x = PLANT_WIDTH;
	clips[1].y = PLANT_HEIGHT * 2;
	clips[1].w = PLANT_WIDTH;
	clips[1].h = PLANT_HEIGHT;

	clips[2].x = PLANT_WIDTH * 2;
	clips[2].y = PLANT_HEIGHT * 2;
	clips[2].w = PLANT_WIDTH;
	clips[2].h = PLANT_HEIGHT;

	clips[3].x = PLANT_WIDTH * 3;
	clips[3].y = PLANT_HEIGHT * 2;
	clips[3].w = PLANT_WIDTH;
	clips[3].h = PLANT_HEIGHT;
}

void Koopa::set_clips()
{
    	//Clip the sprites
    	clipsRight[ 0 ].x = KOOPA_WIDTH * 5;
    	clipsRight[ 0 ].y = KOOPA_HEIGHT * 2;
    	clipsRight[ 0 ].w = KOOPA_WIDTH;
    	clipsRight[ 0 ].h = KOOPA_HEIGHT;

    	clipsRight[ 1 ].x = KOOPA_WIDTH * 6;
    	clipsRight[ 1 ].y = KOOPA_HEIGHT * 2;
    	clipsRight[ 1 ].w = KOOPA_WIDTH;
    	clipsRight[ 1 ].h = KOOPA_HEIGHT;

   	clipsRight[ 2 ].x = KOOPA_WIDTH * 7;
   	clipsRight[ 2 ].y = KOOPA_HEIGHT * 2;
   	clipsRight[ 2 ].w = KOOPA_WIDTH;
    	clipsRight[ 2 ].h = KOOPA_HEIGHT;

   	clipsRight[ 3 ].x = KOOPA_WIDTH * 8;
   	clipsRight[ 3 ].y = KOOPA_HEIGHT * 2;
   	clipsRight[ 3 ].w = KOOPA_WIDTH;
   	clipsRight[ 3 ].h = KOOPA_HEIGHT;

   	clipsLeft[ 0 ].x = KOOPA_WIDTH * 4;
    	clipsLeft[ 0 ].y = KOOPA_HEIGHT * 2;
   	clipsLeft[ 0 ].w = KOOPA_WIDTH;
    	clipsLeft[ 0 ].h = KOOPA_HEIGHT;

    	clipsLeft[ 1 ].x = KOOPA_WIDTH * 3;
    	clipsLeft[ 1 ].y = KOOPA_HEIGHT * 2;
   	clipsLeft[ 1 ].w = KOOPA_WIDTH;
    	clipsLeft[ 1 ].h = KOOPA_HEIGHT;
	
	clipsLeft[ 2 ].x = KOOPA_WIDTH * 2;
    	clipsLeft[ 2 ].y = KOOPA_HEIGHT * 2;
   	clipsLeft[ 2 ].w = KOOPA_WIDTH;
    	clipsLeft[ 2 ].h = KOOPA_HEIGHT;

	clipsLeft[ 3 ].x = KOOPA_WIDTH;
    	clipsLeft[ 3 ].y = KOOPA_HEIGHT * 2;
   	clipsLeft[ 3 ].w = KOOPA_WIDTH;
    	clipsLeft[ 3 ].h = KOOPA_HEIGHT;

}

void Goomba::set_clips()
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
	SDL_WM_SetCaption( "Basic Enemies", NULL );

    	//If everything initialized fine
    	return true;
}

bool load_files()
{
	//Load the background and enemy images
	goomba = load_image( "goomba.png" );
	koopa = load_image( "koopa2.png" );
	plant = load_image( "plant.png" );
	background = load_image( "level1-1.png" );

	//If there was an error in loading the background or enemies
	if( background == NULL )
	{
		return false;
	}

	if( goomba == NULL )
	{
		return false;
	}
	if( koopa == NULL )
	{
		return false;
	}
	if( plant == NULL )
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
	SDL_FreeSurface( koopa );
	SDL_FreeSurface( plant );
	SDL_FreeSurface( background );

    	//Quit SDL
    	SDL_Quit();
}


