#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/ui.h"

class Button final : public UI {
public:

	Button(Texture2D spritesheet, Rectangle spritesheet_source, float spritesheet_destination_x, float spritesheet_destination_y, float scale, std::string button_text, ButtonType button_type);
	Button(Texture2D spritesheet, float spritesheet_source_x, float spritesheet_source_y, float spritesheet_source_width, float spritesheet_source_height, float spritesheet_destination_x, float spritesheet_destination_y, float scale, std::string button_text, ButtonType button_type);

	~Button();

	void update() override;
	void draw() override;

	void setScale(float scale);
	void setIsButtonAction(bool isButtonAction);
	void setTextPosition(Vector2 text_position);
	void setTextPosition(float text_position_x, float text_position_y);
	void setButtonBounds(Rectangle button_bounds);
	void setButtonBounds(float pos_x, float pos_y, float width, float height);
	void setCurrentState(ButtonState current_state);
	void setButtonType(ButtonType button_type);
	void setButtonText(std::string button_text);

	float getScale();
	bool getIsButtonAction();
	Vector2 getTextPosition();
	Rectangle getButtonBounds();
	ButtonState getCurrentState();
	ButtonType getButtonType();
	std::string getButtonText();

private:

	float scale;
	bool isButtonAction;
	Vector2 text_position;
	Rectangle button_bounds;
	ButtonState current_state;
	ButtonType button_type;
	std::string button_text;

protected:



};