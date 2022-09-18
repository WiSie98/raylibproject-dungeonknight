#include "headerfiles/inventory.h"

Inventory::Inventory() {}

Inventory::~Inventory() {}

void Inventory::update() {
	
}

void Inventory::draw() {

}

void Inventory::removeDedicatedWeapon(int slot_num) {
	if (slot_num == 1) {
		this->dedicated_weapon_slot1 = nullptr;
	}
	else if (slot_num == 2) {
		this->dedicated_weapon_slot2 = nullptr;
	}
}

void Inventory::removeDedicatedItem(int slot_num) {
	if (slot_num == 1) {
		this->dedicated_item_slot1 = nullptr;
	}
	else if (slot_num == 2) {
		this->dedicated_item_slot2 = nullptr;
	}
	else if (slot_num == 3) {
		this->dedicated_item_slot3 = nullptr;
	}
	else if (slot_num == 4) {
		this->dedicated_item_slot4 = nullptr;
	}
	else if (slot_num == 5) {
		this->dedicated_item_slot5 = nullptr;
	}
}

//----------------------------Setter----------------------------------

void Inventory::addDedicatedWeapon(int slot_num, std::shared_ptr<ItemBase>& weapon) {
	if (slot_num == 1 && weapon->getType() == WEAPON) {
		this->dedicated_weapon_slot1 = weapon;
	}
	else if (slot_num == 2 && weapon->getType() == WEAPON) {
		this->dedicated_weapon_slot2 = weapon;
	}
	else {
		std::cout << "ERROR: Could not set the dedicatet Weapon";
	}
}

void Inventory::addDedicatedItem(int slot_num, std::shared_ptr<ItemBase>& item) {
	if (slot_num == 1 && (item->getType() == CONSUMABLE || item->getType() == USABLE)) {
		this->dedicated_item_slot1 = item;
	}
	else if (slot_num == 2 && (item->getType() == CONSUMABLE || item->getType() == USABLE)) {
		this->dedicated_item_slot2 = item;
	}
	else if (slot_num == 3 && (item->getType() == CONSUMABLE || item->getType() == USABLE)) {
		this->dedicated_item_slot3 = item;
	}
	else if (slot_num == 4 && (item->getType() == CONSUMABLE || item->getType() == USABLE)) {
		this->dedicated_item_slot4 = item;
	}
	else if (slot_num == 5 && (item->getType() == CONSUMABLE || item->getType() == USABLE)) {
		this->dedicated_item_slot5 = item;
	}
	else {
		std::cout << "ERROR: Could not set the dedicatet Item";
	}
}

//----------------------------Getter----------------------------------

std::shared_ptr<ItemBase> Inventory::getDedicatedWeapon(int slot_num) {
	if (slot_num == 1 && this->dedicated_weapon_slot1 != nullptr) {
		return this->dedicated_weapon_slot1;
	}
	else if (slot_num == 2 && this->dedicated_weapon_slot2 != nullptr) {
		return this->dedicated_weapon_slot2;
	}
	else {
		std::cout << "ERROR: Could not retrive the dedicatet Weapon";
		return nullptr;
	}
}

std::shared_ptr<ItemBase> Inventory::getDedicatedItem(int slot_num) {
	if (slot_num == 1 && this->dedicated_item_slot1 != nullptr) {
		return this->dedicated_item_slot1;
	}
	else if (slot_num == 2 && this->dedicated_item_slot2 != nullptr) {
		return this->dedicated_item_slot2;
	}
	else if (slot_num == 3 && this->dedicated_item_slot3 != nullptr) {
		return this->dedicated_item_slot3;
	}
	else if (slot_num == 4 && this->dedicated_item_slot4 != nullptr) {
		return this->dedicated_item_slot4;
	}
	else if (slot_num == 5 && this->dedicated_item_slot5 != nullptr) {
		return this->dedicated_item_slot5;
	}
	else {
		std::cout << "ERROR: Could not retrive the dedicatet Item";
		return nullptr;
	}
}