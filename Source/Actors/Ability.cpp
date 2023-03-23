#include "../Actors/Ability.h"
#include "../GameMode/Game.h"
#include "../Renderer/Renderer.h"
#include "../Window/Window.h"
#include "../Components/SpriteComponent.h"
#include "../Texture/Texture.h"
#include "../Texture/TextureManager.h"

const float Ability::cVelocityIncreased = 1.40f;
const float Ability::cVelocityDecreased = 0.6f;

Ability::Ability(Game* game)
    : Actor(game)
{
    SpriteComponent* sprite = new SpriteComponent(this, 100);

    float screenWidth = game->GetWindow()->GetScreenWidth();
    float screenHeight = game->GetWindow()->GetScreenHeight();

    SetScale(0.15f);
    Texture* texture = nullptr;
    int randomAbility = rand() % 5;
    if (randomAbility == (int)AbilityType::IncreaseSpeed)
    {
        texture = game->GetTextureManager()->GetTexture("Data/42-Breakout-Tiles.png");
        sprite->SetTexture(texture);
        mAbilityType = AbilityType::IncreaseSpeed;
    }
    else if (randomAbility == (int)AbilityType::DecreaseSpeed)
    {
        texture = game->GetTextureManager()->GetTexture("Data/41-Breakout-Tiles.png");
        sprite->SetTexture(texture);
        mAbilityType = AbilityType::DecreaseSpeed;
    }
    else if (randomAbility == (int)AbilityType::ExtensionPlatform)
    {
        texture = game->GetTextureManager()->GetTexture("Data/47-Breakout-Tiles.png");
        sprite->SetTexture(texture);
        mAbilityType = AbilityType::ExtensionPlatform;

    }
    else if (randomAbility == (int)AbilityType::ConstrictionPlatform)
    {
        texture = game->GetTextureManager()->GetTexture("Data/46-Breakout-Tiles.png");
        sprite->SetTexture(texture);
        mAbilityType = AbilityType::ConstrictionPlatform;
    }
    else
    {
        texture = game->GetTextureManager()->GetTexture("Data/48-Breakout-Tiles.png");
        sprite->SetTexture(texture);
        mAbilityType = AbilityType::Shooting;

    }
    SetHeight(static_cast<float>(texture->GetTextureHeight()));
    SetWidth(static_cast<float>(texture->GetTextureWidth()));
    Vector2D position;
    position.mY = 40.0f;
    int randomX = rand() % ((int)screenWidth - (2 * (int)GetWidth())) + (int)GetWidth();
    position.mX = (float)randomX;

    SetPosition(position);

    game->AddAbility(this);
}

Ability::~Ability()
{
    GetGame()->RemoveAbility(this);
}

void Ability::UpdateActor(float deltaTime)
{
    Vector2D position = GetPosition();

    position.mY += cDefaultVelocity * deltaTime;

    SetPosition(position);
}
