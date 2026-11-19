# Lahore Dash

Lahore Dash is a student-developed 2D game written in C++ with SFML 3.1.0. Inspired by Lahore, the project is being built as a hands-on way to explore game development, from menus and player movement to collision handling, audio, and future enemy behaviour.

The game is a work in progress. This README separates what is currently implemented from ideas planned for later development.

## Technologies

- **Language:** C++
- **Graphics and audio:** SFML 3.1.0
- **IDE:** Visual Studio 2026
- **Project files:** Visual Studio solution and project files (`LahoreDash.slnx`, `LahoreDash.vcxproj`)

## Project structure

The following is the project-specific source and asset layout (third-party SFML headers and libraries are not expanded here):

```text
.
├── main.cpp
├── menu.cpp
├── Player.cpp
├── Player.h
├── Enemy.cpp
├── Enemy.h
├── LahoreDash.slnx
├── LahoreDash.vcxproj
├── assets/
│   ├── Background_music.ogg
│   ├── menu_background.jpeg
│   └── player.png
├── include/                 # Bundled dependency headers
└── lib/                     # Bundled libraries and CMake package files
```

`Enemy.cpp` and `Enemy.h` are present as placeholders; enemy functionality has not been implemented yet. The menu implementation is in `menu.cpp`.

## Implemented features

- A main menu with a pixel-art background created with AI assistance.
- A clickable **Start** button in the menu.
- A player character displayed using the external image in `assets/player.png`.
- Keyboard-controlled player movement.
- Temporary wall collision handling and restrictions that keep the player within the screen boundaries.
- Background music integrated from `assets/Background_music.ogg`.

## Planned work

These items are not implemented yet and are part of the development roadmap:

- Build out the game environment and refine wall collision handling.
- Implement enemy behaviour and interactions with the player.
- Add player animations.
- Add gameplay sound effects.
- Expand the game with additional gameplay and interface elements as development continues.

## Learning objectives

Lahore Dash is also a practical learning project. Its development provides experience with:

- Organizing a C++ project into focused source files and classes.
- Using SFML for rendering, input, and audio.
- Loading and displaying image assets.
- Handling keyboard input and updating player movement.
- Exploring collision detection and screen boundaries.
- Integrating audio into a real-time application.
- Planning and building a game incrementally, distinguishing working features from future ideas.

## Development status

The project is actively being developed. The menu, basic player movement, preliminary collision and boundary handling, and background music are in place. Enemy gameplay, player animation, additional sound effects, and further game content remain future work.
