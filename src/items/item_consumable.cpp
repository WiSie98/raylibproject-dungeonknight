#include "headerfiles/item_consumable.h"

/*
Consumable::Consumable(std::string name, std::string description, float weight, float cost, int max_quantity, unsigned int id, ItemType type, Rectangle spritesheet_position, Texture2D spritesheet) {
	setName(name);
	setDescription(description);
	setWeight(weight);
	setCost(cost);
	setMaxQuantity(max_quantity);
	setId(id);
	setType(type);
	setSpritesheetPosition(spritesheet_position);
	setSpritesheet(spritesheet);

	setIsVisible(true);
	setDedicatedSlot(-1);
	setDynamicId(0);
	setQuantity(1);
}
*/

Consumable::~Consumable() {

}

bool operator== (Consumable& lhs, Consumable& rhs) {
	if (lhs.id == rhs.id) {
		return true;
	}
	else {
		return false;
	}
}

void Consumable::setNull() {}

//----------------------------Setter----------------------------------

/*
void Consumable::setQuantity(int quantity) {
	this->quantity = quantity;
}

void Consumable::setMaxQuantity(int max_quantity) {
	this->max_quantity = max_quantity;
}

//----------------------------Getter----------------------------------

int Consumable::getQuantity() {
	return this->quantity;
}

int Consumable::getMaxQuantity() {
	return this->max_quantity;
}
*/