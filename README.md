# CPPND: Capstone - Shooter Game

## Project Description

This game was created for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213), using Capstone Option 2 (add features to a video game).

Udacity's [starter repo](https://github.com/udacity/CppND-Capstone-Snake-Game) was used to start off this project. The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

I modified the repo to go from a snake game using SDL2 library, to a simple version of a shooter game (like Space Invaders / Galaga).

<img src="shooter_game.png"/>

## File / Class Structure
These files all exist in "src" directory
* main.cpp
** Starts the game, creates instances of renderer, controller, and game, and calls "game.Run(...)" to start the game loop
* game.cpp / game.h
 * Manages the game play
* controller.cpp / controller.h
 * Handles user input
* renderer.cpp / renderer.h
 * Renders necessary components for users to see on the screen
* shooter.cpp / shooter.h
 * handles the shooter object; populates its body, shoots missiles, and checks if any enemy missiles hit the shooter
* EnemyShipManager.cpp / EnemyShipManager.h
 * handles a cluster of enemy ships; creates enemy ships at appropriate locations, shoots missiles from the bottom-most ships, and checks if any shooter missiles hit enemy ships 
* EnemyShip.cpp / EnemyShip.h
 * handles individual enemy ship; populates its body, and moves it around based on the direction given by EnemyShipManager 
* Direction.h
 * just an enum class for direction, used by shooter, EnemyShipManager, and EnemyShip.

## Criteria / Specifications Met
### Loops, Functions, I/O
1. Criteria: The project demonstrates an understanding of C++ functions and control structures
 * Specification: A variety of control structures are used in the project
  * EnemyShipManager.cpp: ProcessShooterMissiles method (line 122)
  * shooter.cpp: ProcessEnemyMissiles method (line 78)
 * Specification: The project code is clearly organized into functions
  * shooter.cpp: see functions throughtout the file 
2.  Criteria: The project accepts user input and processes the input
 * Specification: The projects accepts input from a user as part of the necessary operation of the program
  * controller.cpp: HandleInput method (line 16) 
### Object Oriented Programming
3. Criteria: The project uses Object Oriented Programming (OOP) techniques
 * Specificiation: The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
  * shooter.h: See methods / member variables listed in the header file
  * EnemyShipManager.h: See methods / member variables listed in the header file  
4. Criteria: Classes use appropriate access specifiers for class members
 * Specification: All class data members are explicitly specified as public, protected, or private
  * EnemyShipManager.h: see public / private member variables (lines 19-30, 34-63) 
  * shooter.h: see public/private member variables (lines 23-40, 44-50)
5. Criteria: Class constructors utilize member initialization lists
 * Specification: All classs members that are set to argument values are initialized through member initialization lists
  * Enemyship.h: line 14
  * EnemyShipManager.cpp: line 6
  * game.cpp: line 9
  * missile.h: line 7
  * renderer.cpp: line 7
  * shooter.h: line 13
### Memory Management
6. Criteria: The project makes use of references in function declarations
 * Specification: At least two variables are defined as references, or two functions use pass-by-reference in the project code.
  * EnemyShipManager.h: ProcessShooterMissiles method (line 22)
  * shooter.h: ProcessEnemyMissiles method (line 25)
 

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Game Controls
* The shooter only moves horizontally
 * Left key - to move left
 * Right key - to move right
 * Down key - to stop the shooter
* The shooter will fire two missiles at a time, one from each wing.
 * Space bar - to shoot at enemy ships
 
## Gameplay
* The shooter will start with 3 lives
* There will be a total of 40 enemy ships (4 rows of 10), and only the bottom-most ships will be able to fire missiles at the shooter (one enemy ship at a time)
* If the shooter destroys all 40 enemy ships, a new level will start with 40 new ships that move faster and shoot at a higher frequency.
* Once the shooter loses all its 3 lives, or if the enemy ships reach all the way down to the shooter's location, the game is over.
* Score is calculated in the following way:
 * Every enemy ship destroyed = (level #) * 10 points
 * Every level cleared = (level #) * 1000 points

