# Chess
A quick and dirty chess project using OpenGL and SDL. This most likely will end up being a throw-away educational project.

> [!CAUTION]
> This codebase is not an example for you to learn how to organize code or build larger projects. Please refrain from using this project as an example project of a good project, as it isn't one. Also as I've mentioned before, this project probably won't earn any further maintenance as it was only a educational project for myself to learn new things, feedback and pull requests are welcome, of course.

## Libraries used
- [GLAD](https://github.com/Dav1dde/glad)
- [SDL2](https://www.libsdl.org/)
- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
- [glm](https://github.com/g-truc/glm)

## Screenshots
![Screenshot of in-game](/.github/screenshot.png)

## Supported platforms
Currently only *nix-based platforms are supported due to me implementing my own io utils, specifically using POSIX-only features. Windows support may come in the future (not on high priority).

## Building

### Requirements
In addition to C++ development tools (no tutorial here, look up: `setup c++ development environment on <distro>`), you need to install your distro's SDL2 (usually called `libsdl2-dev`) development libraries, everything else is packaged and ready-to-go.

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
- [zKevz](https://github.com/zKevz) for the idea
