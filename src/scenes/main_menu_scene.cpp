#include "headerfiles/main_menu_scene.h"

MainMenuScene::MainMenuScene() {
	setSceneType(MAIN_MENU_SCENE);
	this->logo = LoadTexture("./assets/graphics/sprites/dk_spt_mainlogo.png");
	this->ui_buttons = LoadTexture("./assets/graphics/spritesheets/dk_sptsht_ui_buttons.png");

	Button start_button(this->ui_buttons, 72, 0, 72, 24, (GetScreenWidth() / 2) - ((72 * 4) / 2), (GetScreenHeight() / 2), 4, "Start", START_BUTTON);
	start_button.setSpritesheet(this->ui_buttons);
	this->button_vector.push_back(start_button);

	Button resume_button(this->ui_buttons, 72, 0, 72, 24, (GetScreenWidth() / 2) - ((72 * 4) / 2), (GetScreenHeight() / 2) + 100, 4, "Resume", RESUME_BUTTON);
	resume_button.setSpritesheet(this->ui_buttons);
	this->button_vector.push_back(resume_button);

	Button options_button(this->ui_buttons, 72, 0, 72, 24, (GetScreenWidth() / 2) - ((72 * 4) / 2), (GetScreenHeight() / 2) + 200, 4, "Options", OPTIONS_BUTTON);
	options_button.setSpritesheet(this->ui_buttons);
	this->button_vector.push_back(options_button);

	Button exit_button(this->ui_buttons, 72, 0, 72, 24, (GetScreenWidth() / 2) - ((72 * 4) / 2), (GetScreenHeight() / 2) + 300, 4, "Exit", EXIT_BUTTON);
	exit_button.setSpritesheet(this->ui_buttons);
	this->button_vector.push_back(exit_button);
}

MainMenuScene::~MainMenuScene() {
	UnloadTexture(this->logo);
	UnloadTexture(this->ui_buttons);
}

void MainMenuScene::update(Player& player, PlayerCamera& camera) {
	for (int i = 0; i < this->button_vector.size(); i++) {
		this->button_vector[i].update();
	}
}

void MainMenuScene::draw(Player& player, PlayerCamera& camera) {
	DrawTexturePro(this->logo, Rectangle{ 0.0f, 0.0f, static_cast<float>(this->logo.width), static_cast<float>(this->logo.height) }, Rectangle{ static_cast<float>((GetScreenWidth() / 2)), static_cast<float>((GetScreenHeight() / 3)), static_cast<float>(this->logo.width * 2), static_cast<float>(this->logo.height * 2) }, Vector2{ static_cast<float>(this->logo.width), static_cast<float>(this->logo.height) }, 0, WHITE);
	for (int i = 0; i < this->button_vector.size(); i++) {
		this->button_vector[i].draw();
	}
}

SceneType MainMenuScene::setNextScene(Player& player, bool& exitWindowRequested) {

	for (int i = 0; i < this->button_vector.size(); i++) {
		if (this->button_vector[i].getIsButtonAction()) {
			if (this->button_vector[i].getButtonType() == START_BUTTON) {
				player.setCurrentPosition(5936, 2960);
				return WOODLAND_SCENE;
			}
			else if (this->button_vector[i].getButtonType() == EXIT_BUTTON) {
				exitWindowRequested = true;
			}
		}
	}
	if (IsKeyPressed(KEY_BACKSPACE)) {
		return START_SCENE;
	}
	return MAIN_MENU_SCENE;
}