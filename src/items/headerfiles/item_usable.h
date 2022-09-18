#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/item_base.h"

class Usable final : public ItemBase {
public:

	Usable(std::string name, std::string description, float weight, float cost, float durability, unsigned int id, ItemType type, Rectangle spritesheet_position, Texture2D spritesheet);

	~Usable();

	void setDurability(float durability);

	float getDurability();

private:

	float durability;

protected:



};