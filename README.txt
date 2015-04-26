Super Mario Bros
Dina Vu, Nicholas Ward, Victoria Johnston, Jose Suarez

CSE20212 - Fundamentals of Computing II: Final Project
University of Notre Dame

April 26, 2015


====== THE PROJECT: Super Mario Bros ======
This program is a recreation of the original Super Mario Bros game.
The goal of the project was to create a version of this traditional, 2-D scrolling game.
The game is composed of the first world of the original game full of enemies.
Note that only the option with one player (Mario) is available at this point.

The most up-to-date version of this Super Mario Bros prjoect can be found on Dina Vu's github - 
https://github.com/dinavu/Project


====== INSTALLING AND RUNNING THE GAME ======
To run the program and play Super Mario Bros on your computer, you must first download this game and compile it appropriately. Go to the GitHub Repository link included above and clone the project.

Once all the files in the repository have been appropriately downloaded into a folder of your choice, simply enter the make command ("make") to compile all the files simultaneously. This will access the fonts and images folders appropriately, compile all the classes required to run the game, and make an executable file "main". Once the make command has finished running, the compilation process is complete. Enter "main" into the command line to prompt the game to open in an new, graphics window.

Note: the libraries included all belong to SDL1. This means that you must have an appropriate program running to open the graphics. That being said, no libraries outside of SDL1 were used.


====== GAMEPLAY ======
The game opens in a title screen where the user can select one or two players through the Goomba Selector and the arrow keys. Once the desired gameplay is selected, simply push ENTER/RETURN to enter the first world of Super Mario Bros.

Mario begins at the start of the first world of Super Mario Bros with three lives. A life is lost if Mario collides with an enemy or falls of the map where there is no floor.
In the case that Mario dies through either of the mentioned causes, Mario will restart from the start of that world/level.

Mario is controlled using the arrow keys and the SPACE bar.
There are two main ways to kill enemies:
	(1) use Mario's fireballs to kill them from a safe distance; or
	(2) jump on top of them (although this is a collision, landing on top of them will in fact kill them).
Lastly, enemies can simply be avoided by jumping over different blocks and do not have to be killed.

The goal of this game is to safely move Mario from its starting position in the world to the very end, signaled by a raised flag and a castle.

In the case you safely make it to the end of the world with Mario, you win the game!


====== CONTROLS ======
Once inside the game (past the homescreen), the goal is to reach the end of the level without dying. These are the controls:
	- Arrow Keys:
		Right	Move Right
		Left	Move Left
		Up	Jump
		Down	Crouch
	- SPACE Bar: throw fireball
		(Note: only 1 fireball permitted at a time; trying to 			throw more than one fireball will reset the original 			fireball so only one is present at any point in time)


====== DOCUMENTATION ======
The link provided for the GitHub Repository includes the most up-to-date version of this game. It is in that location that all the changes and updates of the game were made. A history of commits can be found within the same GitHub Repository.

A time log of all the contributions by individual group members can be found in the following link - 
https://docs.google.com/document/d/1PLDvAwGydSXTyPNbGjX854IBhLAibcGoJ74npbypmEE/edit?usp=sharing


====== BUGS ======
What follows is a list of known bugs present in the game:

- Game title screen allows to chose one or two players but gameplay is the same regardless.




