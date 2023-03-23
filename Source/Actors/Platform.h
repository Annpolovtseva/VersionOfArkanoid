#pragma once

#include "../Actors/Actor.h"
#include "../Actors/Ability.h"

class Texture;

struct GainedAbility
{
    AbilityType mAbilityType = AbilityType::IncreaseSpeed;
    float mLifeSpan = 0.0f;
    float mSpeedChange = 0.0f;
};

class Platform : public Actor
{
public:
    Platform(Game* game);
    ~Platform();

    void UpdateActor(float deltaTime) override;

    void ProcessKeyboard(const uint8_t* state);

    void GainAbility(AbilityType mAbilityType);

    bool ShootingAbility();

private:
    void UpdateGainedAbilities(float deltaTime);
    void ReturnDefaultAnimsprites();

    std::vector<GainedAbility> mGainedAbility;
    std::vector<Texture*> mDefaultAnimsprites;

    float mSpeed = 0.0f;
    int mDirection = 0;
    float mLaserCooldown = 0.0f;
    const float cDefaultSpeed = 400.0f;
};
