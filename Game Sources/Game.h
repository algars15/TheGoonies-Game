#pragma once
#include "Globals.h"
#include "Scene.h"

enum class GameState { CREDITS, MENU, MENU_START, PLAYING, WIN, LOSE };

class Game
{
public:
    Game();
    ~Game();

    AppStatus Initialise(float scale);
    AppStatus Update();
    void Render();
    void Cleanup();

private:
    AppStatus BeginPlay();
    void FinishPlay();

    AppStatus LoadResources();
    void UnloadResources();

    GameState state;
    Scene *scene;
    const Texture2D *img_menu, *img_menu_start, *img_credits, *img_win, *img_lose;

    Music music[NUM_MUSIC];

    //To work with original game units and then scale the result
    RenderTexture2D target;
    Rectangle src, dst;
};