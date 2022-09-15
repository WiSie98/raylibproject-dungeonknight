#pragma once

#include "../../core/headerfiles/header.h"

#include "../../core/headerfiles/actor_base.h"
#include "../../core/headerfiles/animation.h"
#include "actor_player.h"

class Enemy final : public ActorBase {
public:

	Enemy(std::string name, std::string description, Vector2 origin, Texture2D texture, int frame_speed, int frame_width, int frame_height, float health, float traverse_speed, int money_drop, float damage, Weaknesses weaknesses);

	~Enemy();

	void update() override;
	void draw() override;

	bool searchForPlayer(Player& player);

	void setName(std::string name);
	void setDescription(std::string description);
	void setMoneyDrop(int money_drop);
	void setMaxDeathTimer(int max_death_timer);
	void setDeathTimer(int death_timer);
	void setFrameConter(int frame);
	void setIsDead(bool is_dead);
	void setIsWalking(bool is_walking);
	void setDamage(float damage);
	void setOrigin(Vector2 origin);
	void setCurrentDirection(AnimationState current_direction);
	void setWeakness(ElementalEffects element, float weakness_in_percent);
	void setWeakness(Weaknesses weaknesses);

	std::string getName();
	std::string getDescription();
	int getMoneyDrop();
	int getMaxDeathTimer();
	int getDeathTimer();
	int getFrameCounter();
	bool getIsDead();
	bool getIsWalking();
	float getDamage();
	Vector2 getOrigin();
	AnimationState getCurrentDirection();
	float getWeaknesses(ElementalEffects element);
	Weaknesses getWeaknesses();

private:

	std::string name;
	std::string description;
	int money_drop;
	int max_death_timer;
	int death_timer;
	int frame_counter;
	bool is_dead;
	bool is_walking;
	bool is_chasing;
	float damage;
	Vector2 origin;
	AnimationState current_direction;
	Weaknesses weaknesses;
	Animation animation;

	void enemyMovement();
	void updateFrameCounter();
	void updateDeathTimer();

protected:



};