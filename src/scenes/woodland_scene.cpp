#include "headerfiles/woodland_scene.h"

WoodlandScene::WoodlandScene() {
	setSceneType(WOODLAND_SCENE);

    this->purple_slime_texture = LoadTexture("assets/graphics/spritesheets/actors/dk_sptsht_purpleslime.png");
    this->blue_slime_texture = LoadTexture("assets/graphics/spritesheets/actors/dk_sptsht_blueslime.png");
    this->falcon_texture = LoadTexture("assets/graphics/spritesheets/actors/dk_sptsht_falcon.png");
    this->possesed_bear_texture = LoadTexture("assets/graphics/spritesheets/actors/dk_sptsht_possessedbear.png");
    this->skeleton_texture = LoadTexture("assets/graphics/spritesheets/actors/dk_sptsht_skeleton.png");
    this->stone_golem_texture = LoadTexture("assets/graphics/spritesheets/actors/dk_sptsht_stonegolem.png");
    this->wild_boar_texture = LoadTexture("assets/graphics/spritesheets/actors/dk_sptsht_wildboar.png");
    this->wolf_texture = LoadTexture("assets/graphics/spritesheets/actors/dk_sptsht_wolf.png");

    std::ifstream tileset_description_file("./assets/level/dk_ts_woodlandbiom.json");
    nlohmann::json tileset_description = nlohmann::json::parse(tileset_description_file);
    tileset_description_file.close();

    std::ifstream level_map_file("./assets/level/dk_lv_fin_woodlandbiom.json");
    nlohmann::json level_map = nlohmann::json::parse(level_map_file);
    level_map_file.close();

    this->tile_atlas_texture = LoadTexture(("./assets/graphics/tilesets/" + tileset_description["image"].get<std::string>()).c_str());

    parseLevelBackgroundTiles(tileset_description, level_map);
    parseLevelForegroundTiles(tileset_description, level_map);
    parseLevelCollider(tileset_description, level_map);

    generateEnemies();
}

WoodlandScene::~WoodlandScene() {
	UnloadTexture(this->tile_atlas_texture);
    UnloadTexture(this->purple_slime_texture);
    UnloadTexture(this->blue_slime_texture);
    UnloadTexture(this->falcon_texture);
    UnloadTexture(this->possesed_bear_texture);
    UnloadTexture(this->skeleton_texture);
    UnloadTexture(this->stone_golem_texture);
    UnloadTexture(this->wild_boar_texture);
    UnloadTexture(this->wolf_texture);
}

//---------------------------Functions---------------------------------

void WoodlandScene::update(Player& player, PlayerCamera& camera) {

    player.update();
    for (int i = 0; i < this->enemies_vector.size(); i++) {
        if (!this->enemies_vector[i].searchForPlayer(player)) {
            this->enemies_vector[i].update();
        }
    }
    detectCollision(player, camera);

    // Camera and Inventory.
    camera.update(player);
    player.getInventory().checkDedicatedWeaponSlotPressed(camera.getPlayerCamera().target, camera.getInventoryUI());
    player.getInventory().checkDedicatedItemSlotPressed(camera.getPlayerCamera().target, camera.getInventoryUI());
    player.getInventory().checkInventorySlotPressed(camera.getPlayerCamera().target, camera.getInventoryUI());
}

void WoodlandScene::draw(Player& player, PlayerCamera& camera) {
	//DrawText("Woodland scene", 10, 10, 30, LIGHTGRAY);
    BeginMode2D(camera.getPlayerCamera());
    drawBackground(camera);

    //Everything that is not part of the map schould be rendered here.
    for (int i = 0; i < this->enemies_vector.size(); i++) {
        this->enemies_vector[i].draw();
    }
    player.draw();

    drawForeground(camera);
    camera.draw(player);
    player.getInventory().draw();
    EndMode2D();
}

void WoodlandScene::drawBackground(PlayerCamera& camera) {
    Vector2 camera_position = camera.getPlayerCamera().target;
    camera_position.x = camera_position.x - static_cast<float>(GetScreenWidth() / 2);
    camera_position.y = camera_position.y - static_cast<float>(GetScreenHeight() / 2);
    for (const auto& tile : this->woodland_tiles_background_vector) {
        if (camera_position.x < tile->position_on_screen.x && tile->position_on_screen.x < camera_position.x + static_cast<float>(GetScreenWidth()) && camera_position.y < tile->position_on_screen.y && tile->position_on_screen.y < camera_position.y + static_cast<float>(GetScreenHeight())) {
            DrawTextureRec(this->tile_atlas_texture, tile->spritesheet_position, tile->position_on_screen, WHITE);
        }
    }
}

void WoodlandScene::drawForeground(PlayerCamera& camera) {
    Vector2 camera_position = camera.getPlayerCamera().target;
    camera_position.x = camera_position.x - static_cast<float>(GetScreenWidth() / 2);
    camera_position.y = camera_position.y - static_cast<float>(GetScreenHeight() / 2);
    for (const auto& tile : this->woodland_tiles_foreground_vector) {
        if (camera_position.x < tile->position_on_screen.x && tile->position_on_screen.x < camera_position.x + static_cast<float>(GetScreenWidth()) && camera_position.y < tile->position_on_screen.y && tile->position_on_screen.y < camera_position.y + static_cast<float>(GetScreenHeight())) {
            DrawTextureRec(this->tile_atlas_texture, tile->spritesheet_position, tile->position_on_screen, WHITE);
        }
    }
}

void WoodlandScene::parseLevelBackgroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map) {

    Vector2 vec = { 0, 0 };
    Rectangle rec = { 0, 0, level_map["tilewidth"], level_map["tileheight"] };

    for (auto const& layer : level_map["layers"]) {
        if (layer["type"] == "tilelayer" && layer["visible"]) {
            for (auto const& tileId : layer["data"]) {
                if (layer["id"] < 8 ) {
                    if (tileId != 0) {
                        rec.x = static_cast<float>(((static_cast<int>(tileId) - 1) % static_cast<int>(tileset_description["columns"]))) * static_cast<float>(level_map["tilewidth"]);
                        rec.y = static_cast<float>(floor(static_cast<float>(tileId) / static_cast<float>(tileset_description["columns"]))) * static_cast<float>(level_map["tilewidth"]);
                        if (static_cast<int>(tileId) % 32 == 0) {
                            rec.y -= 16;
                        }

                        std::shared_ptr<LevelTile> tile = std::make_shared<LevelTile>();
                        tile->position_on_screen = vec;
                        tile->spritesheet_position = rec;
                        this->woodland_tiles_background_vector.push_back(tile);
                    }
                }
                else {
                    return;
                }

                vec.x += static_cast<float>(level_map["tilewidth"]);
                if (vec.x >= static_cast<float>(layer["width"]) * static_cast<float>(level_map["tilewidth"])) {
                    vec.x = 0;
                    vec.y += static_cast<float>(level_map["tileheight"]);
                }
                if (vec.y >= static_cast<float>(layer["height"]) * static_cast<float>(level_map["tileheight"])) {
                    vec.y = 0;
                }
            }
        }

    }
}

void WoodlandScene::parseLevelForegroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map) {
    Vector2 vec = { 0, 0 };
    Rectangle rec = { 0, 0, level_map["tilewidth"], level_map["tileheight"] };

    for (auto const& layer : level_map["layers"]) {
        if (layer["type"] == "tilelayer" && layer["visible"]) {
            for (auto const& tileId : layer["data"]) {
                if (layer["id"] > 8 && layer["id"] != 13) {
                    if (tileId != 0) {
                        rec.x = static_cast<float>(((static_cast<int>(tileId) - 1) % static_cast<int>(tileset_description["columns"]))) * static_cast<float>(level_map["tilewidth"]);
                        rec.y = static_cast<float>(floor(static_cast<float>(tileId) / static_cast<float>(tileset_description["columns"]))) * static_cast<float>(level_map["tilewidth"]);
                        if (static_cast<int>(tileId) % 32 == 0) {
                            rec.y -= 16;
                        }

                        std::shared_ptr<LevelTile> tile = std::make_shared<LevelTile>();
                        tile->position_on_screen = vec;
                        tile->spritesheet_position = rec;
                        this->woodland_tiles_foreground_vector.push_back(tile);
                    }
                }

                vec.x += static_cast<float>(level_map["tilewidth"]);
                if (vec.x >= static_cast<float>(layer["width"]) * static_cast<float>(level_map["tilewidth"])) {
                    vec.x = 0;
                    vec.y += static_cast<float>(level_map["tileheight"]);
                }
                if (vec.y >= static_cast<float>(layer["height"]) * static_cast<float>(level_map["tileheight"])) {
                    vec.y = 0;
                }
            }
        }

    }
}

void WoodlandScene::parseLevelCollider(nlohmann::json& tileset_description, nlohmann::json& level_map) {
    Vector2 vec = { 0, 0 };
    Rectangle rec = { 0, 0, level_map["tilewidth"], level_map["tileheight"] };

    for (auto const& layer : level_map["layers"]) {
        if (layer["type"] == "tilelayer" && layer["id"] == 13) {
            for (auto const& tileId : layer["data"]) {
                if (tileId != 0) {
                    std::shared_ptr<ColliderTile> collider_tile = std::make_shared<ColliderTile>();
                    collider_tile->id = 0;
                    collider_tile->collider_position = vec;
                    this->woodland_tiles_collider_vector.push_back(collider_tile);
                }

                vec.x += static_cast<float>(level_map["tilewidth"]);
                if (vec.x >= static_cast<float>(layer["width"]) * static_cast<float>(level_map["tilewidth"])) {
                    vec.x = 0;
                    vec.y += static_cast<float>(level_map["tileheight"]);
                }
                if (vec.y >= static_cast<float>(layer["height"]) * static_cast<float>(level_map["tileheight"])) {
                    vec.y = 0;
                }
            }
        }

    }
}

void WoodlandScene::generateEnemies() {

    Enemy enemy1("Blue Slime", "test", 1, Vector2{ 4960, 2224 }, this->blue_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy2("Blue Slime", "test", 2, Vector2{ 5104, 2336 }, this->blue_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy3("Blue Slime", "test", 3, Vector2{ 3664, 2560 }, this->blue_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy4("Blue Slime", "test", 4, Vector2{ 5744, 1824 }, this->blue_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy5("Blue Slime", "test", 5, Vector2{ 5008, 1744 }, this->blue_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy6("Blue Slime", "test", 6, Vector2{ 4608, 1584 }, this->blue_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy7("Blue Slime", "test", 7, Vector2{ 3216, 2784 }, this->blue_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy8("Blue Slime", "test", 8, Vector2{ 1568, 3104 }, this->blue_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy9("Blue Slime", "test", 9, Vector2{ 1824, 3088 }, this->blue_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy10("Blue Slime", "test", 10, Vector2{ 1824, 2976 }, this->blue_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy11("Blue Slime", "test", 11, Vector2{ 2288, 2704 }, this->blue_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });

    Enemy enemy12("Purple Slime", "test", 12, Vector2{ 2352, 1696 }, this->purple_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy13("Purple Slime", "test", 13, Vector2{ 2640, 1728 }, this->purple_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy14("Purple Slime", "test", 14, Vector2{ 2512, 1824 }, this->purple_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy15("Purple Slime", "test", 15, Vector2{ 1424, 2160 }, this->purple_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy16("Purple Slime", "test", 16, Vector2{ 1488, 2352 }, this->purple_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy17("Purple Slime", "test", 17, Vector2{ 1920, 2544 }, this->purple_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy18("Purple Slime", "test", 18, Vector2{ 1952, 2816 }, this->purple_slime_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });

    Enemy enemy19("Wolf", "test", 19, Vector2{ 4832, 992 }, this->wolf_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy20("Wolf", "test", 20, Vector2{ 4496, 1248 }, this->wolf_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy21("Wolf", "test", 21, Vector2{ 6192, 1632 }, this->wolf_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy22("Wolf", "test", 22, Vector2{ 5920, 1408 }, this->wolf_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy23("Wolf", "test", 23, Vector2{ 3600, 2608 }, this->wolf_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy24("Wolf", "test", 24, Vector2{ 3296, 1808 }, this->wolf_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy25("Wolf", "test", 25, Vector2{ 1808, 1776 }, this->wolf_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy26("Wolf", "test", 26, Vector2{ 1584, 1392 }, this->wolf_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy27("Wolf", "test", 27, Vector2{ 1728, 1136 }, this->wolf_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy28("Wolf", "test", 28, Vector2{ 3184, 1232 }, this->wolf_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });

    Enemy enemy29("Falcon", "test", 29, Vector2{ 5536, 1424 }, this->falcon_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy30("Falcon", "test", 30, Vector2{ 4784, 1296 }, this->falcon_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy31("Falcon", "test", 31, Vector2{ 3648, 1616 }, this->falcon_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy32("Falcon", "test", 32, Vector2{ 3936, 1728 }, this->falcon_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy33("Falcon", "test", 33, Vector2{ 3744, 1904 }, this->falcon_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy34("Falcon", "test", 34, Vector2{ 592, 2160 }, this->falcon_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy35("Falcon", "test", 35, Vector2{ 960, 2320 }, this->falcon_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy36("Falcon", "test", 36, Vector2{ 784, 2208 }, this->falcon_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });

    Enemy enemy37("Wild Boar", "test", 37, Vector2{ 5200, 1312}, this->wild_boar_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy38("Wild Boar", "test", 38, Vector2{ 4064, 1424 }, this->wild_boar_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy39("Wild Boar", "test", 39, Vector2{ 3472, 2608 }, this->wild_boar_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy40("Wild Boar", "test", 40, Vector2{ 3152, 2528 }, this->wild_boar_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy41("Wild Boar", "test", 41, Vector2{ 3648, 1008 }, this->wild_boar_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy42("Wild Boar", "test", 42, Vector2{ 3888, 2032 }, this->wild_boar_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy43("Wild Boar", "test", 43, Vector2{ 1392, 1728 }, this->wild_boar_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy44("Wild Boar", "test", 44, Vector2{ 1264, 2528 }, this->wild_boar_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });

    Enemy enemy45("Possesed Bear", "test", 45, Vector2{ 4448, 736 }, this->possesed_bear_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy46("Possesed Bear", "test", 46, Vector2{ 3952, 784 }, this->possesed_bear_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy47("Possesed Bear", "test", 47, Vector2{ 736, 1888 }, this->possesed_bear_texture, 24, 32, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });

    Enemy enemy48("Stone Golem", "test", 48, Vector2{ 5584, 1120 }, this->stone_golem_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy49("Stone Golem", "test", 49, Vector2{ 5536, 816 }, this->stone_golem_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy50("Stone Golem", "test", 50, Vector2{ 5904, 992 }, this->stone_golem_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy51("Stone Golem", "test", 51, Vector2{ 4336, 1856 }, this->stone_golem_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy52("Stone Golem", "test", 52, Vector2{ 4352, 2208 }, this->stone_golem_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy53("Stone Golem", "test", 53, Vector2{ 2816, 2224 }, this->stone_golem_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy54("Stone Golem", "test", 54, Vector2{ 2960, 1968 }, this->stone_golem_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy55("Stone Golem", "test", 55, Vector2{ 2368, 2032 }, this->stone_golem_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy56("Stone Golem", "test", 56, Vector2{ 2592, 1312 }, this->stone_golem_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy57("Stone Golem", "test", 57, Vector2{ 2848, 992 }, this->stone_golem_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });
    Enemy enemy58("Stone Golem", "test", 58, Vector2{ 2176, 1040 }, this->stone_golem_texture, 24, 16, 16, 1000, 0.8f, 35, 124, Weaknesses{ 0.12f, 0.15f, 0.85f, 0.5f, 0.32f });

    this->enemies_vector.push_back(enemy1);
    this->enemies_vector.push_back(enemy2);
    this->enemies_vector.push_back(enemy3);
    this->enemies_vector.push_back(enemy4);
    this->enemies_vector.push_back(enemy5);
    this->enemies_vector.push_back(enemy6);
    this->enemies_vector.push_back(enemy7);
    this->enemies_vector.push_back(enemy8);
    this->enemies_vector.push_back(enemy9);
    this->enemies_vector.push_back(enemy10);
    this->enemies_vector.push_back(enemy11);
    this->enemies_vector.push_back(enemy12);
    this->enemies_vector.push_back(enemy13);
    this->enemies_vector.push_back(enemy14);
    this->enemies_vector.push_back(enemy15);
    this->enemies_vector.push_back(enemy16);
    this->enemies_vector.push_back(enemy17);
    this->enemies_vector.push_back(enemy18);
    this->enemies_vector.push_back(enemy19);
    this->enemies_vector.push_back(enemy20);
    this->enemies_vector.push_back(enemy21);
    this->enemies_vector.push_back(enemy22);
    this->enemies_vector.push_back(enemy23);
    this->enemies_vector.push_back(enemy24);
    this->enemies_vector.push_back(enemy25);
    this->enemies_vector.push_back(enemy26);
    this->enemies_vector.push_back(enemy27);
    this->enemies_vector.push_back(enemy28);
    this->enemies_vector.push_back(enemy29);
    this->enemies_vector.push_back(enemy30);
    this->enemies_vector.push_back(enemy31);
    this->enemies_vector.push_back(enemy32);
    this->enemies_vector.push_back(enemy33);
    this->enemies_vector.push_back(enemy34);
    this->enemies_vector.push_back(enemy35);
    this->enemies_vector.push_back(enemy36);
    this->enemies_vector.push_back(enemy37);
    this->enemies_vector.push_back(enemy38);
    this->enemies_vector.push_back(enemy39);
    this->enemies_vector.push_back(enemy40);
    this->enemies_vector.push_back(enemy41);
    this->enemies_vector.push_back(enemy42);
    this->enemies_vector.push_back(enemy43);
    this->enemies_vector.push_back(enemy44);
    this->enemies_vector.push_back(enemy45);
    this->enemies_vector.push_back(enemy46);
    this->enemies_vector.push_back(enemy47);
    this->enemies_vector.push_back(enemy48);
    this->enemies_vector.push_back(enemy49);
    this->enemies_vector.push_back(enemy50);
    this->enemies_vector.push_back(enemy51);
    this->enemies_vector.push_back(enemy52);
    this->enemies_vector.push_back(enemy53);
    this->enemies_vector.push_back(enemy54);
    this->enemies_vector.push_back(enemy55);
    this->enemies_vector.push_back(enemy56);
    this->enemies_vector.push_back(enemy57);
    this->enemies_vector.push_back(enemy58);
}

void WoodlandScene::detectCollision(Player& player, PlayerCamera& camera) {

    Vector2 camera_position = camera.getPlayerCamera().target;
    camera_position.x = camera_position.x - static_cast<float>(GetScreenWidth() / 2);
    camera_position.y = camera_position.y - static_cast<float>(GetScreenHeight() / 2);

    Rectangle player_rec = { player.getCurrentPosition().x, player.getCurrentPosition().y, 16, 16 };
    Rectangle collider_rec = { 0, 0, 16, 16 };
    for (const auto& tile : this->woodland_tiles_collider_vector) {

        collider_rec.x = tile->collider_position.x;
        collider_rec.y = tile->collider_position.y;

        if (camera_position.x < collider_rec.x && collider_rec.x < camera_position.x + static_cast<float>(GetScreenWidth()) && camera_position.y < collider_rec.y && collider_rec.y < camera_position.y + static_cast<float>(GetScreenHeight())) {
            if (CheckCollisionRecs(player_rec, collider_rec)) {
                player.setCurrentPosition(player.getLastPosition());
            }
        }
    }
    player.setLastPosition(player.getCurrentPosition());

    for (const auto& tile : this->woodland_tiles_collider_vector) {

        collider_rec.x = tile->collider_position.x;
        collider_rec.y = tile->collider_position.y;

        for (int i = 0; i < this->enemies_vector.size(); i++) {
            Rectangle enemy_rec = { this->enemies_vector[i].getCurrentPosition().x, this->enemies_vector[i].getCurrentPosition().y, 16, 16};
            if ((enemy_rec.x - 48) < collider_rec.x && collider_rec.x < (enemy_rec.x + 48) && (enemy_rec.y - 48) < collider_rec.y && collider_rec.y < (enemy_rec.y + 48)) {
                if (CheckCollisionRecs(enemy_rec, collider_rec)) {
                    this->enemies_vector[i].setCurrentPosition(this->enemies_vector[i].getLastPosition());
                }
            }
            if (CheckCollisionCircles(this->enemies_vector[i].getCurrentPosition(), 6, player.getCurrentPosition(), 6)) {
                this->enemies_vector[i].setIsDead(true);
                this->enemies_vector[i].setFrameConter(0);
            }
        }
    }

    /*
    for (const auto& tile : this->woodland_tiles_collider_vector) {
        if (CheckCollisionCircles(player.getCurrentPosition(), 6, tile->collider_position, 8)) {
            player.setCurrentPosition(player.getLastPosition());
        }
        if (CheckCollisionCircles(this->enemy.getCurrentPosition(), 6, tile->collider_position, 8)) {
            this->enemy.setCurrentPosition(this->enemy.getLastPosition());
        }
        if (CheckCollisionCircles(this->enemy.getCurrentPosition(), 6, player.getCurrentPosition(), 6)) {
            this->enemy.setIsDead(true);
            this->enemy.setFrameConter(0);
        }
    }*/
    for (int i = 0; i < this->enemies_vector.size(); i++) {
        this->enemies_vector[i].setLastPosition(this->enemies_vector[i].getCurrentPosition());
    }
}

//----------------------------Setter----------------------------------

SceneType WoodlandScene::setNextScene(Player& player, bool& exitWindowRequested) {
	if (IsKeyPressed(KEY_ENTER)) {
        player.setCurrentPosition(2048, 2048);
		return MAIN_MENU_SCENE;
	}
	return WOODLAND_SCENE;
}