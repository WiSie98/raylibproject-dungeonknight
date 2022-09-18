#include "headerfiles/item_base.h"

//----------------------------Setter----------------------------------

void ItemBase::setName(std::string name) {
	this->name = name;
}

void ItemBase::setDescription(std::string description) {
	this->description = description;
}

void ItemBase::setWeight(float weight) {
	this->weight = weight;
}

void ItemBase::setCost(float cost) {
	this->cost = cost;
}

void ItemBase::setIsVisible(bool is_visible) {
	this->is_visible = is_visible;
}

void ItemBase::setDedicatedSlot(int dedicated_slot) {
	this->dedicated_slot = dedicated_slot;
}

void ItemBase::setId(unsigned int id) {
	this->id = id;
}

void ItemBase::setType(ItemType type) {
	this->type = type;
}

void ItemBase::setSpritesheetPosition(Rectangle spritesheet_position) {
	this->spritesheet_position = spritesheet_position;
}

//----------------------------Getter----------------------------------

std::string ItemBase::getName() {
	return this->name;
}

std::string ItemBase::getDescription() {
	return this->description;
}

float ItemBase::getWeight() {
	return this->weight;
}

float ItemBase::getCost() {
	return this->cost;
}

bool ItemBase::getIsVisible() {
	return is_visible;
}

int ItemBase::getDedicatedSlot() {
	return this->dedicated_slot;
}

unsigned int ItemBase::getId() {
	return this->id;
}

ItemType ItemBase::getType() {
	return this->type;
}

Rectangle ItemBase::getSpritesheetPosition() {
	return this->spritesheet_position;
}
