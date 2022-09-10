#include "headerfiles/start_scene.h"

StartScene::StartScene() {
	setSceneType(START_SCENE);
}

StartScene::~StartScene() {}

void StartScene::update(Player& player, PlayerCamera& camera) {
    updateAnimatedLogo();
}

void StartScene::draw(Player& player, PlayerCamera& camera) {
    drawAnimatedLogo();
}

SceneType StartScene::setNextScene(Player& player, bool& exitWindowRequested) {
	if (this->is_finished || IsKeyPressed(KEY_SPACE)) {

        this->is_finished = false;
        this->framesCounter = 0;
        this->lettersCount = 0;

        this->topSideRecWidth = 16;
        this->bottomSideRecWidth = 16;

        this->rightSideRecHeight = 16;
        this->leftSideRecHeight = 16;

        this->alpha = 1.0f;
        this->state = 0;

		return MAIN_MENU_SCENE;
	}
	return START_SCENE;
}

void StartScene::updateAnimatedLogo() {
    if (this->state == 0) {
        this->framesCounter++;

        if (this->framesCounter == 120) {
            this->state = 1;
            this->framesCounter = 0;
        }
    }
    else if (this->state == 1) {
        this->topSideRecWidth += 4;
        this->leftSideRecHeight += 4;

        if (this->topSideRecWidth == 256) this->state = 2;
    }
    else if (this->state == 2) {
        this->bottomSideRecWidth += 4;
        this->rightSideRecHeight += 4;

        if (this->bottomSideRecWidth == 256) this->state = 3;
    }
    else if (this->state == 3) {
        this->framesCounter++;

        if (this->framesCounter / 12) {
            this->lettersCount++;
            this->framesCounter = 0;
        }

        if (this->lettersCount >= 10) {
            this->alpha -= 0.02f;

            if (this->alpha <= 0.0f) {
                this->alpha = 0.0f;
                this->state = 4;
            }
        }
    }
    else if (this->state == 4) {
        this->is_finished = true;
    }
}

void StartScene::drawAnimatedLogo() {
    if (this->state == 0) {
        if ((this->framesCounter / 15) % 2) DrawRectangle(this->logoPositionX, this->logoPositionY, 16, 16, BLACK);
    }
    else if (this->state == 1) {
        DrawRectangle(this->logoPositionX, this->logoPositionY, this->topSideRecWidth, 16, BLACK);
        DrawRectangle(this->logoPositionX, this->logoPositionY, 16, this->leftSideRecHeight, BLACK);
    }
    else if (this->state == 2) {
        DrawRectangle(this->logoPositionX, this->logoPositionY, this->topSideRecWidth, 16, BLACK);
        DrawRectangle(this->logoPositionX, this->logoPositionY, 16, this->leftSideRecHeight, BLACK);

        DrawRectangle(this->logoPositionX + 240, this->logoPositionY, 16, this->rightSideRecHeight, BLACK);
        DrawRectangle(this->logoPositionX, this->logoPositionY + 240, this->bottomSideRecWidth, 16, BLACK);
    }
    else if (this->state == 3) {
        DrawRectangle(this->logoPositionX, this->logoPositionY, this->topSideRecWidth, 16, Fade(BLACK, this->alpha));
        DrawRectangle(this->logoPositionX, this->logoPositionY + 16, 16, this->leftSideRecHeight - 32, Fade(BLACK, this->alpha));

        DrawRectangle(this->logoPositionX + 240, this->logoPositionY + 16, 16, this->rightSideRecHeight - 32, Fade(BLACK, this->alpha));
        DrawRectangle(this->logoPositionX, this->logoPositionY + 240, this->bottomSideRecWidth, 16, Fade(BLACK, this->alpha));

        DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(RAYWHITE, this->alpha));

        DrawText(TextSubtext("raylib", 0, this->lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(BLACK, this->alpha));
    }
}