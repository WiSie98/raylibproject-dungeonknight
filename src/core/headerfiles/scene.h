#pragma once

#include "header.h"

#include "../../actors/headerfiles/actor_player.h"
#include "camera.h"

class Scene {
public:

	void setSceneType(SceneType scene_type);
	SceneType getSceneType();

	virtual void update(Player& player, PlayerCamera& camera) = 0;
	virtual void draw(Player& player, PlayerCamera& camera) = 0;

	virtual SceneType setNextScene(Player& player, bool& exitWindowRequested) = 0;

private:



protected:

	SceneType scene_type;

};