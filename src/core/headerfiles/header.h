#pragma once

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <String>
#include <vector>
#include <memory>
#include <map>

#include "raylib.h"
#include "json.hpp"

enum ButtonState { IDLE, ACTIVE, PRESSED };
enum ItemType { WEAPON, CONSUMABLE, USABLE };
enum SceneType { START_SCENE, MAIN_MENU_SCENE, WOODLAND_SCENE, WOODLAND_DUNGEON_SCENE, TOWER_SCENE, TOWER_DUNGEON_SCENE };
enum AnimationState { STANDING, WALKING, RUNNING, ATTACKING, DAMAGE, DYING, SPAWNING };

struct LevelTile { Vector2 position_on_screen; Rectangle spritesheet_position; };
struct ColliderTile { int id; Vector2 collider_position; };