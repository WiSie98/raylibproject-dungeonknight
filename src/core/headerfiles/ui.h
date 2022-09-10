#pragma once

#include "header.h"

class UI {
public:

	virtual void update() = 0;
	virtual void draw() = 0;

	void setScale(float scale);
	void setOrigin(Vector2 on_screen_position);
	void setOrigin(float pos_x, float pos_y);
	void setSpritesheetSource(Rectangle spritesheet_source);
	void setSpritesheetSource(float pos_x, float pos_y, float width, float height);
	void setSpritesheetDestination(Rectangle spritesheet_sorigin);
	void setSpritesheetDestination(float pos_x, float pos_y, float width, float height);
	void setSpritesheet(Texture2D spritesheet);

	float getScale();
	Vector2 getOrigin();
	Rectangle getSpritesheetSource();
	Rectangle getSpritesheetDestination();
	Texture2D getSpritesheet();

private:



protected:

	float scale;
	Vector2 origin;
	Rectangle spritesheet_source;
	Rectangle spritesheet_destination;
	Texture2D spritesheet;

};