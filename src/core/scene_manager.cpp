#include "headerfiles/scene_manager.h"

SceneManager::SceneManager(std::shared_ptr<Scene> scene) : current_scene(scene) {}

//---------------------------Functions---------------------------------

void SceneManager::switchToScene(SceneType scene_type) {
	for (const auto& scene : this->scenes) {
		if (scene->getSceneType() == scene_type) {
			this->current_scene = scene;
		}
	}
}

void SceneManager::update() {
	this->current_scene->update();
}

void SceneManager::draw() {
	this->current_scene->draw();
}

//----------------------------Getter----------------------------------

std::shared_ptr<Scene> SceneManager::getCurrentScene() {
	return this->current_scene;
}

std::vector<std::shared_ptr<Scene>>& SceneManager::getScenes() {
	return this->scenes;
}