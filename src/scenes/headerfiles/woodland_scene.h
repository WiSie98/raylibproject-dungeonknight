#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/scene.h"
#include "../../actors/headerfiles/actor_enemy.h"

class WoodlandScene final : public Scene {
public:

	WoodlandScene();

	~WoodlandScene();

	void update(Player& player, PlayerCamera& camera) override;
	void draw(Player& player, PlayerCamera& camera) override;

	void drawBackground(PlayerCamera& camera);
	void drawForeground(PlayerCamera& camera);

	void parseLevelBackgroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map);
	void parseLevelForegroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map);
	void parseLevelCollider(nlohmann::json& tileset_description, nlohmann::json& level_map);

	void detectCollision(Player& player);

	SceneType setNextScene(Player& player, bool& exitWindowRequested) override;

private:

	Texture2D player_ui_texture;
	Texture2D tile_atlas_texture;
	LevelTile woodland_tiles;
	Enemy enemy;

	std::vector<std::shared_ptr<LevelTile>> woodland_tiles_background_vector;
	std::vector<std::shared_ptr<LevelTile>> woodland_tiles_foreground_vector;
	std::vector<std::shared_ptr<ColliderTile>> woodland_tiles_collider_vector;

};