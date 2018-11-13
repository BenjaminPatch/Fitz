# Fitz
A command line tile game wherein two players (either computer or human) verse eachother. Whoever can't fit a tile in the board first loses.
### Skills Tested
- Basic-Intermediate C programming with the C99 Standard
- UNIX File I/O
- The ability to follow a specification written abstractly
- Introduction to Systems Programming
- Memory Management
### Getting Started
##### Prerequisites
To run this program on a unix system, you must have gcc (or some other valid compiler).
If you are using a compiler other than gcc, you will need to set up the compilation process accordingly.
##### Installing/Compiling
The Makefile in /src outlines which files should be compiled then linked to other object files.
Running the "make" command should be valid for most unix systems, provided gcc is installed. This project was made on Ubuntu and compiles with the provided makefile on that.
##### Outline of file structure
fitz.c, gameInput.c, startProgramValidation.c & tilesAndBoard.c are compiled into individual object files.
These object files are linked together to provide the resultant fitz executable.
### Authors
Benjamin Patch (myself)
