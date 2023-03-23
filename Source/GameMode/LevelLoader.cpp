#include "../Components/BGSpriteComponent.h"
#include "../Actors/Ball.h"
#include "../Actors/Block.h"
#include "../Actors/Cursor.h"
#include  "../GameMode/Game.h"
#include  "../GameMode/GameMode.h"
#include  "../GameMode/LevelLoader.h"
#include "../Actors/Life.h"
#include "../Actors/Platform.h"
#include "../Renderer/Renderer.h"
#include "../Window/Window.h"
#include "../Texture/TextureManager.h"

LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{
}

void LevelLoader::Load(Game* game, int levelIndex)
{
    LevelLoader level;
    level.LoadTextures(game);
    level.AddLevelBlocks();
    level.LoadBGSprite(game);
    level.LoadBlocks(game, level.mBlockLevelData[levelIndex]);
    level.LoadMainActors(game);
}

void LevelLoader::LoadTextures(Game* game)
{
    game->GetTextureManager()->GetTexture("Data/Background.jpg");
    game->GetTextureManager()->GetTexture("Data/Stars.png");
    game->GetTextureManager()->GetTexture("Data/03-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/04-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/11-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/12-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/13-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/14-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/41-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/42-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/46-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/47-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/48-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/50-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/51-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/52-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/53-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/54-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/55-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/57-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/59-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/60-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/61-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/65-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/66-Breakout-Tiles.png");
    game->GetTextureManager()->GetTexture("Data/67-Breakout-Tiles.png");
}

void LevelLoader::LoadBGSprite(Game* game)
{
    float screenWidth = game->GetWindow()->GetScreenWidth();
    float screenHeight = game->GetWindow()->GetScreenHeight();

    Actor* temp = new Actor(game);
    temp->SetPosition(Vector2D((float)screenWidth / 2.0f, (float)screenHeight / 2.0f));
    BGSpriteComponent* background = new BGSpriteComponent(temp);
    background->SetScreenSize(Vector2D((float)screenWidth, (float)screenHeight));
    std::vector<Texture*> bgtexs = {
        game->GetTextureManager()->GetTexture("Data/Background.jpg"),
        game->GetTextureManager()->GetTexture("Data/Background.jpg")
    };
    background->SetBGTextures(bgtexs);
    background->SetScrollSpeed(-100.0f);
    background = new BGSpriteComponent(temp, 50);
    background->SetScreenSize(Vector2D((float)screenWidth, (float)screenHeight));
    bgtexs = {
        game->GetTextureManager()->GetTexture("Data/Stars.png"),
        game->GetTextureManager()->GetTexture("Data/Stars.png")
    };
    background->SetBGTextures(bgtexs);
    background->SetScrollSpeed(-200.0f);
}

void LevelLoader::LoadBlocks(Game* game,const std::vector<InitBlockData>& initLevelBlockData)
{
    game->GetBlocks().reserve(initLevelBlockData.size());

    for (size_t i = 0; i < initLevelBlockData.size(); i++)
    {
        new Block(game, initLevelBlockData[i]);
    }
}

void LevelLoader::LoadMainActors(Game* game)
{
    Cursor* cursor = new Cursor(game);
    game->AddCursor(cursor);

    float screenWidth = game->GetWindow()->GetScreenWidth();
    float screenHeight = game->GetWindow()->GetScreenHeight();

    Platform* platform = new Platform(game);
    platform->SetPosition(Vector2D(screenWidth / 2.0f, screenHeight * 0.95f));
    game->AddPlatform(platform);

    Ball* ball = new Ball(game);
    Vector2D ballPosition;
    float platformPositionY = game->GetPlatform()->GetPosition().mY;
    float ballHalfWidth = ball->GetWidth() / 2.0f;
    float platformHalfHeight = game->GetPlatform()->GetHeight() / 2.0f;
    ballPosition.mX = screenWidth / 2.0f;
    ballPosition.mY = platformPositionY - platformHalfHeight - ballHalfWidth;
    ball->SetPosition(ballPosition);
    game->AddBall(ball);
}

void LevelLoader::AddLevelBlocks()
{
    const int sizeWidth = 96;
    const int sizeHeight = 32;
    float pointXForInit = 130.0f;
    float pointYForInit = 100.0f;
    //Level 1
    mBlockLevelData[0] = { {Vector2D{pointXForInit, pointYForInit}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth, pointYForInit}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit}, BlockType::TwoLife},
        {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit}, BlockType::TwoLife}, {Vector2D{pointXForInit + sizeWidth * 4, pointYForInit}, BlockType::Indestructible}, {Vector2D{pointXForInit + sizeWidth * 5, pointYForInit}, BlockType::TwoLife},
        {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit}, BlockType::TwoLife}, {Vector2D{pointXForInit + sizeWidth * 7, pointYForInit}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 8, pointYForInit}, BlockType::OneLife},

        {Vector2D{pointXForInit, pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 2}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4, pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 5, pointYForInit + sizeHeight * 2}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 7, pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 8, pointYForInit + sizeHeight * 2}, BlockType::OneLife},

        {Vector2D{pointXForInit, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 4}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 5, pointYForInit + sizeHeight * 4}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 7, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 8, pointYForInit + sizeHeight * 4}, BlockType::OneLife},

        {Vector2D{pointXForInit, pointYForInit + sizeHeight * 5}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight * 5}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 5}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 5}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4, pointYForInit + sizeHeight * 5}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 5, pointYForInit + sizeHeight * 5}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight * 5}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 7, pointYForInit + sizeHeight * 5}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 8, pointYForInit + sizeHeight * 5}, BlockType::OneLife},

        {Vector2D{pointXForInit, pointYForInit + sizeHeight * 6}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight * 6}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 6}, BlockType::TwoLife},
        {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 6}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4, pointYForInit + sizeHeight * 6}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 5, pointYForInit + sizeHeight * 6}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight * 6}, BlockType::TwoLife}, {Vector2D{pointXForInit + sizeWidth * 7, pointYForInit + sizeHeight * 6}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 8, pointYForInit + sizeHeight * 6}, BlockType::OneLife},
    };

    pointXForInit = 80.0f;

    mBlockLevelData[1] = { {Vector2D{pointXForInit, pointYForInit}, BlockType::Indestructible}, {Vector2D{pointXForInit + sizeWidth * 1.5f, pointYForInit}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4.5f, pointYForInit}, BlockType::TwoLife},
        {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit}, BlockType::OneLife},{Vector2D{pointXForInit + sizeWidth * 7.5f, pointYForInit}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 9, pointYForInit}, BlockType::Indestructible},

        {Vector2D{pointXForInit, pointYForInit + sizeHeight}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 1.5f, pointYForInit + sizeHeight}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4.5f, pointYForInit + sizeHeight}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 7.5f, pointYForInit + sizeHeight}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 9, pointYForInit + sizeHeight}, BlockType::OneLife},

        {Vector2D{pointXForInit, pointYForInit + sizeHeight * 2}, BlockType::TwoLife}, {Vector2D{pointXForInit + sizeWidth * 1.5f, pointYForInit + sizeHeight * 2}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4.5f, pointYForInit + sizeHeight * 2}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 7.5f, pointYForInit + sizeHeight * 2}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 9, pointYForInit + sizeHeight * 2}, BlockType::TwoLife},

        {Vector2D{pointXForInit, pointYForInit + sizeHeight * 3}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 1.5f, pointYForInit + sizeHeight * 3}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 3}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4.5f, pointYForInit + sizeHeight * 3}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight * 3}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 7.5f, pointYForInit + sizeHeight * 3}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 9, pointYForInit + sizeHeight * 3}, BlockType::OneLife},

        {Vector2D{pointXForInit, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 1.5f, pointYForInit + sizeHeight * 4}, BlockType::Indestructible},
        {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4.5f, pointYForInit + sizeHeight * 4}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight * 4}, BlockType::Indestructible}, {Vector2D{pointXForInit + sizeWidth * 7.5f, pointYForInit + sizeHeight * 4}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 9, pointYForInit + sizeHeight * 4}, BlockType::OneLife},

        {Vector2D{pointXForInit, pointYForInit + sizeHeight * 5}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 1.5f, pointYForInit + sizeHeight * 5}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 5}, BlockType::TwoLife}, {Vector2D{pointXForInit + sizeWidth * 4.5f, pointYForInit + sizeHeight * 5}, BlockType::OneLife},
        {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight * 5}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 7.5f, pointYForInit + sizeHeight * 5}, BlockType::TwoLife},
        {Vector2D{pointXForInit + sizeWidth * 9, pointYForInit + sizeHeight * 5}, BlockType::OneLife}
    };

    // Level 3
    mBlockLevelData[2] = { {Vector2D{pointXForInit + sizeWidth, pointYForInit}, BlockType::TwoLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit}, BlockType::TwoLife},
                {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit}, BlockType::TwoLife}, {Vector2D{pointXForInit + sizeWidth * 4, pointYForInit}, BlockType::TwoLife},
                {Vector2D{pointXForInit + sizeWidth * 5, pointYForInit}, BlockType::TwoLife}, {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit}, BlockType::TwoLife},
                {Vector2D{pointXForInit + sizeWidth * 7, pointYForInit}, BlockType::TwoLife}, {Vector2D{pointXForInit + sizeWidth * 8, pointYForInit}, BlockType::TwoLife},

                {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight}, BlockType::OneLife},
                {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4, pointYForInit + sizeHeight}, BlockType::OneLife},
                {Vector2D{pointXForInit + sizeWidth * 5, pointYForInit + sizeHeight}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight}, BlockType::OneLife},
                {Vector2D{pointXForInit + sizeWidth * 7, pointYForInit + sizeHeight}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 8, pointYForInit + sizeHeight}, BlockType::OneLife},

                {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 2}, BlockType::OneLife},
                {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4, pointYForInit + sizeHeight * 2}, BlockType::OneLife},
                {Vector2D{pointXForInit + sizeWidth * 5, pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight * 2}, BlockType::OneLife},
                {Vector2D{pointXForInit + sizeWidth * 7, pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 8, pointYForInit + sizeHeight * 2}, BlockType::OneLife},

                {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight * 3}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 3}, BlockType::OneLife},
                {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 3}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4, pointYForInit + sizeHeight * 3}, BlockType::OneLife},
                {Vector2D{pointXForInit + sizeWidth * 5, pointYForInit + sizeHeight * 3}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight * 3}, BlockType::OneLife},
                {Vector2D{pointXForInit + sizeWidth * 7, pointYForInit + sizeHeight * 3}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 8, pointYForInit + sizeHeight * 3}, BlockType::OneLife},

                {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 4}, BlockType::OneLife},
                {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 4, pointYForInit + sizeHeight * 4}, BlockType::OneLife},
                {Vector2D{pointXForInit + sizeWidth * 5, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 6, pointYForInit + sizeHeight * 4}, BlockType::OneLife},
                {Vector2D{pointXForInit + sizeWidth * 7, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 8, pointYForInit + sizeHeight * 4}, BlockType::OneLife},

                {Vector2D{pointXForInit, pointYForInit + sizeHeight * 7}, BlockType::Indestructible},
                {Vector2D{pointXForInit - sizeWidth + sizeWidth * 4, pointYForInit + sizeHeight * 7}, BlockType::Indestructible}, {Vector2D{pointXForInit - sizeWidth + sizeWidth * 5.5f, pointYForInit + sizeHeight * 7}, BlockType::Indestructible},
                {Vector2D{pointXForInit - sizeWidth + sizeWidth * 7, pointYForInit + sizeHeight * 7}, BlockType::Indestructible},
                {Vector2D{pointXForInit - sizeWidth + sizeWidth * 10, pointYForInit + sizeHeight * 7}, BlockType::Indestructible}
    };

    // Level 4
    pointXForInit = 1024.0f / 2.0f - sizeWidth / 2.0f;

    mBlockLevelData[3] = { {Vector2D{pointXForInit, pointYForInit}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth , pointYForInit}, BlockType::OneLife},
                       {Vector2D{pointXForInit - sizeWidth , pointYForInit + sizeHeight}, BlockType::OneLife},{Vector2D{pointXForInit, pointYForInit + sizeHeight}, BlockType::OneLife},
                       {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight}, BlockType::Indestructible}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight}, BlockType::OneLife},

                       {Vector2D{pointXForInit - sizeWidth , pointYForInit + sizeHeight * 2}, BlockType::OneLife},{Vector2D{pointXForInit, pointYForInit + sizeHeight * 2}, BlockType::OneLife},
                       {Vector2D{pointXForInit + sizeWidth , pointYForInit + sizeHeight * 2}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 2}, BlockType::OneLife},

                       {Vector2D{pointXForInit - sizeWidth , pointYForInit + sizeHeight * 3}, BlockType::Indestructible},{Vector2D{pointXForInit, pointYForInit + sizeHeight * 3}, BlockType::OneLife},
                       {Vector2D{pointXForInit + sizeWidth , pointYForInit + sizeHeight * 3}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 3}, BlockType::OneLife},

                       {Vector2D{pointXForInit - sizeWidth * 2, pointYForInit + sizeHeight * 4}, BlockType::OneLife},{Vector2D{pointXForInit - sizeWidth, pointYForInit + sizeHeight * 4}, BlockType::OneLife},
                       {Vector2D{pointXForInit, pointYForInit + sizeHeight * 4}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight * 4}, BlockType::OneLife},
                       {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 4}, BlockType::TwoLife}, {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 4}, BlockType::OneLife},

                       {Vector2D{pointXForInit - sizeWidth * 2, pointYForInit + sizeHeight * 5}, BlockType::OneLife},{Vector2D{pointXForInit - sizeWidth, pointYForInit + sizeHeight * 5}, BlockType::OneLife},
                       {Vector2D{pointXForInit, pointYForInit + sizeHeight * 5}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight * 5}, BlockType::TwoLife},
                       {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 5}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 5}, BlockType::OneLife},

                       {Vector2D{pointXForInit - sizeWidth * 2, pointYForInit + sizeHeight * 6}, BlockType::OneLife},{Vector2D{pointXForInit - sizeWidth, pointYForInit + sizeHeight * 6}, BlockType::OneLife},
                       {Vector2D{pointXForInit, pointYForInit + sizeHeight * 6}, BlockType::TwoLife}, {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight * 6}, BlockType::OneLife},
                       {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 6}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 6}, BlockType::Indestructible},

                       {Vector2D{pointXForInit - sizeWidth * 2, pointYForInit + sizeHeight * 7}, BlockType::OneLife},{Vector2D{pointXForInit - sizeWidth, pointYForInit + sizeHeight * 7}, BlockType::TwoLife},
                       {Vector2D{pointXForInit, pointYForInit + sizeHeight * 7}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight * 7}, BlockType::OneLife},
                       {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 7}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 3, pointYForInit + sizeHeight * 7}, BlockType::OneLife},

                       {Vector2D{pointXForInit - sizeWidth , pointYForInit + sizeHeight * 8}, BlockType::OneLife},{Vector2D{pointXForInit, pointYForInit + sizeHeight * 8}, BlockType::OneLife},
                       {Vector2D{pointXForInit + sizeWidth , pointYForInit + sizeHeight * 8}, BlockType::Indestructible}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 8}, BlockType::OneLife},

                       {Vector2D{pointXForInit - sizeWidth , pointYForInit + sizeHeight * 9}, BlockType::OneLife},{Vector2D{pointXForInit, pointYForInit + sizeHeight * 9}, BlockType::OneLife},
                       {Vector2D{pointXForInit + sizeWidth , pointYForInit + sizeHeight * 9}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 9}, BlockType::OneLife},

                       {Vector2D{pointXForInit - sizeWidth , pointYForInit + sizeHeight * 10}, BlockType::Indestructible},{Vector2D{pointXForInit, pointYForInit + sizeHeight * 10}, BlockType::OneLife},
                       {Vector2D{pointXForInit + sizeWidth , pointYForInit + sizeHeight * 10}, BlockType::OneLife}, {Vector2D{pointXForInit + sizeWidth * 2, pointYForInit + sizeHeight * 10}, BlockType::OneLife},

                       {Vector2D{pointXForInit, pointYForInit + sizeHeight * 11}, BlockType::OneLife},{Vector2D{pointXForInit + sizeWidth, pointYForInit + sizeHeight * 11}, BlockType::OneLife} };
}