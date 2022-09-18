#pragma once

#include "../../core/headerfiles/header.h"

#include "start_scene.h"
#include "main_menu_scene.h"
#include "woodland_scene.h"

void GenerateScenes(std::vector<std::shared_ptr<Scene>>* scenes) {
	std::shared_ptr<StartScene> startScene = std::make_shared<StartScene>();
	scenes->push_back(startScene);

	std::shared_ptr<MainMenuScene> mainMenuScene = std::make_shared<MainMenuScene>();
	scenes->push_back(mainMenuScene);

	std::shared_ptr<WoodlandScene> woodlandScene = std::make_shared<WoodlandScene>();
	scenes->push_back(woodlandScene);
}