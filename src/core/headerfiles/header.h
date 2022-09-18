#pragma once

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <future>

#include "raylib.h"
#include "json.hpp"

enum ButtonState { IDLE, ACTIVE, PRESSED };
enum ButtonType { NO_BUTTON, START_BUTTON, RESUME_BUTTON, OPTIONS_BUTTON, EXIT_BUTTON };
enum ItemType { WEAPON, CONSUMABLE, USABLE };
enum SceneType { START_SCENE, MAIN_MENU_SCENE, WOODLAND_SCENE, WOODLAND_DUNGEON_SCENE, TOWER_SCENE, TOWER_DUNGEON_SCENE };
enum AnimationState {NONE, STANDING_UP, STANDING_DOWN, STANDING_LEFT, STANDING_RIGHT, WALKING_UP, WALKING_DOWN, WALKING_LEFT, WALKING_RIGHT, RUNNING_UP, RUNNING_DOWN, RUNNING_LEFT, RUNNING_RIGHT, ATTACKING, DAMAGE, DYING, SPAWNING };
enum ElementalEffects { WATER, FIRE, THUNDER, POISON, MAGIC };
enum InventoryWindow { WEAPONS_WINDOW, ITEMS_WINDOW, MAP_WINDOW, QUEST_WINDOW, MONSTER_WINDOW };

struct LevelTile { Vector2 position_on_screen; Rectangle spritesheet_position; };
struct ColliderTile { int id; Vector2 collider_position; };
struct Weaknesses {	float water_weakness; float fire_weakness; float thunder_weakness; float poison_weakness; float magic_weakness; };
struct InventoryHitbox { int id; Rectangle hitbox; };