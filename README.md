Lahore Dash 

Lahore Dash is a 2D game developed in C++ using SFML 3.1.0, inspired by the streets, culture and environment of Lahore.

The project focuses on building a playable 2D game using Object-Oriented Programming (OOP), with an emphasis on understanding game development fundamentals, including rendering, player movement, collision detection, enemy behaviour, animations and audio integration.

 Technologies Used

Language: C++

Graphics Library: SFML 3.1.0

IDE: Visual Studio 2026

Build System: CMake

Project Structure

The project currently consists of four main source files:

Lahore_Dash/
│
├── Main.cpp
├── Menu.cpp / Menu.h
├── Player.cpp / Player.h
├── Enemy.cpp / Enemy.h
│
└── assets/
    ├── menu_background.jpeg
    ├── player.png
    └── audio/
        └── background_music

Note: The structure is representative; asset names and individual file extensions may change as development progresses.

 Current Development Progress

1. Main Menu

Created a main menu with a pixel-art visual style.

Used AI assistance to create the menu artwork.

Implemented a clickable Start button.

Established the initial interface through which players can enter the game.

2. Player Implementation

Created a dedicated Player class.

Implemented player rendering using an external character image.

Configured sprite scaling and positioning.

Implemented player movement and keyboard controls.

Added temporary wall collision handling.

Implemented boundary restrictions to prevent the player from moving outside the intended game area.

3. Enemy System

Created a separate Enemy file to keep enemy functionality modular.

Enemy implementation has not started yet.

Enemy movement, behaviour and interaction with the player will be developed later.

4. Audio Integration

Successfully implemented background music.

Additional sound effects will be introduced as development progresses.

5. Graphics and Assets

Integrated a pixel-art main menu.

Added an external image for the player character.

Character animations are planned for a later development stage.

 Development Roadmap

The following features represent the planned direction of Lahore Dash.

Gameplay

Basic player movement.

Temporary wall collision.

Game boundary restrictions.

Develop a complete maze environment.

Implement proper wall collision detection.

Develop enemy movement and behaviour.

Implement player-enemy interactions.

Introduce scoring and collectible items.

Graphics and UI

Pixel-art main menu.

Clickable Start button.

Player character image.

Player movement animations.

Enemy character sprites and animations.

Additional UI elements.

Audio

Background music.

Movement and interaction sound effects.

Additional gameplay audio.

 Learning Objectives

Lahore Dash is also a practical learning project focused on developing proficiency in:

Object-Oriented Programming in C++.

Classes, objects, constructors and member functions.

SFML rendering and event handling.

Textures, sprites and animations.

Keyboard input and player movement.

Collision detection and boundary restrictions.

Game loops and real-time updates.

Audio integration.

Modular code organization and game architecture.

 Development Status

Currently in active development.

The project has progressed beyond its initial setup, with a functional main menu, player character, movement system, preliminary collision handling and background music.

The next major stages involve developing the game environment, implementing the enemy system, improving collision detection and introducing character animations and additional gameplay mechanics.
