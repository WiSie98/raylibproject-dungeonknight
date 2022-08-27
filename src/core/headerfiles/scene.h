#pragma once

#include "header.h"

class Scene {
public:

	void setSceneType(SceneType scene_type);
	SceneType getSceneType();

	virtual void update() = 0;
	virtual void draw() = 0;

	virtual SceneType setNextScene() = 0;

private:



protected:

	SceneType scene_type;

};