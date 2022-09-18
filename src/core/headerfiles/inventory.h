#pragma once

#include "header.h"
#include "../../core/headerfiles/item_base.h"
#include "../../ui/headerfiles/ui_inventory.h"

class Inventory {
public:

	Inventory();

	~Inventory();

	void update();
	void draw();

	void checkDedicatedWeaponSlotPressed(Vector2 target);
	void checkDedicatedItemSlotPressed(Vector2 target);
	void checkInventorySlotPressed(std::vector<std::shared_ptr<InventoryHitbox>>& hitbox_vector, InventoryWindow current_window, Vector2 target);

	void addDedicatedWeapon(int slot_num, std::shared_ptr<ItemBase>& weapon);
	void addDedicatedItem(int slot_num, std::shared_ptr<ItemBase>& item);
	void removeDedicatedWeapon(int slot_num);
	void removeDedicatedItem(int slot_num);
	std::shared_ptr<ItemBase> getDedicatedWeapon(int slot_num);
	std::shared_ptr<ItemBase> getDedicatedItem(int slot_num);

	void addItemToInventory(std::shared_ptr<ItemBase> item);
	void removeItemFromInventory(int slot);
	std::shared_ptr<ItemBase> getItemFromInventory(int slot);

	std::vector<std::shared_ptr<ItemBase>>& getInventoryVector();
	std::vector<std::shared_ptr<ItemBase>>& getStorageVector();
	std::vector<std::shared_ptr<ItemBase>>& getLostInventoryVector();

private:
	
	std::shared_ptr<ItemBase> dedicated_weapon_slot1;
	std::shared_ptr<ItemBase> dedicated_weapon_slot2;

	std::shared_ptr<ItemBase> dedicated_item_slot1;
	std::shared_ptr<ItemBase> dedicated_item_slot2;
	std::shared_ptr<ItemBase> dedicated_item_slot3;
	std::shared_ptr<ItemBase> dedicated_item_slot4;
	std::shared_ptr<ItemBase> dedicated_item_slot5;

	std::vector<std::shared_ptr<ItemBase>> inventory_weapons_vector;
	std::vector<std::shared_ptr<ItemBase>> inventory_items_vector;
	std::vector<std::shared_ptr<ItemBase>> storage_weapons_vector;
	std::vector<std::shared_ptr<ItemBase>> storage_items_vector;
	std::vector<std::shared_ptr<ItemBase>> lost_inventory_vector;

protected:



};