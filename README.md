Terrain_Generator
=================

A Graphical Implementation of a Rubiks cube using opengl

![Sample Image 1](https://raw.github.com/rgruener/RubiksCube/master/sample_images/rubiks_cube.png)

## Description ##

The goal of this project was to create a 3D graphical implementation of
a Rubiks cube with animated turns as well as a save option.

This project was created for ECE462 Interactive Engineering Graphics at
Cooper Union taught by Professor Carl Sable in the Spring 2013 Term

## Dependencies ##

* OpenGL 3.0 or Higher
* GLUT
* GLEW

## Compilation ##

Compilation instructions are for linux machines.  For other operating
systems such as Windows or Mac OS compilation flags within the makefile
must be changed in addition to other changes.  Refer to 
http://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/
for instructions on compiling on other environments.

To compile the make utility must be installed, simply type make in the root folder.
If all dependencies are installed it should successfully compile.

## Usage ##

### General Syntax ###
./rubiks.exe

### Usage ###

Upon start a command prompt will appear asking whether to load a saved cube
or the number of random turns to give the cube upon start.

The other controls appear at the bottom of the Rubiks cube window as seen in
the image at the top of the README.
