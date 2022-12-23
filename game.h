#ifndef GAME_H
#define GAME_H

#include "camera.h"
#include "primitiveObject.h"

class Game
{
public:
    Game();

    void Init();
    void Update(float deltaTime);
    void Draw();
    void Run();
    void Destroy();

private:
    float dTime = 0.1f;
    float want_fps;

    double lastTime;
    int nbFrames;

    Camera2D cam2D;
    Camera3D cam3D;
    PrimitiveObject some_cube;
};

#endif // GAME_H
