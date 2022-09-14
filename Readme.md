```
  _____                                       _  __      _       _     _     _____           _           _   
 |  __ \                                     | |/ /     (_)     | |   | |   |  __ \         (_)         | |  
 | |  | |_   _ _ __   __ _  ___  ___  _ __   | ' / _ __  _  __ _| |__ | |_  | |__) | __ ___  _  ___  ___| |_ 
 | |  | | | | | '_ \ / _` |/ _ \/ _ \| '_ \  |  < | '_ \| |/ _` | '_ \| __| |  ___/ '__/ _ \| |/ _ \/ __| __|
 | |__| | |_| | | | | (_| |  __/ (_) | | | | | . \| | | | | (_| | | | | |_  | |   | | | (_) | |  __/ (__| |_ 
 |_____/ \__,_|_| |_|\__, |\___|\___/|_| |_| |_|\_\_| |_|_|\__, |_| |_|\__| |_|   |_|  \___/| |\___|\___|\__|
                      __/ |                                 __/ |                          _/ |              
                     |___/                                 |___/                          |__/               
```

# raylibproject - Dungeon Knight

[![CMakeBuilds](https://github.com/chfhhd/raylibstarter-minimal/actions/workflows/cmake.yml/badge.svg)](https://github.com/chfhhd/raylibstarter/actions/workflows/cmake.yml)

A simple raylib project template for CMake and C/C++

## Usage

Use CMake or a CMake compatible development environment to build a minimalistic raylib project. The raylib library will be downloaded automatically by CMake.

### Changing the project title and version number

The project name and version number can be customized in the `src/CMakeLists.txt` file. By default, the project name is 'game':

```
project(game VERSION 0.1 LANGUAGES CXX)
```

### Change the window size and switch to fullscreen

The width and height of the output window can be adjusted in the `src/config.h.in` file.

By removing the comment

```
//#define GAME_START_FULLSCREEN
```

the project starts in full screen mode.

### Manage assets

Store assets in the designated 'assets' folder. The project already contains a sample graphic file. In the `main.cpp` file, this image is loaded and displayed.

### Choose a different raylib version

Which raylib version is used can be specified in the `cmake/raylib.cmake` file. If this is changed after CMake has already created the project once, you must use CMake to completely rebuild the project.

### What next?

Modify the `main.cpp` file according to your needs.

### Create a binary distribution

The cpack command can be used on the command line to create a binary distribution of the project, for example:

```
cpack -G ZIP -C Debug
```

All assets will be packed into the distribution.

## License

see `LICENCE` file for details.
