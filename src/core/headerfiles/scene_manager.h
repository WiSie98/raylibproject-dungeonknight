#pragma once

#include "header.h"
#include "scene.h"

class SceneManager final {
public:

	std::vector<std::shared_ptr<Scene>> scenes;

	SceneManager(std::shared_ptr<Scene>);

	virtual ~SceneManager() = default;

	void switchToScene(SceneType scene_type);

	void update();
	void draw();

	std::shared_ptr<Scene> getCurrentScene();

private:

	std::shared_ptr<Scene> current_scene;

};