#include <cstdlib>

#include "raylib.h"
#include "config.h"

#include "core/headerfiles/header.h"
#include "scenes/headerfiles/scenes.h"
#include "core/headerfiles/scene_manager.h"
#include "actors/headerfiles/actor_player.h"

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
    Texture2D player_texture = LoadTexture("assets/graphics/sprites/dk_spt_player.png");

    SceneManager sceneManager;
    GenerateScenes(sceneManager.getScenes());
    sceneManager.switchToScene(START_SCENE);

    Player player(100, 100, 100, 5, 0, 0, player_texture);

    Camera2D playerCamera;
    playerCamera.offset.x = GetScreenWidth() / 2;
    playerCamera.offset.y = GetScreenHeight() / 2;
    playerCamera.zoom = 3.0f;
    playerCamera.rotation = 0;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        //Update code here
        sceneManager.switchToScene(sceneManager.getCurrentScene()->setNextScene(player));
        sceneManager.update(player, playerCamera);

        playerCamera.target = player.getCurrentPosition();

        BeginDrawing();
            //Draw code between BeginDrawing() and EndDrawing()
            ClearBackground(WHITE);

            sceneManager.draw(player, playerCamera);

        EndDrawing();

        frame_counter++;
    } // Main game loop end

    //De-initialization code here
    UnloadTexture(player_texture);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
