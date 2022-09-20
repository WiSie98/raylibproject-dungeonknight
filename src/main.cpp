#include <cstdlib>

#include "raylib.h"
#include "config.h"

#include "core/headerfiles/header.h"
#include "scenes/headerfiles/scenes.h"
#include "core/headerfiles/scene_manager.h"
#include "actors/headerfiles/actor_player.h"
#include "core/headerfiles/camera.h"

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file

	unsigned int target_fps = 60;       // Flag to set the Target FPS
    bool exitWindowRequested = false;   // Flag to request window to exit
    bool exitWindow = false;            // Flag to set window to exit

    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    InitAudioDevice();
    SetTargetFPS(target_fps);
    SetExitKey(KEY_F4);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    //Initialization code here
    Texture2D player_texture = LoadTexture("assets/graphics/spritesheets/actors/dk_sptsht_playercharacter.png");

    SceneManager sceneManager;
    GenerateScenes(&sceneManager.getScenes());
    sceneManager.switchToScene(START_SCENE);

    Player player(1000, 500, 100, 0, 0, player_texture);

    PlayerCamera playerCamera(player);

    // Main game loop
    while (!exitWindow) // Detect window close button or ESC key
    {
        //Update code here
        if (WindowShouldClose() || exitWindowRequested) {
			exitWindow = true;
        }

        sceneManager.switchToScene(sceneManager.getCurrentScene()->setNextScene(player, exitWindowRequested));
        sceneManager.update(player, playerCamera);

        playerCamera.setTarget(player.getCurrentPosition());

        BeginDrawing();
            //Draw code between BeginDrawing() and EndDrawing()
            ClearBackground(WHITE);

            sceneManager.draw(player, playerCamera);

        EndDrawing();

    } // Main game loop end

    //De-initialization code here
    UnloadTexture(player_texture);

    // Close window and OpenGL context
    CloseAudioDevice();
    CloseWindow();

    return EXIT_SUCCESS;
}
