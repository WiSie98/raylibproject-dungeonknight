#include "headerfiles/item_weapon.h"

Weapon::Weapon(std::string name, std::string description, float weight, float cost, float damage, float durability, ElementalEffects element, unsigned int id, ItemType type, Rectangle spritesheet_position, Texture2D spritesheet) {
	setName(name);
	setDescription(description);
	setWeight(weight);
	setCost(cost);
	setDamage(damage);
	setDurability(durability);
	setElement(element);
	setId(id);
	setType(type);
	setSpritesheetPosition(spritesheet_position);
	setSpritesheet(spritesheet);

	setIsVisible(true);
	setDedicatedSlot(-1);
	setDynamicId(0);
}

Weapon::~Weapon() {

}

//----------------------------Setter----------------------------------

void Weapon::setDamage(float damage) {
	this->damage = damage;
}

void Weapon::setDurability(float durability) {
	this->durability = durability;
}

void Weapon::setElement(ElementalEffects element) {
	this->element = element;
}

//----------------------------Getter----------------------------------

float Weapon::getDamage() {
	return this->damage;
}

float Weapon::getDurability() {
	return this->durability;
}

ElementalEffects Weapon::getElement() {
	return this->element;
}