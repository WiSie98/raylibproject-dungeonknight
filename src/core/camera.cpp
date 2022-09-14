#include "headerfiles/camera.h"

PlayerCamera::PlayerCamera(Player& player) : main_hud(this->main_hud_texture, 0, 0, 72, 24, 0, 0, 1.0f) {
    this->main_hud_texture = LoadTexture("./assets/graphics/spritesheets/dk_sptsht_ui_mainhud.png");
    this->main_hud.setSpritesheet(this->main_hud_texture);

    this->main_hud.setMaxHealth(player.getMaxHealth());
    this->main_hud.setMaxShield(player.getMaxShield());
    this->main_hud.setMaxStamina(player.getMaxStamina());

    setOffset(static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2));
    setZoom(3.0f);
    setRotation(0.0f);
}

PlayerCamera::~PlayerCamera() {
    UnloadTexture(this->main_hud_texture);
}

void PlayerCamera::update(Player& player) {
    this->main_hud.setHealth(player.getHealth());
    this->main_hud.setShield(player.getShield());
    this->main_hud.setStamina(player.getStamina());

    this->main_hud.update();
    this->main_hud.setSpritesheetDestination(player.getCurrentPosition().x - (static_cast<float>(GetScreenWidth() / 2)) / getPlayerCamera().zoom, player.getCurrentPosition().y - (static_cast<float>(GetScreenHeight() / 2)) / getPlayerCamera().zoom, this->main_hud.getSpritesheetDestination().width, this->main_hud.getSpritesheetDestination().height);
}

void PlayerCamera::draw(Player& player) {
    this->main_hud.draw();
    DrawTexturePro(this->main_hud_texture, Rectangle{ 96, 0, 216, 48 }, Rectangle{ player.getCurrentPosition().x - (216 * this->main_hud.getScale()) / 2, player.getCurrentPosition().y - (static_cast<float>(GetScreenHeight() / 2)) / getPlayerCamera().zoom, 216 * this->main_hud.getScale(), 48 * this->main_hud.getScale()}, Vector2{0, 0}, 0, WHITE);
    DrawText(TextFormat("%i", player.getMoney()), player.getCurrentPosition().x, (player.getCurrentPosition().y - (static_cast<float>(GetScreenHeight() / 2)) / getPlayerCamera().zoom) + 24, 4, BLACK);
}

//----------------------------Setter----------------------------------

void PlayerCamera::setTarget(Vector2 target) {
    this->playerCamera.target = target;
}

void PlayerCamera::setOffset(Vector2 offset) {
    this->playerCamera.offset = offset;
}

void PlayerCamera::setOffset(float x, float y) {
    this->playerCamera.offset.x = x;
    this->playerCamera.offset.y = y;
}

void PlayerCamera::setZoom(float zoom) {
    this->playerCamera.zoom = zoom;
}

void PlayerCamera::setRotation(float rotation) {
    this->playerCamera.rotation = rotation;
}

void PlayerCamera::setMainHUDTexture(Texture2D main_hud_texture) {
    this->main_hud_texture = main_hud_texture;
}

//----------------------------Getter----------------------------------

Camera2D PlayerCamera::getPlayerCamera() {
    return this->playerCamera;
}

Texture2D PlayerCamera::getMainHUDTexture() {
    return this->main_hud_texture;
}