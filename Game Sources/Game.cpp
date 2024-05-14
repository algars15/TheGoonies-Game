#include "Game.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <stdio.h>

Game::Game()
{
    state = GameState::CREDITS;
    scene = nullptr;
    img_menu = nullptr;

    target = {};
    src = {};
    dst = {};
}
Game::~Game()
{
    if (scene != nullptr)
    {
        scene->Release();
        delete scene;
        scene = nullptr;
    }
}
AppStatus Game::Initialise(float scale)
{
    float w, h;
    w = WINDOW_WIDTH * scale;
    h = WINDOW_HEIGHT * scale;

    //Initialise window
    InitWindow((int)w, (int)h, "The Goonies");

    //Render texture initialisation, used to hold the rendering result so we can easily resize it
    target = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (target.id == 0)
    {
        LOG("Failed to create render texture");
        return AppStatus::ERROR;
    }
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
    src = { 0, 0, WINDOW_WIDTH, -WINDOW_HEIGHT };
    dst = { 0, 0, w, h };

    //Load resources
    if (LoadResources() != AppStatus::OK)
    {
        LOG("Failed to load resources");
        return AppStatus::ERROR;
    }

    InitAudioDevice();

    music[0] = LoadMusicStream("sound/music/01_Opening_Demo.ogg");
    music[1] = LoadMusicStream("sound/music/02_The Goonies_'R'_Good_Enough.ogg");
    music[2] = LoadMusicStream("sound/music/04_Game_Clear.ogg");
    music[3] = LoadMusicStream("sound/music/06_Game_Over.ogg");

    //Set the target frame rate for the application
    SetTargetFPS(60);
    //Disable the escape key to quit functionality
    SetExitKey(0);

    return AppStatus::OK;
}
AppStatus Game::LoadResources()
{
    ResourceManager& data = ResourceManager::Instance();

    //Credits
    if (data.LoadTexture(Resource::IMG_CREDITS, "images/Credits.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_credits = data.GetTexture(Resource::IMG_CREDITS);
   


    //menu
    if (data.LoadTexture(Resource::IMG_MENU, "images/menu.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_menu = data.GetTexture(Resource::IMG_MENU);
    


    //menu start
    if (data.LoadTexture(Resource::IMG_MENU_START, "images/menu_start.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_menu_start = data.GetTexture(Resource::IMG_MENU_START);
    return AppStatus::OK;

    //WIN
    if (data.LoadTexture(Resource::IMG_WIN, "images/GooniesWinScreen.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_win = data.GetTexture(Resource::IMG_WIN);
    return AppStatus::OK;

    //LOSE
    if (data.LoadTexture(Resource::IMG_LOSE, "images/GooniesLoseScreen.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_lose = data.GetTexture(Resource::IMG_LOSE);
    return AppStatus::OK;

}

AppStatus Game::BeginPlay()
{
    scene = new Scene();
    if (scene == nullptr)
    {
        LOG("Failed to allocate memory for Scene");
        return AppStatus::ERROR;
    }
    if (scene->Init() != AppStatus::OK)
    {
        LOG("Failed to initialise Scene");
        return AppStatus::ERROR;
    }

    return AppStatus::OK;
}
void Game::FinishPlay()
{
    scene->Release();
    delete scene;
    scene = nullptr;
}
AppStatus Game::Update()
{
    //Check if user attempts to close the window, either by clicking the close button or by pressing Alt+F4
    if(WindowShouldClose()) return AppStatus::QUIT;

    switch (state)
    {
        case GameState::CREDITS: 
            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (IsKeyPressed(KEY_SPACE))
            {
                if(BeginPlay() != AppStatus::OK) return AppStatus::ERROR;
                state = GameState::MENU;
            }
            break;

        case GameState::MENU:
            PlayMusicStream(music[0]);
            UpdateMusicStream(music[0]);
            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (IsKeyPressed(KEY_SPACE))
            {
                if (BeginPlay() != AppStatus::OK) return AppStatus::ERROR;
                state = GameState::MENU_START;
            }
            break;

        case GameState::MENU_START:
            UpdateMusicStream(music[0]);
            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (IsKeyPressed(KEY_SPACE))
            {
                if (BeginPlay() != AppStatus::OK) return AppStatus::ERROR;
                state = GameState::PLAYING;
            }
            break;

        case GameState::PLAYING:  
            StopMusicStream(music[0]);
            PlayMusicStream(music[1]);
            UpdateMusicStream(music[1]);
            if (IsKeyPressed(KEY_ESCAPE))
            {
                FinishPlay();
                state = GameState::MENU_START;
                StopMusicStream(music[1]);
            }
            //else if (IsKeyPressed(KEY_W))
            //{
            //    FinishPlay();
            //    state = GameState::WIN;
            //    if (BeginPlay() != AppStatus::OK) return AppStatus::ERROR;
            //    state = GameState::WIN;
            //    StopMusicStream(music[1]);
            //    PlayMusicStream(music[2]);
            //    UpdateMusicStream(music[2]);

            //}
            //else if (IsKeyPressed(KEY_L))
            //{
            //    FinishPlay();
            //    state = GameState::LOSE;
            //    if (BeginPlay() != AppStatus::OK) return AppStatus::ERROR;
            //    state = GameState::LOSE;
            //    StopMusicStream(music[1]);
            //    PlayMusicStream(music[3]);
            //    UpdateMusicStream(music[3]);
            //}
            else
            {
                //Game logic
                scene->Update();
            }
            break;
    }
    return AppStatus::OK;
}
void Game::Render()
{
    //Draw everything in the render texture, note this will not be rendered on screen, yet
    BeginTextureMode(target);
    ClearBackground(BLACK);
    
    switch (state)
    {
        case GameState::CREDITS:
            DrawTexture(*img_credits, 0, 0, WHITE);
        break;
        case GameState::MENU:
            DrawTexture(*img_menu, 0, 0, WHITE);
            break;
        case GameState::MENU_START:
            DrawTexture(*img_menu_start, 0, 0, WHITE);
            break;
        //case GameState::WIN:
        //    DrawTexture(*img_win, 0, 0, WHITE);
        //    break;
        //case GameState::LOSE:
        //    DrawTexture(*img_lose, 0, 0, WHITE);
        //    break;
  
        case GameState::PLAYING:
            scene->Render();
            break;
    }
    
    EndTextureMode();

    //Draw render texture to screen, properly scaled
    BeginDrawing();
    DrawTexturePro(target.texture, src, dst, { 0, 0 }, 0.0f, WHITE);
    EndDrawing();
}
void Game::Cleanup()
{
    UnloadResources();
    CloseWindow();
}
void Game::UnloadResources()
{
    ResourceManager& data = ResourceManager::Instance();
    data.ReleaseTexture(Resource::IMG_MENU);

    UnloadRenderTexture(target);
}