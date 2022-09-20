#pragma once

#include "header.h"

class ItemBase {
public:

	virtual void setNull() = 0;

	void setName(std::string name);
	void setDescription(std::string description);
	void setWeight(float weight);
	void setCost(float cost);
	void setIsVisible(bool is_visible);
	void setId(unsigned int id);
	void setDynamicId(unsigned int dynamic_id);
	void setType(ItemType type);
	void setSpritesheetPosition(Rectangle spritesheet_position);
	void setSpritesheet(Texture2D spritesheet);

	std::string getName();
	std::string getDescription();
	float getWeight();
	float getCost();
	bool getIsVisible();
	unsigned int getId();
	unsigned int getDynamicId();
	ItemType getType();
	Rectangle getSpritesheetPosition();
	Texture2D& getSpritesheet();

	// Weapon setter and getter.
	void setDamage(float damage);
	void setDurability(float durability);		// Is also used for usable items.
	void setElement(ElementalEffects element);

	float getDamage();
	float getDurability();						// Is also used for usable items.
	ElementalEffects getElement();

	// Consumable setter and getter.
	void setQuantity(int quantity);
	void setMaxQuantity(int max_quantity);

	int getQuantity();
	int getMaxQuantity();

private:



protected:

	std::string name;
	std::string description;
	float weight;
	float cost;
	bool is_visible;
	unsigned int id;
	unsigned int dynamic_id;
	ItemType type;
	Rectangle spritesheet_position;
	Texture2D spritesheet;

	// Weapon variables.
	float damage;
	float durability;			// Is also used for usable items.
	ElementalEffects element;

	// Consumable variables.
	int quantity;
	int max_quantity;

};