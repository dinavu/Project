# Super Mario Bros
![](https://github.com/dinavu/Project/blob/master/images/GameScreen.png)
By: Dina Vu, Nicholas Ward, Victoria Johnston, Jose Suarez

CSE20212 - Fundamentals of Computing II: Final Project
University of Notre Dame

Last Updated: April 27, 2015


====== THE PROJECT: Super Mario Bros ======

This program is a recreation of the original Super Mario Bros game.
The goal of the project was to create a version of this traditional,
2-D scrolling game. The game is composed of the first level of the
first world of the original game full of enemies. Note that only the
option with one player (Mario) is available at this point.

The most up-to-date version of this Super Mario Bros prjoect can be
found on Dina Vu's github - https://github.com/dinavu/Project


====== INSTALLING AND RUNNING THE GAME ======

To run the program and play Super Mario Bros on your computer, you must
first download this game and compile it appropriately. Go to the GitHub
Repository link included above and clone the project.

Once all the files in the repository have been appropriately downloaded
into a folder of your choice, simply enter the make command ("make") to
compile all the files simultaneously. This will access the fonts and
images folders appropriately, compile all the classes required to run the
game, and make an executable file "main". Once the make command has
finished running, the compilation process is complete. Enter "main" into
the command line to prompt the game to open in a new graphics window.

Note: the libraries included all belong to SDL1. This means that you must
have an appropriate program running to open the graphics. That being said,
no libraries outside of SDL1 were used.


====== GAMEPLAY ======

The game opens in a title screen where the user can select one or two
players through the Goomba Selector and the arrow keys. Once the desired
gameplay is selected, simply push ENTER/RETURN to enter the first world
of Super Mario Bros.

Mario begins at the start of the first world of Super Mario Bros with
three lives. A life is lost if Mario collides with an enemy or falls off
the map where there is no floor. In the case that Mario dies, he will
restart at the start of the level with the life count updated accordingly.

Mario is controlled using the arrow keys and the SPACE bar.
There are two main ways to kill enemies:
	(1) use Mario's fireballs to kill them from a safe distance; or
	(2) jump on top of them (although this is a collision, landing 
	on top of them will in fact kill them). Lastly, enemies can
	simply be avoided by jumping over different blocks and do not
	have to be killed.

The goal of this game is to safely move Mario from his starting position
in the world to the flag pole at the other end of the level. In the evemt
you safely make it to the end of the level with Mario, you win the game!


====== CONTROLS ======

Once inside the game (past the homescreen), the goal is to reach the
end of the level without dying. These are the controls:
	- Arrow Keys:
		Right	Move Right
		Left	Move Left
		Up	Jump
		Down	Crouch
	- SPACE Bar: throw fireball
		(Note: only 1 fireball permitted at a time; trying to
		throw more than one fireball will reset the original
		fireball so only one is present at any point in time)


====== DOCUMENTATION ======

The link provided for the GitHub Repository includes the most up-to-date
version of this game. It is in that location that all the changes and
updates of the game were made. A history of commits can be found within
the same GitHub Repository.

A time log of all the contributions by individual group members can be found in the following link - 
https://docs.google.com/document/d/1PLDvAwGydSXTyPNbGjX854IBhLAibcGoJ74npbypmEE/edit?usp=sharing


====== BUGS ======

What follows is a list of known bugs present in the game:

- Game title screen allows to chose one or two players but gameplay
  is the same regardless.
- Some pipe collisions prevent the user from walking off the left side.
- Sometimes the hit box for a plant reports a hit but the plant does
  not die.
- Ending a jump prematurely can result in jumping higher and further
  the next time Mario jumps
- Jumping collision can result in Mario temporarily going into the
  level's floor or the blocks he is standing on. Jumping again can
  help free Mario from the inside of the block or floor.
- While jumping, sometimes side collisions are not immediately
  immediately detected and Mario might pass through part of an object
  such as pipe or block.
- Part of the level has a narrow space between two triangular block
  sections and it is possible for Mario to be trapped there due to the
  jump being parabolic. It is possible to free Mario from this area by
  repeatedly jumping and trying to move through the sides of the
  blocks, but it is difficult.
- When trying to crouch, the jumping clip of Mario is displayed though
  Mario remains stationary.
- Occasionally Mario's death image is displayed when hitting multiple
  buttons while trying to jump.
- Fireball always fires right while Mario is jumping, even if Mario is
  facing left.

