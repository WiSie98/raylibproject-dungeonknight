#include "headerfiles/animation.h"

Animation::Animation(int frame_speed, float frame_width, float frame_height, Texture2D& spritesheet) : frame_speed(frame_speed), frame_counter(0), current_frame(0), spritesheet(spritesheet), current_state(NONE), last_state(STANDING_DOWN) {
	setSpritesheetRectangle(0, 0, frame_width, frame_height);
}

Animation::~Animation() {}

void Animation::update(AnimationState state) {
	if (this->current_state != state) {
		this->frame_counter = 0;
		this->current_frame = 0;
		this->last_state = current_state;
		this->current_state = state;
	}
	this->frame_counter++;

	if (this->frame_counter >= (60 / this->frame_speed)) {
		this->frame_counter = 0;
		this->current_frame++;

		if (this->current_frame > (this->spritesheet.width / this->spritesheet_rectangle.width)) {
			this->current_frame = 0;
		}
	}
	//this->spritesheet_rectangle.x = (float)this->current_frame * this->spritesheet_rectangle.width;

	if (this->current_state == NONE) {
		if (this->last_state == WALKING_UP || this->last_state == STANDING_UP) {
			this->current_state = STANDING_UP;
		}
		else if (this->last_state == WALKING_DOWN || this->last_state == STANDING_DOWN) {
			this->current_state = STANDING_DOWN;
		}
		else if (this->last_state == WALKING_LEFT || this->last_state == STANDING_LEFT) {
			this->current_state = STANDING_LEFT;
		}
		else if (this->last_state == WALKING_RIGHT || this->last_state == STANDING_RIGHT) {
			this->current_state = STANDING_RIGHT;
		}
		else {
			this->current_state = STANDING_DOWN;
		}
	}
}

void Animation::draw(Vector2& position) {
	if (this->current_state == STANDING_UP || this->current_state == STANDING_DOWN || this->current_state == STANDING_LEFT || this->current_state == STANDING_RIGHT) {
		drawStanding(position);
	}
	else if (this->current_state == WALKING_UP || this->current_state == WALKING_DOWN || this->current_state == WALKING_LEFT || this->current_state == WALKING_RIGHT) {
		drawWalking(position);
	}
	else if (this->current_state == ATTACKING) {
		drawAttaking(position);
	}
	else if (this->current_state == DAMAGE) {
		drawDamage(position);
	}
	else if (this->current_state == DYING) {
		drawDying(position);
	}
	else if (this->current_state == SPAWNING) {
		drawSpawning(position);
	}
}

void Animation::drawStanding(Vector2& position) {
	if (this->current_state == STANDING_UP) {
		this->spritesheet_rectangle.x = 0;
		this->spritesheet_rectangle.y = 0;
		DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
	}
	else if (this->current_state == STANDING_DOWN) {
		this->spritesheet_rectangle.x = this->spritesheet_rectangle.width;
		this->spritesheet_rectangle.y = 0;
		DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
	}
	else if (this->current_state == STANDING_LEFT) {
		this->spritesheet_rectangle.x = this->spritesheet_rectangle.width * 2;
		this->spritesheet_rectangle.y = 0;
		DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
	}
	else if (this->current_state == STANDING_RIGHT) {
		this->spritesheet_rectangle.x = this->spritesheet_rectangle.width * 3;
		this->spritesheet_rectangle.y = 0;
		DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
	}
}

void Animation::drawWalking(Vector2& position) {
	if (this->current_state == WALKING_UP) {
		this->spritesheet_rectangle.x = static_cast<float>(this->current_frame) * this->spritesheet_rectangle.width;
		this->spritesheet_rectangle.y = this->spritesheet_rectangle.height;
		DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
	}
	else if (this->current_state == WALKING_DOWN) {
		this->spritesheet_rectangle.x = static_cast<float>(this->current_frame) * this->spritesheet_rectangle.width;
		this->spritesheet_rectangle.y = this->spritesheet_rectangle.height * 2;
		DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
	}
	else if (this->current_state == WALKING_LEFT) {
		this->spritesheet_rectangle.x = static_cast<float>(this->current_frame) * this->spritesheet_rectangle.width;
		this->spritesheet_rectangle.y = this->spritesheet_rectangle.height * 3;
		DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
	}
	else if (this->current_state == WALKING_RIGHT) {
		this->spritesheet_rectangle.x = static_cast<float>(this->current_frame) * this->spritesheet_rectangle.width;
		this->spritesheet_rectangle.y = this->spritesheet_rectangle.height * 4;
		DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
	}
}

void Animation::drawAttaking(Vector2& position) {
	//DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
}

void Animation::drawDamage(Vector2& position) {
	//DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
}

void Animation::drawDying(Vector2& position) {
	//DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
}

void Animation::drawSpawning(Vector2& position) {
	//DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
}

//----------------------------Setter----------------------------------

void Animation::setFrameSpeed(int frame_speed) {
	this->frame_speed = frame_speed;
}

void Animation::setFrameCounter(int frame_counter) {
	this->frame_counter = frame_counter;
}

void Animation::setCurrentFrame(int current_frame) {
	this->current_frame = current_frame;
}

void Animation::setSpritesheet(Texture2D spritesheet) {
	this->spritesheet = spritesheet;
}

void Animation::setSpritesheetRectangle(float x, float y, float width, float height) {
	this->spritesheet_rectangle.x = x;
	this->spritesheet_rectangle.y = y;
	this->spritesheet_rectangle.width = width;
	this->spritesheet_rectangle.height = height;
}

void Animation::setSpritesheetRectangle(Rectangle spritesheet_rectangle) {
	this->spritesheet_rectangle = spritesheet_rectangle;
}

void Animation::setCurrentState(AnimationState current_state) {
	this->current_state = current_state;
}

void Animation::setLastState(AnimationState last_state) {
	this->last_state = last_state;
}

//----------------------------Getter----------------------------------

int Animation::getFrameSpeed() {
	return this->frame_speed;
}

int Animation::getFrameCounter() {
	return this->frame_counter;
}

int Animation::getCurrentFrame() {
	return this->current_frame;
}

Texture2D Animation::getSpritesheet() {
	return this->spritesheet;
}

Rectangle Animation::getSpritesheetRectangle() {
	return this->spritesheet_rectangle;
}

AnimationState Animation::getCurrentState() {
	return this->current_state;
}

AnimationState Animation::getLastState() {
	return this->last_state;
}