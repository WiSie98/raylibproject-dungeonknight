#include "headerfiles/woodland_scene.h"

WoodlandScene::WoodlandScene() {
	setSceneType(WOODLAND_SCENE);

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
}

WoodlandScene::~WoodlandScene() {
	UnloadTexture(this->tile_atlas_texture);
}

//---------------------------Functions---------------------------------

void WoodlandScene::update(Player& player, PlayerCamera& camera) {

    player.update();

    detectCollision(player);

    camera.update(player);
}

void WoodlandScene::draw(Player& player, PlayerCamera& camera) {
	//DrawText("Woodland scene", 10, 10, 30, LIGHTGRAY);
    BeginMode2D(camera.getPlayerCamera());
    drawBackground(camera);

    //Everything that is not part of the map schould be rendered here.
    player.draw();

    drawForeground(camera);
    camera.draw(player);
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
                        rec.x = static_cast<float>((static_cast<int>(tileId - 1) % static_cast<int>(tileset_description["columns"]))) * static_cast<float>(level_map["tilewidth"]);
                        rec.y = static_cast<float>(floor(static_cast<float>(tileId) / static_cast<float>(tileset_description["columns"]))) * static_cast<float>(level_map["tilewidth"]);
                        if (tileId % 32 == 0) {
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
                        rec.x = static_cast<float>((static_cast<int>(tileId - 1) % static_cast<int>(tileset_description["columns"]))) * static_cast<float>(level_map["tilewidth"]);
                        rec.y = static_cast<float>(floor(static_cast<float>(tileId) / static_cast<float>(tileset_description["columns"]))) * static_cast<float>(level_map["tilewidth"]);
                        if (tileId % 32 == 0) {
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

void WoodlandScene::detectCollision(Player& player) {
    /*
    Rectangle player_rec = { player.getCurrentPosition().x, player.getCurrentPosition().y, 16, 16 };
    Rectangle collider_rec = { 0, 0, 16, 16 };
    for (const auto& tile : this->woodland_tiles_collider_vector) {

        collider_rec.x = tile->collider_position.x;
        collider_rec.y = tile->collider_position.y;

        if (CheckCollisionRecs(player_rec, collider_rec)) {
            player.setCurrentPosition(player.getLastPosition());
        }
    }
    */

    for (const auto& tile : this->woodland_tiles_collider_vector) {
        if (CheckCollisionCircles(player.getCurrentPosition(), 6, tile->collider_position, 8)) {
            player.setCurrentPosition(player.getLastPosition());
        }
    }
    player.setLastPosition(player.getCurrentPosition());
}

//----------------------------Setter----------------------------------

SceneType WoodlandScene::setNextScene(Player& player, bool& exitWindowRequested) {
	if (IsKeyPressed(KEY_ENTER)) {
        player.setCurrentPosition(2048, 2048);
		return MAIN_MENU_SCENE;
	}
	return WOODLAND_SCENE;
}