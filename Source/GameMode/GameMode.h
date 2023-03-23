#pragma once

class Game;

class GameMode
{
public:
	GameMode(Game* game);
	~GameMode();

	void Initialize();

	void Update(float deltaTime);
	void UpdateAbilities(float deltaTime);
	void UpdateBloks();

	void CheckWinLoseConditions();

	bool IsAllBlocksDestroyed() { return mAllBlocksDestroyed; }

private:
	void LoadLifes();

	int mLevelIndex = 0;
	int mNumberOfLifes = 0;
	bool mAllBlocksDestroyed;
	float mTimeToAppearanceAbility = 0.0f;

	Game* mGame = nullptr;
};
