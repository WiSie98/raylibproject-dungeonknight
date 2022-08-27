#include <cstdlib>

#include "raylib.h"
#include "config.h"

#include "core/headerfiles/header.h"
#include "scenes/headerfiles/scenes.h"
#include "core/headerfiles/scene_manager.h"

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    
    unsigned int target_fps = 60;
    unsigned int frame_counter = 0;

    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(target_fps);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    //Initialization code here
    std::shared_ptr<StartScene> startScene = std::make_shared<StartScene>();

    SceneManager sceneManager(startScene);
    GenerateScenes(sceneManager.scenes);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        //Update code here
        sceneManager.switchToScene(sceneManager.getCurrentScene()->setNextScene());
        sceneManager.update();

        BeginDrawing();
            //Draw code between BeginDrawing() and EndDrawing()
            ClearBackground(WHITE);
            sceneManager.draw();

        EndDrawing();

        frame_counter++;
    } // Main game loop end

    //De-initialization code here
    //UnloadTexture(myTexture);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
