# CPP nanodegree: Capstone - Snake extended

This is a clone from the starter repo for the (Capstone project)[https://github.com/udacity/CppND-Capstone-Snake-Game] in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).  

The starter repo was refactored and extended with the following new features:  

- a configuration file (e.g. change size of food, snake and the size of the game area)
- a demonstration mode (automatically play of the computer without any interaction of a human player)
- one-to-one battle (human vs computer)

<img src="snake_game.gif"/>  

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Adapt the deployed (configuration file)[https://github.com/Sepphod/CppND-Capstone-Snake-Game/blob/master/src/snake.cfg].
5. Run it: `./SnakeGame`../src/snake.cfg. If no config file is provided default values will be used. The default values can be found in (settings.h)[https://github.com/Sepphod/CppND-Capstone-Snake-Game/blob/master/src/settings.h]

## SW design


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
