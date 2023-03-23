#pragma once
#include "../Actors/Actor.h"

enum class AbilityType
{
    IncreaseSpeed = 1,
    DecreaseSpeed,
    ExtensionPlatform,
    ConstrictionPlatform,
    Shooting
};

class Ability : public Actor
{
public:
    Ability(Game* game);
    ~Ability();

    void UpdateActor(float deltaTime);

    AbilityType GetAbilityType() { return mAbilityType; }
    static float GetVelocityIncreased() { return cVelocityIncreased; }
    static float GetVelocityDecreased() { return cVelocityDecreased; }

private:
    AbilityType mAbilityType = AbilityType::IncreaseSpeed;

    const float cDefaultVelocity = 150.0f;

    static const float cVelocityIncreased;
    static const float cVelocityDecreased;
};
