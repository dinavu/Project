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
const int FRAMES_PER_SECOND = 10;

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

//Vector of obstructions
vector<SDL_Rect> obs;

class Enemy
{
	public:
	Enemy(); //Initializes the variables
	void virtual move(); //Moves Goomba left
	void virtual show(); //Shows goomba
	void virtual set_camera();
	void virtual set_clips();

	protected:
	int xVel,yVel; //Its rate of movement
	int frame; //Its current frame
	int status; //Its animation status
	int enemy_height, enemy_width;
	SDL_Rect box;
};

class Goomba: public Enemy
{
	public:
	Goomba(int, int);
	void virtual move();
	void virtual show();
	void virtual set_clips();
	private:
	SDL_Rect clipsLeft[8];
	SDL_Rect clipsDeath[4];
};

class Koopa: public Enemy
{
	public:
	Koopa(int, int, int, int);
	void virtual move();
	void virtual show();
	void virtual set_clips();
	private:
	SDL_Rect clipsLeft[4];
	SDL_Rect clipsRight[4];
	int xmin,xmax;
};	

class Plant: public Enemy
{
	public:
	Plant(int, int);
	void virtual move();
	void virtual show();
	void virtual set_clips();
	private:
	SDL_Rect clips[4];
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
	Koopa Koopa1(350, 100, 300, 375);
	Plant Plant1(451, 142);

	//assign vector of enemies
	myenemies[0] = &Goomba1;
	myenemies[1] = &Goomba2;
	myenemies[2] = &Koopa1;
	myenemies[3] = &Plant1;

	// sets the necessary images
	for (int i=0; i<e_num; i++ )
	{		
		myenemies[i]->set_clips();
	}

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
	box.x = startx;
	box.y = starty;
	xVel = -1;
	yVel = 0;
	enemy_height = 25.5;
	enemy_width = 25;
	//set box dimensions
	box.w = enemy_width;
	box.h = enemy_height;
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
	apply_surface(box.x, SCREEN_HEIGHT-enemy_height-BLOCK_HEIGHT, goomba, screen, &clipsLeft[frame]);
}

Koopa::Koopa(int startx, int starty, int startmin, int startmax)
{
	//Initialize movement variables
	box.x = startx;
	box.y = starty;
	xVel = 1;
	yVel = 0;
	enemy_height = 37.5;
	enemy_width = 39;
	//kstatus = 1; //start left
	xmin = startmin;
	xmax = startmax;

	box.w = enemy_width;
	box.h = enemy_height;
}

void Koopa::move()
{
	if (box.x<=xmin)
	{
		status = 0; //go right
		frame = 0;
		xVel = 1;
	}
	if (box.x>xmax)
	{	
		status = 1; //go left
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
	if(status==0) {
		apply_surface(box.x,box.y, koopa, screen, &clipsRight[frame]);
	}
	if (status==1) {
		apply_surface(box.x,box.y, koopa, screen, &clipsLeft[frame]);
	}
}

Plant::Plant(int startx, int starty)
{
	//Initialize movement variables
	box.x = startx;
	box.y = starty;
	xVel = 0;
	yVel = 0;
	enemy_height = 26.5;
	enemy_width = 25.1;
	box.w = enemy_width;
	box.h = enemy_height;
}

void Plant::move()
{
	Enemy::move();
}

void Plant::show()
{
	Enemy::show();

	if(frame>=2) { // reset frame count
		frame=0;
	}

	apply_surface(box.x,box.y, plant, screen, &clips[frame]);
}

Enemy::Enemy()
{
	//Initialize animation variables
	frame = 0;
	status = 1; //staryt left
}

void Enemy::move()
{
    	//Move left or right
   	 box.x += xVel;

    	//Keep enemy in bounds
    	if( ( box.x < 0 ) || ( box.x + enemy_width > SCREEN_WIDTH ) )
    	{
    		box.x -= xVel;
    	}

	//move up or down
	box.y += yVel;

	//Keep enemy in bounds
	if( (box.y < 0) || ( box.y + enemy_height > LEVEL_HEIGHT ) ) {
		box.y -= yVel;
	}
}

void Enemy::show()
{
	if (xVel<0) { // choose proper leftward movement frame
		status = 1; //move left
		frame++;
	}
	else if (xVel>0) { // choose proper rightward movement frame
		status = 0; //move right
		frame++;
	}
	else {
		frame++;
	}
}

void Enemy::set_clips(){}

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
	clips[0].y = enemy_height * 2;
	clips[0].w = enemy_width;
	clips[0].h = enemy_height;

	clips[1].x = enemy_width;
	clips[1].y = enemy_height * 2;
	clips[1].w = enemy_width;
	clips[1].h = enemy_height;

	clips[2].x = enemy_width * 2;
	clips[2].y = enemy_height * 2;
	clips[2].w = enemy_width;
	clips[2].h = enemy_height;

	clips[3].x = enemy_width * 3;
	clips[3].y = enemy_height * 2;
	clips[3].w = enemy_width;
	clips[3].h = enemy_height;
}

void Koopa::set_clips()
{
    	//Clip the sprites
    	clipsRight[ 0 ].x = enemy_width * 5;
    	clipsRight[ 0 ].y = enemy_height * 2;
    	clipsRight[ 0 ].w = enemy_width;
    	clipsRight[ 0 ].h = enemy_height;

    	clipsRight[ 1 ].x = enemy_width * 6;
    	clipsRight[ 1 ].y = enemy_height * 2;
    	clipsRight[ 1 ].w = enemy_width;
    	clipsRight[ 1 ].h = enemy_height;

   	clipsRight[ 2 ].x = enemy_width * 7;
   	clipsRight[ 2 ].y = enemy_height * 2;
   	clipsRight[ 2 ].w = enemy_width;
    	clipsRight[ 2 ].h = enemy_height;

   	clipsRight[ 3 ].x = enemy_width * 8;
   	clipsRight[ 3 ].y = enemy_height * 2;
   	clipsRight[ 3 ].w = enemy_width;
   	clipsRight[ 3 ].h = enemy_height;

   	clipsLeft[ 0 ].x = enemy_width * 4;
    	clipsLeft[ 0 ].y = enemy_height * 2;
   	clipsLeft[ 0 ].w = enemy_width;
    	clipsLeft[ 0 ].h = enemy_height;

    	clipsLeft[ 1 ].x = enemy_width * 3;
    	clipsLeft[ 1 ].y = enemy_height * 2;
   	clipsLeft[ 1 ].w = enemy_width;
    	clipsLeft[ 1 ].h = enemy_height;
	
	clipsLeft[ 2 ].x = enemy_width * 2;
    	clipsLeft[ 2 ].y = enemy_height * 2;
   	clipsLeft[ 2 ].w = enemy_width;
    	clipsLeft[ 2 ].h = enemy_height;

	clipsLeft[ 3 ].x = enemy_width;
    	clipsLeft[ 3 ].y = enemy_height * 2;
   	clipsLeft[ 3 ].w = enemy_width;
    	clipsLeft[ 3 ].h = enemy_height;

}

void Goomba::set_clips()
{
    	//Clip the sprites
    	clipsLeft[ 0 ].x = 0;
    	clipsLeft[ 0 ].y = enemy_height;
    	clipsLeft[ 0 ].w = enemy_width;
    	clipsLeft[ 0 ].h = enemy_height;

    	clipsLeft[ 1 ].x = enemy_width;
    	clipsLeft[ 1 ].y = enemy_height;
    	clipsLeft[ 1 ].w = enemy_width;
    	clipsLeft[ 1 ].h = enemy_height;

   	clipsLeft[ 2 ].x = enemy_width * 2;
   	clipsLeft[ 2 ].y = enemy_height;
   	clipsLeft[ 2 ].w = enemy_width;
    	clipsLeft[ 2 ].h = enemy_height;

   	clipsLeft[ 3 ].x = enemy_width * 3;
   	clipsLeft[ 3 ].y = enemy_height;
   	clipsLeft[ 3 ].w = enemy_width;
   	clipsLeft[ 3 ].h = enemy_height;

   	clipsLeft[ 4 ].x = enemy_width * 4;
   	clipsLeft[ 4 ].y = enemy_height;
    	clipsLeft[ 4 ].w = enemy_width;
    	clipsLeft[ 4 ].h = enemy_height;

   	clipsLeft[ 5 ].x = enemy_width * 5;
   	clipsLeft[ 5 ].y = enemy_height;
   	clipsLeft[ 5 ].w = enemy_width;
   	clipsLeft[ 5 ].h = enemy_height;

   	clipsLeft[ 6 ].x = enemy_width * 6;
    	clipsLeft[ 6 ].y = enemy_height;
   	clipsLeft[ 6 ].w = enemy_width;
    	clipsLeft[ 6 ].h = enemy_height;

    	clipsLeft[ 7 ].x = enemy_width * 7;
    	clipsLeft[ 7 ].y = enemy_height;
    	clipsLeft[ 7 ].w = enemy_width;
    	clipsLeft[ 7 ].h = enemy_height;

	clipsDeath[0].x = 0;
	clipsDeath[0].y = 0;
	clipsDeath[0].w = enemy_width;
	clipsDeath[0].h = enemy_height;

	clipsDeath[1].x = enemy_width;
	clipsDeath[1].y = 0;
	clipsDeath[1].w = enemy_width;
	clipsDeath[1].h = enemy_height;

	clipsDeath[2].x = enemy_width * 2;
	clipsDeath[2].y = 0;
	clipsDeath[2].w = enemy_width;
	clipsDeath[2].h = enemy_height;

	clipsDeath[2].x = enemy_width * 3;
	clipsDeath[2].y = 0;
	clipsDeath[2].w = enemy_width;
	clipsDeath[2].h = enemy_height;
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
            		SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ));
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


