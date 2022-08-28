#include "headerfiles/main_menu_scene.h"

MainMenuScene::MainMenuScene() {
	setSceneType(MAIN_MENU_SCENE);
	this->logo = LoadTexture("./assets/graphics/sprites/dk_spt_mainlogo.png");
}

MainMenuScene::~MainMenuScene() {
	UnloadTexture(logo);
}

void MainMenuScene::update(Player& player, Camera2D& camera) {

}

void MainMenuScene::draw(Player& player, Camera2D& camera) {
	DrawTexture(logo, (GetScreenWidth() / 2) - (logo.width / 2), (GetScreenHeight() / 2) - (logo.height / 2), WHITE);
	DrawText("Press ENTER to Start", (GetScreenWidth() / 2) - 120, (GetScreenHeight() / 2) + 60, 20, BLACK);
}

SceneType MainMenuScene::setNextScene(Player& player) {
	if (IsKeyPressed(KEY_BACKSPACE)) {
		return START_SCENE;
	}
	else if (IsKeyPressed(KEY_ENTER)) {
		return WOODLAND_SCENE;
	}

	return MAIN_MENU_SCENE;
}