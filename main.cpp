// main.cpp

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "graphics.h"
#include "mario.h"
#include "timer.h"
#include "fireball.h"
#include "enemy.h"
#include "goomba.h"
#include "koopa.h"
#include "plant.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main( int argc, char* args[] ) {

	// instantiate objects
	Graphics myGraphics;					// create graphics object
	Mario myMario;						// create mario object
	Fireball myFireball(myMario.getX(), myMario.getY());	// create fireball object
	Timer fps;						// frame rate regulator

	// instantiate enemies
	vector < Enemy* > myenemies(4);		//Create a vector of enemies

	// Number of fireballs used
	int fireballcount = 0;

	Goomba Goomba1(500, 168);	
	Goomba Goomba2(550, 168);
	Koopa Koopa1(350, 100, 300, 375);
	Plant Plant1(451, 142);
	
	// assign enemies
	myenemies[0] = &Goomba1;
	myenemies[1] = &Goomba2;
	myenemies[2] = &Koopa1;
	myenemies[3] = &Plant1;

	//Number of enemies
	int e_num = 4;

	// declare variables
	int marioDir;			// direction mario faces when initially using fireball
	int lifeCount=3;		// number of lives mario has remaining
	bool quitLevel=false;		// quits level if true
	bool quitGame=false;		// quits game if true
	bool win=false;			// displays victory screen if true
	int time;			// current time from timer
	bool isJumped;			// determine if mario is jumping or not
	SDL_Event event;

	// images
	SDL_Surface *background = NULL;
	SDL_Surface *startScreen = NULL;
	SDL_Surface *goombaIcon = NULL;
	SDL_Surface *mario = NULL;
	SDL_Surface *fireball = NULL;
	SDL_Surface *goomba = NULL;
	SDL_Surface *koopa = NULL;
	SDL_Surface *plant = NULL;
	background = myGraphics.load_image("images/level1-1.png");
	startScreen = myGraphics.load_image("images/super-mario-bros-screen.jpg");
	goombaIcon = myGraphics.load_image("images/goomba");
	fireball = myGraphics.load_image("images/fireball_sprites.png");
	mario = myGraphics.load_image("images/bigMarioMotion1.png");
	goomba = myGraphics.load_image("images/goomba.png");
	koopa = myGraphics.load_image("images/koopa2.png");
	plant = myGraphics.load_image("images/plant.png");

	// fonts
	TTF_Font *inGamefont;
	TTF_Font *endFont;
	SDL_Color textColor = {255, 255, 255};
	SDL_Color winColor = {0, 255, 0};
	SDL_Color loseColor = {255, 0, 0};
	SDL_Surface *preLevel = NULL;
	SDL_Surface *lifetext1 = NULL;
	SDL_Surface *lifetext2 = NULL;
	SDL_Surface *lifetext3 = NULL;
	SDL_Surface *victoryText = NULL;
	SDL_Surface *gameOverText = NULL;
	inGamefont = TTF_OpenFont("fonts/Lato-Regular.ttf", 28);
	endFont = TTF_OpenFont("fonts/journal.ttf", 72);
	preLevel = TTF_RenderText_Solid( inGamefont, "World 1-1", textColor );
	lifetext1 = TTF_RenderText_Solid( inGamefont, " x  3", textColor );
	lifetext2 = TTF_RenderText_Solid( inGamefont, " x  2", textColor );
	lifetext3 = TTF_RenderText_Solid( inGamefont, " x  1", textColor );
	victoryText = TTF_RenderText_Solid( endFont, "You Win!", winColor );
	gameOverText = TTF_RenderText_Solid( endFont, "Game Over!", loseColor );

	// set image clips
	myMario.set_clips();		// sets the mario images
	myFireball.set_clips();		// sets the fireball images
	
	//set enemy clips
	for (int i=0; i<e_num; i++ ) {		
		myenemies[i]->set_clips();
	}

	// run the homescreen
	myGraphics.runHomescreen(event);

	// run the game
	while((quitGame==false)&&(lifeCount>0)) {

		if (myMario.isDead()==true) {
			myMario.resetDeath();
			myMario.setX();
			myMario.setY();
			Goomba1.setX(500);
			Goomba1.setY(168);	
			Goomba2.setX(550);
			Goomba2.setY(168);
			Koopa1.setX(350);
			Koopa1.setY(100);
			Koopa1.setXmin(300);
			Koopa1.setXmax(375);
			Plant1.setX(451);
			Plant1.setY(142);
			for (int a=0; a<e_num; a++ ) {
				myenemies[a]->resetDeath();
			}
		}

		// prelevel Screen
		myGraphics.init();
	        myGraphics.apply_surface(245, 90, preLevel, myGraphics.getScreen(), NULL);
		myGraphics.apply_surface(280, 125, mario, myGraphics.getScreen(), myMario.getOclip());
		if (lifeCount==3) {
			myGraphics.apply_surface(295, 125, lifetext1, myGraphics.getScreen(), NULL);
		}
		else if (lifeCount==2) {
			myGraphics.apply_surface(295, 125, lifetext2, myGraphics.getScreen(), NULL);
		}
		else if (lifeCount==1) {
			myGraphics.apply_surface(295, 125, lifetext3, myGraphics.getScreen(), NULL);
		}
		SDL_Flip(myGraphics.getScreen());
		SDL_Delay(1500);
		quitLevel = false;

	// run until death or quit
	myGraphics.init();					// resize the game window
	while((quitLevel==false)&&(quitGame==false)&&(win==false)) {// user has not quit
     		fps.start();					// start the frame timer
		time = SDL_GetTicks();				// microseconds that have passed 	

		while(SDL_PollEvent(&event)) {			// there are events to handle
        		myMario.handle_input(event,time);	// handle events for mario
			myFireball.handleFire(event);		// handle events for fireball
        		if(event.type==SDL_QUIT) {		// user has Xed out the window
                		quitGame=true;			// quit the program
        		}
			else if(event.type == SDL_KEYDOWN) {
				if(event.key.keysym.sym == SDLK_SPACE){
					myFireball.countup();
					fireballcount = myFireball.getCount();
					if (fireballcount < 15){
						if (myMario.getX()>312) {
							myFireball.setFireX(myMario.getX()-myMario.getCamerax());
						}
						else {
							myFireball.setFireX(myMario.getX());
						}
				
						myFireball.setFireY(myMario.getY()-myMario.getHeight()/2);
						marioDir=myMario.getStatus();
					}
				}
			}
        	}

		// determine how to update mario's position
		isJumped = myMario.getisJumped(); 
		if (isJumped == true) {
			myMario.jump(time);
		}	
		else {
	        	myMario.move();
		}
	
        	myMario.set_camera();	// set the camera centered on mario
		
		//move enemies
		for (int i=0; i<e_num; i++ ) {		
			myenemies[i]->move();
		}
		
		for (int j=0; j<e_num; j++){			
			myFireball.checkDeath(myenemies[j]->getX(),myenemies[j]->getY(),myenemies[j]->getWidth(),myenemies[j]->getHeight(), myenemies[j]->isDead());
		}

		if (myFireball.getIsFire()){
			myFireball.moveFire(marioDir);
		}
		
		// reset the screen and display updated scene
		myGraphics.clearScreen(myGraphics.getScreen());
        	myGraphics.apply_surface(0, 0, background, myGraphics.getScreen(), myMario.getCamera());
		myMario.updateStatus();
		myFireball.updateFire();
		//update the enemies
		for (int i=0; i<e_num; i++ ) {		
			myenemies[i]->update();
		}

		// mario moving right
		if(myMario.getStatus()==0) {
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getRclip());
			if (myFireball.getIsFire() == true) {
				if ( myFireball.getFireStatus() == 0) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY() , fireball, myGraphics.getScreen(), myFireball.getFireR());
				}
				else if ( myFireball.getFireStatus() == 1) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY(), fireball, myGraphics.getScreen(), myFireball.getFireL());
				}
			}
		}

		// mario moving left
		else if(myMario.getStatus()==1) {
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getLclip());
			if (myFireball.getIsFire() == true) {
				if ( myFireball.getFireStatus() == 0) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY() , fireball, myGraphics.getScreen(), myFireball.getFireR());
				}
				else if ( myFireball.getFireStatus() == 1) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY(), fireball, myGraphics.getScreen(), myFireball.getFireL());
				}
			}
		}

		// mario crouching
		else if(myMario.getStatus()==2) {
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getCclip());
			if (myFireball.getIsFire() == true) {
				if ( myFireball.getFireStatus() == 0) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY() , fireball, myGraphics.getScreen(), myFireball.getFireR());
				}
				else if ( myFireball.getFireStatus() == 1) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY(), fireball, myGraphics.getScreen(), myFireball.getFireL());
				}
			}
		}

		// mario jumping
		else if(myMario.getStatus()==3) {
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getJclip());
			if (myFireball.getIsFire() == true) {
				if ( myFireball.getFireStatus() == 0) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY() , fireball, myGraphics.getScreen(), myFireball.getFireR());
				}
				else if ( myFireball.getFireStatus() == 1) {
					myGraphics.apply_surface(myFireball.getFireX(), myFireball.getFireY(), fireball, myGraphics.getScreen(), myFireball.getFireL());
				}
			}
		}

		//check if enemy is hit by fireball
		for (int i=0; i<e_num; i++ ) {		
			myenemies[i]->checkDeath(myMario.getY(),myMario.getX(),myFireball.getFireX(),myFireball.getFireY(),myFireball.getFireW(),myFireball.getFireH(),myFireball.getIsFire());
		}

		//Move goomba left
		if (myenemies[0]->isDead() == false){
			myGraphics.apply_surface(myenemies[0]->getX()-myMario.getCamerax(),myGraphics.getHeight()-myenemies[0]->getHeight()-24, goomba, myGraphics.getScreen(), myenemies[0]->getLclip());
		}
			
		if (myenemies[1]->isDead() == false){
			myGraphics.apply_surface(myenemies[1]->getX()-myMario.getCamerax(),myGraphics.getHeight()-myenemies[1]->getHeight()-24, goomba, myGraphics.getScreen(), myenemies[1]->getLclip());
		}

		//Move plant
		if (myenemies[3]->isDead() == false){
			myGraphics.apply_surface(myenemies[3]->getX()-myMario.getCamerax(),myenemies[3]->getY(), plant, myGraphics.getScreen(), myenemies[3]->getLclip());
		}

		//Move Koopa left or right
		if (myenemies[2]->isDead() == false){
			if(myenemies[2]->getStatus()==0) { //move right
				myGraphics.apply_surface(myenemies[2]->getX()-myMario.getCamerax(),myenemies[2]->getY(), koopa, myGraphics.getScreen(), myenemies[2]->getRclip());
			}
			if (myenemies[2]->getStatus()==1) { //move left
				myGraphics.apply_surface(myenemies[2]->getX()-myMario.getCamerax(),myenemies[2]->getY(), koopa, myGraphics.getScreen(), myenemies[2]->getLclip());
			}
		}

		// update the screen
        	if(SDL_Flip(myGraphics.getScreen())==-1) {
        		return 1;
        	}

		// cap the frame rate
		if(fps.get_ticks()<1000/20) {
        		SDL_Delay((1000/20)-fps.get_ticks());
    		}

		// check if mario has collided with enemies
		for (int i=0; i<e_num; i++ ) {
			if (myenemies[i]->mDead(myMario.getX(),myMario.getY()) == true){
				myMario.makeDead();
				quitLevel = true;
			}
		}

		// check if mario has reached the end
		if (myMario.getX()>3160) {
			myGraphics.clearScreen(myGraphics.getScreen());
        		myGraphics.apply_surface(0, 0, background, myGraphics.getScreen(), myMario.getCamera());
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getFPclip());
			win = true;
			quitGame = true;
			quitLevel = true;
			SDL_Flip(myGraphics.getScreen());
			SDL_Delay(1000);
		}

		//check if quit is true
		if (myMario.isDead()==true){
			myGraphics.clearScreen(myGraphics.getScreen());
        		myGraphics.apply_surface(0, 0, background, myGraphics.getScreen(), myMario.getCamera());
			myGraphics.apply_surface(myMario.getX()-myMario.getCamerax(), myMario.getY(), mario, myGraphics.getScreen(), myMario.getDclip());
			SDL_Flip(myGraphics.getScreen());
			SDL_Delay(1000);
			quitLevel = true;
			lifeCount--;
		}
	}

	}

	// victory screen
	if (win == true) {
		myGraphics.clearScreenB(myGraphics.getScreen());
		myGraphics.apply_surface(240, 80, victoryText, myGraphics.getScreen(), NULL);
		SDL_Flip(myGraphics.getScreen());
		SDL_Delay(2000);
	}

	// game over screen
	if (win == false) {
		myGraphics.clearScreenB(myGraphics.getScreen());
		myGraphics.apply_surface(210, 90, gameOverText, myGraphics.getScreen(), NULL);
		SDL_Flip(myGraphics.getScreen());
		SDL_Delay(2000);
	}
	


	SDL_FreeSurface(mario);
	SDL_FreeSurface(background);
	SDL_FreeSurface(startScreen);
	SDL_FreeSurface(goombaIcon);
	SDL_FreeSurface(fireball);
	SDL_FreeSurface(goomba);
	SDL_FreeSurface(koopa);
	SDL_FreeSurface(plant);
	SDL_FreeSurface(preLevel);
	SDL_FreeSurface(lifetext1);
	SDL_FreeSurface(lifetext2);
	SDL_FreeSurface(lifetext3);
	SDL_FreeSurface(victoryText);
	SDL_FreeSurface(gameOverText);

	TTF_CloseFont(inGamefont);
	TTF_CloseFont(endFont);
	TTF_Quit();

	return 0;
}
