/* timer.h */

#ifndef TIMER_H
#define TIMER_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
using namespace std;

class Timer {
	public:
	Timer();		// class constructor
	void start();		// start timer
	void stop();		// stop timer
	void pause();		// pause timer
	void unpause();		// unpause timer
	int get_ticks();	// get the timer's time
	bool is_started();	// true/false the timer is started
	bool is_paused();	// true/false the timer is paused

	private:
	int startTicks;		//The clock time when the timer started
 	int pausedTicks;	//The ticks stored when the timer was paused
	bool paused, started;	//The timer status
};

#endif
