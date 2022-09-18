#pragma once

#include "header.h"

class ItemBase {
public:

	void setName(std::string name);
	void setDescription(std::string description);
	void setWeight(float weight);
	void setCost(float cost);
	void setIsVisible(bool is_visible);
	void setDedicatedSlot(int dedicated_slot);
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
	int getDedicatedSlot();
	unsigned int getId();
	unsigned int getDynamicId();
	ItemType getType();
	Rectangle getSpritesheetPosition();
	Texture2D& getSpritesheet();

private:



protected:

	std::string name;
	std::string description;
	float weight;
	float cost;
	bool is_visible;
	int dedicated_slot;
	unsigned int id;
	unsigned int dynamic_id;
	ItemType type;
	Rectangle spritesheet_position;
	Texture2D spritesheet;

};