#include "headerfiles/ui.h"

//----------------------------Setter----------------------------------

void UI::setScale(float scale) {
	this->scale = scale;
}

void UI::setOrigin(Vector2 on_screen_position) {
	this->origin = on_screen_position;
}

void UI::setOrigin(float pos_x, float pos_y) {
	this->origin.x = pos_x;
	this->origin.y = pos_y;
}

void UI::setSpritesheetSource(Rectangle spritesheet_source) {
	this->spritesheet_source = spritesheet_source;
}

void UI::setSpritesheetSource(float pos_x, float pos_y, float width, float height) {
	this->spritesheet_source.x = pos_x;
	this->spritesheet_source.y = pos_y;
	this->spritesheet_source.width = width;
	this->spritesheet_source.height = height;
}

void UI::setSpritesheetDestination(Rectangle spritesheet_destination) {
	this->spritesheet_destination = spritesheet_destination;
}

void UI::setSpritesheetDestination(float pos_x, float pos_y, float width, float height) {
	this->spritesheet_destination.x = pos_x;
	this->spritesheet_destination.y = pos_y;
	this->spritesheet_destination.width = width;
	this->spritesheet_destination.height = height;
}

void UI::setSpritesheet(Texture2D spritesheet) {
	this->spritesheet = spritesheet;
}

//----------------------------Getter----------------------------------

float UI::getScale() {
	return this->scale;
}

Vector2 UI::getOrigin() {
	return this->origin;
}

Rectangle UI::getSpritesheetSource() {
	return this->spritesheet_source;
}

Rectangle UI::getSpritesheetDestination() {
	return this->spritesheet_destination;
}

Texture2D UI::getSpritesheet() {
	return this->spritesheet;
}