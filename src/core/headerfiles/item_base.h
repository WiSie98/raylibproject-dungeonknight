#pragma once

#include "header.h"

class ItemBase {
public:

	void setName(std::string name);
	void setDescription(std::string description);
	void setWeight(float weight);
	void setCost(float cost);
	void setIsVisible(bool is_visible);
	void setType(ItemType type);
	void setSpritesheetPosition(Rectangle spritesheet_position);

	std::string getName();
	std::string getDescription();
	float getWeight();
	float getCost();
	bool getIsVisible();
	int getDedicatedSlot();
	unsigned int getId();
	ItemType getType();
	Rectangle getSpritesheetPosition();

private:

	void setId(unsigned int id);

protected:

	std::string name;
	std::string description;
	float weight;
	float cost;
	bool is_visible;
	int dedicated_slot;
	unsigned int id;
	ItemType type;
	Rectangle spritesheet_position;

	virtual void setDedicatedSlot(int dedicated_slot) = 0;

};