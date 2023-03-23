#include "../Actors/Ability.h"
#include "../Actors/Actor.h"
#include "../Actors/Ball.h"
#include "../Math/Collision.h"
#include "../Actors/Cursor.h"
#include "../GameMode/Game.h"
#include "../GameMode/GameMode.h"
#include "../Actors/Laser.h"
#include "../Actors/Life.h"
#include "../GameMode/LevelLoader.h"
#include "../Actors/Platform.h"
#include "../Renderer/Renderer.h"
#include "../Window/Window.h"
#include "../Texture/TextureManager.h"

#include <iostream>

Game::Game()
    : mTicksCount(0)
    , mIsRunning(true)
{
}

bool Game::Initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = new Window();
    if (!mWindow->Initialize(cScreenWidth, cScreenHeight))
    {
        SDL_Log("Failed to initialize Window");
        delete mWindow;
        mWindow = nullptr;
        return false;
    }

    mRenderer = new Renderer();
    if (!mRenderer->InitializeRenderer(this))
    {
        SDL_Log("Failed to initialize renderer");
        delete mRenderer;
        mRenderer = nullptr;
        return false;
    }

    mTextureManager = new TextureManager(mRenderer);

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    mGameMode = new GameMode(this);

    mGameMode->Initialize();

    mTicksCount = SDL_GetTicks();

    return true;
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION:
        {
            SDL_ShowCursor(0);
            Vector2D position((float)event.motion.x, (float)event.motion.y);
            if (mCursor)
            {
                mCursor->SetPosition(position);
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button = SDL_BUTTON_LEFT && !mBall->IsLaunched())
            {
                Vector2D positionBall = mBall->GetPosition();
                Vector2D velocity = mBall->GetVelocity();
                Vector2D positionCursor = mCursor->GetPosition();

                velocity.mX = positionCursor.mX - positionBall.mX;
                velocity.mY = positionCursor.mY - positionBall.mY;
                velocity.Normalize();
                velocity = velocity * mBall->GetDefaultVelocity();

                if (mCursor)
                {
                    delete mCursor;
                    mCursor = nullptr;
                }

                mBall->SetVelocity(velocity);

                mBall->SetLaunched(true);
            }
            break;
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
    mPlatform->ProcessKeyboard(state);
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    mTicksCount = SDL_GetTicks();

    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }

    mGameMode->Update(deltaTime);

    std::vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == Actor::State::EDead)
        {
            deadActors.emplace_back(actor);
        }
    }

    for (auto actor : deadActors)
    {
        delete actor;
    }
}

void Game::GenerateOutput()
{
    mRenderer->GenerateOutput();
}

void Game::Shutdown()
{
    UnloadData();

    if (mGameMode)
    {
        delete mGameMode;
        mGameMode = nullptr;
    }

    if (mTextureManager)
    {
        mTextureManager->Shutdown();
        delete mTextureManager;
        mTextureManager = nullptr;
    }

    if (mRenderer)
    {
        mRenderer->Shutdown();
        delete mRenderer;
        mRenderer = nullptr;
    }
    if (mWindow)
    {
        mWindow->Shutdown();
        delete mWindow;
        mWindow = nullptr;
    }
    SDL_Quit();
}

void Game::UnloadData()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }
}

void Game::AddBlock(Block* block)
{
    mBlocks.emplace_back(block);
}

void Game::AddActor(Actor* actor)
{
    mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
    auto iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::RemoveBlock(Block* block)
{
    auto iter = std::find(mBlocks.begin(), mBlocks.end(), block);
    if (iter != mBlocks.end())
    {
        mBlocks.erase(iter);
    }
}

void Game::AddAbility(Ability* ability)
{
    mAbilities.emplace_back(ability);
}

void Game::RemoveAbility(Ability* ability)
{
    auto iter = std::find(mAbilities.begin(), mAbilities.end(), ability);
    if (iter != mAbilities.end())
    {
        mAbilities.erase(iter);
    }
}

void Game::AddLife(Life* life)
{
    mLifes.emplace_back(life);
}

void Game::RemoveLife(Life* life)
{
    auto iter = std::find(mLifes.begin(), mLifes.end(), life);
    if (iter != mLifes.end())
    {
        mLifes.erase(iter);
    }
}
