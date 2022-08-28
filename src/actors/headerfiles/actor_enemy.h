#pragma once

#include "..\..\core\headerfiles\header.h"

#include "..\..\core\headerfiles\actor_base.h"

class Enemy final : public ActorBase {
public:

	void update() override;
	void draw() override;

	void setName(std::string name);
	void setDescription(std::string description);
	void setMoneyDrop(int money_drop);
	void setMaxDeathTimer(int max_death_timer);
	void setDeathTimer(int death_timer);
	void setIsDead(bool is_dead);
	void setDamage(float damage);
	void setWeakness(ElementalEffects element, float weakness_in_percent);

	std::string getName();
	std::string getDescription();
	int getMoneyDrop();
	int getMaxDeathTimer();
	int getDeathTimer();
	bool getIsDead();
	float getDamage();
	float getWeaknesses(ElementalEffects element);

private:

	std::string name;
	std::string description;
	int money_drop;
	int max_death_timer;
	int death_timer;
	bool is_dead;
	float damage;
	Weaknesses weaknesses;

protected:



};