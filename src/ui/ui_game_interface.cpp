#include "headerfiles/ui_game_interface.h"

GameInterface::GameInterface(Texture2D spritesheet, float spritesheet_source_x, float spritesheet_source_y, float spritesheet_source_width, float spritesheet_source_height, float spritesheet_destination_x, float spritesheet_destination_y, float scale) {
	setSpritesheet(spritesheet);
	setOrigin(0, 0);
	setSpritesheetSource(spritesheet_source_x, spritesheet_source_y, spritesheet_source_width, spritesheet_source_height);
	setSpritesheetDestination(spritesheet_destination_x, spritesheet_destination_y, spritesheet_source.width * scale, spritesheet_source.height * scale);
	setScale(scale);
}

GameInterface::~GameInterface() {

}

void GameInterface::update() {
	this->healthbar_width = (this->spritesheet_destination.width / this->max_health) * this->health;
	this->shieldbar_width = ((this->spritesheet_destination.width - (12 * this->scale)) / this->max_shield) * this->shield;
	this->staminabar_width = ((this->spritesheet_destination.width - (26 * this->scale)) / this->max_stamina) * this->stamina;
}

void GameInterface::draw() {
	//Draw Background UI
	DrawTexturePro(this->spritesheet, Rectangle{this->spritesheet_source.x, this->spritesheet_source.y + 24, this->spritesheet_source.width, this->spritesheet_source.height}, this->spritesheet_destination, this->origin, 0.0f, WHITE);

	//Draw Player Healthbar
	DrawTexturePro(this->spritesheet, Rectangle{this->spritesheet_source.x + 72, this->spritesheet_source.y + 26, 1.0f, 6.0f}, Rectangle{ this->spritesheet_destination.x, this->spritesheet_destination.y + (2 * this->scale), this->healthbar_width, 6.0f * this->scale }, this->origin, 0.0f, WHITE);

	//Draw Player Shieldbar
	DrawTexturePro(this->spritesheet, Rectangle{this->spritesheet_source.x + 72, this->spritesheet_source.y + 33, 1.0f, 6.0f}, Rectangle{ this->spritesheet_destination.x, this->spritesheet_destination.y + (8 * this->scale), this->shieldbar_width, 6.0f * this->scale }, this->origin, 0.0f, WHITE);

	//Draw Player Staminabar
	DrawTexturePro(this->spritesheet, Rectangle{this->spritesheet_source.x + 72, this->spritesheet_source.y + 40, 1.0f, 5.0f}, Rectangle{ this->spritesheet_destination.x, this->spritesheet_destination.y + (16 * this->scale), this->staminabar_width, 6.0f * this->scale }, this->origin, 0.0f, WHITE);

	//Draw Foreground UI
	DrawTexturePro(this->spritesheet, this->spritesheet_source, this->spritesheet_destination, this->origin, 0, WHITE);
}

//----------------------------Setter----------------------------------

void GameInterface::setHealth(float health) {
	this->health = health;
}

void GameInterface::setMaxHealth(float max_health) {
	this->max_health = max_health;
}

void GameInterface::setShield(float shield) {
	this->shield = shield;
}

void GameInterface::setMaxShield(float max_shield) {
	this->max_shield = max_shield;
}

void GameInterface::setStamina(float stamina) {
	this->stamina = stamina;
}

void GameInterface::setMaxStamina(float max_stamina) {
	this->max_stamina = max_stamina;
}

//----------------------------Getter----------------------------------


