#pragma once

#include "../../core/headerfiles/header.h"

#include "../../core/headerfiles/actor_base.h"
#include "../../core/headerfiles/inventory.h"
#include "../../core/headerfiles/item_base.h"
#include "../../core/headerfiles/animation.h"

class Player final : public ActorBase {
public:

	Player(float health, float shield, float stamina, float position_x, float position_y, Texture2D texture);

	~Player() {}

	void update() override;
	void draw() override;

	void setMoney(int money);
	void setShield(float shield);
	void setMaxShield(float max_shield);
	void setStamina(float stamina);
	void setMaxStamina(float max_stamina);

	int getMoney();
	float getShield();
	float getMaxShield();
	float getStamina();
	float getMaxStamina();
	Inventory& getInventory();

private:

	int money;
	float shield;
	float max_shield;
	float stamina;
	float max_stamina;
	bool isKeyPressed;

	Animation animation;
	Inventory inventory;

	void playerMovement();

protected:



};