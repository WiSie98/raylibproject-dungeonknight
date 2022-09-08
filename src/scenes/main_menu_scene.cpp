#include "headerfiles/main_menu_scene.h"

MainMenuScene::MainMenuScene() : start_button(this->ui_buttons, 72, 0, 72, 24, (GetScreenWidth() / 2) - (72 / 2), (GetScreenHeight() / 2) + 100, 2, "Start") {
	setSceneType(MAIN_MENU_SCENE);
	this->logo = LoadTexture("./assets/graphics/sprites/dk_spt_mainlogo.png");
	this->ui_buttons = LoadTexture("./assets/graphics/spritesheets/dk_sptsht_ui_buttons.png");
	this->start_button.setSpritesheet(this->ui_buttons);
}

MainMenuScene::~MainMenuScene() {
	UnloadTexture(this->logo);
	UnloadTexture(this->ui_buttons);
}

void MainMenuScene::update(Player& player, Camera2D& camera) {
	this->start_button.update();
}

void MainMenuScene::draw(Player& player, Camera2D& camera) {
	DrawTexture(logo, (GetScreenWidth() / 2) - (logo.width / 2), (GetScreenHeight() / 2) - (logo.height / 2), WHITE);
	DrawText("Press ENTER to Start", (GetScreenWidth() / 2) - 120, (GetScreenHeight() / 2) + 60, 20, BLACK);
	this->start_button.draw();
}

SceneType MainMenuScene::setNextScene(Player& player) {
	if (IsKeyPressed(KEY_BACKSPACE)) {
		return START_SCENE;
	}
	else if (IsKeyPressed(KEY_ENTER)) {
		player.setCurrentPosition(2048, 2048);
		return WOODLAND_SCENE;
	}

	return MAIN_MENU_SCENE;
}