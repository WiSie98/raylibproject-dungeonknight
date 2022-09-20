#include "headerfiles/inventory.h"

Inventory::Inventory() {
	this->weapon_texture = LoadTexture("assets/graphics/spritesheets/dk_sptsht_weapons.png");
	this->item_texture = LoadTexture("assets/graphics/spritesheets/dk_sptsht_items.png");
}

Inventory::~Inventory() {
	UnloadTexture(this->weapon_texture);
	UnloadTexture(this->item_texture);
}

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

void Inventory::generateItems() {
	// Name, Description, Weight, Cost, is_visible, id, dynamic_id, Type, spritesheet_position, spritesheet, damage, durability, element, quantity, max_quantity.
// Weapons
	ItemParameters Item1{ "Knights Dagger", "Test Description", 1, 10, true, 1, 0, WEAPON, Rectangle{ 0, 0, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item2{ "Obsidian Dagger", "Test Description", 1, 10, true, 2, 0, WEAPON, Rectangle{ 32, 0, 16, 16 }, this->weapon_texture, 400, 100, MAGIC, 1, 1 };
	ItemParameters Item3{ "Mysterious Dagger", "Test Description", 1, 10, true, 3, 0, WEAPON, Rectangle{ 112, 0, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item4{ "Dagger of the Fire Guard", "Test Description", 1, 10, true, 4, 0, WEAPON, Rectangle{ 160, 0, 16, 16 }, this->weapon_texture, 400, 100, FIRE, 1, 1 };
	ItemParameters Item5{ "Kristall Dagger", "Test Description", 1, 10, true, 5, 0, WEAPON, Rectangle{ 224, 0, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item6{ "Bloody Victim", "Test Description", 1, 10, true, 6, 0, WEAPON, Rectangle{ 320, 0, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item7{ "Dagger of Horror", "Test Description", 1, 10, true, 7, 0, WEAPON, Rectangle{ 352, 0, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };

	ItemParameters Item8{ "Knights Swoard", "Test Description", 1, 10, true, 8, 0, WEAPON, Rectangle{ 0, 16, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item9{ "Obsidian Swoard", "Test Description", 1, 10, true, 9, 0, WEAPON, Rectangle{ 32, 16, 16, 16 }, this->weapon_texture, 400, 100, MAGIC, 1, 1 };
	ItemParameters Item10{ "Mysterious Swoard", "Test Description", 1, 10, true, 10, 0, WEAPON, Rectangle{ 112, 16, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item11{ "Swoard of the Fire Guard", "Test Description", 1, 10, true, 11, 0, WEAPON, Rectangle{ 160, 16, 16, 16 }, this->weapon_texture, 400, 100, FIRE, 1, 1 };
	ItemParameters Item12{ "Kristall Swoard", "Test Description", 1, 10, true, 12, 0, WEAPON, Rectangle{ 224, 16, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item13{ "Executioners Blade", "Test Description", 1, 10, true, 13, 0, WEAPON, Rectangle{ 320, 16, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item14{ "Bone Swoard", "Test Description", 1, 10, true, 14, 0, WEAPON, Rectangle{ 336, 16, 16, 16 }, this->weapon_texture, 400, 100, POISON, 1, 1 };
	ItemParameters Item15{ "Swoard of Horror", "Test Description", 1, 10, true, 15, 0, WEAPON, Rectangle{ 352, 16, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };

	ItemParameters Item16{ "Knights Spear", "Test Description", 1, 10, true, 16, 0, WEAPON, Rectangle{ 0, 48, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item17{ "Thorn of Greed", "Test Description", 1, 10, true, 17, 0, WEAPON, Rectangle{ 96, 48, 16, 16 }, this->weapon_texture, 400, 100, POISON, 1, 1 };
	ItemParameters Item18{ "Mysterious Spear", "Test Description", 1, 10, true, 18, 0, WEAPON, Rectangle{ 112, 48, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item19{ "Flaming Spear", "Test Description", 1, 10, true, 19, 0, WEAPON, Rectangle{ 160, 48, 16, 16 }, this->weapon_texture, 400, 100, FIRE, 1, 1 };
	ItemParameters Item20{ "Kristall Spear", "Test Description", 1, 10, true, 20, 0, WEAPON, Rectangle{ 224, 48, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item21{ "Tormentor", "Test Description", 1, 10, true, 21, 0, WEAPON, Rectangle{ 320, 48, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item22{ "Spear of Horror", "Test Description", 1, 10, true, 22, 0, WEAPON, Rectangle{ 352, 48, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };

	ItemParameters Item23{ "Obsidian Axe", "Test Description", 1, 10, true, 23, 0, WEAPON, Rectangle{ 32, 80, 16, 16 }, this->weapon_texture, 400, 100, MAGIC, 1, 1 };
	ItemParameters Item24{ "Wrath", "Test Description", 1, 10, true, 24, 0, WEAPON, Rectangle{ 64, 80, 16, 16 }, this->weapon_texture, 400, 100, POISON, 1, 1 };
	ItemParameters Item25{ "Inferno", "Test Description", 1, 10, true, 25, 0, WEAPON, Rectangle{ 160, 80, 16, 16 }, this->weapon_texture, 400, 100, FIRE, 1, 1 };
	ItemParameters Item26{ "Kristall Axe", "Test Description", 1, 10, true, 26, 0, WEAPON, Rectangle{ 224, 80, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item27{ "Battle Axe", "Test Description", 1, 10, true, 27, 0, WEAPON, Rectangle{ 272, 80, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item28{ "Executioners Axe", "Test Description", 1, 10, true, 28, 0, WEAPON, Rectangle{ 320, 80, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };
	ItemParameters Item29{ "Deathbringer", "Test Description", 1, 10, true, 29, 0, WEAPON, Rectangle{ 352, 80, 16, 16 }, this->weapon_texture, 400, 100, NO_ELEMENT, 1, 1 };

	// Consumable
	ItemParameters Item30{ "Healing Potion", "Test Description", 1, 10, true, 30, 0, CONSUMABLE, Rectangle{ 0, 0, 16, 16 }, this->item_texture, 0, 0, NO_ELEMENT, 1, 99 };
	ItemParameters Item31{ "Sprinting Potion", "Test Description", 1, 10, true, 31, 0, CONSUMABLE, Rectangle{ 16, 0, 16, 16 }, this->item_texture, 0, 0, NO_ELEMENT, 1, 99 };
	ItemParameters Item32{ "Shield Potion", "Test Description", 1, 10, true, 32, 0, CONSUMABLE, Rectangle{ 32, 0, 16, 16 }, this->item_texture, 0, 0, NO_ELEMENT, 1, 99 };
	ItemParameters Item33{ "Anti-Poison Potion", "Test Description", 1, 10, true, 33, 0, CONSUMABLE, Rectangle{ 48, 0, 16, 16 }, this->item_texture, 0, 0, NO_ELEMENT, 1, 99 };
	ItemParameters Item34{ "Small Healing Potion", "Test Description", 1, 10, true, 34, 0, CONSUMABLE, Rectangle{ 64, 0, 16, 16 }, this->item_texture, 0, 0, NO_ELEMENT, 1, 99 };
	ItemParameters Item35{ "Small Sprinting Potion", "Test Description", 1, 10, true, 35, 0, CONSUMABLE, Rectangle{ 80, 0, 16, 16 }, this->item_texture, 0, 0, NO_ELEMENT, 1, 99 };
	ItemParameters Item36{ "Small Shield Potion", "Test Description", 1, 10, true, 36, 0, CONSUMABLE, Rectangle{ 96, 0, 16, 16 }, this->item_texture, 0, 0, NO_ELEMENT, 1, 99 };
	ItemParameters Item37{ "Small Anti-Poison Potion", "Test Description", 1, 10, true, 37, 0, CONSUMABLE, Rectangle{ 112, 0, 16, 16 }, this->item_texture, 0, 0, NO_ELEMENT, 1, 99 };

	// Usable
	ItemParameters Item38{ "Golden Key", "Test Description", 1, 10, true, 38, 0, CONSUMABLE, Rectangle{ 112, 16, 16, 16 }, this->item_texture, 0, 0, NO_ELEMENT, 1, 99 };
	ItemParameters Item39{ "Silver Key", "Test Description", 1, 10, true, 39, 0, CONSUMABLE, Rectangle{ 128, 16, 16, 16 }, this->item_texture, 0, 0, NO_ELEMENT, 1, 99 };

	std::vector<ItemParameters> item_vector = { Item1, Item2, Item3, Item4, Item5, Item6, Item7, Item8, Item9, Item10, Item11, Item12, Item13,  Item14, Item15, Item16, Item17, Item18, Item19, Item20, Item21, Item22, Item23, Item24, Item25, Item26, Item27, Item28, Item29, Item30, Item31, Item32, Item33, Item34, Item35, Item36, Item37, Item38, Item39 };
	
	for (int i = 0; i < item_vector.size(); i++) {
		if (item_vector[i].type == WEAPON) {
			std::shared_ptr<Weapon> item = std::make_shared<Weapon>();
			item->setName(item_vector[i].name);
			item->setDescription(item_vector[i].description);
			item->setWeight(item_vector[i].weight);
			item->setCost(item_vector[i].cost);
			item->setIsVisible(item_vector[i].is_visible);
			item->setId(item_vector[i].id);
			item->setDynamicId(item_vector[i].dynamic_id);
			item->setType(item_vector[i].type);
			item->setSpritesheetPosition(item_vector[i].spritesheet_position);
			item->setSpritesheet(item_vector[i].spritesheet);
			item->setDamage(item_vector[i].damage);
			item->setDurability(item_vector[i].durability);
			item->setElement(item_vector[i].element);
			item->setQuantity(item_vector[i].quantity);
			item->setMaxQuantity(item_vector[i].max_quantity);
			this->items_vector.push_back(item);
		}
		else if (item_vector[i].type == CONSUMABLE) {
			std::shared_ptr<Consumable> item = std::make_shared<Consumable>();
			item->setName(item_vector[i].name);
			item->setDescription(item_vector[i].description);
			item->setWeight(item_vector[i].weight);
			item->setCost(item_vector[i].cost);
			item->setIsVisible(item_vector[i].is_visible);
			item->setId(item_vector[i].id);
			item->setDynamicId(item_vector[i].dynamic_id);
			item->setType(item_vector[i].type);
			item->setSpritesheetPosition(item_vector[i].spritesheet_position);
			item->setSpritesheet(item_vector[i].spritesheet);
			item->setDamage(item_vector[i].damage);
			item->setDurability(item_vector[i].durability);
			item->setElement(item_vector[i].element);
			item->setQuantity(item_vector[i].quantity);
			item->setMaxQuantity(item_vector[i].max_quantity);
			this->items_vector.push_back(item);
		}
		else if (item_vector[i].type == USABLE) {
			std::shared_ptr<Usable> item = std::make_shared<Usable>();
			item->setName(item_vector[i].name);
			item->setDescription(item_vector[i].description);
			item->setWeight(item_vector[i].weight);
			item->setCost(item_vector[i].cost);
			item->setIsVisible(item_vector[i].is_visible);
			item->setId(item_vector[i].id);
			item->setDynamicId(item_vector[i].dynamic_id);
			item->setType(item_vector[i].type);
			item->setSpritesheetPosition(item_vector[i].spritesheet_position);
			item->setSpritesheet(item_vector[i].spritesheet);
			item->setDamage(item_vector[i].damage);
			item->setDurability(item_vector[i].durability);
			item->setElement(item_vector[i].element);
			item->setQuantity(item_vector[i].quantity);
			item->setMaxQuantity(item_vector[i].max_quantity);
			this->items_vector.push_back(item);
		}
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

	unsigned int id = 0;

	if (item->getType() == WEAPON) {
		for (int i = 0; i < this->inventory_weapons_vector.size(); i++) {
			if (this->inventory_weapons_vector[i]->getDynamicId() > id) {
				id = this->inventory_weapons_vector[i]->getDynamicId();
			}
		}
		id++;
		item->setDynamicId(id);
		this->inventory_weapons_vector.push_back(item);
		return;
	}
	else if (item->getType() == USABLE) {
		for (int i = 0; i < this->inventory_items_vector.size(); i++) {
			if (this->inventory_items_vector[i]->getDynamicId() > id) {
				id = this->inventory_items_vector[i]->getDynamicId();
			}
		}
		id++;
		item->setDynamicId(id);
		this->inventory_items_vector.push_back(item);
		return;
	}
	else {
		for (int i = 0; i < this->inventory_weapons_vector.size(); i++) {
			if (this->inventory_weapons_vector[i]->getId() == item->getId()) {
				if (this->inventory_weapons_vector[i]->getQuantity() < this->inventory_weapons_vector[i]->getMaxQuantity()) {
					this->inventory_weapons_vector[i]->setQuantity(this->inventory_weapons_vector[i]->getQuantity() + 1);
					return;
				}
			}
			else {
				this->inventory_items_vector.push_back(item);
				return;
			}
		}
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

std::vector<std::shared_ptr<ItemBase>>& Inventory::getItemsVector() {
	return this->items_vector;
}

std::shared_ptr<ItemBase> Inventory::getRandomItem() {
	int random_value = GetRandomValue(0, this->items_vector.size() - 2);
	return this->items_vector[random_value];
}