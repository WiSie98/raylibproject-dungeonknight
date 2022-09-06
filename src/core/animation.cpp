#include "headerfiles/animation.h"

Animation::Animation(int frame_speed, float frame_width, float frame_height, Texture2D& spritesheet) : frame_speed(frame_speed), frame_counter(0), current_frame(0), spritesheet(spritesheet), state(NONE) {
	this->spritesheet_rectangle.x = 0;
	this->spritesheet_rectangle.y = 0;
	this->spritesheet_rectangle.width = frame_width;
	this->spritesheet_rectangle.height = frame_height;
}

Animation::~Animation() {}

void Animation::update(AnimationState state) {
	if (this->state != state) {
		this->frame_counter = 0;
		this->current_frame = 0;
		this->state = state;
	}
	this->frame_counter++;

	if (this->frame_counter >= (60 / this->frame_speed)) {
		this->frame_counter = 0;
		this->current_frame++;

		if (this->current_frame > (this->spritesheet.width / this->spritesheet_rectangle.width)) {
			this->current_frame = 0;
		}
	}
	this->spritesheet_rectangle.x = (float)this->current_frame * this->spritesheet_rectangle.width;
}

void Animation::draw(Vector2& position) {
	if (this->state == STANDING_UP || this->state == STANDING_DOWN || this->state == STANDING_LEFT || this->state == STANDING_RIGHT) {
		drawStanding(position);
	}
	else if (this->state == WALKING_UP || this->state == WALKING_DOWN || this->state == WALKING_LEFT || this->state == WALKING_RIGHT) {
		drawWalking(position);
	}
	else if (this->state == ATTACKING) {
		drawAttaking(position);
	}
	else if (this->state == DAMAGE) {
		drawDamage(position);
	}
	else if (this->state == DYING) {
		drawDying(position);
	}
	else if (this->state == SPAWNING) {
		drawSpawning(position);
	}
}

void Animation::drawStanding(Vector2& position) {
	DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
}

void Animation::drawWalking(Vector2& position) {
	DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
}

void Animation::drawAttaking(Vector2& position) {
	DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
}

void Animation::drawDamage(Vector2& position) {
	DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
}

void Animation::drawDying(Vector2& position) {
	DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
}

void Animation::drawSpawning(Vector2& position) {
	DrawTextureRec(this->spritesheet, this->spritesheet_rectangle, position, WHITE);
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

void Animation::setState(AnimationState state) {
	this->state = state;
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

AnimationState Animation::getState() {
	return this->state;
}