#pragma once

#include "..\..\core\headerfiles\header.h"
#include "..\..\core\headerfiles\scene.h"

class WoodlandScene final : public Scene {
public:

	WoodlandScene();

	~WoodlandScene();

	void update(Player& player, Camera2D& camera) override;
	void draw(Player& player, Camera2D& camera) override;

	void parseLevelBackgroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map);
	void parseLevelForegroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map);
	void parseLevelCollider(nlohmann::json& tileset_description, nlohmann::json& level_map);

	void detectCollision(Player& player);

	SceneType setNextScene(Player& player) override;

private:

	Texture2D tile_atlas_texture;
	LevelTile woodland_tiles;

	std::vector<std::shared_ptr<LevelTile>> woodland_tiles_background_vector;
	std::vector<std::shared_ptr<LevelTile>> woodland_tiles_foreground_vector;
	std::vector<std::shared_ptr<ColliderTile>> woodland_tiles_collider_vector;

};