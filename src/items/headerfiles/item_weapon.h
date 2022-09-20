#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/item_base.h"

class Weapon final : public ItemBase {
public:

	/*
	Weapon(std::string name, std::string description, float weight, float cost, float damage, float durability, ElementalEffects element, unsigned int id, ItemType type, Rectangle spritesheet_position, Texture2D spritesheet);
	*/


	~Weapon();

	friend bool operator== (Weapon& lhs, Weapon& rhs);

	void setNull() override;

	/*
	void setDamage(float damage);
	void setDurability(float durability);
	void setElement(ElementalEffects element);

	float getDamage();
	float getDurability();
	ElementalEffects getElement();
	*/

private:

	/*
	float damage;
	float durability;
	ElementalEffects element;
	*/

protected:



};