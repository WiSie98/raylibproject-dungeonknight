#pragma once

#include "..\..\core\headerfiles\header.h"
#include "..\..\core\headerfiles\scene.h"
#include "..\..\ui\headerfiles\ui_button.h"

class MainMenuScene final : public Scene {
public:

	MainMenuScene();

	~MainMenuScene();

	void update(Player& player, Camera2D& camera) override;
	void draw(Player& player, Camera2D& camera) override;
	SceneType setNextScene(Player& player, bool& exitWindowRequested) override;

private:
	
	Texture2D logo;
	Texture2D ui_buttons;

	std::vector<Button> button_vector;
};