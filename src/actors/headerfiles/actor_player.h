#pragma once

#include "../../core/headerfiles/header.h"

#include "../../core/headerfiles/actor_base.h"
#include "../../core/headerfiles/container.h"
#include "../../core/headerfiles/item_base.h"
#include "../../core/headerfiles/animation.h"

class Player final : public ActorBase {
public:

	Player(float health, float shield, float stamina, float position_x, float position_y, Texture2D texture);

	~Player() {}

	void update() override;
	void draw() override;

	void removeDedicatedWeapon(int slot_num);
	void removeDedicatedItem(int slot_num);

	void setMoney(int money);
	void setShield(float shield);
	void setMaxShield(float max_shield);
	void setStamina(float stamina);
	void setMaxStamina(float max_stamina);
	void setDedicatedWeapon(int slot_num, std::shared_ptr<ItemBase> weapon);
	void setDedicatedItem(int slot_num, std::shared_ptr<ItemBase> item);

	int getMoney();
	float getShield();
	float getMaxShield();
	float getStamina();
	float getMaxStamina();
	std::shared_ptr<ItemBase> getDedicatedWeapon(int slot_num);
	std::shared_ptr<ItemBase> getDedicatedItem(int slot_num);

private:

	int money;
	float shield;
	float max_shield;
	float stamina;
	float max_stamina;
	bool isKeyPressed;

	Animation animation;

	std::shared_ptr<ItemBase> dedicated_weapon_slot1;
	std::shared_ptr<ItemBase> dedicated_weapon_slot2;

	std::shared_ptr<ItemBase> dedicated_item_slot1;
	std::shared_ptr<ItemBase> dedicated_item_slot2;
	std::shared_ptr<ItemBase> dedicated_item_slot3;
	std::shared_ptr<ItemBase> dedicated_item_slot4;
	std::shared_ptr<ItemBase> dedicated_item_slot5;

	void playerMovement();

	//Container<std::shared_ptr<ItemBase>> weapon_inventory;
	//Container<std::shared_ptr<ItemBase>> item_inventory;

protected:



};