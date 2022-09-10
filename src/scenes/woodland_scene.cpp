#include "headerfiles/woodland_scene.h"

WoodlandScene::WoodlandScene() : player_ui(this->player_ui_texture, 0, 0, 72, 24, 0, 0, 1.0f) {
	setSceneType(WOODLAND_SCENE);

    std::ifstream tileset_description_file("./assets/level/dk_ts_woodlandbiom.json");
    nlohmann::json tileset_description = nlohmann::json::parse(tileset_description_file);
    tileset_description_file.close();

    std::ifstream level_map_file("./assets/level/dk_lv_fin_woodlandbiom.json");
    nlohmann::json level_map = nlohmann::json::parse(level_map_file);
    level_map_file.close();

    this->player_ui_texture = LoadTexture("./assets/graphics/spritesheets/dk_sptsht_ui_mainhud.png");
    this->tile_atlas_texture = LoadTexture(("./assets/graphics/tilesets/" + tileset_description["image"].get<std::string>()).c_str());
    
    this->player_ui.setSpritesheet(this->player_ui_texture);

	parseLevelBackgroundTiles(tileset_description, level_map);
    parseLevelForegroundTiles(tileset_description, level_map);
    parseLevelCollider(tileset_description, level_map);
}

WoodlandScene::~WoodlandScene() {
	UnloadTexture(this->tile_atlas_texture);
    UnloadTexture(this->player_ui_texture);
}

//---------------------------Functions---------------------------------

void WoodlandScene::update(Player& player, Camera2D& camera) {
    this->player_ui.setMaxHealth(player.getMaxHealth());
    this->player_ui.setMaxShield(player.getMaxShield());
    this->player_ui.setMaxStamina(player.getMaxStamina());

    this->player_ui.setHealth(player.getHealth());
    this->player_ui.setShield(player.getShield());
    this->player_ui.setStamina(player.getStamina());

    player.update();

    detectCollision(player);
    player.setLastPosition(player.getCurrentPosition());

    this->player_ui.update();
    this->player_ui.setSpritesheetDestination(player.getCurrentPosition().x - ((float)GetScreenWidth() / 2) / camera.zoom, player.getCurrentPosition().y - ((float)GetScreenHeight() / 2) / camera.zoom, this->player_ui.getSpritesheetDestination().width, this->player_ui.getSpritesheetDestination().height);
}

void WoodlandScene::draw(Player& player, Camera2D& camera) {
	//DrawText("Woodland scene", 10, 10, 30, LIGHTGRAY);
    BeginMode2D(camera);
    for (const auto& tile : this->woodland_tiles_background_vector) {
        DrawTextureRec(this->tile_atlas_texture, tile->spritesheet_position, tile->position_on_screen, WHITE);
    }

    //Everything that is not part of the map schould be rendered here.
    player.draw();

    for (const auto& tile : this->woodland_tiles_foreground_vector) {
        DrawTextureRec(this->tile_atlas_texture, tile->spritesheet_position, tile->position_on_screen, WHITE);
    }
    this->player_ui.draw();
    DrawTexturePro(this->player_ui_texture, Rectangle{ 96, 0, 216, 48 }, Rectangle{ (player.getCurrentPosition().x + 56) - (player_ui_texture.width * this->player_ui.getScale()) / 2, player.getCurrentPosition().y - ((float)GetScreenHeight() / 2) / camera.zoom, 216 * this->player_ui.getScale(), 48 * this->player_ui.getScale() }, Vector2{ 0, 0 }, 0, WHITE);
    DrawText(TextFormat("%i", player.getMoney()), player.getCurrentPosition().x + 5, (player.getCurrentPosition().y - ((float)GetScreenHeight() / 2) / camera.zoom) + 24, 4, BLACK);
    EndMode2D();
}

void WoodlandScene::parseLevelBackgroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map) {

    Vector2 vec = { 0, 0 };
    Rectangle rec = { 0, 0, level_map["tilewidth"], level_map["tileheight"] };

    for (auto const& layer : level_map["layers"]) {
        if (layer["type"] == "tilelayer" && layer["visible"]) {
            for (auto const& tileId : layer["data"]) {
                if (layer["id"] < 8 ) {
                    if (tileId != 0) {
                        rec.x = (float)((int)tileId - 1 % (int)tileset_description["columns"]) * (float)level_map["tilewidth"];
                        rec.y = (float)floor((float)tileId / (float)tileset_description["columns"]) * (float)level_map["tilewidth"];
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

                vec.x += (float)level_map["tilewidth"];
                if (vec.x >= (float)layer["width"] * (float)level_map["tilewidth"]) {
                    vec.x = 0;
                    vec.y += (float)level_map["tileheight"];
                }
                if (vec.y >= (float)layer["height"] * (float)level_map["tileheight"]) {
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
                        rec.x = (float)((int)tileId - 1 % (int)tileset_description["columns"]) * (float)level_map["tilewidth"];
                        rec.y = (float)floor((float)tileId / (float)tileset_description["columns"]) * (float)level_map["tilewidth"];
                        if (tileId % 32 == 0) {
                            rec.y -= 16;
                        }

                        std::shared_ptr<LevelTile> tile = std::make_shared<LevelTile>();
                        tile->position_on_screen = vec;
                        tile->spritesheet_position = rec;
                        this->woodland_tiles_foreground_vector.push_back(tile);
                    }
                }

                vec.x += (float)level_map["tilewidth"];
                if (vec.x >= (float)layer["width"] * (float)level_map["tilewidth"]) {
                    vec.x = 0;
                    vec.y += (float)level_map["tileheight"];
                }
                if (vec.y >= (float)layer["height"] * (float)level_map["tileheight"]) {
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

                vec.x += (float)level_map["tilewidth"];
                if (vec.x >= (float)layer["width"] * (float)level_map["tilewidth"]) {
                    vec.x = 0;
                    vec.y += (float)level_map["tileheight"];
                }
                if (vec.y >= (float)layer["height"] * (float)level_map["tileheight"]) {
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
}

//----------------------------Setter----------------------------------

SceneType WoodlandScene::setNextScene(Player& player, bool& exitWindowRequested) {
	if (IsKeyPressed(KEY_ENTER)) {
        player.setCurrentPosition(2048, 2048);
		return MAIN_MENU_SCENE;
	}
	return WOODLAND_SCENE;
}