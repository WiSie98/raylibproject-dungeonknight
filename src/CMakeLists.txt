cmake_minimum_required(VERSION 3.11)

include(../cmake/raylib.cmake)

project(Dungeon_Knight VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp "core/headerfiles/header.h" "core/headerfiles/container.h" "core/container.cpp" "core/headerfiles/scene.h" "core/headerfiles/scene_manager.h" "core/scene_manager.cpp" "core/scene.cpp" "scenes/headerfiles/main_menu_scene.h" "scenes/headerfiles/start_scene.h" "scenes/start_scene.cpp" "scenes/main_menu_scene.cpp" "scenes/headerfiles/scenes.h" "core/headerfiles/actor_base.h" "core/actor_base.cpp" "core/headerfiles/item_base.h" "core/item_base.cpp" "actors/headerfiles/actor_player.h" "actors/actor_player.cpp" "scenes/headerfiles/woodland_scene.h" "scenes/woodland_scene.cpp" "actors/headerfiles/actor_enemy.h" "actors/actor_enemy.cpp" "items/headerfiles/item_weapon.h" "items/item_weapon.cpp" "items/headerfiles/item_consumable.h" "items/item_consumable.cpp" "items/headerfiles/item_usable.h" "items/item_usable.cpp" "core/headerfiles/animation.h" "core/animation.cpp")

# Add config.h.in file
configure_file(config.h.in config.h)
target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

#  Link to Raylib
target_link_libraries(${PROJECT_NAME} raylib)

# Copy assets to assets path
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_LIST_DIR}/../cmake/copy-assets.cmake"
        )
add_dependencies(${PROJECT_NAME} copy_assets)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif ()

# CPack instructions
# call e.g. cpack -G ZIP -C Debug to create a binary distribution
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${PROJECT_NAME}_Bundle")
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/assets" DESTINATION "${PROJECT_NAME}_Bundle")