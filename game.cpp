#include "game.h"

#include <unistd.h>

#include "engine.h"
#include "gameObject.h"

#include "transform.h"
#include "e_math.h"
#include "tools.h"

Game::Game()
{

}

void Game::Init()
{

    EngineInitSystem(1024, 800, "Test");


    Camera2DInit(&cam2D);
    Camera3DInit(&cam3D);

    want_fps = 60;

    lastTime = 0;
    nbFrames = 0;

    char path[] = "/home/ilia/Projects/TestCPP/";

    DrawParam dParam;
    memset(&dParam, 0, sizeof(DrawParam));
    ToolsAddStrings(dParam.diffuse, 256, path, "textures/texture.jpg");
    SphereParam sParam;
    sParam.radius = 1.0f;
    sParam.sectorCount = 20;
    sParam.stackCount = 20;
    PrimitiveObjectInit(&some_cube, dParam, ENGINE_PRIMITIVE3D_SPHERE, &sParam);
    Transform3DSetPosition((GameObject3D *)&some_cube, 0, 0, -1);
}

void Game::Update(float deltaTime)
{

}

void Game::Draw()
{
    EngineDraw(&some_cube);
}

void Game::Run()
{
    while(!EngineWindowIsClosed()){
        double startTime = EngineGetTime();
        EnginePoolEvents();
        Update(dTime);
        Draw();
        EngineLoop();
        double endTime = EngineGetTime();

        //Вычисление потенциала обновления кадров, для дальнейшего использования
        dTime = startTime - endTime;
        if(dTime < 0)
            dTime = -dTime;

        //Ограничение кадров
        int time_to_sleep = (1.f/want_fps - dTime);

        if (time_to_sleep > 0) {
            sleep(time_to_sleep);
        }

        double curr_time = EngineGetTime();

        nbFrames++;
        if (curr_time - lastTime > 1.0f ){
            //fpsCounter = nbFrames;
            nbFrames = 0;
            lastTime = curr_time;
        }
    }

    EngineDeviceWaitIdle();
}

void Game::Destroy()
{
    GameObjectDestroy((GameObject *)&some_cube);

    EngineCleanUp();
}
