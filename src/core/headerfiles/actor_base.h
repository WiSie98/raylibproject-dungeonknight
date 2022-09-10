#pragma once

#include "header.h"

class ActorBase {
public:

	void setHealth(float health);
	void setMaxHealth(float max_health);
	void setTraverseSpeed(float traverse_speed);
	void setCurrentPosition(Vector2 position);
	void setCurrentPosition(float pos_x, float pos_y);
	void setLastPosition(Vector2 position);
	void setLastPosition(float pos_x, float pos_y);
	void setTexture(Texture2D texture);

	float getHealth();
	float getMaxHealth();
	float getTraverseSpeed();
	Vector2 getCurrentPosition();
	Vector2 getLastPosition();
	Texture2D getTexture();

	virtual void update() = 0;
	virtual void draw() = 0;

private:



protected:

	float health;
	float max_health;
	float traverse_speed;
	Vector2 current_position;
	Vector2 last_position;
	Texture2D texture;

};