#include "UserCamera.h"



#include <iostream>

UserCamera::UserCamera()
{
    cameraInit();
}

void UserCamera::cameraInit()
{
    camera = {0};
    camera.target = {0.0f, 0.0f}; 
    camera.offset = {0.0f, 0.0f};
    camera.zoom = 1.0f;                               
    camera.rotation = 0.0f;                          

    cameraSpeed = CAMERA_DEFAULT_SPEED;
    maxCameraZoom = 3.0f;
    minCameraZoom = 0.5f;
}

void UserCamera::cameraInputHandler()
{
    cameraSpeed = IsKeyDown(KEY_LEFT_SHIFT) ? CAMERA_SHIFT_PRESSED_SPEED : CAMERA_DEFAULT_SPEED;

    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        camera.zoom += wheel * 0.1f;
        camera.zoom = Clamp(camera.zoom, minCameraZoom, maxCameraZoom);
    }

    Vector2 delta = {0, 0};
    if (IsKeyDown(KEY_D) && camera.target.x < worldBounds.width)
        delta.x += 1.0f;
    if (IsKeyDown(KEY_A) && camera.target.x > worldBounds.x)
        delta.x -= 1.0f;
    if (IsKeyDown(KEY_W) && camera.target.y > worldBounds.y)
        delta.y -= 1.0f;
    if (IsKeyDown(KEY_S) && camera.target.y < worldBounds.height)
        delta.y += 1.0f;

    if (delta != Vector2{0,0})
        move(delta);
}

void UserCamera::setCameraTarget(Vector2 target)
{
    camera.target = target;
}

void UserCamera::setCameraWorldBounds(Rectangle worldBounds)
{
    this->worldBounds = worldBounds;
}

void UserCamera::move(Vector2 delta)
{
    if (delta.x != 0 || delta.y != 0)
    {
        float dt = GetFrameTime();
        delta = Vector2Normalize(delta);
        camera.target.x += delta.x * cameraSpeed * dt;
        camera.target.y += delta.y * cameraSpeed * dt;
    }
}

void UserCamera::process()
{
    camera.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    cameraInputHandler();
    std::cout << "cameraX" << camera.target.x << "\ncameraY" << camera.target.y;
}

UserCamera::~UserCamera()
{
}
