#include "headerfiles/actor_player.h"

Player::Player(float health, float shield, float stamina, float position_x, float position_y, Texture2D texture) : animation(24, 16, 16, texture) {
	setMaxHealth(1000);
	setMaxShield(500);
	setMaxStamina(100);
	setTraverseSpeed(5);
	setHealth(health);
	setShield(shield);
	setStamina(stamina);
	setCurrentPosition(position_x, position_y);
	setLastPosition(position_x, position_y);
	setTexture(texture);
	setMoney(0);
}

void Player::update() {
	this->playerMovement();
	this->inventory.update();
}

void Player::draw() {
	this->animation.draw(this->current_position);
}

void Player::playerMovement() {
	this->isKeyPressed = false;

	if (IsKeyDown(KEY_LEFT_SHIFT) && this->stamina > 0) {
		setTraverseSpeed(5);
		setStamina(getStamina() - 0.7f);
		this->animation.setFrameSpeed(32);
	}
	else {
		setTraverseSpeed(3.4f);
		this->animation.setFrameSpeed(28);
		if (this->stamina < this->max_stamina && !IsKeyDown(KEY_NULL)) {
			setStamina(getStamina() + 0.5);
		}
		else if (this->stamina < this->max_stamina && IsKeyDown(KEY_NULL)) {
			setStamina(getStamina() + 1);
		}
	}

	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
		this->current_position.y = this->current_position.y - this->traverse_speed;
		this->animation.update(WALKING_UP);
		this->isKeyPressed = true;
	}
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
		this->current_position.x = this->current_position.x + this->traverse_speed;
		if (!(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && !(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))) {
			this->animation.update(WALKING_RIGHT);
		}
		this->isKeyPressed = true;
	}
	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
		this->current_position.y = this->current_position.y + this->traverse_speed;
		this->animation.update(WALKING_DOWN);
		this->isKeyPressed = true;
	}
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
		this->current_position.x = this->current_position.x - this->traverse_speed;
		if (!(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && !(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))) {
			this->animation.update(WALKING_LEFT);
		}
		this->isKeyPressed = true;
	}
	if (this->isKeyPressed == false) {
		this->animation.update(NONE);
	}
}

//----------------------------Setter----------------------------------

void Player::setMoney(int money) {
	if (money < 0) {
		this->money = 0;
	}
	else {
		this->money = money;
	}
}

void Player::setShield(float shield) {
	if (shield > this->max_shield) {
		this->shield = this->max_shield;
	}
	else {
		this->shield = shield;
	}
}

void Player::setMaxShield(float max_shield) {
	this->max_shield = max_shield;
}

void Player::setStamina(float stamina) {
	if (stamina > this->max_stamina) {
		this->stamina = this->max_stamina;
	}
	else {
		this->stamina = stamina;
	}
}

void Player::setMaxStamina(float max_stamina) {
	this->max_stamina = max_stamina;
}

//----------------------------Getter----------------------------------

int Player::getMoney() {
	return this->money;
}

float Player::getShield() {
	return this->shield;
}

float Player::getMaxShield() {
	return this->max_shield;
}

float Player::getStamina() {
	return this->stamina;
}

float Player::getMaxStamina() {
	return this->max_stamina;
}

Inventory& Player::getInventory() {
	return this->inventory;
}