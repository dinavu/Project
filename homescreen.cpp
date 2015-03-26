/* Jose Suarez
 * March 21, 2015
 * Home screen attempt for SUPER MARIO BROS Project
 */

/*
 *
 * FIX ISSUES:
 * 
 * 1) Get rid of original Player Goomba
 *
 * 2) Press ENTER = go into game
 *
 */

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 692;
const int SCREEN_HEIGHT = 484;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *goomba = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *playWorld = NULL;

class Goomba {
	private:
		int x,y;
		int play;
	public:
		Goomba();
		void handle_input();
		int show();
}; //end GOOMBA CLASS


//The event structure
SDL_Event event;

SDL_Surface *load_image( string filename )
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
	    //Map the color key
	    Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0xFF, 0xFF);
		
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );

//            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
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
    SDL_WM_SetCaption( "SUPER MARIO BROS HOMESCREEN", NULL );

    //If everything initialized fine
    return true;
}

bool init2()
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {return false;}
	screen = SDL_SetVideoMode(640,224,SCREEN_BPP,SDL_SWSURFACE | SDL_RESIZABLE);
	if( screen == NULL ) {return false;}
	SDL_WM_SetCaption( "GAME WORLD", NULL);
	return true;

}

bool load_files()
{
    //Load the background image
    background = load_image( "super-mario-bros-screen.jpg" );
    goomba = load_image( "goomba" );
    playWorld = load_image( "level1-1.png" );

    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }

    if( goomba == NULL )
    {
	return false;
    }

    if( playWorld == NULL )
    {
	return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( goomba );
    SDL_FreeSurface( playWorld );

    //Quit SDL
    SDL_Quit();
}

//Constructor
Goomba::Goomba() {
	x=150;
	y=260;
	play=0;
} //end

void Goomba::handle_input() {

	if (event.type == SDL_KEYDOWN ) {
		switch (event.key.keysym.sym) {
			case SDLK_UP: y=260; break;
			case SDLK_DOWN: y=295; break;
			case SDLK_RETURN: play=1; break;
		} //end SWITCH
	} //end IF
} //end

int Goomba::show() {
	if (play==0) {
		apply_surface(0,0,background,screen);
		apply_surface(x,y,goomba,screen);
		return 0;
	} else if (play==1) {
//		clean_up();
//		init2();
//		load_files();
//		apply_surface(0,0,playWorld,screen);
		return 1;
	}
	return 0;
} //end


int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;
	int enterPlay=0;

	Goomba myGoomba;

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

	//While the user hasn't quit
	while( quit == false ) {
		//While there's events to handle
		while( SDL_PollEvent( &event ) ) {

			myGoomba.handle_input();

			//If the user has Xed out the window
			if( event.type == SDL_QUIT ) {
				quit = true;
			} //end IF
		} //end INNER WHILE
		
		//Apply the background
//		apply_surface( 0, 0, background, screen );
		enterPlay=myGoomba.show();

		//Update the screen
		if( SDL_Flip( screen ) == -1 ) {
			return 1;
		}
		
		if (enterPlay == 1) { quit = true; }
	}
	clean_up();
	
	quit = false;

	init2();
	load_files();

	while (quit == false) {
		while ( SDL_PollEvent( &event ) ) {
			if (event.type == SDL_QUIT) { quit = true; }
		}

		apply_surface(0,0,playWorld,screen);

		if( SDL_Flip(screen) == -1) { return 1; }
	}

	clean_up();
	return 0;
}
