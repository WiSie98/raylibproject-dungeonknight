#include "headerfiles/actor_player.h"

Player::Player(float health, float shield, float stamina, float traverse_speed, float position_x, float position_y, Texture2D texture) : animation(32, 16, 16, texture) {
	setHealth(health);
	setShield(shield);
	setStamina(stamina);
	setTraverseSpeed(traverse_speed);
	setCurrentPosition(position_x, position_y);
	setLastPosition(position_x, position_y);
	setTexture(texture);
}

void Player::update() {
	this->isKeyPressed = false;
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

void Player::draw() {
	this->animation.draw(this->current_position);
}

void Player::removeDedicatedWeapon(int slot_num) {

}

void Player::removeDedicatedItem(int slot_num) {

}

//----------------------------Setter----------------------------------

void Player::setMoney(int money) {
	this->money = money;
}

void Player::setShield(float shield) {
	this->shield = shield;
}

void Player::setStamina(float stamina) {
	this->stamina = stamina;
}

void Player::setDedicatedWeapon(int slot_num, std::shared_ptr<ItemBase> weapon) {
	if (slot_num == 1 && weapon->getType() == WEAPON) {
		this->dedicated_weapon_slot1 = weapon;
	}
	else if (slot_num == 2 && weapon->getType() == WEAPON) {
		this->dedicated_weapon_slot2 = weapon;
	}
	else {
		std::cout << "ERROR: Could not set the dedicatet Weapon";
	}
}

void Player::setDedicatedItem(int slot_num, std::shared_ptr<ItemBase> item) {
	if (slot_num == 1 && (item->getType() == CONSUMABLE || item->getType() == USABLE)) {
		this->dedicated_item_slot1 = item;
	}
	else if (slot_num == 2 && (item->getType() == CONSUMABLE || item->getType() == USABLE)) {
		this->dedicated_item_slot2 = item;
	}
	else if (slot_num == 3 && (item->getType() == CONSUMABLE || item->getType() == USABLE)) {
		this->dedicated_item_slot3 = item;
	}
	else if (slot_num == 4 && (item->getType() == CONSUMABLE || item->getType() == USABLE)) {
		this->dedicated_item_slot4 = item;
	}
	else if (slot_num == 5 && (item->getType() == CONSUMABLE || item->getType() == USABLE)) {
		this->dedicated_item_slot5 = item;
	}
	else {
		std::cout << "ERROR: Could not set the dedicatet Item";
	}
}


//----------------------------Getter----------------------------------

int Player::getMoney() {
	return this->money;
}

float Player::getShield() {
	return this->shield;
}

float Player::getStamina() {
	return this->stamina;
}

std::shared_ptr<ItemBase> Player::getDedicatedWeapon(int slot_num) {
	if (slot_num == 1 && this->dedicated_weapon_slot1 != nullptr) {
		return this->dedicated_weapon_slot1;
	}
	else if (slot_num == 2 && this->dedicated_weapon_slot2 != nullptr) {
		return this->dedicated_weapon_slot2;
	}
	else {
		std::cout << "ERROR: Could not retrive the dedicatet Weapon";
	}
}

std::shared_ptr<ItemBase> Player::getDedicatedItem(int slot_num) {
	if (slot_num == 1 && this->dedicated_item_slot1 != nullptr) {
		return this->dedicated_item_slot1;
	}
	else if (slot_num == 2 && this->dedicated_item_slot2 != nullptr) {
		return this->dedicated_item_slot2;
	}
	else if (slot_num == 3 && this->dedicated_item_slot3 != nullptr) {
		return this->dedicated_item_slot3;
	}
	else if (slot_num == 4 && this->dedicated_item_slot4 != nullptr) {
		return this->dedicated_item_slot4;
	}
	else if (slot_num == 5 && this->dedicated_item_slot5 != nullptr) {
		return this->dedicated_item_slot5;
	}
	else {
		std::cout << "ERROR: Could not retrive the dedicatet Item";
	}
}
