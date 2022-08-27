#include "headerfiles/main_menu_scene.h"

MainMenuScene::MainMenuScene() {
	setSceneType(MAIN_MENU_SCENE);
}

MainMenuScene::~MainMenuScene() {}

void MainMenuScene::update() {

}

void MainMenuScene::draw() {
	DrawText("Menu scene", 10, 10, 30, LIGHTGRAY);
}

SceneType MainMenuScene::setNextScene() {
	if (IsKeyPressed(KEY_ENTER)) {
		return START_SCENE;
	}
	return MAIN_MENU_SCENE;
}