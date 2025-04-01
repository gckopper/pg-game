# pg-game
![gameplay](https://github.com/user-attachments/assets/ab334cf4-7a5d-4df1-8b85-558d9f0296f4)

A simple 2D game making use of OpenGL, developed for a class on graphics processing.

## How to play
Use `WASD` or `ARROW` keys to move around and `SPACE` to attack.

Enemies spawn around the player and gradually move towards it.
Coming into contact with an enemy drains the player's health. \
The player can move around and attack to dodge and/or defeat enemies, which respawn after a short delay.

The game ends once the player's health reaches zero, indicated by the health bar at the top left.

## Building
**Prerequisites:**
- A compiler with *some* C++20 support
- CMake 3.25+
- On Unix-like systems, you might need [additional dependencies](https://www.glfw.org/docs/latest/compile_guide.html#compile_deps) to build GLFW

Firstly, clone this repository and go into its directory:
```
git clone https://github.com/gckopper/pg-game.git
cd pg-game
```

Initialize and update git submodules to get the dependencies:
```
git submodule update --init --recursive
```

Compiling:
```
cmake -B build
cmake --build build --target install
```

This will create a folder named `install` in the project's root, from within which the game can be run. This folder can be renamed and moved wherever you want.
