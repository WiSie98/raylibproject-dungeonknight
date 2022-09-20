#include "headerfiles/item_usable.h"

/*
Usable::Usable(std::string name, std::string description, float weight, float cost, float durability, unsigned int id, ItemType type, Rectangle spritesheet_position, Texture2D spritesheet) {
	setName(name);
	setDescription(description);
	setWeight(weight);
	setCost(cost);
	setDurability(durability);
	setId(id);
	setType(type);
	setSpritesheetPosition(spritesheet_position);
	setSpritesheet(spritesheet);

	setIsVisible(true);
	setDedicatedSlot(-1);
	setDynamicId(0);
}
*/

Usable::~Usable() {

}

bool operator== (Usable& lhs, Usable& rhs) {
	if (lhs.id == rhs.id) {
		return true;
	}
	else {
		return false;
	}
}

void Usable::setNull() {}

//----------------------------Setter----------------------------------

/*
void Usable::setDurability(float durability) {
	this->durability = durability;
}

//----------------------------Getter----------------------------------

float Usable::getDurability() {
	return this->durability;
}
*/