#pragma once

#include "..\..\core\headerfiles\header.h"
#include "..\..\core\headerfiles\scene.h"

class MainMenuScene final : public Scene {
public:

	MainMenuScene();

	~MainMenuScene();

	void update() override;
	void draw() override;
	SceneType setNextScene() override;

private:
	

};