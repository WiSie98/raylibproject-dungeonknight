#include "headerfiles/woodland_scene.h"

WoodlandScene::WoodlandScene() {
	setSceneType(WOODLAND_SCENE);

    std::ifstream tileset_description_file("./assets/level/dk_ts_woodlandbiom.json");
    nlohmann::json tileset_description = nlohmann::json::parse(tileset_description_file);
    tileset_description_file.close();

    std::ifstream level_map_file("./assets/level/dk_lv_woodlandbiom.json");
    nlohmann::json level_map = nlohmann::json::parse(level_map_file);
    level_map_file.close();

    this->tile_atlas_texture = LoadTexture(("./assets/graphics/tilesets/" + tileset_description["image"].get<std::string>()).c_str());

	parseLevelBackgroundTiles(this->woodland_tiles_background_vector, tileset_description, level_map);
    parseLevelForegroundTiles(this->woodland_tiles_foreground_vector, tileset_description, level_map);
    parseLevelCollider( this->woodland_tiles_collider_vector, tileset_description, level_map);
}

WoodlandScene::~WoodlandScene() {
	UnloadTexture(this->tile_atlas_texture);
}

//---------------------------Functions---------------------------------

void WoodlandScene::update() {

}

void WoodlandScene::draw() {
	//DrawText("Woodland scene", 10, 10, 30, LIGHTGRAY);
    for (const auto& tile : this->woodland_tiles_background_vector) {
        DrawTextureRec(this->tile_atlas_texture, tile->spritesheet_position, tile->position_on_screen, WHITE);
    }

    //Everything that is not part of the map schould be rendered here.


    for (const auto& tile : this->woodland_tiles_foreground_vector) {
        DrawTextureRec(this->tile_atlas_texture, tile->spritesheet_position, tile->position_on_screen, WHITE);
    }
}

void WoodlandScene::parseLevelBackgroundTiles(std::vector<std::shared_ptr<LevelTile>>& woodland_tiles_vector, nlohmann::json& tileset_description, nlohmann::json& level_map) {

    Vector2 vec = { 0, 0 };
    Rectangle rec = { 0, 0, level_map["tilewidth"], level_map["tileheight"] };

    for (auto const& layer : level_map["layers"]) {
        if (layer["type"] == "tilelayer" && layer["visible"]) {
            for (auto const& tileId : layer["data"]) {
                if ( 8 > layer["id"] > 0 ) {
                    if (tileId != 0) {
                        rec.x = 0;
                        rec.x = (float)((int)tileId - 1 % (int)tileset_description["columns"]) * (float)level_map["tilewidth"];
                        rec.y = 0;
                        rec.y = (float)floor((float)tileId / (float)tileset_description["columns"]) * (float)level_map["tilewidth"];

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

void WoodlandScene::parseLevelForegroundTiles(std::vector<std::shared_ptr<LevelTile>>& woodland_tiles_vector, nlohmann::json& tileset_description, nlohmann::json& level_map) {
    Vector2 vec = { 0, 0 };
    Rectangle rec = { 0, 0, level_map["tilewidth"], level_map["tileheight"] };

    for (auto const& layer : level_map["layers"]) {
        if (layer["type"] == "tilelayer" && layer["visible"]) {
            for (auto const& tileId : layer["data"]) {
                if (layer["id"] > 7 || layer["id"] == 1) {
                    if (tileId != 0) {
                        rec.x = 0;
                        rec.x = (float)((int)tileId - 1 % (int)tileset_description["columns"]) * (float)level_map["tilewidth"];
                        rec.y = 0;
                        rec.y = (float)floor((float)tileId / (float)tileset_description["columns"]) * (float)level_map["tilewidth"];

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

void WoodlandScene::parseLevelCollider(std::vector<std::shared_ptr<ColliderTile>>& woodland_tiles_collider_vector, nlohmann::json& tileset_description, nlohmann::json& level_map) {
    //Implementation of the collider vector parser.
}

//----------------------------Setter----------------------------------

SceneType WoodlandScene::setNextScene() {
	if (IsKeyPressed(KEY_ENTER)) {
		return MAIN_MENU_SCENE;
	}
	return WOODLAND_SCENE;
}