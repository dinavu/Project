#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

//Screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//Frame rate
const int FRAMES_PER_SECOND = 20;

//Dimensions of Fireball
const int FIREBALL_WIDTH = 24;
const int FIREBALL_HEIGHT = 100;

//Direction of fireball
const int FIREBALL_RIGHT = 0;
const int FIREBALL_LEFT = 1;

//Surfaces
SDL_Surface *fireball = NULL;
SDL_Surface *screen = NULL;

//Event structure
SDL_Event event;

//Areas of sprite sheet
SDL_Rect clipsRight [ 4 ];
SDL_Rect clipsLeft [ 4 ];

//Fireball
class Fireball
{
	private:
	int offSet;
	int velocity;
	int yvelocity;
	int yoffSet;
	int frame;
	int status;

	public:
	Fireball();
	void handle_events();
	void move();
	void show();
};

class Timer
{
	private:
	int startTicks;
	int pausedTicks;
	bool paused;
	bool started;

	public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	int get_ticks();
	bool is_started();
	bool is_paused();
};

SDL_Surface *load_image(std::string filename)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load( filename.c_str() );
	
	if( loadedImage != NULL )
	{
		optimizedImage = SDL_DisplayFormat( loadedImage );
		SDL_FreeSurface( loadedImage );
		if( optimizedImage != NULL )
		{
			//Color key surface
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF) );
		}
	}

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

void set_clips()
{
	//Clip the sprites
	clipsRight[ 0 ].x = 0;
	clipsRight[ 0 ].y = FIREBALL_HEIGHT;
	clipsRight[ 0 ].w = FIREBALL_WIDTH;
	clipsRight[ 0 ].h = FIREBALL_HEIGHT;

	clipsRight[ 1 ].x = FIREBALL_WIDTH;
	clipsRight[ 1 ].y = FIREBALL_HEIGHT;
	clipsRight[ 1 ].w = FIREBALL_WIDTH;
	clipsRight[ 1 ].h = FIREBALL_HEIGHT;

	clipsRight[ 2 ].x = FIREBALL_WIDTH * 2;
	clipsRight[ 2 ].y = FIREBALL_HEIGHT;
	clipsRight[ 2 ].w = FIREBALL_WIDTH;
	clipsRight[ 2 ].h = FIREBALL_HEIGHT;

	clipsRight[ 3 ].x = FIREBALL_WIDTH * 3;
	clipsRight[ 3 ].y = FIREBALL_HEIGHT;
	clipsRight[ 3 ].w = FIREBALL_WIDTH;
	clipsRight[ 3 ].h = FIREBALL_HEIGHT;

	clipsLeft[ 0 ].x = 0;
	clipsLeft[ 0 ].y = FIREBALL_HEIGHT;
	clipsLeft[ 0 ].w = FIREBALL_WIDTH;
	clipsLeft[ 0 ].h = FIREBALL_HEIGHT;

	clipsLeft[ 1 ].x = FIREBALL_WIDTH;
	clipsLeft[ 1 ].y = FIREBALL_HEIGHT;
	clipsLeft[ 1 ].w = FIREBALL_WIDTH;
	clipsLeft[ 1 ].h = FIREBALL_HEIGHT;

	clipsLeft[ 2 ].x = FIREBALL_WIDTH * 2;
	clipsLeft[ 2 ].y = FIREBALL_HEIGHT;
	clipsLeft[ 2 ].w = FIREBALL_WIDTH;
	clipsLeft[ 2 ].h = FIREBALL_HEIGHT;

	clipsLeft[ 3 ].x = FIREBALL_WIDTH * 3;
	clipsLeft[ 3 ].y = FIREBALL_HEIGHT;
	clipsLeft[ 3 ].w = FIREBALL_WIDTH;
	clipsLeft[ 3 ].h = FIREBALL_HEIGHT;
}

bool init()
{
	if( (SDL_INIT_EVERYTHING ) == -1 )
	{
		return false;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if( screen == NULL)
	{
		return false;
	}

	return true;
}

bool load_files()
{
	fireball = load_image("fireball_sprites.png");
	
	if( fireball == NULL )
	{
		return false;
	}

	return true;
}

void clean_up()
{
	//Free the surface
	SDL_FreeSurface( fireball );
	
	SDL_Quit();
}

Fireball::Fireball()
{
	offSet = 0;
	velocity = 0;
	yvelocity = 0;
	yoffSet = SCREEN_HEIGHT - FIREBALL_HEIGHT;

	frame = 0;
	status = FIREBALL_RIGHT;
}

void Fireball::handle_events()
{

	if( event.type == SDL_KEYDOWN )
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{ 
				velocity = FIREBALL_WIDTH / 4;
				yvelocity = sqrt(FIREBALL_WIDTH/4);
		}
	}
}

void Fireball::move()
{
	offSet += velocity/2;
	yoffSet += yvelocity;

	if( ( offSet < 0) || (offSet + FIREBALL_WIDTH > SCREEN_WIDTH ) )
	{
		offSet -= velocity;
		yvelocity = 0;
	}

	if ( yoffSet > (SCREEN_HEIGHT-FIREBALL_HEIGHT/2))
	{
		yvelocity = -sqrt(FIREBALL_WIDTH/4);
	}
	else if (yoffSet < (SCREEN_HEIGHT - FIREBALL_HEIGHT) )
	{
		yvelocity = sqrt(FIREBALL_WIDTH/4);
	}
}

void Fireball::show()
{

	if( velocity < 0 )
	{
		status = FIREBALL_LEFT;
		frame++;
	}
	else if (velocity > 0)
	{
		status = FIREBALL_RIGHT;
		frame++;
	}

	frame = frame % 3;
	



	if ( status == FIREBALL_RIGHT)
	{
		apply_surface( offSet, yoffSet , fireball, screen, &clipsRight[ frame ] );
	}
	else if (status ==FIREBALL_LEFT)
	{
		apply_surface( offSet, yoffSet, fireball, screen, &clipsLeft[ frame ]);
	}

}


	

Timer::Timer()
{
    //Initialize the variables
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

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
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

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //Clip the sprite sheet
    set_clips();

    //The frame rate regulator
    Timer fps;

    Fireball walk;
    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the stick figure
            walk.handle_events();

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        walk.move();

        //Fill the screen white
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

        walk.show();

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    //Clean up
    clean_up();

    return 0;
}
