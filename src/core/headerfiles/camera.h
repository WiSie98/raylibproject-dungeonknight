#pragma once

#include "header.h"
#include "../../ui/headerfiles/ui_player_bar.h"
#include "../../actors/headerfiles/actor_player.h"

class PlayerCamera {
public:

	PlayerCamera(Player& player);

	~PlayerCamera();

	void update(Player& player);
	void draw(Player& player);

	void setTarget(Vector2 target);
	void setOffset(Vector2 offset);
	void setOffset(float x, float y);
	void setZoom(float zoom);
	void setRotation(float rotation);
	void setMainHUDTexture(Texture2D main_hud_texture);

	Camera2D getPlayerCamera();
	Texture2D getMainHUDTexture();

private:

	Camera2D playerCamera;

	Texture2D main_hud_texture;
	
	GameInterface main_hud;

protected:



};