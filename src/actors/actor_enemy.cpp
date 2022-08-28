#include "headerfiles/actor_enemy.h"

void Enemy::update() {
	//Random Enemy Movement.
	//Updating the Deathtimer if the Enemy is dead.
}

void Enemy::draw() {
	DrawTexture(this->texture, this->current_position.x, this->current_position.y, WHITE);
}

//----------------------------Setter----------------------------------

void Enemy::setName(std::string name) {
	this->name = name;
}

void Enemy::setDescription(std::string description) {
	this->description = description;
}

void Enemy::setMoneyDrop(int money_drop) {
	this->money_drop = money_drop;
}

void Enemy::setMaxDeathTimer(int max_death_timer) {
	this->max_death_timer = max_death_timer;
}

void Enemy::setDeathTimer(int death_timer) {
	this->death_timer = death_timer;
}

void Enemy::setIsDead(bool is_dead) {
	this->is_dead = is_dead;
}

void Enemy::setDamage(float damage) {
	this->damage = damage;
}

void Enemy::setWeakness(ElementalEffects element, float weakness_in_percent) {
	switch (element) {
	case WATER:
		this->weaknesses.water_weakness = weakness_in_percent;
		break;

	case FIRE:
		this->weaknesses.fire_weakness = weakness_in_percent;
		break;

	case THUNDER:
		this->weaknesses.thunder_weakness = weakness_in_percent;
		break;

	case POISON:
		this->weaknesses.poison_weakness = weakness_in_percent;
		break;

	case MAGIC:
		this->weaknesses.magic_weakness = weakness_in_percent;
		break;

	default:
		break;
	}
}

//----------------------------Getter----------------------------------

std::string Enemy::getName() {
	return this->name;
}

std::string Enemy::getDescription() {
	return this->description;
}

int Enemy::getMoneyDrop() {
	return this->money_drop;
}

int Enemy::getMaxDeathTimer() {
	return this->max_death_timer;
}

int Enemy::getDeathTimer() {
	return this->death_timer;
}

bool Enemy::getIsDead() {
	return this->is_dead;
}

float Enemy::getDamage() {
	return damage;
}

float Enemy::getWeaknesses(ElementalEffects element) {
	switch (element) {
	case WATER:
		return this->weaknesses.water_weakness;
		break;

	case FIRE:
		return this->weaknesses.fire_weakness;
		break;

	case THUNDER:
		return this->weaknesses.thunder_weakness;
		break;

	case POISON:
		return this->weaknesses.poison_weakness;
		break;

	case MAGIC:
		return this->weaknesses.magic_weakness;
		break;

	default:
		return 0.0f;
		break;
	}
}