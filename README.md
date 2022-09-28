# pacman

This repository is composed by a source code of pacman in C++. the project needs an implementation of A* algorithm, sound FX, and better conception.

![](https://raw.githubusercontent.com/FACON-Nicolas/FACON-Nicolas/main/resources/pacman.gif)

# Summary

* **[Summary](#summary)**
* **[Credits](#credits)**
* **[Features](#features)**
    * **[Dijkstra](#dijkstra)**
        * **[Boost](#boost)**
        * **[Dijkstra algorithm](#dijkstra-algorithm)**
        * **[Ghosts' path](#ghosts-path)**
* **[Install](#install)**
    * **[Pre-requisites](#pre-requisites)**
    * **[Installation](#installation)**
    * **[Launch](#launch)**
* **[Inputs](#inputs)**
* **[Versions](#versions)**

# Credits

 * **[FACON Nicolas](github.com/FACON-Nicolas)** : developer and creator of the project.

# Features

## Dijkstra

My pacman project is composed by a pacman played by a human, and 3 ghosts Clyde, Pinky, Blinky

These ghosts need a graph implementation to search pacman in the map. I chose to implement this with the **[Boost](boost.org)** library.

### Boost 
Boost is like a fast standard library extension for C/C++ developers, for examples, you can:
 + Maths (Random generators)
 + manage memory when you're using dangerously the pointers
 + use the network
 + measure time and date
 + execute python source code in C++ 
 + use graph and dijkstra algorithm

### Dijkstra algorithm

Dijkstra Algorithm is used to search the shortest path in the **[Graph Theory](https://fr.wikipedia.org/wiki/Théorie_des_graphes)**.

![](https://upload.wikimedia.org/wikipedia/commons/d/d1/Yen%27s_K-Shortest_Path_Algorithm%2C_K%3D3%2C_A_to_F.gif?20121130050940).

### Ghosts' path

I used it to go from the host position, to a goal position.
Theses positions are differents for each ghost:
 + [Blinky](https://pacman.fandom.com/wiki/Blinky) : to player position
 + [Pinky](https://pacman.fandom.com/wiki/Pinky) : to next player position
 + [Clyde](https://pacman.fandom.com/wiki/Clyde) : random between player position and bottom right corner position 

# Install

## Pre-requisites

 + gcc/g++ compiler 
 + C++ 17
 + git 
 + SFML

 ```sh

 #install gcc compiler
 sudo apt install g++

 #install git
 sudo apt install git

 #install SFML
 sudo apt-get install libsfml-dev

 #install Boost
 sudo apt-get install libboost-all-dev

 ```

## Installation

 ```sh
 git clone https://github.com/FACON-Nicolas/pacman
 ```

## Launch

```sh
g++ -c includes/Constant.hpp includes/Direction.hpp includes/Wall.hpp includes/PacGum.hpp sources/Tile.cpp sources/Grid.cpp sources/Animation.cpp sources/Player.cpp sources/Human.cpp sources/Enemy.cpp sources/Pacman.cpp -std=c++17

g++ -o pacman_game Tile.o Grid.o Animation.o Player.o Human.o Enemy.o Pacman.o -lsfml-graphics -lsfml-window -lsfml-system

./pacman_game
```

# Inputs 

|    Action   |  Key  |
| :---------: | :---: |
|  move right | RIGHT |
| move bottom | DOWN  |
|    move up  |   UP  |
|  move left  |  LEFT |
|   restart   | SPACE |
|     quit    |  QUIT |


# Versions

 * **1.0.0** : First version of the project, developed in August 2022
 
