#include "headerfiles/actor_enemy.h"

Enemy::Enemy(std::string name, std::string description, unsigned int id, Vector2 origin, Texture2D texture, int frame_speed, int frame_width, int frame_height, float health, float traverse_speed, int money_drop, float damage, Weaknesses weaknesses) : animation(frame_speed, static_cast<float>(frame_width), static_cast<float>(frame_height), texture) {
	setName(name);
	setDescription(description);
	setId(id);
	setOrigin(origin);
	setTexture(texture);
	setHealth(health);
	setTraverseSpeed(traverse_speed);
	setMoneyDrop(money_drop);
	setDamage(damage);
	setWeakness(weaknesses);

	//--------------------------------------------

	setCurrentPosition(origin);
	setLastPosition(origin);
	setMaxHealth(health);
	setMaxDeathTimer(10);
	setDeathTimer(0);
	setFrameConter(0);
	setIsDead(false);
	setIsWalking(false);
	setCurrentDirection(NONE);
}

Enemy::~Enemy() {

}

void Enemy::update() {
	enemyMovement();
	updateDeathTimer();
}

void Enemy::draw() {
	if (!getIsDead()) {
		this->animation.draw(this->current_position);
	}
}

bool Enemy::searchForPlayer(Player& player) {
	if (CheckCollisionCircles(player.getCurrentPosition(), 6, this->current_position, 120) && !getIsDead()) {
		if (player.getCurrentPosition().y < this->current_position.y) {
			if ((this->current_position.y - player.getCurrentPosition().y) > 3) {
				this->current_position.y = this->current_position.y - this->traverse_speed;
				this->animation.update(WALKING_UP);
			}
		}
		else if (player.getCurrentPosition().y > this->current_position.y) {
			if ((player.getCurrentPosition().y - this->current_position.y) > 3) {
				this->current_position.y = this->current_position.y + this->traverse_speed;
				this->animation.update(WALKING_DOWN);
			}
		}

		if (player.getCurrentPosition().x < this->current_position.x) {
			if ((this->current_position.x - player.getCurrentPosition().x) > 3) {
				this->current_position.x = this->current_position.x - this->traverse_speed;
				this->animation.update(WALKING_LEFT);
			}
		}
		else if (player.getCurrentPosition().x > this->current_position.x) {
			if ((player.getCurrentPosition().x - this->current_position.x) > 3) {
				this->current_position.x = this->current_position.x + this->traverse_speed;
				this->animation.update(WALKING_RIGHT);
			}
		}
		return true;
	}
	return false;
}

void Enemy::enemyMovement() {
	if (!getIsDead()) {
		if (this->is_walking && this->frame_counter == 0 && this->current_direction != NONE) {
			this->is_walking = false;
			this->current_direction = NONE;
			updateFrameCounter();
		}
		else if (!this->is_walking && this->frame_counter == 0 && this->current_direction == NONE) {
			int random = GetRandomValue(1, 4);

			switch (random) {
			case 1:
				this->is_walking = true;
				this->current_direction = WALKING_UP;
				break;
			case 2:
				this->is_walking = true;
				this->current_direction = WALKING_DOWN;
				break;
			case 3:
				this->is_walking = true;
				this->current_direction = WALKING_LEFT;
				break;
			case 4:
				this->is_walking = true;
				this->current_direction = WALKING_RIGHT;
				break;
			default:
				break;
			}
			updateFrameCounter();
		}
		else if (this->is_walking) {

			switch (this->current_direction) {
			case WALKING_UP:
				this->current_position.y = this->current_position.y - this->traverse_speed;
				this->animation.update(WALKING_UP);
				break;
			case WALKING_DOWN:
				this->current_position.y = this->current_position.y + this->traverse_speed;
				this->animation.update(WALKING_DOWN);
				break;
			case WALKING_LEFT:
				this->current_position.x = this->current_position.x - this->traverse_speed;
				this->animation.update(WALKING_LEFT);
				break;
			case WALKING_RIGHT:
				this->current_position.x = this->current_position.x + this->traverse_speed;
				this->animation.update(WALKING_RIGHT);
				break;
			default:
				break;
			}
			updateFrameCounter();
		}
		else {
			updateFrameCounter();
		}
	}
}

void Enemy::updateFrameCounter() {
	if (this->frame_counter < 120) {
		this->frame_counter++;
	}
	else {
		this->frame_counter = 0;
	}
}

void Enemy::updateDeathTimer() {
	if (getIsDead()) {
		if (this->frame_counter < 60) {
			this->frame_counter++;
		}
		else {
			this->death_timer++;
			this->frame_counter = 0;
		}

		if (this->death_timer == this->max_death_timer) {
			this->death_timer = 0;
			this->current_position = this->origin;
			setIsDead(false);
		}
	}
}

//----------------------------Setter----------------------------------

void Enemy::setName(std::string name) {
	this->name = name;
}

void Enemy::setDescription(std::string description) {
	this->description = description;
}

void Enemy::setId(unsigned int id) {
	this->id = id;
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

void Enemy::setFrameConter(int frame) {
	this->frame_counter = frame;
}

void Enemy::setIsDead(bool is_dead) {
	this->is_dead = is_dead;
}

void Enemy::setIsWalking(bool is_walking) {
	this->is_walking = is_walking;
}

void Enemy::setDamage(float damage) {
	this->damage = damage;
}

void Enemy::setOrigin(Vector2 origin) {
	this->origin = origin;
}

void Enemy::setCurrentDirection(AnimationState current_direction) {
	this->current_direction = current_direction;
}

void Enemy::setWeakness(Weaknesses weaknesses) {
	this->weaknesses = weaknesses;
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

unsigned int Enemy::getId() {
	return this->id;
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

int Enemy::getFrameCounter() {
	return this->frame_counter;
}

bool Enemy::getIsDead() {
	return this->is_dead;
}

bool Enemy::getIsWalking() {
	return this->is_walking;
}

float Enemy::getDamage() {
	return this->damage;
}

Vector2 Enemy::getOrigin() {
	return this->origin;
}

AnimationState Enemy::getCurrentDirection() {
	return this->current_direction;
}

Weaknesses Enemy::getWeaknesses() {
	return this->weaknesses;
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