#include "headerfiles/ui_button.h"

Button::Button(Texture2D spritesheet, Rectangle spritesheet_source, float spritesheet_destination_x, float spritesheet_destination_y, float scale, std::string button_text) {
	setSpritesheet(spritesheet);
	setOrigin(spritesheet_source.width, spritesheet_source.height);
	setSpritesheetSource(spritesheet_source);
	setSpritesheetDestination(spritesheet_destination_x, spritesheet_destination_y, spritesheet_source.width * scale, spritesheet_source.height * scale);
	setIsButtonAction(false);
	setCurrentState(IDLE);
	setButtonBounds(spritesheet_destination_x - ((spritesheet_source.width * scale) / scale), spritesheet_destination_y - ((spritesheet_source.height * scale) / scale), spritesheet_source.width * scale, spritesheet_source.height * scale);
	setButtonText(button_text);
	setTextPosition(spritesheet_destination_x, spritesheet_destination_y);
}

Button::Button(Texture2D spritesheet, float spritesheet_source_x, float spritesheet_source_y, float spritesheet_source_width, float spritesheet_source_height, float spritesheet_destination_x, float spritesheet_destination_y, float scale, std::string button_text) {
	setSpritesheet(spritesheet);
	setOrigin(spritesheet_source_width, spritesheet_source_height);
	setSpritesheetSource(spritesheet_source_x, spritesheet_source_y, spritesheet_source_width, spritesheet_source_height);
	setSpritesheetDestination(spritesheet_destination_x, spritesheet_destination_y, spritesheet_source_width * scale, spritesheet_source_height * scale);
	setIsButtonAction(false);
	setCurrentState(IDLE);
	setButtonBounds(spritesheet_destination_x - ((spritesheet_source_width * scale) / scale), spritesheet_destination_y - ((spritesheet_source_height * scale) / scale), spritesheet_source_width * scale, spritesheet_source_height * scale);
	setButtonText(button_text);
	setTextPosition(spritesheet_destination_x, spritesheet_destination_y);
}

Button::~Button() {}

void Button::update() {
	this->isButtonAction = false;

	if (CheckCollisionPointRec(GetMousePosition(), getButtonBounds())) {
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			this->current_state = PRESSED;
		}
		else {
			this->current_state = ACTIVE;
		}
		
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			this->isButtonAction = true;
		}
	}
	else {
		this->current_state = IDLE;
	}

	if (this->isButtonAction) {
		//TODO: Any desired action like play Sound.
	}
	this->spritesheet_source.y = (this->current_state * this->spritesheet_source.height);
}

void Button::draw() {
	DrawTexturePro(this->spritesheet, this->spritesheet_source, this->spritesheet_destination, this->origin, 0, WHITE);
	if (this->current_state == PRESSED) {
		DrawTextPro(GetFontDefault(), this->button_text.c_str(), this->text_position, { (float)((this->button_text.length() * 23) / 4), 11 - 2}, 0, 20, 2, BLACK);
	}
	else {
		DrawTextPro(GetFontDefault(), this->button_text.c_str(), this->text_position, { (float)((this->button_text.length() * 23) / 4), 11 }, 0, 20, 2, BLACK);
	}
}

//----------------------------Setter----------------------------------

void Button::setIsButtonAction(bool isButtonAction) {
	this->isButtonAction = isButtonAction;
}

void Button::setTextPosition(Vector2 text_position) {
	this->text_position = text_position;
}

void Button::setTextPosition(float text_position_x, float text_position_y) {
	this->text_position.x = text_position_x;
	this->text_position.y = text_position_y;
}

void Button::setButtonBounds(Rectangle button_bounds) {
	this->button_bounds = button_bounds;
}

void Button::setButtonBounds(float pos_x, float pos_y, float width, float height) {
	this->button_bounds.x = pos_x;
	this->button_bounds.y = pos_y;
	this->button_bounds.width = width;
	this->button_bounds.height = height;
}

void Button::setCurrentState(ButtonState current_state) {
	this->current_state = current_state;
}

void Button::setButtonText(std::string button_text) {
	this->button_text = button_text;
}

//----------------------------Getter----------------------------------

bool Button::getIsButtonAction() {
	return this->isButtonAction;
}

Vector2 Button::getTextPosition() {
	return this->text_position;
}

Rectangle Button::getButtonBounds() {
	return this->button_bounds;
}

ButtonState Button::getCurrentState() {
	return this->current_state;
}

std::string Button::getButtonText() {
	return this->button_text;
}