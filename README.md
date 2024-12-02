# Chess
A quick and dirty chess project using OpenGL and SDL. This most likely will end up being a throw-away educational project.

> [!CAUTION]
> This codebase is not an example for you to learn how to organize code or build larger projects. Please refrain from using this project as an example project of a good project, as it isn't one. Also as I've mentioned before, this project probably won't earn any further maintenance as it was only an educational project for myself to learn new things, feedback and pull requests are welcome, of course.

## Libraries used
- [GLAD](https://github.com/Dav1dde/glad)
- [SDL2](https://www.libsdl.org/)
- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
- [glm](https://github.com/g-truc/glm)

## Screenshots
Running on Linux (Debian):
![Screenshot in-game (old screenshot before a few QoL updates)](/.github/screenshot.png)
Running on Windows:
![Screenshot in-game on Windows](/.github/windows.png)

## Features
- can move chess pieces
- can eat other chess pieces (no validation whether your own or your opponents!)
- highlight currently selected chess piece
- highlight possible moves (not validated! only for pawns!)

To support more features and my sanity (due to messy code base), this whole project needs a rewrite. 

## Supported platforms
Currently only supported platforms are Windows and Linux. It should technically also compile on macOS, but I don't have a macOS device to test it on.

## Building

### Requirements
In addition to C++ development tools (no tutorial here, look up: `setup c++ development environment on <distr/os>`), everything else is packaged and ready-to-go.

Example, in Ubuntu/Debian:
```sh
$ sudo apt update && sudo apt install libsdl2-dev
```

### Building
Usually done as such:
```sh
$ mkdir build && cd build
$ cmake -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo  <other flags> ..
$ cmake --build .
```

### Execution
Please either copy or symlink `assets` directory in the root directory to `<build dir>/bin`, as the executable expects an asset directory on the same level as the executable itself. After this, you're ready to go:
```sh
$ ./ftd
```

## Attributions

- https://greenchess.net/info.php?item=downloads for chess pieces
- https://en.m.wikipedia.org/wiki/File:Chess_Board.svg for chess board (converted to PNG & rescaled)
- https://learnopengl.com/
- [zKevz](https://github.com/zKevz)
