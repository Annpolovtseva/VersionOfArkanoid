#pragma once
#include "../Actors/Block.h"
#include <vector>

class Game;

class LevelLoader
{
public:
    LevelLoader();

    static void Load(Game* game, int levelIndex);
    ~LevelLoader();

private:
    void AddLevelBlocks();
    void LoadBGSprite(Game* game);
    void LoadMainActors(Game* game);
    void LoadBlocks(Game* game, const std::vector<InitBlockData>& initLevelBlockData);
    void LoadTextures(Game* game);

    std::vector<InitBlockData> mBlockLevelData[cLevelsNumber];
    int mLevelIndex = 0;
};