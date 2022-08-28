#pragma once

#include "header.h"
#include "scene.h"

class SceneManager final {
public:

	SceneManager();

	virtual ~SceneManager() = default;

	void switchToScene(SceneType scene_type);

	void update(Player& player, Camera2D& camera);
	void draw(Player& player, Camera2D& camera);

	std::shared_ptr<Scene> getCurrentScene();
	std::vector<std::shared_ptr<Scene>>& getScenes();

private:

	std::shared_ptr<Scene> current_scene;
	std::vector<std::shared_ptr<Scene>> scenes;

};