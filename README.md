# Turing Machine

Hi, this is my little project I did during vacation, because I was slightly bored.
It's an open-source Turing Machine simulator!

## Description

This project is a nice and simple interactive Turing Machine written with SFML.
If you've never heard of a Turing Machine before, it's basically a device which takes a piece of tape with cells on it (that's a metaphor)
It has some fundamental features, such as: moving, setting the value to 0, setting the value to 1, checking if the value is 1, checking if the value is 0.
A real, programmable Turing Machine usually has a feature which allows it to execute some bonus instructions only if a TRUE is returned from a check!
This one doesn't have it, as it's fully human-controlled.
The Turing Machine might seem simple, but it's actually the basis of all modern electronical devices.
If you have a working, automated Turing Machine, it should in theory be able to do everything a modern computer can do, computation-wise.

P.S
The code is well-documented, so I highly recommend checking it out!

## Getting Started

### Dependencies

* C++ compiler
* SFML

### Compiling (Debian-based linux)

* apt-get install g++
* apt-get install libsfml-dev
* apt-get install git
* git clone https://github.com/AptRock327/Turing-Machine
* cd Turing-Machine
* g++ TuringMachine.cpp -o TuringMachine -lsfml-graphics -lsfml-window -lsfml-system
* chmod +x TuringMachine
* The folder should now contain a fully-runnable executable file.

### Compiling (Gentoo-based linux)

* emerge media-libs/libsfml
* emerge dev-vcs/git
* git clone https://github.com/AptRock327/Turing-Machine
* cd Turing-Machine
* g++ TuringMachine.cpp -o TuringMachine -lsfml-graphics -lsfml-window -lsfml-system
* chmod +x TuringMachine
* The folder should now contain a fully-runnable executable file.

### Compiling (Windows 7/10/11)

* [Set up MinGW](https://sourceforge.net/projects/mingw/)
* [Compile SFML](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php) and set it up with MinGW
* Compile TuringMachine.cpp with SFML and the flags: -lsfml-graphics -lsfml-window -lsfml-system
* The folder should now contain a fully-runnable executable file.
Note that since this guide isn't that precise, you might want to search up on how to set up SFML with Windows on your own.

### Instructions

The syntax looks like this:
```
./TuringMachine [amount of cells]
```
If no amount of cells is given, the program will default it to 4.

Use left-right arrows to move between cells
Use up-down arrows to increase/decrease the cell value
Hold Q to check if the currently selected cell has the value 0, and R to check if it is 1

## License

This project is licensed under the GNU GPL v2 License - see the LICENSE.md file for details

## Acknowledgments

* [This amazing readme template](https://gist.github.com/DomPizzie/7a5ff55ffa9081f2de27c315f5018afc)
* [The SFML project](https://www.sfml-dev.org/)