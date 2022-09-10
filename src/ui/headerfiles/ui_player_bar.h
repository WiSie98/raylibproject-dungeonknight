#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/ui.h"

class GameInterface final : public UI {
public:

	GameInterface(Texture2D spritesheet, float spritesheet_source_x, float spritesheet_source_y, float spritesheet_source_width, float spritesheet_source_height, float spritesheet_destination_x, float spritesheet_destination_y, float scale);

	~GameInterface();

	void update() override;
	void draw() override;

	void setHealth(float health);
	void setMaxHealth(float max_health);
	void setShield(float shield);
	void setMaxShield(float max_shield);
	void setStamina(float stamina);
	void setMaxStamina(float max_stamina);

private:

	float health;
	float max_health;
	float shield;
	float max_shield;
	float stamina;
	float max_stamina;

	float healthbar_width;
	float shieldbar_width;
	float staminabar_width;

protected:



};