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

	void generateEnemies();
	void detectCollision(Player& player, PlayerCamera& camera);

	SceneType setNextScene(Player& player, bool& exitWindowRequested) override;

private:

	Texture2D tile_atlas_texture;
	LevelTile woodland_tiles;

	Texture2D purple_slime_texture;
	Texture2D blue_slime_texture;
	Texture2D falcon_texture;
	Texture2D possesed_bear_texture;
	Texture2D skeleton_texture;
	Texture2D stone_golem_texture;
	Texture2D wild_boar_texture;
	Texture2D wolf_texture;

	std::vector<std::shared_ptr<LevelTile>> woodland_tiles_background_vector;
	std::vector<std::shared_ptr<LevelTile>> woodland_tiles_foreground_vector;
	std::vector<std::shared_ptr<ColliderTile>> woodland_tiles_collider_vector;
	std::vector<Enemy> enemies_vector;

};