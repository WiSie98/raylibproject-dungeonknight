#pragma once

#include "header.h"

#include "..\..\actors\headerfiles\actor_player.h"

class Scene {
public:

	void setSceneType(SceneType scene_type);
	SceneType getSceneType();

	virtual void update(Player& player, Camera2D& camera) = 0;
	virtual void draw(Player& player, Camera2D& camera) = 0;

	virtual SceneType setNextScene(Player& player) = 0;

private:



protected:

	SceneType scene_type;

};