#pragma once

#include <cstdlib>
#include <iostream>
#include <String>
#include <vector>
#include <memory>
#include <map>

#include "raylib.h"

enum ButtonState { IDLE, ACTIVE, PRESSED };
enum ItemType { WEAPON, CONSUMABLE, USABLE };
enum SceneType { START_SCENE, MAIN_MENU_SCENE, WOODLAND_SCENE, WOODLAND_DUNGEON_SCENE, TOWER_SCENE, TOWER_DUNGEON_SCENE };
enum AnimationState { STANDING, WALKING, RUNNING, ATTACKING, DAMAGE, DYING, SPAWNING };
