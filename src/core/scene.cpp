#include "headerfiles/scene.h"

void Scene::setSceneType(SceneType scene_type) {
	this->scene_type = scene_type;
}

SceneType Scene::getSceneType() {
	return this->scene_type;
}