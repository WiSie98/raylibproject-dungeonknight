#include "headerfiles/ui_inventory.h"

InventoryUI::InventoryUI() {
	setSpritesheet(LoadTexture("assets/graphics/spritesheets/dk_sptsht_ui_inventory.png"));
	setScale(1.5f);
	setSpritesheetSource(0, 0, this->spritesheet.width / 5, this->spritesheet.height);
	setSpritesheetDestination( 0, 0, this->spritesheet_source.width * this->scale, this->spritesheet_source.height * this->scale);
	setIsInventoryOpen(false);
	setCurrentWindow(WEAPONS_WINDOW);
	setOrigin(this->spritesheet_source.width, this->spritesheet_source.height);
}

InventoryUI::~InventoryUI() {
	UnloadTexture(this->spritesheet);
}

void InventoryUI::update() {
	openCloseInventory();
	changeCurrentWindow();
}

void InventoryUI::draw() {
	
}

void InventoryUI::openCloseInventory() {
	if ((IsKeyPressed(KEY_I) || IsKeyPressed(KEY_TAB)) && this->is_inventory_open == false) {
		this->is_inventory_open = true;
	}
	else if ((IsKeyPressed(KEY_I) || IsKeyPressed(KEY_TAB)) && this->is_inventory_open == true) {
		this->is_inventory_open = false;
		this->current_window = WEAPONS_WINDOW;
	}
}

void InventoryUI::changeCurrentWindow() {
	if (this->is_inventory_open) {
		if (IsKeyPressed(KEY_Q) && this->current_window == ITEMS_WINDOW) {
			this->current_window = WEAPONS_WINDOW;
		}
		else if ((IsKeyPressed(KEY_E) && this->current_window == WEAPONS_WINDOW) || (IsKeyPressed(KEY_Q) && this->current_window == MAP_WINDOW)) {
			this->current_window = ITEMS_WINDOW;
		}
		else if ((IsKeyPressed(KEY_E) && this->current_window == ITEMS_WINDOW) || (IsKeyPressed(KEY_Q) && this->current_window == QUEST_WINDOW)) {
			this->current_window = MAP_WINDOW;
		}
		else if ((IsKeyPressed(KEY_E) && this->current_window == MAP_WINDOW) || (IsKeyPressed(KEY_Q) && this->current_window == MONSTER_WINDOW)) {
			this->current_window = QUEST_WINDOW;
		}
		else if (IsKeyPressed(KEY_E) && this->current_window == QUEST_WINDOW) {
			this->current_window = MONSTER_WINDOW;
		}
	}
}

void InventoryUI::drawCurrentWindow(Vector2 target) {
	if (this->is_inventory_open) {
		switch (this->current_window) {
		case WEAPONS_WINDOW:
			DrawTexturePro(this->spritesheet, this->spritesheet_source, Rectangle{target.x - ((this->spritesheet_source.width / 2) * this->scale), target.y - ((this->spritesheet_source.height / 2) * this->scale), this->spritesheet_destination.width, this->spritesheet_destination.height}, Vector2{ 0, 0 }, 0, WHITE);
			break;
		case ITEMS_WINDOW:
			DrawTexturePro(this->spritesheet, Rectangle{this->spritesheet_source.x + 260, this->spritesheet_source.y, this->spritesheet_source.width, this->spritesheet_source.height}, Rectangle{ target.x - ((this->spritesheet_source.width / 2) * this->scale), target.y - ((this->spritesheet_source.height / 2) * this->scale), this->spritesheet_destination.width, this->spritesheet_destination.height }, Vector2{0, 0}, 0, WHITE);
			break;
		case MAP_WINDOW:
			DrawTexturePro(this->spritesheet, Rectangle{this->spritesheet_source.x + 520, this->spritesheet_source.y, this->spritesheet_source.width, this->spritesheet_source.height}, Rectangle{ target.x - ((this->spritesheet_source.width / 2) * this->scale), target.y - ((this->spritesheet_source.height / 2) * this->scale), this->spritesheet_destination.width, this->spritesheet_destination.height }, Vector2{0, 0}, 0, WHITE);
			break;
		case QUEST_WINDOW:
			DrawTexturePro(this->spritesheet, Rectangle{this->spritesheet_source.x + 780, this->spritesheet_source.y, this->spritesheet_source.width, this->spritesheet_source.height}, Rectangle{ target.x - ((this->spritesheet_source.width / 2) * this->scale), target.y - ((this->spritesheet_source.height / 2) * this->scale), this->spritesheet_destination.width, this->spritesheet_destination.height }, Vector2{0, 0}, 0, WHITE);
			break;
		case MONSTER_WINDOW:
			DrawTexturePro(this->spritesheet, Rectangle{this->spritesheet_source.x + 1040, this->spritesheet_source.y, this->spritesheet_source.width, this->spritesheet_source.height}, Rectangle{ target.x - ((this->spritesheet_source.width / 2) * this->scale), target.y - ((this->spritesheet_source.height / 2) * this->scale), this->spritesheet_destination.width, this->spritesheet_destination.height }, Vector2{0, 0}, 0, WHITE);
			break;
		default:
			break;
		}
	}
}

void InventoryUI::generateInventoryHitbox(Vector2 target) {
	this->inventory_hitbox_vector.clear();
	Rectangle rec = { target.x - (((this->spritesheet_source.width / 2) + 22) * this->scale), target.y - (((this->spritesheet_source.height / 2) + 42) * this->scale), 20, 20 };
	for (int i = 0; i < 25; i++) {
		std::shared_ptr<InventoryHitbox> inventory_hitbox = std::make_shared<InventoryHitbox>();
		inventory_hitbox->id = i;
		inventory_hitbox->hitbox = rec;
		this->inventory_hitbox_vector.push_back(inventory_hitbox);

		if (rec.x < (target.x - ((this->spritesheet_source.width / 2) * this->scale) + 100)) {
			rec.x += 20;
		}
		else {
			rec.x = (target.x - ((this->spritesheet_source.width / 2) * this->scale)) + 20;
			rec.y += 20;
		}
	}
}

//----------------------------Setter----------------------------------

void InventoryUI::setIsInventoryOpen(bool is_inventory_open) {
	this->is_inventory_open = is_inventory_open;
}

void InventoryUI::setCurrentWindow(InventoryWindow current_window) {
	this->current_window = current_window;
}

//----------------------------Getter----------------------------------

bool InventoryUI::getIsInventoryOpen() {
	return this->is_inventory_open;
}

InventoryWindow InventoryUI::getCurrentWindow() {
	return this->current_window;
}

std::vector<std::shared_ptr<InventoryHitbox>>& InventoryUI::getInventoryHitboxVector() {
	return this->inventory_hitbox_vector;
}