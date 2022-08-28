#pragma once

#include "..\..\core\headerfiles\header.h"
#include "..\..\core\headerfiles\scene.h"

class WoodlandScene final : public Scene {
public:

	WoodlandScene();

	~WoodlandScene();

	void update() override;
	void draw() override;

	void parseLevelBackgroundTiles(std::vector<std::shared_ptr<LevelTile>>& woodland_tiles_vector, nlohmann::json& tileset_description, nlohmann::json& level_map);
	void parseLevelForegroundTiles(std::vector<std::shared_ptr<LevelTile>>& woodland_tiles_vector, nlohmann::json& tileset_description, nlohmann::json& level_map);
	void parseLevelCollider(std::vector<std::shared_ptr<ColliderTile>>& woodland_tiles_collider_vector, nlohmann::json& tileset_description, nlohmann::json& level_map);

	SceneType setNextScene() override;

private:

	Texture2D tile_atlas_texture;
	LevelTile woodland_tiles;

	std::vector<std::shared_ptr<LevelTile>> woodland_tiles_background_vector;
	std::vector<std::shared_ptr<LevelTile>> woodland_tiles_foreground_vector;
	std::vector<std::shared_ptr<ColliderTile>> woodland_tiles_collider_vector;

};