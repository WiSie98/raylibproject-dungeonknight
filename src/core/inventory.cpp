#include "headerfiles/inventory.h"

Inventory::Inventory() {}

Inventory::~Inventory() {}

void Inventory::update() {
	
}

void Inventory::draw() {

}

void Inventory::checkDedicatedWeaponSlotPressed(Vector2 target, InventoryUI& inventory_ui) {

	if (inventory_ui.getIsInventoryOpen() && inventory_ui.getCurrentWindow() == WEAPONS_WINDOW) {

		Vector2 mouse_position;
		mouse_position.x = (target.x - (GetScreenWidth() / 2)) + GetMouseX();
		mouse_position.y = (target.y - (GetScreenHeight() / 2)) + GetMouseY();

		Rectangle dedicatedBox1 = { inventory_ui.getSpritesheetDestination().x - (130 * inventory_ui.getScale()), inventory_ui.getSpritesheetDestination().y - (120 * inventory_ui.getScale()), 40 * inventory_ui.getScale(), 40 * inventory_ui.getScale()};
		Rectangle dedicatedBox2 = { inventory_ui.getSpritesheetDestination().x - (10 * inventory_ui.getScale()), inventory_ui.getSpritesheetDestination().y - (120 * inventory_ui.getScale()), 40 * inventory_ui.getScale(), 40 * inventory_ui.getScale() };

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			if ((CheckCollisionCircleRec(mouse_position, 1, dedicatedBox1))) {
				removeDedicatedWeapon(1);
				std::cout << "INFO: Dedicated Weapon removed: 1\n";
			}
			else if ((CheckCollisionCircleRec(mouse_position, 1, dedicatedBox2))) {
				removeDedicatedWeapon(2);
				std::cout << "INFO: Dedicated Weapon removed: 2\n";
			}
		}
	}
}

void Inventory::checkDedicatedItemSlotPressed(Vector2 target, InventoryUI& inventory_ui) {

	if (inventory_ui.getIsInventoryOpen() && inventory_ui.getCurrentWindow() == ITEMS_WINDOW) {

		Vector2 mouse_position;
		mouse_position.x = (target.x - (GetScreenWidth() / 2)) + GetMouseX();
		mouse_position.y = (target.y - (GetScreenHeight() / 2)) + GetMouseY();

		Rectangle dedicatedBox1 = { inventory_ui.getSpritesheetDestination().x - (190 * inventory_ui.getScale()), inventory_ui.getSpritesheetDestination().y - (120 * inventory_ui.getScale()), 40 * inventory_ui.getScale(), 40 * inventory_ui.getScale() };
		Rectangle dedicatedBox2 = { inventory_ui.getSpritesheetDestination().x - (130 * inventory_ui.getScale()), inventory_ui.getSpritesheetDestination().y - (120 * inventory_ui.getScale()), 40 * inventory_ui.getScale(), 40 * inventory_ui.getScale() };
		Rectangle dedicatedBox3 = { inventory_ui.getSpritesheetDestination().x - (70 * inventory_ui.getScale()), inventory_ui.getSpritesheetDestination().y - (120 * inventory_ui.getScale()), 40 * inventory_ui.getScale(), 40 * inventory_ui.getScale() };
		Rectangle dedicatedBox4 = { inventory_ui.getSpritesheetDestination().x - (10 * inventory_ui.getScale()), inventory_ui.getSpritesheetDestination().y - (120 * inventory_ui.getScale()), 40 * inventory_ui.getScale(), 40 * inventory_ui.getScale() };
		Rectangle dedicatedBox5 = { inventory_ui.getSpritesheetDestination().x - (-50 * inventory_ui.getScale()), inventory_ui.getSpritesheetDestination().y - (120 * inventory_ui.getScale()), 40 * inventory_ui.getScale(), 40 * inventory_ui.getScale() };

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			if ((CheckCollisionCircleRec(mouse_position, 1, dedicatedBox1))) {
				removeDedicatedWeapon(1);
				std::cout << "INFO: Dedicated Item removed: 1\n";
			}
			else if ((CheckCollisionCircleRec(mouse_position, 1, dedicatedBox2))) {
				removeDedicatedWeapon(2);
				std::cout << "INFO: Dedicated Item removed: 2\n";
			}
			else if ((CheckCollisionCircleRec(mouse_position, 1, dedicatedBox3))) {
				removeDedicatedWeapon(3);
				std::cout << "INFO: Dedicated Item removed: 3\n";
			}
			else if ((CheckCollisionCircleRec(mouse_position, 1, dedicatedBox4))) {
				removeDedicatedWeapon(4);
				std::cout << "INFO: Dedicated Item removed: 4\n";
			}
			else if ((CheckCollisionCircleRec(mouse_position, 1, dedicatedBox5))) {
				removeDedicatedWeapon(5);
				std::cout << "INFO: Dedicated Item removed: 5\n";
			}
		}
	}
}

void Inventory::checkInventorySlotPressed(Vector2 target, InventoryUI& inventory_ui) {

	if (inventory_ui.getIsInventoryOpen()) {

		Vector2 mouse_position;
		mouse_position.x = (target.x - (GetScreenWidth() / 2)) + GetMouseX();
		mouse_position.y = (target.y - (GetScreenHeight() / 2)) + GetMouseY();

		for (const auto& hitbox : inventory_ui.getInventoryHitboxVector()) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
				if (CheckCollisionCircleRec(mouse_position, 1, hitbox->hitbox)) {
					if (inventory_ui.getCurrentWindow() == WEAPONS_WINDOW) {
						removeWeaponFromInventory(hitbox->id);
						std::cout << "INFO: Weapon removed: " << hitbox->id << "\n";
					}
					else if (inventory_ui.getCurrentWindow() == ITEMS_WINDOW) {
						removeItemFromInventory(hitbox->id);
						std::cout << "INFO: Item removed: " << hitbox->id << "\n";
					}
				}
			}
			else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				if (CheckCollisionCircleRec(mouse_position, 1, hitbox->hitbox)) {
					if (inventory_ui.getCurrentWindow() == WEAPONS_WINDOW) {
						addDedicatedWeapon(hitbox->id);
						std::cout << "INFO: Weapon added: " << hitbox->id << "\n";
					}
					else if (inventory_ui.getCurrentWindow() == ITEMS_WINDOW) {
						addDedicatedItem(hitbox->id);
						std::cout << "INFO: Item added: " << hitbox->id << "\n";
					}
				}
			}
		}
	}
}

void Inventory::removeDedicatedWeapon(int slot_num) {
	if (slot_num == 1) {
		for (const auto& weapon : this->inventory_weapons_vector) {
			if (weapon->getDynamicId() == this->dedicated_weapon_slot1->getDynamicId()) {
				weapon->setIsVisible(true);
			}
		}
		this->dedicated_weapon_slot1 = nullptr;
	}
	else if (slot_num == 2) {
		for (const auto& weapon : this->inventory_weapons_vector) {
			if (weapon->getDynamicId() == this->dedicated_weapon_slot2->getDynamicId()) {
				weapon->setIsVisible(true);
			}
		}
		this->dedicated_weapon_slot2 = nullptr;
	}
}

void Inventory::removeDedicatedItem(int slot_num) {
	if (slot_num == 1) {
		for (const auto& item : this->inventory_items_vector) {
			if (item->getDynamicId() == this->dedicated_item_slot1->getDynamicId()) {
				item->setIsVisible(true);
			}
		}
		this->dedicated_item_slot1 = nullptr;
	}
	else if (slot_num == 2) {
		for (const auto& item : this->inventory_items_vector) {
			if (item->getDynamicId() == this->dedicated_item_slot2->getDynamicId()) {
				item->setIsVisible(true);
			}
		}
		this->dedicated_item_slot2 = nullptr;
	}
	else if (slot_num == 3) {
		for (const auto& item : this->inventory_items_vector) {
			if (item->getDynamicId() == this->dedicated_item_slot3->getDynamicId()) {
				item->setIsVisible(true);
			}
		}
		this->dedicated_item_slot3 = nullptr;
	}
	else if (slot_num == 4) {
		for (const auto& item : this->inventory_items_vector) {
			if (item->getDynamicId() == this->dedicated_item_slot4->getDynamicId()) {
				item->setIsVisible(true);
			}
		}
		this->dedicated_item_slot4 = nullptr;
	}
	else if (slot_num == 5) {
		for (const auto& item : this->inventory_items_vector) {
			if (item->getDynamicId() == this->dedicated_item_slot5->getDynamicId()) {
				item->setIsVisible(true);
			}
		}
		this->dedicated_item_slot5 = nullptr;
	}
}

void Inventory::removeWeaponFromInventory(int slot) {
	if (this->inventory_weapons_vector.size() == 1) {
		this->inventory_weapons_vector.erase(this->inventory_weapons_vector.begin());
	}
	else if (slot < this->inventory_weapons_vector.size()) {
		this->inventory_weapons_vector.erase(this->inventory_weapons_vector.begin() + slot);
	}
	else {
		std::cout << "ERROR: Weapon could not be deleted!\n";
	}
}

void Inventory::removeItemFromInventory(int slot) {
	if (this->inventory_items_vector.size() == 1) {
		this->inventory_items_vector.erase(this->inventory_items_vector.begin());
	}
	else if (slot < this->inventory_items_vector.size()) {
		this->inventory_items_vector.erase(this->inventory_items_vector.begin() + slot);
	}
	else {
		std::cout << "ERROR: Item could not be deleted!\n";
	}
}

//----------------------------Setter----------------------------------

void Inventory::addDedicatedWeapon(int slot_num) {
	if (0 < this->inventory_weapons_vector.size() && slot_num < this->inventory_weapons_vector.size()) {
		if (this->dedicated_weapon_slot1 == nullptr && this->inventory_weapons_vector[slot_num]->getType() == WEAPON) {
			this->dedicated_weapon_slot1 = this->inventory_weapons_vector[slot_num];
			this->inventory_weapons_vector[slot_num]->setIsVisible(false);
		}
		else if (this->dedicated_weapon_slot2 == nullptr && this->inventory_weapons_vector[slot_num]->getType() == WEAPON) {
			this->dedicated_weapon_slot2 = this->inventory_weapons_vector[slot_num];
			this->inventory_weapons_vector[slot_num]->setIsVisible(false);
		}
		else {
			std::cout << "ERROR: Could not set the dedicatet Weapon | Dedicated Weapon slots full\n";
		}
	}
	else {
		std::cout << "ERROR: Could not set the dedicatet Weapon\n";
	}
}

void Inventory::addDedicatedItem(int slot_num) {
	if (0 < this->inventory_items_vector.size() && slot_num < this->inventory_items_vector.size()) {
		if (this->dedicated_item_slot1 == nullptr && (this->inventory_items_vector[slot_num]->getType() == CONSUMABLE || this->inventory_items_vector[slot_num]->getType() == USABLE)) {
			this->dedicated_item_slot1 = this->inventory_items_vector[slot_num];
			this->inventory_items_vector[slot_num]->setIsVisible(false);
		}
		else if (this->dedicated_item_slot2 == nullptr && (this->inventory_items_vector[slot_num]->getType() == CONSUMABLE || this->inventory_items_vector[slot_num]->getType() == USABLE)) {
			this->dedicated_item_slot2 = this->inventory_items_vector[slot_num];
			this->inventory_items_vector[slot_num]->setIsVisible(false);
		}
		else if (this->dedicated_item_slot3 == nullptr && (this->inventory_items_vector[slot_num]->getType() == CONSUMABLE || this->inventory_items_vector[slot_num]->getType() == USABLE)) {
			this->dedicated_item_slot3 = this->inventory_items_vector[slot_num];
			this->inventory_items_vector[slot_num]->setIsVisible(false);
		}
		else if (this->dedicated_item_slot4 == nullptr && (this->inventory_items_vector[slot_num]->getType() == CONSUMABLE || this->inventory_items_vector[slot_num]->getType() == USABLE)) {
			this->dedicated_item_slot4 = this->inventory_items_vector[slot_num];
			this->inventory_items_vector[slot_num]->setIsVisible(false);
		}
		else if (this->dedicated_item_slot5 == nullptr && (this->inventory_items_vector[slot_num]->getType() == CONSUMABLE || this->inventory_items_vector[slot_num]->getType() == USABLE)) {
			this->dedicated_item_slot5 = this->inventory_items_vector[slot_num];
			this->inventory_items_vector[slot_num]->setIsVisible(false);
		}
		else {
			std::cout << "ERROR: Could not set the dedicatet Item | Dedicated Item slots full\n";
		}
	}
	else {
		std::cout << "ERROR: Could not set the dedicatet Item\n";
	}
}

void Inventory::addItemToInventory(std::shared_ptr<ItemBase> item) {
	if (item->getType() == WEAPON) {
		this->inventory_weapons_vector.push_back(item);
	}
	else {
		this->inventory_items_vector.push_back(item);
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