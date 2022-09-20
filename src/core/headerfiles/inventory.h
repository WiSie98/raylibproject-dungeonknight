#pragma once

#include "header.h"
#include "../../core/headerfiles/item_base.h"
#include "../../items/headerfiles/item_weapon.h"
#include "../../items/headerfiles/item_consumable.h"
#include "../../items/headerfiles/item_usable.h"
#include "../../ui/headerfiles/ui_inventory.h"

class Inventory {
public:

	Inventory();

	~Inventory();

	void update();
	void draw();

	// Checks the Hitboxes of the specific Inventory Slots.
	void checkDedicatedWeaponSlotPressed(Vector2 target, InventoryUI& inventory_ui);
	void checkDedicatedItemSlotPressed(Vector2 target, InventoryUI& inventory_ui);
	void checkInventorySlotPressed(Vector2 target, InventoryUI& inventory_ui);

	// Dedicated Inventory Slots.
	void addDedicatedWeapon(int slot_num);
	void addDedicatedItem(int slot_num);
	void removeDedicatedWeapon(int slot_num);
	void removeDedicatedItem(int slot_num);
	std::shared_ptr<ItemBase> getDedicatedWeapon(int slot_num);
	std::shared_ptr<ItemBase> getDedicatedItem(int slot_num);

	// Normal Inventory.
	void addItemToInventory(std::shared_ptr<ItemBase> item);
	void removeWeaponFromInventory(int slot);
	void removeItemFromInventory(int slot);
	std::shared_ptr<ItemBase> getItemFromInventory(int slot);

	std::vector<std::shared_ptr<ItemBase>>& getInventoryVector();
	std::vector<std::shared_ptr<ItemBase>>& getStorageVector();
	std::vector<std::shared_ptr<ItemBase>>& getLostInventoryVector();
	std::vector<std::shared_ptr<ItemBase>>& getItemsVector();
	std::shared_ptr<ItemBase> getRandomItem();

private:

	void generateItems();

	Texture2D weapon_texture;
	Texture2D item_texture;
	
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

	std::vector<std::shared_ptr<ItemBase>> items_vector;

protected:



};