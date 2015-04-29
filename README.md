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


====== HOW THE CODE WORKS ======

The program that runs Super Mario Bros is largely based on the OOP
concept of Inheritance. That being said, the file that controls our
game logic uses Composition to include all the game's classes. That is,
the main file, appropriately called MAIN, features parts of the game
like Mario's lives, fireball count, and looping through collision
detection.

Outside of the MAIN file that instantiates all other classes through
Composition, the rest of our files are classes linked through the OOP
concept of Inheritance. The base class in the inheritance hierarchy
displayed in the UML diagram below, is the GRAPHICS class. This class
runs the background functions that enable the program to run, including
image rendering, initializing all the required surfaces, colors and
fonts. Through this class it is also possible to load images, set clips,
and read in all the files necessary to run the game. The three classes
that inherit from GRAPHICS are: ENEMY (which is then broken down to
three different enemies), FIREBALL (which is Mario's power throughout
the game), and MARIO (which controls all Mario does).

ENEMY is an abstract class used to group all of the enemies under a
single umbrella. It includes some virtual functions like those used to
set the original enemy positions and identify their image clips. The
three concrete classes that inherit from ENEMY are: GOOMBA, KOOPA, and
PLANT. All of these classes are concrete and used to instantiate the
enemies in the entirety of the level. Each class respectively refers to
a different enemy that has unique characteristics, like Koopa's bounded
movement left and right, Goomba's unidirectional motion, and Plant's
location in the pipes.

FIREBALL is a concrete class that holds Mario's power. By including
FIREBALL in MAIN, Mario is able to shoot fireballs in both directions,
while standing or jumping to try and kill enemies.

MARIO is the last main concrete class in the inheritance hierarchy.
This class includes all the function and logic required to control Mario.
This class reads the user controls (arrow keys) to control the movement,
check collisions with the floor and any boxes in the world. MARIO
includes multiple status for moving right, left and jumping. MARIO also
includes a TIMER and controls the game camera to make it follow Mario.

![](https://github.com/dinavu/Project/blob/master/images/UML_Diagram.png)


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
- Sometimes the hit box for an enemy reports a hit but the enemy
  does not die.
- While jumping, sometimes side collisions are not immediately
  detected and Mario might pass through part of an object
  such as pipe or block.
- Part of the level has a narrow space between two triangular block
  sections and it is possible for Mario to be trapped there due to the
  jump being parabolic. At this point the user would have to manually
  hit X on the display window and exit the program.
- Fireball always fires right while Mario is jumping, even if Mario is
  facing left.
- From Mario's starting position if Mario jumps left, he will fall into
  the ground and dies.
- When Mario is ontop of a pipe and walks left, he drops down to a 
  middle layer first before falling to the ground. (can be avoid by
  just holding the left key).
- Sometimes enemies do not respawn upon level restart.
- The fireball can move in the backwards direction temporarily if
  Mario is moving fast enough to cause the camera to change the
  fireball's position.
- When Mario vertically collides with the 1st or either of the last two
  pipes then he ends up partway through the top of the pipe.
- Fireballs sometimes do not fire, even when the player has fireballs
  to fire.
