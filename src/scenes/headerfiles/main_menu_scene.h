#pragma once

#include "..\..\core\headerfiles\header.h"
#include "..\..\core\headerfiles\scene.h"

class MainMenuScene final : public Scene {
public:

	MainMenuScene();

	~MainMenuScene();

	void update(Player& player, Camera2D& camera) override;
	void draw(Player& player, Camera2D& camera) override;
	SceneType setNextScene(Player& player) override;

private:
	
	Texture2D logo;

};