#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/ui.h"

class InventoryUI final : public UI {
public:

	InventoryUI();

	~InventoryUI();

	void update() override;
	void draw() override;

	void drawCurrentWindow(Vector2 target);
	void generateInventoryHitbox(Vector2 target);

	void setIsInventoryOpen(bool is_inventory_open);
	void setCurrentWindow(InventoryWindow current_window);

	bool getIsInventoryOpen();
	InventoryWindow getCurrentWindow();
	std::vector<std::shared_ptr<InventoryHitbox>>& getInventoryHitboxVector();

private:

	void openCloseInventory();
	void changeCurrentWindow();

	bool is_inventory_open;
	InventoryWindow current_window;

	std::vector<std::shared_ptr<InventoryHitbox>> inventory_hitbox_vector;

protected:



};