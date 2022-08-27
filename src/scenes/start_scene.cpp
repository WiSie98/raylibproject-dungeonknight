#include "headerfiles/start_scene.h"

StartScene::StartScene() {
	setSceneType(START_SCENE);
}

StartScene::~StartScene() {}

void StartScene::update() {
    if (state == 0)
    {
        framesCounter++;

        if (framesCounter == 120)
        {
            state = 1;
            framesCounter = 0;
        }
    }
    else if (state == 1)
    {
        topSideRecWidth += 4;
        leftSideRecHeight += 4;

        if (topSideRecWidth == 256) state = 2;
    }
    else if (state == 2)
    {
        bottomSideRecWidth += 4;
        rightSideRecHeight += 4;

        if (bottomSideRecWidth == 256) state = 3;
    }
    else if (state == 3)
    {
        framesCounter++;

        if (framesCounter / 12)
        {
            lettersCount++;
            framesCounter = 0;
        }

        if (lettersCount >= 10)
        {
            alpha -= 0.02f;

            if (alpha <= 0.0f)
            {
                alpha = 0.0f;
                state = 4;
            }
        }
    }
    else if (state == 4)
    {
        is_finished = true;
    }
}

void StartScene::draw() {
    if (state == 0)
    {
        if ((framesCounter / 15) % 2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
    }
    else if (state == 1)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
    }
    else if (state == 2)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

        DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
    }
    else if (state == 3)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

        DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

        DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(RAYWHITE, alpha));

        DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(BLACK, alpha));
    }
}

SceneType StartScene::setNextScene() {
	if (is_finished || IsKeyPressed(KEY_SPACE)) {

        is_finished = false;
        framesCounter = 0;
        lettersCount = 0;

        topSideRecWidth = 16;
        bottomSideRecWidth = 16;

        rightSideRecHeight = 16;
        leftSideRecHeight = 16;

        alpha = 1.0f;
        state = 0;

		return MAIN_MENU_SCENE;
	}
	return START_SCENE;
}