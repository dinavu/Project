// timer.cpp

#include "timer.h"
using namespace std;

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
