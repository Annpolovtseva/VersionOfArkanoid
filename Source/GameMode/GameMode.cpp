#include "../Actors/Ability.h"
#include "../Actors/Ball.h"
#include "../Math/Collision.h"
#include "../Actors/Cursor.h"
#include  "../GameMode/Game.h"
#include  "../GameMode/GameMode.h"
#include  "../GameMode/LevelLoader.h"
#include "../Actors/Life.h"
#include "../Actors/Platform.h"
#include "../Renderer/Renderer.h"
#include "../Window/Window.h"
#include <iostream>

static const int cNumberOfLifes = 3;

GameMode::GameMode(Game* game)
    : mNumberOfLifes(0)
    , mAllBlocksDestroyed(false)
    , mTimeToAppearanceAbility(15.0f)
    , mLevelIndex(0)
    , mGame(game)
{

}

GameMode::~GameMode()
{
}
void GameMode::Initialize()
{
    LevelLoader::Load(mGame, mLevelIndex);

    LoadLifes();
}

void GameMode::LoadLifes()
{
    float screenWidth = mGame->GetWindow()->GetScreenWidth();
    float screenHeight = mGame->GetWindow()->GetScreenHeight();

    mNumberOfLifes = cNumberOfLifes;
    Vector2D lifePosition;
    int countLifes = 1;
    for (int i = 0; i < mNumberOfLifes; i++)
    {
        new Life(mGame);
    }
    for (Life* life : mGame->GetLifes())
    {
        lifePosition.mX = screenWidth - life->GetWidth() * countLifes;
        lifePosition.mY = life->GetHeight();
        life->SetPosition(lifePosition);
        countLifes++;
    }
}

void GameMode::Update(float deltaTime)
{
    UpdateAbilities(deltaTime);
    UpdateBloks();
    CheckWinLoseConditions();
}

void GameMode::UpdateAbilities(float deltaTime)
{
    float screenWidth = mGame->GetWindow()->GetScreenWidth();
    float screenHeight = mGame->GetWindow()->GetScreenHeight();

    float timeToAppearance = mTimeToAppearanceAbility;

    if (mGame->GetBall())
    {
        if (mGame->GetBall()->IsLaunched())
        {
            mTimeToAppearanceAbility = timeToAppearance - deltaTime;
        }
        else if (!mGame->GetBall()->IsLaunched())
        {
            mTimeToAppearanceAbility = 15.0f;
        }
    }
    if (timeToAppearance <= 0)
    {
        mTimeToAppearanceAbility = 15.0f;
        Ability* ability = new Ability(mGame);
    }

    for (auto abilityIter = mGame->GetAbilities().begin(); abilityIter != mGame->GetAbilities().end();)
    {
        if (CollisionRectangleToRectangle(mGame->GetPlatform()->GetPosition(), mGame->GetPlatform()->GetSize(), (*abilityIter)->GetPosition(), (*abilityIter)->GetSize()))
        {
            mGame->GetPlatform()->GainAbility((*abilityIter)->GetAbilityType());
            delete *abilityIter;
            abilityIter = mGame->GetAbilities().begin();
        }
        else
        {
            abilityIter++;
        }
    }

    for (Ability* ability : mGame->GetAbilities())
    {
        if ((ability->GetPosition().mY + (ability->GetHeight() / 2.0f)) > screenHeight)
        {
            ability->SetState(Actor::State::EDead);
        }
    }
}

void GameMode::UpdateBloks()
{
    mAllBlocksDestroyed = true;
    for (Block* block : mGame->GetBlocks())
    {
        if (block == nullptr)
        {
            continue;
        }
        if (block->GetType() != BlockType::Indestructible && block->GetHealth() > 0)
        {
            mAllBlocksDestroyed = false;
            break;
        }
    }
}

void GameMode::CheckWinLoseConditions()
{
    float screenWidth = mGame->GetWindow()->GetScreenWidth();
    float screenHeight = mGame->GetWindow()->GetScreenHeight();

    if (mGame->GetBall()->GetPosition().mY > screenHeight)
    {
        if (mNumberOfLifes == 0)
        {
            std::cout << "You Lost" << std::endl;
            mGame->UnloadData();
            Initialize();
        }
        else
        {
            mNumberOfLifes--;
            for (Life* life : mGame->GetLifes())
            {
                if (life == mGame->GetLifes().back())
                {
                    life->SetState(Actor::State::EDead);
                }
            }
            mGame->GetBall()->SetLaunched(false);
            Cursor* cursor = new Cursor(mGame);
            mGame->AddCursor(cursor);
        }
    }
    else if (mGame->GetBall()->IsCaught())
    {
        std::cout << "You Win" << std::endl;
        mGame->UnloadData();
        mLevelIndex++;
        if (mLevelIndex >= cLevelsNumber)
        {
            mLevelIndex = 0;
        }
        Initialize();
    }
}
