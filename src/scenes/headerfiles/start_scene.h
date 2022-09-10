#pragma once

#include "..\..\core\headerfiles\header.h"
#include "..\..\core\headerfiles\scene.h"

class StartScene final : public Scene {
public:

	StartScene();

	~StartScene();

	void update(Player& player, PlayerCamera& camera) override;
	void draw(Player& player, PlayerCamera& camera) override;
	SceneType setNextScene(Player& player, bool& exitWindowRequested) override;

    void updateAnimatedLogo();
    void drawAnimatedLogo();

private:

    bool is_finished = false;

    int logoPositionX = GetScreenWidth() / 2 - 128;
    int logoPositionY = GetScreenHeight() / 2 - 128;

    int framesCounter = 0;
    int lettersCount = 0;

    int topSideRecWidth = 16;
    int leftSideRecHeight = 16;

    int bottomSideRecWidth = 16;
    int rightSideRecHeight = 16;

    int state = 0;                  // Tracking animation states (State Machine)
    float alpha = 1.0f;             // Useful for fading

};