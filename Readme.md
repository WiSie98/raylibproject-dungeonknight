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

Dungeon Knight is an open world RPG with rougelike and puzzle elements which was created with the RayLib library.

![Screenshot (7)](https://user-images.githubusercontent.com/100346454/211833451-76660a5c-1eeb-4d7b-8925-4b1760ea0f73.png)

The project was created as part of a project during my studies and is not completely finished but is still executable and playable.
We also used the raylib-minimal template which was provided by `https://github.com/chfhhd`.

The parts that are not finished are:
- sound
- combat system
- puzzles
- additional levels
- frendly npcs

The parts that are finished are:
- ui
- scenes
- scene manager
- player character
- enemies
- animation system
- inventory (it is finished but you cannot add any items at the moment)
- items

We used the `https://github.com/nlohmann/json` parser to parse the levels form the json format into c++.

![Screenshot (8)](https://user-images.githubusercontent.com/100346454/211840999-84a77d4a-fd23-4c5a-b168-f50f97ea7aab.png)
![Screenshot (2)](https://user-images.githubusercontent.com/100346454/211841034-a1ea376f-bf95-4a16-a1e0-d82e7345d4d8.png)
![Screenshot (1)](https://user-images.githubusercontent.com/100346454/211841076-2ab732a0-0d15-4825-8761-6843f8e6d45f.png)
![Screenshot (6)](https://user-images.githubusercontent.com/100346454/211841141-9b5a1512-8dd9-4a1b-9547-e3ab82f053ad.png)
![Screenshot (5)](https://user-images.githubusercontent.com/100346454/211841156-a8f02f4e-d513-414f-bc86-db5f28e707f5.png)


## Usage

You need to download or clone this repository into your prefered IDE. The raylib library will be downloaded automatically by CMake.
The game will load a little while at startup so please be patient.

### Controlls

- Use the mouse and the `left mouse button` to navigate in the menu.
- The player character can be controlled with the `WASD` or `Arrow keys`.
- Press `TAB` or `I` to open the inventory.
- You can navigate trough the inventory by pressing the `Q` or `E key`.
- You can equip an item by selecting it in the inventory with the `left mouse button` and unequip or drop an item with the `right mouse button`.

### Choose a different raylib version

Which raylib version is used can be specified in the `cmake/raylib.cmake` file. If this is changed after CMake has already created the project once, you must use CMake to completely rebuild the project.

## License

You can use this project for what ever you like. For further information see the `LICENCE` file for details.
