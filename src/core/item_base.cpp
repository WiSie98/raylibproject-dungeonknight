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

void ItemBase::setId(unsigned int id) {
	this->id = id;
}

void ItemBase::setDynamicId(unsigned int dynamic_id) {
	this->dynamic_id = dynamic_id;
}

void ItemBase::setType(ItemType type) {
	this->type = type;
}

void ItemBase::setSpritesheetPosition(Rectangle spritesheet_position) {
	this->spritesheet_position = spritesheet_position;
}

void ItemBase::setSpritesheet(Texture2D spritesheet) {
	this->spritesheet = spritesheet;
}

// Weapon setter.
void ItemBase::setDamage(float damage) {
	this->damage = damage;
}

void ItemBase::setDurability(float durability) {
	this->durability = durability;
}

void ItemBase::setElement(ElementalEffects element) {
	this->element = element;
}

// Consumable setter.
void ItemBase::setQuantity(int quantity) {
	this->quantity = quantity;
}

void ItemBase::setMaxQuantity(int max_quantity) {
	this->max_quantity = max_quantity;
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

unsigned int ItemBase::getId() {
	return this->id;
}

unsigned int ItemBase::getDynamicId() {
	return this->dynamic_id;
}

ItemType ItemBase::getType() {
	return this->type;
}

Rectangle ItemBase::getSpritesheetPosition() {
	return this->spritesheet_position;
}

Texture2D& ItemBase::getSpritesheet() {
	return this->spritesheet;
}

// Weapon getter.
float ItemBase::getDamage() {
	return this->damage;
}

float ItemBase::getDurability() {
	return this->durability;
}

ElementalEffects ItemBase::getElement() {
	return this->element;
}

// Consumable getter.
int ItemBase::getQuantity() {
	return this->quantity;
}

int ItemBase::getMaxQuantity() {
	return this->max_quantity;
}