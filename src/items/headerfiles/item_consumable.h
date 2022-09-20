#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/item_base.h"

class Consumable final : public ItemBase {
public:

	/*
	Consumable(std::string name, std::string description, float weight, float cost, int max_quantity, unsigned int id, ItemType type, Rectangle spritesheet_position, Texture2D spritesheet);
	*/

	~Consumable();

	friend bool operator== (Consumable& lhs, Consumable& rhs);

	void setNull() override;

	/*
	void setQuantity(int quantity);
	void setMaxQuantity(int max_quantity);

	int getQuantity();
	int getMaxQuantity();
	*/

private:

	/*
	int quantity;
	int max_quantity;
	*/

protected:



};