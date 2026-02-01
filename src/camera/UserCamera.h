#pragma once
#include "raylib.h"
#include "raymath.h"

#define CAMERA_DEFAULT_SPEED 600
#define CAMERA_SHIFT_PRESSED_SPEED 1500

class UserCamera
{
  public:
    UserCamera();
    ~UserCamera();
    Camera2D camera;

    void process();
    void setCameraTarget(Vector2 target);
    void move(Vector2 delta);

  private:
    int cameraSpeed;
    float maxCameraZoom;
    float minCameraZoom;
    float zoomSpeed = 10.0f;

    void cameraInit();
    void cameraInputHandler();
};
