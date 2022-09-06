#pragma once

#include "header.h"

class Animation {
public:

	Animation(int frame_speed, float frame_width, float frame_height, Texture2D& spritesheet);
	
	~Animation();

	void update(AnimationState state);
	void draw(Vector2& position);

	void drawStanding(Vector2& position);
	void drawWalking(Vector2& position);
	void drawAttaking(Vector2& position);
	void drawDamage(Vector2& position);
	void drawDying(Vector2& position);
	void drawSpawning(Vector2& position);

	void setFrameSpeed(int frame_speed);
	void setFrameCounter(int frame_counter);
	void setCurrentFrame(int current_frame);
	void setSpritesheet(Texture2D spritesheet);
	void setSpritesheetRectangle(float x, float y, float width, float height);
	void setSpritesheetRectangle(Rectangle spritesheet_rectangle);
	void setState(AnimationState state);

	int getFrameSpeed();
	int getFrameCounter();
	int getCurrentFrame();
	Texture2D getSpritesheet();
	Rectangle getSpritesheetRectangle();
	AnimationState getState();

private:

	int frame_speed;
	int frame_counter;
	int current_frame;
	Texture2D spritesheet;
	Rectangle spritesheet_rectangle;
	AnimationState state;

protected:



};